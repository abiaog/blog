---
layout: post
title:  "Understanding the Linux Virtual Memory Manager"
date:   2017-08-04 
categories: jekyll update
---


# Describing Physical Memory


[![relationship-between-nodes-zones-and-pages.png](https://s19.postimg.org/ud1eskh1v/relationship-between-nodes-zones-and-pages.png)](https://postimg.org/image/luryo8aj3/)

	/*
	 * On NUMA machines, each NUMA node would have a pg_data_t to describe
	 * it's memory layout. On UMA machines there is a single pglist_data which
	 * describes the whole memory.
	 *
	 * Memory statistics and page replacement data structures are maintained on a
	 * per-zone basis.
	 */

	typedef struct pglist_data {
		struct zone node_zones[MAX_NR_ZONES];
	#ifdef CONFIG_FLAT_NODE_MEM_MAP	/* means !SPARSEMEM */
		struct page *node_mem_map;
	#endif
	#ifndef CONFIG_NO_BOOTMEM
		struct bootmem_data *bdata;
	#endif
	} pg_data_t;












- 4.3  Process Address Space Descriptor

The process address space is described by the mm_struct struct meaning that only one exists for each process and is shared between userspace threads. In fact, threads are identified in the task list by finding all task_structs which have pointers to the same mm_struct.

- 4.4 Memory Regions

Each region is represented by a `vm_area_struct` which never overlap and represent a set of addresses with the same protection and purpose. Examples of a region include a read-only shared library loaded into the address space or the process heap. A full list of mapped regions a process has may be viewed via the proc interface at /proc/PID/maps where PID is the process ID of the process that is to be examined

e.g /proc/3981/maps

      b7520000-b7523000 r-xp 00000000 08:01 527837     /lib/i386-linux-gnu/libdl-2.19.so
      b7523000-b7524000 r--p 00002000 08:01 527837     /lib/i386-linux-gnu/libdl-2.19.so
      b7524000-b7525000 rw-p 00003000 08:01 527837     /lib/i386-linux-gnu/libdl-2.19.so


If the region is backed by a file, the struct file is available through the vm_file field which has a pointer to the struct inode. The inode is used to get the struct address_space which has all the private information about the file including a set of pointers to filesystem functions which perform the filesystem specific operations such as reading and writing pages to disk.

	./include/linux/mm_types.h

	struct vm_area_struct {
		struct mm_struct *vm_mm;	/* The address space we belong to. */
		struct file * vm_file;		/* File we map to (can be NULL). */
	};


	./include/linux/fs.h

	struct file {
		struct inode		*f_inode;	/* cached value */
	};

	struct inode {
		struct address_space	*i_mapping;
	};

[![process_address_space_structures.png](https://s19.postimg.org/r1h5v64r7/process_address_space_structures.png)](https://postimg.org/image/greqvxevj/)





# Reference

[Understanding the Linux Virtual Memory Manager](https://www.kernel.org/doc/gorman/html/understand/)





