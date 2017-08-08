---
layout: post
title:  "What are exokernel, microkernel and monolithic kernel?"
date:   2017-03-07 
categories: jekyll update
---


# exokernel

Exokernel is an operating system kernel developed by the MIT Parallel and Distributed Operating Systems group, and also a class of similar operating systems.

Operating systems generally present hardware resources to applications through high-level abstractions such as (virtual) file systems. The idea behind exokernels is to force as few abstractions as possible on application developers, enabling them to make as many decisions as possible about hardware abstractions. Exokernels are tiny, since functionality is limited to ensuring protection and multiplexing of resources, which is considerably simpler than conventional microkernels' implementation of message passing and monolithic kernels' implementation of high-level abstractions.


## Motivation

Traditionally kernel designers have sought to make individual hardware resources invisible to application programs by requiring the programs to interact with the hardware via some abstraction model. These models include file systems for disk storage, virtual address spaces for memory, schedulers for task management, and sockets for network communication. These abstractions of the hardware make it easier to write programs in general, but limit performance and stifle experimentation in new abstractions. A security-oriented application might need a file system that does not leave old data on the disk, while a reliability-oriented application might need a file system that keeps such data for failure recovery.

One option is to remove the kernel completely and program directly to the hardware, but then the entire machine would be dedicated to the application being written (and, conversely, the entire application codebase would be dedicated to that machine). The exokernel concept is a compromise: let the kernel allocate the basic physical resources of the machine (e.g. disk blocks, memory pages, and processor time) to multiple application programs, and let each program decide what to do with these resources. The program can then link to a support library that implements the abstractions it needs (or it can implement its own).

One view on how Exokernel operating systems should be defined is that they have kernels with less than 5000 lines of code.



# Reference

[Exokernel](https://en.wikipedia.org/wiki/Exokernel)

[MonoMicroExo](https://www.inso.tuwien.ac.at/uploads/media/OSKP_MonoMicroExo.pdf)



