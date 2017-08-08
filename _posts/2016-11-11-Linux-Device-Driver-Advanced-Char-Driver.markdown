---
layout: post
title:  "Linux Device Driver --- Advanced Char Driver"
date:   2016-11-11
categories: jekyll update
---

# ioctl

ioctl() is one of the remaining parts of the kernel which runs under the Big Kernel Lock (BKL). In the past, the usage of the BKL has made it possible for long-running ioctl() methods to create long latencies for unrelated processes.

Follows an explanation of the patch that introduced `unlocked_ioctl` and `compat_ioctl` into 2.6.11. The removal of the ioctl field happened a lot later, in 2.6.36.

Explanation: When ioctl was executed, it took the Big Kernel Lock (BKL), so nothing else could execute at the same time. This is very bad on a multiprocessor machine, so there was a big effort to get rid of the BKL. First, unlocked_ioctl was introduced. It lets each driver writer choose what lock to use instead. This can be difficult, so there was a period of transition during which old drivers still worked (using ioctl) but new drivers could use the improved interface (unlocked_ioctl). Eventually all drivers were converted and ioctl could be removed.

compat_ioctl is actually unrelated, even though it was added at the same time. Its purpose is to allow 32-bit userland programs to make ioctl calls on a 64-bit kernel. The meaning of the last argument to ioctl depends on the driver, so there is no way to do a driver-independent conversion.

include/linux/fs.h

	struct file_operations {
		long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
		long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	};



## Choosing the ioctl Commands


### include/uapi/asm-generic/ioctl.h

	/* used to create numbers */
	#define _IO(type,nr)		_IOC(_IOC_NONE,(type),(nr),0)
	#define _IOR(type,nr,size)	_IOC(_IOC_READ,(type),(nr),(_IOC_TYPECHECK(size)))
	#define _IOW(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))
	#define _IOWR(type,nr,size)	_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))
	#define _IOR_BAD(type,nr,size)	_IOC(_IOC_READ,(type),(nr),sizeof(size))
	#define _IOW_BAD(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),sizeof(size))
	#define _IOWR_BAD(type,nr,size)	_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),sizeof(size))

	/* used to decode ioctl numbers.. */
	#define _IOC_DIR(nr)		(((nr) >> _IOC_DIRSHIFT) & _IOC_DIRMASK)
	#define _IOC_TYPE(nr)		(((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
	#define _IOC_NR(nr)		(((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
	#define _IOC_SIZE(nr)		(((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)


### Documentation/ioctl/ioctl-number.txt

If you are adding new ioctl's to the kernel, you should use the _IO
macros defined in <linux/ioctl.h>:

    _IO    an ioctl with no parameters
    _IOW   an ioctl with write parameters (copy_from_user)
    _IOR   an ioctl with read parameters  (copy_to_user)
    _IOWR  an ioctl with both write and read parameters.

'Write' and 'read' are from the user's point of view, just like the
system calls 'write' and 'read'.  For example, a SET_FOO ioctl would
be _IOW, although the kernel would actually read data from user space;
a GET_FOO ioctl would be _IOR, although the kernel would actually write
data to user space.

The first argument to _IO, _IOW, _IOR, or _IOWR is an identifying letter
or number from the table below.  Because of the large number of drivers,
many drivers share a partial letter with other drivers.

If you are writing a driver for a new device and need a letter, pick an
unused block with enough room for expansion: 32 to 256 ioctl commands.
You can register the block by patching this file and submitting the
patch to Linus Torvalds.  Or you can e-mail me at <mec@shout.net> and
I'll register one for you.

The second argument to _IO, _IOW, _IOR, or _IOWR is a sequence number
to distinguish ioctls from each other.  The third argument to _IOW,
_IOR, or _IOWR is the type of the data going into the kernel or coming
out of the kernel (e.g.  'int' or 'struct foo').  NOTE!  Do NOT use
sizeof(arg) as the third argument as this results in your ioctl thinking
it passes an argument of type size_t.

Some devices use their major number as the identifier; this is OK, as
long as it is unique.  Some devices are irregular and don't follow any
convention at all.



