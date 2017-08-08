/*
 * Resizable simple ram filesystem for Linux.
 *
 * Copyright (C) 2000 Linus Torvalds.
 *               2000 Transmeta Corp.
 *
 * Usage limits added by David Gibson, Linuxcare Australia.
 * This file is released under the GPL.
 */

/*
 * NOTE! This filesystem is probably most useful
 * not as a real filesystem, but as an example of
 * how virtual filesystems can be written.
 *
 * It doesn't get much simpler than this. Consider
 * that this file implements the full semantics of
 * a POSIX-compliant read-write filesystem.
 *
 * Note in particular how the filesystem does not
 * need to implement any data structures of its own
 * to keep track of the virtual data: using the VFS
 * caches is sufficient.
 */

#include <linux/fs.h>
#include <linux/pagemap.h>
#include <linux/highmem.h>
#include <linux/time.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/backing-dev.h>
#include <linux/ramfs.h>
#include <linux/sched.h>
#include <linux/parser.h>
#include <linux/magic.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "internal.h"

#define RAMFS_DEFAULT_MODE	0755

static const struct super_operations ramfs_ops;
static const struct inode_operations ramfs_dir_inode_operations;

static const struct address_space_operations ramfs_aops = {
	.readpage	= simple_readpage,
	.write_begin	= simple_write_begin,
	.write_end	= simple_write_end,
	.set_page_dirty	= __set_page_dirty_no_writeback,
};

static struct backing_dev_info ramfs_backing_dev_info = {
	.name		= "ramfs",
	.ra_pages	= 0,	/* No readahead */
	.capabilities	= BDI_CAP_NO_ACCT_AND_WRITEBACK |
			  BDI_CAP_MAP_DIRECT | BDI_CAP_MAP_COPY |
			  BDI_CAP_READ_MAP | BDI_CAP_WRITE_MAP | BDI_CAP_EXEC_MAP,
};

struct inode *ramfs_get_inode(struct super_block *sb,
				const struct inode *dir, umode_t mode, dev_t dev)
{
	struct inode * inode = new_inode(sb);

	if (inode) {
		inode->i_ino = get_next_ino();
		inode_init_owner(inode, dir, mode);
		inode->i_mapping->a_ops = &ramfs_aops;
		inode->i_mapping->backing_dev_info = &ramfs_backing_dev_info;
		mapping_set_gfp_mask(inode->i_mapping, GFP_HIGHUSER);
		mapping_set_unevictable(inode->i_mapping);
		inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
		switch (mode & S_IFMT) {
		default:
			init_special_inode(inode, mode, dev);
			break;
		case S_IFREG:
			inode->i_op = &ramfs_file_inode_operations;
			inode->i_fop = &ramfs_file_operations;
			break;
		case S_IFDIR:
			inode->i_op = &ramfs_dir_inode_operations;
			inode->i_fop = &simple_dir_operations;

			/* directory inodes start off with i_nlink == 2 (for "." entry) */
			inc_nlink(inode);
			break;
		case S_IFLNK:
			inode->i_op = &page_symlink_inode_operations;
			break;
		}
	}
	return inode;
}

/*
 * File creation. Allocate an inode, and we're done..
 */
/* SMP-safe */
static int
ramfs_mknod(struct inode *dir, struct dentry *dentry, umode_t mode, dev_t dev)
{
	struct inode * inode = ramfs_get_inode(dir->i_sb, dir, mode, dev);
	int error = -ENOSPC;

	if (inode) {
		d_instantiate(dentry, inode);
		dget(dentry);	/* Extra count - pin the dentry in core */
		error = 0;
		dir->i_mtime = dir->i_ctime = CURRENT_TIME;
	}
	return error;
}

static int ramfs_mkdir(struct inode * dir, struct dentry * dentry, umode_t mode)
{
	int retval = ramfs_mknod(dir, dentry, mode | S_IFDIR, 0);
	if (!retval)
		inc_nlink(dir);
	return retval;
}

static int ramfs_create(struct inode *dir, struct dentry *dentry, umode_t mode, bool excl)
{
	return ramfs_mknod(dir, dentry, mode | S_IFREG, 0);
}

static int ramfs_symlink(struct inode * dir, struct dentry *dentry, const char * symname)
{
	struct inode *inode;
	int error = -ENOSPC;

	inode = ramfs_get_inode(dir->i_sb, dir, S_IFLNK|S_IRWXUGO, 0);
	if (inode) {
		int l = strlen(symname)+1;
		error = page_symlink(inode, symname, l);
		if (!error) {
			d_instantiate(dentry, inode);
			dget(dentry);
			dir->i_mtime = dir->i_ctime = CURRENT_TIME;
		} else
			iput(inode);
	}
	return error;
}

static const struct inode_operations ramfs_dir_inode_operations = {
	.create		= ramfs_create,
	.lookup		= simple_lookup,
	.link		= simple_link,
	.unlink		= simple_unlink,
	.symlink	= ramfs_symlink,
	.mkdir		= ramfs_mkdir,
	.rmdir		= simple_rmdir,
	.mknod		= ramfs_mknod,
	.rename		= simple_rename,
};

static const struct super_operations ramfs_ops = {
	.statfs		= simple_statfs,
	.drop_inode	= generic_delete_inode,
	.show_options	= generic_show_options,
};

struct ramfs_mount_opts {
	umode_t mode;
};

