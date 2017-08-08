



# How to download an entire website as plain text documents?

In some cases, I would like to read html documents with VIM if all of the contents are plain text.

First, wget the whole site do local machine. And then, filter all the html files into correct order. Finally,using some plain text browser, for example, elinks to dump the contents into plain text.


## wget the entire web site

	#/bin/bash
	wget \
		--recursive \
		--no-clobber \
		--page-requisites \
		--html-extension \
		--convert-links \
		--restrict-file-names=windows \
		--domains kernel.org \
		--no-parent \
		https://www.kernel.org/doc/gorman/html/understand/


## dump html contents into plain text (or dump html one by one)

elinks -dump https://www.kernel.org/doc/gorman/html/understand/understand008.html > BootMemoryAllocator.txt

elinks -dump https://www.kernel.org/doc/gorman/html/understand/understand008.html >> <more contents>


[Downloading an Entire Web Site with wget](http://www.linuxjournal.com/content/downloading-entire-web-site-wget)


#  How to extract tar.bz2?

	tar -jxvf qemu-2.0.2.tar.bz2



# How does ubuntu access iPhone?  Unhandled Lockdown error (-20)


https://bugs.launchpad.net/ubuntu/+source/libimobiledevice/+bug/1623666


----------------------------------------------------------------------------
checking if g++ supports -c -o file.o... yes
checking if g++ supports -c -o file.o... (cached) yes
checking whether the g++ linker (/usr/bin/ld -m elf_x86_64) supports shared libraries... yes
checking dynamic linker characteristics... (cached) GNU/Linux ld.so
checking how to hardcode library paths into programs... immediate
checking for pkg-config... /usr/bin/pkg-config
checking pkg-config is at least version 0.9.0... yes
checking for libusbmuxd... no
configure: error: Package requirements (libusbmuxd >= 1.0.9) were not met:

No package 'libusbmuxd' found

Consider adjusting the PKG_CONFIG_PATH environment variable if you
installed software in a non-standard prefix.

Alternatively, you may set the environment variables libusbmuxd_CFLAGS
and libusbmuxd_LIBS to avoid the need to call pkg-config.
See the pkg-config man page for more details.
peter@peter-ThinkPad-T430:~/work/src/libimobiledevice$ make
make: *** No targets specified and no makefile found.  Stop.
peter@peter-ThinkPad-T430:~/work/src/libimobiledevice$ 


----------------------------------------------------------------------------




#28 & #29 did the trick for me as well after a small hiccup.

To get the ./autogen.sh script working for libimobiledevice, I first needed to install libusbmuxd.

  $ cd ~/path/to/my/build/dir
  $ https://github.com/libimobiledevice/libusbmuxd.git
  $ cd libusbmuxd
  $ ./autogen.sh
  $ make
  $ sudo make install

Then proceeded successfully with #28 and #29.

Linux Mint 18.1 Cinnamon 64-bit
iPhone SE iOS 10.3.1


--------------------------------------------------------


configure: error: Package requirements (libplist >= 1.11) were not met:

Requested 'libplist >= 1.11' but version of libplist is 1.10

Consider adjusting the PKG_CONFIG_PATH environment variable if you
installed software in a non-standard prefix.

Alternatively, you may set the environment variables libplist_CFLAGS
and libplist_LIBS to avoid the need to call pkg-config.
See the pkg-config man page for more details.

# CodeViz 

https://github.com/petersenna/codeviz

http://www.linuxidc.com/Linux/2015-01/111501.htm


