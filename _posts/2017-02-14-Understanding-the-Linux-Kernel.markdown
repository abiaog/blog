---
layout: post
title:  "Understanding the Linux Kernel"
date:   2017-02-14 
categories: jekyll update
---


# Chapter 1. Memory Addressing

## Memory Addresses

* Logical address

	Each logical address consists of a `segment` and an `offset` that denotes the distance from the start of the segment to the actual address.

* Linear address(also known as virtual address)

	
* Physical address

	Logical address -> |segmentation unit| -> Linear address -> | paging unit| -> Physical address

		Figure 2-1. Logical address translation

## Segment Selectors and Segmentation Registers

To make it easy to retrieve segment selectors quickly, the processor provides segmentation registers whose only purpose is to hold Segment Selectors; these registers are called cs, ss, ds, es, fs and gs.

Three specific purposes,

cs

code segment register

ss 

stack segment register

ds 

data segment regitster

### Segment Descriptors

Segment Descriptors are stored either in the Global Descriptor Table(GDT) or the the Local Descriptor Table(LDT).


### Current Privilege Level(CPL)


### The Linux GDT
In uniprocessor systems there is only one GDT, while in multiprocessor systems there is one GDT for every CPU in the system.

Task State Segment(TSS), different for each processor in the system.


### Linux Kernel Development(3rd edition)

#### struct page

"struct page" stands for physical page.

	struct page {
		unsigned long flags; // pageflags in  ./include/linux/page-flags.h
		atomic_t _count; // usage count, check with page_count()
		atomic_t _mapcount;
		unsigned long private;
		struct address_space *mapping;
		pgoff_t index;
		struct list_head lru;
		void *virtual; // page virtual address

	};

FILE: ./include/linux/mm_types.h (version: Linux 4.0-rc1)


#### struct zone

"zone" is logical concept used to organize the pages according to their attributes.

FILE: ./include/linux/mmzone.h

	enum zone_type {
		ZONE_DMA,
		ZONE_DMA32,
		ZONE_NORMAL,
		ZONE_HIGHMEM,
		ZONE_MOVABLE,
		__MAX_NR_ZONES
	};


	struct zone {
		/* Read-mostly fields */

		/* zone watermarks, access with *_wmark_pages(zone) macros */
		unsigned long watermark[NR_WMARK];

		const char		*name;  // "DMA", "Normal", "HighMem"

		/* Write-intensive fields used from the page allocator */
		spinlock_t		lock;
	} ____cacheline_internodealigned_in_smp;


#### allocate pages

FILE: ./include/linux/gfp.h

	struct page *alloc_pages(gfp_t gfp_mask, unsigned int order)
	  |
	  |-> struct page *alloc_pages_current(gfp_t gfp, unsigned order) /*	@gfp:
									   *		%GFP_USER   user allocation,
									   *      	%GFP_KERNEL kernel allocation,
									   *      	%GFP_HIGHMEM highmem allocation,
									   *      	%GFP_FS     don't call back into a file system.
									   *      	%GFP_ATOMIC don't sleep.
									   */	@order: Power of two of allocation size in pages. 0 is a single page.
 
"page_address" is used to convert physical page into logical address,

	void *page_address(const struct page *page);


#### bootmem (ARM)


	start_kernel(void)
		setup_arch(char **cmdline_p)
			paging_init(mdesc);
				bootmem_init();


	typedef struct bootmem_data {
		unsigned long node_min_pfn;
		unsigned long node_low_pfn;
		void *node_bootmem_map;
		unsigned long last_end_off;
		unsigned long hint_idx;
		struct list_head list;
	} bootmem_data_t;


