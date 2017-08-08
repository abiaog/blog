---
layout: post
title:  "Linux Device Driver --- Hello World"
date:   2016-08-26 
categories: jekyll update
---

# Hello World 

Implement hello world driver based on Linux Device Driver Chapter2.

[hello.c](/code_for_post/ldd/hello/hello.c)

[Makefile](/code_for_post/ldd/hello/Makefile)

[Makefile_1](/code_for_post/ldd/hello/Makefile_1)

Make as below,

	  root@peter-VirtualBox:/home/peter/develop/linux/drivers/char/hello# ll
	  total 16
	  drwxr-xr-x  2 root   root   4096  8月 26 15:58 ./
	  drwxrwxr-x 13 peter peter 4096  8月 26 15:26 ../
	  -rw-r--r--  1 root   root    292  8月 26 15:27 hello.c
	  -rw-r--r--  1 root   root    194  8月 26 15:55 Makefile
	  root@peter-VirtualBox:/home/peter/develop/linux/drivers/char/hello# make
	  make -C /lib/modules/4.0.0-rc1+/build M=/home/peter/develop/linux/drivers/char/hello modules
	  make[1]: Entering directory `/home/peter/develop/linux'
	    CC [M]  /home/peter/develop/linux/drivers/char/hello/hello.o
	    Building modules, stage 2.
	    MODPOST 1 modules
	    CC      /home/peter/develop/linux/drivers/char/hello/hello.mod.o
	    LD [M]  /home/peter/develop/linux/drivers/char/hello/hello.ko
	  make[1]: Leaving directory `/home/peter/develop/linux'
	  root@peter-VirtualBox:/home/peter/develop/linux/drivers/char/hello# ll
	  total 100
	  drwxr-xr-x  3 root   root    4096  8月 26 15:58 ./
	  drwxrwxr-x 13 peter peter  4096  8月 26 15:26 ../
	  -rw-r--r--  1 root   root     292  8月 26 15:27 hello.c
	  -rw-r--r--  1 root   root    1999  8月 26 15:58 hello.ko
	  -rw-r--r--  1 root   root     293  8月 26 15:58 .hello.ko.cmd
	  -rw-r--r--  1 root   root     454  8月 26 15:58 hello.mod.c
	  -rw-r--r--  1 root   root    1432  8月 26 15:58 hello.mod.o
	  -rw-r--r--  1 root   root   25872  8月 26 15:58 .hello.mod.o.cmd
	  -rw-r--r--  1 root   root    1152  8月 26 15:58 hello.o
	  -rw-r--r--  1 root   root   25764  8月 26 15:58 .hello.o.cmd
	  -rw-r--r--  1 root   root     194  8月 26 15:55 Makefile
	  -rw-r--r--  1 root   root      62  8月 26 15:58 modules.order
	  -rw-r--r--  1 root   root       0  8月 26 15:58 Module.symvers
	  drwxr-xr-x  2 root   root    4096  8月 26 15:58 .tmp_versions/
	  root@peter-VirtualBox:/home/peter/develop/linux/drivers/char/hello# insmod ./hello.ko 
	  insmod: ERROR: could not insert module ./hello.ko: File exists
	  root@peter-VirtualBox:/home/peter/develop/linux/drivers/char/hello# rmmod hello.ko
	  root@peter-VirtualBox:/home/peter/develop/linux/drivers/char/hello# insmod ./hello.ko 
	  root@peter-VirtualBox:/home/peter/develop/linux/drivers/char/hello# 

view the log from /var/log/syslog,

	  Aug 26 15:50:05 peter-VirtualBox kernel: [ 6641.824580] Hello, world
	  Aug 26 15:55:01 peter-VirtualBox CRON[16299]: (root) CMD (command -v debian-sa1 > /dev/null && debian-sa1 1 1)
	  Aug 26 16:00:06 peter-VirtualBox kernel: [ 7242.631977] Goodbye, cruel world
	  Aug 26 16:00:09 peter-VirtualBox kernel: [ 7245.632334] Hello, world
     
# ioctl

ioctl() is one of the remaining parts of the kernel which runs under the Big Kernel Lock (BKL). In the past, the usage of the BKL has made it possible for long-running ioctl() methods to create long latencies for unrelated processes.

## What is the difference between ioctl(), unlocked_ioctl() and compat_ioctl()?

http://unix.stackexchange.com/questions/4711/what-is-the-difference-between-ioctl-unlocked-ioctl-and-compat-ioctl

# Kconfig

# FAQ

## How to deal with driver build failed?

Double check .config to make sure that the .config is compatible with current platform and kernel version.

# Reference

[Hello World](http://blog.chinaunix.net/uid-27012654-id-3862516.html)

