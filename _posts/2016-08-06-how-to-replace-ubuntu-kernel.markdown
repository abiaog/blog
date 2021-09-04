

# Replace Ubuntu Kernel


## Alternative 1


According to [BuildYourOwnKernel](https://wiki.ubuntu.com/Kernel/BuildYourOwnKernel)

	sudo apt-get build-dep linux linux-image-$(uname -r)
	sudo apt-get install libncurses-dev gawk flex bison openssl libssl-dev dkms libelf-dev libudev-dev libpci-dev libiberty-dev autoconf
	apt-get source linux-image-unsigned-$(uname -r)

	LANG=C fakeroot debian/rules clean
	# quicker build:
	LANG=C fakeroot debian/rules binary-headers binary-generic binary-perarch


### For solving dependencies errors while executing "sudo apt-get build-dep linux linux-image-$(uname -r)"
Edit source.list
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
	deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
	deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
	deb http://archive.ubuntu.com/ubuntu/ trusty main universe restricted multiverse

## Alternative 2
On Ubuntu, you can get these tools by running:

	sudo apt-get install libncurses5-dev gcc make git exuberant-ctags bc libssl-dev
	sudo apt-get install libelf-dev # for fixing a warning

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

