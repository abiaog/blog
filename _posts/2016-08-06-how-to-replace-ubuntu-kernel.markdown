---
layout: post
title:  "How to Replace Ubuntu Kernel"
date:   2016-08-06 
categories: jekyll update
---


# Replace Ubuntu Kernel

On Ubuntu, you can get these tools by running:

	sudo apt-get install libncurses5-dev gcc make git exuberant-ctags bc libssl-dev

Downloading the latest stable tree

First, checkout the stable kernel git repository:

	git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
	cd linux-stable

Next, find the latest stable kernel tag by running

	git tag -l | less
	git checkout -b 3.16 v3.16
	cp /boot/config-3.16.0-50-generic .config
	make -j4
	sudo make modules_install install

Update grub

	sudo grub-mkconfig -o /boot/grub/grub.cfg  

	reboot

Use below command to check the version

	dmesg | less

	uname -a

# kernel newbies


# kdump

[kdump](http://www.ibm.com/developerworks/cn/linux/l-cn-kdump1/)

# kexec

# Reference

[KernelBuild](https://kernelnewbies.org/KernelBuild)

[FirstKernelPatch](https://kernelnewbies.org/FirstKernelPatch)