enum {
	Opt_mode,
	Opt_err
};

static const match_table_t tokens = {
	{Opt_mode, "mode=%o"},
	{Opt_err, NULL}
};

struct ramfs_fs_info {
	struct ramfs_mount_opts mount_opts;
};

static int ramfs_parse_options(char *data, struct ramfs_mount_opts *opts)
{
	substring_t args[MAX_OPT_ARGS];
	int option;
	int token;
	char *p;

	opts->mode = RAMFS_DEFAULT_MODE;

	while ((p = strsep(&data, ",")) != NULL) {
		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_mode:
			if (match_octal(&args[0], &option))
				return -EINVAL;
			opts->mode = option & S_IALLUGO;
			break;
		/*
		 * We might like to report bad mount options here;
		 * but traditionally ramfs has ignored all mount options,
		 * and as it is used as a !CONFIG_SHMEM simple substitute
		 * for tmpfs, better continue to ignore other mount options.
		 */
		}
	}

	return 0;
}

// 作用：初始化ramfs的超级块。
// 注释：包括挂载参数，根inode和根目录项等的初始化。
int ramfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct ramfs_fs_info *fsi;
	struct inode *inode;
	int err;

	save_mount_options(sb, data); // 将文件系统的挂载参数保存到sb.s_options字段。该值用于generic_show_options() 函数对文件系统挂载参数的显示操作。

	fsi = kzalloc(sizeof(struct ramfs_fs_info), GFP_KERNEL); // 分配ramfs特有的ramfs_fs_info结构。
								// struct ramfs_fs_info {
								// 	struct ramfs_mount_opts mount_opts;
								// };
								// 
								// struct ramfs_mount_opts {
								// 	umode_t mode;
								// };


	sb->s_fs_info = fsi; //  指向ramfs_fs_info结构的指针存放在ramfs的超级块的私有字段s_fs_info中。
	if (!fsi)
		return -ENOMEM;

	err = ramfs_parse_options(data, &fsi->mount_opts); // 调用ramfs_parse_options()对挂载参数进行解析。将挂载参数“mode=XX”中的XX保存在ramfs_mount_opts的mode字段。默认值为0755。其他挂载参数都被忽略。

	if (err)
		return err;

	
	
	
	
	
	sb->s_maxbytes		= MAX_LFS_FILESIZE;   // 初始化超级块的s_maxbytes为MAX_LFS_FILESIZE。该字段表示最大的文件长度。
	sb->s_blocksize		= PAGE_CACHE_SIZE;    // 初始化超级块的s_blocksize字段为PAGE_CACHE_SIZE。该字段表示文件系统块的长度，单位为字节。
	sb->s_blocksize_bits	= PAGE_CACHE_SHIFT;   // 另一个字段为s_blocksize_bits字段，该字段也表示文件系统块的长度， 只是它为s_blocksize取以2为底的对数。
	sb->s_magic		= RAMFS_MAGIC;        // 初始化超级块的s_magic字段，该字段为超级块的魔数，用于检查超级块的损坏。
	sb->s_op		= &ramfs_ops;         // 初始化超级块的s_op字段为ramfs_ops。该结构包含了用于处理超级块的相关操作。
	                                              /* 
							static const struct super_operations ramfs_ops = { 
								    .statfs     = simple_statfs, //给出文件系统的统计信息，例如使用和未使用的数据块的数目，或者文件件名的最大长度。  
								        .drop_inode = generic_delete_inode, //当inode的引用计数降为0时，将inode删除。
									    .show_options   = generic_show_options, //用以显示文件系统装载的选项。
							};
						      */

	sb->s_time_gran		= 1;                  // 初始化超级块的s_time_gran字段。它表示文件系统支持的各种时间戳的最大可能的粒度。单位为ns。

	inode = ramfs_get_inode(sb, NULL, S_IFDIR | fsi->mount_opts.mode, 0); // 调用ramfs_get_inode()为ramfs超级块在生成一个代表根节点inode。并将inode各个字段进行初始化。最后，返回指向该根inode的指针。(具体操作详见下文分析。)
	sb->s_root = d_make_root(inode); // 调用d_make_root()为根inode创建并初始化一个目录项。
	if (!sb->s_root)
		return -ENOMEM;

	return 0;
}

// 作用：查找或者创建一个VFS超级块super_block结构。执行ramfs_fill_super()对ramfs的超级块进行初始化。然后，对根目录的目录项引用计数增一。
struct dentry *ramfs_mount(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data)
{
	return mount_nodev(fs_type, flags, data, ramfs_fill_super);
}

static void ramfs_kill_sb(struct super_block *sb)
{
	kfree(sb->s_fs_info);
	kill_litter_super(sb);
}

static struct file_system_type ramfs_fs_type = {
	.name		= "ramfs",
	.mount		= ramfs_mount,
	.kill_sb	= ramfs_kill_sb,
	.fs_flags	= FS_USERNS_MOUNT,
};

int __init init_ramfs_fs(void)
{
	static unsigned long once;
	int err;

	if (test_and_set_bit(0, &once))
		return 0;

	err = bdi_init(&ramfs_backing_dev_info);
	if (err)
		return err;

	err = register_filesystem(&ramfs_fs_type);
	if (err)
		bdi_destroy(&ramfs_backing_dev_info);

	return err;
}
fs_initcall(init_ramfs_fs);