### The Return Value

-ENOTTY: "inappropriate ioctl for device"

-EINVAL: "Invalid argument"


### The Predefined Commands


### Using the ioctl Argument

	/**
	 * access_ok: - Checks if a user space pointer is valid
	 * @type: Type of access: %VERIFY_READ or %VERIFY_WRITE.  Note that
	 *        %VERIFY_WRITE is a superset of %VERIFY_READ - if it is safe
	 *        to write to a block, it is always safe to read from it.
	 * @addr: User space pointer to start of block to check
	 * @size: Size of block to check
	 *
	 * Context: User context only.  This function may sleep.
	 *
	 * Checks if a pointer to a block of memory in user space is valid.
	 *
	 * Returns true (nonzero) if the memory block may be valid, false (zero)
	 * if it is definitely invalid.
	 *
	 * Note that, depending on architecture, this function probably just
	 * checks that the pointer is in the user space range - after calling
	 * this function, memory access functions may still return -EFAULT.
	 */
	#define access_ok(type, addr, size) \
		likely(!__range_not_ok(addr, size, user_addr_max()))

# Simple Sleeping

[sleepy.c](/code_for_post/ldd/examples/misc-modules/sleepy.c)


# Blocking and Nonblocking Operations

O_NONBLOCK

Only the read, write, and open file operation are affected by the nonblocking flag.

# How to enable dynamic debug?

Refer to  `Documentation/dynamic-debug-howto.txt` under source tree.

[如何输出dev_dbg log](http://blog.csdn.net/armlinuxtech/article/details/50729070)

[Linux内核里的DebugFS](http://www.cnblogs.com/wwang/archive/2011/01/17/1937609.html)






# How to test driver?

[Linux device driver functional testing](http://stackoverflow.com/questions/11347027/linux-device-driver-functional-testing)

[Avocado - Automated Testing Framework](http://avocado-framework.github.io/)

[Unit testing device drivers](http://stackoverflow.com/questions/1957212/unit-testing-device-drivers0)





# How to find the major/minor numbers for your device

cat /proc/devices




# proc_create

[proc_create的使用方法](http://blog.csdn.net/njuitjf/article/details/16940865)

# strace






# Kernel version

`uname -a`

	peter@peter-ThinkPad-T430:~/work/src/linux/linux/drivers/char/scull$ uname -a
	Linux peter-ThinkPad-T430 3.16.0 #2 SMP Sun Aug 7 18:04:04 CST 2016 x86_64 x86_64 x86_64 GNU/Linux


# Error

	peter@peter-ThinkPad-T430:~/work/src/linux/linux/drivers/char/scull$ make
	make -C /lib/modules/3.16.0/build M=/home/peter/work/src/linux/linux/drivers/char/scull LDDINC=/home/peter/work/src/linux/linux/drivers/char/scull/../include modules
	make[1]: Entering directory `/home/peter/work/src/linux/linux'
	  CC [M]  /home/peter/work/src/linux/linux/drivers/char/scull/main.o
	/home/peter/work/src/linux/linux/drivers/char/scull/main.c:17:26: fatal error: linux/config.h: No such file or directory
	 #include <linux/config.h>
				  ^
	compilation terminated.
	make[2]: *** [/home/peter/work/src/linux/linux/drivers/char/scull/main.o] Error 1
	make[1]: *** [_module_/home/peter/work/src/linux/linux/drivers/char/scull] Error 2
	make[1]: Leaving directory `/home/peter/work/src/linux/linux'
	make: *** [modules] Error 2




# Reference

[What is the difference between ioctl(), unlocked_ioctl() and compat_ioctl()?](http://unix.stackexchange.com/questions/4711/what-is-the-difference-between-ioctl-unlocked-ioctl-and-compat-ioctl)

[ldd3-examples-3.x](https://github.com/duxing2007/ldd3-examples-3.x)

[CFLAGS was changed](http://blog.chinaunix.net/uid-24467128-id-3125691.html)

[scull在Ubuntu11.10上的编译](http://www.cnblogs.com/xiaoya901109/archive/2012/11/21/2780789.html)