[linux内存模型之bootmem分配器<一>](http://blog.csdn.net/gdt_a20/article/details/7229329)



#### buddy system



[linux内存模型之buddy(伙伴)系统一概览及相关数据结构](http://blog.csdn.net/gdt_a20/article/details/7327183)


#### slab


[What is slab?](http://blog.csdn.net/ganggexiongqi/article/details/8921643)


#### SLOB, SLAB, SLUB

Slab allocators available

* SLOB: K&R allocator (1991-1999)

* SLAB: Solaris type allocator (1999-2008)

* SLUB: Unqueued allocator (2008-today)

Design philosophies

* SLOB: As compact as possible

* SLAB: As cache friendly as possible. Benchmark friendly.

* SLUB: Simple and instruction cost counts. Superior Debugging. Defragmentation. Execution time friendly.

[Slab allocators in the Linux Kernel: SLAB, SLOB, SLUB](https://events.linuxfoundation.org/sites/events/files/slides/slaballocators.pdf)




### inode

[The “inode” is sometimes referred to as an index node. But what is it? Basically, it is a file structure on a file system. More easily, it is a “database” of all file information except the file contents and the file name.](http://www.linux.org/threads/intro-to-inodes.4130/)

	ls –i test
	stat –i test
	tree -a -L 1 --inodes /


`struct inode` defined in  `./include/linux/fs.h`

[The inode struct](http://www.makelinux.net/books/lkd2/ch12lev1sec6)



### MMU

[Turning on an ARM MMU and Living to tell the Tale: Some Theory](http://www.embedded-bits.co.uk/2011/mmutheory/)

[Turning on an ARM MMU and Living to tell the tale: The code](https://www.embedded-bits.co.uk/2011/mmucode/)

[Introduction to Memory Management in Linux by Alan Ott](https://www.youtube.com/watch?v=EWwfMM2AW9g&t=193s)


### What does the Virtual kernel Memory Layout in dmesg imply?

For example, below output,

	Memory: 2047804k/2086248k available (3179k kernel code, 37232k reserved, 1935k data, 436k init, 1176944k highmem)
	virtual kernel memory layout:
	    fixmap  : 0xffc57000 - 0xfffff000   (3744 kB)
	    pkmap   : 0xff800000 - 0xffa00000   (2048 kB)
	    vmalloc : 0xf7ffe000 - 0xff7fe000   ( 120 MB)
	    lowmem  : 0xc0000000 - 0xf77fe000   ( 887 MB)
	      .init : 0xc0906000 - 0xc0973000   ( 436 kB)
	      .data : 0xc071ae6a - 0xc08feb78   (1935 kB)
	      .text : 0xc0400000 - 0xc071ae6a   (3179 kB)

User space (high memory) can be accessed by the user and, if necessary, also by the kernel.

Kernel space (low memory) can only be accessed by the kernel.

Like this, 

	0x00000000             0xc0000000  0xffffffff 
	    |                        |          |
	    +------------------------+----------+
	    |  User                  |  Kernel  |
	    |  space                 |  space   |
	    +------------------------+----------+



* Physical memory: 2GB RAM

First, the .text, .data and .init sequences which provide the initialization of the kernel's own page tables (translate linear into physical addresses).

* .text : 0xc0400000 - 0xc071ae6a   (3179 kB)

The range where the kernel code resides.

* .data : 0xc071ae6a - 0xc08feb78   (1935 kB)

The range where the kernel data segments reside.

* .init : 0xc0906000 - 0xc0973000   ( 436 kB)

The range where the kernel's initial page tables reside.



Second, the usage of kernel space after initialization

* lowmem  : 0xc0000000 - 0xf77fe000   ( 887 MB)

The lowmem range can be used by the kernel to directly access physical addresses.
This is not the full 1 GB, because the kernel always requires at least 128 MB of linear addresses to implement noncontiguous memory allocation and fix-mapped linear addresses.

* vmalloc : 0xf7ffe000 - 0xff7fe000   ( 120 MB)

Virtual memory allocation can allocate page frames based on a noncontiguous scheme. The main advantage of this schema is to avoid external fragmentation, this is used for swap areas, kernel modules or allocation of buffers to some I/O devices.

* pkmap   : 0xff800000 - 0xffa00000   (2048 kB)

The permanent kernel mapping allows the kernel to establish long-lasting mappings of high-memory page frames into the kernel address space. When a HIGHMEM page is mapped using kmap(), virtual addresses are assigned from here.

* fixmap  : 0xffc57000 - 0xfffff000   (3744 kB)

These are fix-mapped linear addresses which can refer to any physical address in the RAM, not just the last 1 GB like the lowmem addresses. Fix-mapped linear addresses are a bit more efficient than their lowmem and pkmap colleagues. There are dedicated page table descriptors assigned for fixed mapping, and mappings of HIGHMEM pages using kmap_atomic are allocated from here.


Call tree, 

	start_kernel(void)
		mm_init(void)
			mem_init(void)

[What does the Virtual kernel Memory Layout in dmesg imply?](https://unix.stackexchange.com/questions/5124/what-does-the-virtual-kernel-memory-layout-in-dmesg-imply)

[Turning on an ARM MMU and Living to tell the Tale: Some Theory](http://www.embedded-bits.co.uk/2011/mmutheory/)

[Turning on an ARM MMU and Living to tell the tale: The code](https://www.embedded-bits.co.uk/2011/mmucode/)


#### TLB(Translation lookaside buffer)

A Translation lookaside buffer (TLB) is a memory cache that is used to reduce the time taken to access a user memory location. It is a part of the chip’s memory-management unit (MMU). The TLB stores the recent translations of virtual memory to physical memory and can be called an address-translation cache. A TLB may reside between the CPU and the CPU cache, between CPU cache and the main memory or between the different levels of the multi-level cache. The majority of desktop, laptop, and server processors include one or more TLBs in the memory management hardware, and it is nearly always present in any processor that utilizes paged or segmented virtual memory.


[Translation lookaside buffer](https://en.wikipedia.org/wiki/Translation_lookaside_buffer)









### Reference

[Why is page size 4 kb in most operating systems?](https://www.quora.com/Why-is-page-size-4-kb-in-most-operating-systems)

[Why is page size 4KB](http://stackoverflow.com/questions/11783981/is-number-of-frame-number-of-pageslinux])

[how is page size determined in virtual address space?](http://unix.stackexchange.com/questions/128213/how-is-page-size-determined-in-virtual-address-space)

[Why using hierarchical page tables?](http://stackoverflow.com/questions/9834542/why-using-hierarchical-page-tables)

[控制寄存器(CR0,CR1,CR2,CR3)和CR4](http://blog.chinaunix.net/uid-29512885-id-4575143.html)





# MTD & Flash 





[General MTD documentation](http://www.linux-mtd.infradead.org/doc/general.html#L_overview)

[MTD子系统分析](http://blog.csdn.net/a1232345/article/details/46628979)

[Flash设备驱动](http://blog.csdn.net/a1232345/article/details/46629151)




# SPI

[Overview of Linux kernel SPI support](https://www.kernel.org/doc/Documentation/spi/spi-summary)


[关于IIC和SPI总线](http://blog.csdn.net/skyflying2012/article/details/11910173)




# Chapter 20. Program ExZecution

## Program Segments and Process Memory Regions

* Text Segment
* Initiallized data segment
* Uninitialized data segment (bss)
* Stack segment


# Reference

