---
layout: post
title:  "c language"
date:   2017-03-22 
categories: jekyll update
---


# packed

`Data structure alignment` is the way data is arranged and accessed in computer memory. It consists of two separate but related issues: data alignment and data structure padding.

When a modern computer reads from or writes to a memory address, it will do this in word sized chunks (e.g. 4 byte chunks on a 32-bit system). `Data alignment` means putting the data at a memory offset equal to some multiple of the word size, which increases the system's performance due to the way the CPU handles memory.

To align the data, it may be necessary to insert some meaningless bytes between the end of the last data structure and the start of the next, which is `data structure padding`.

[What is the meaning of "__attribute__((packed, aligned(4))) "](http://stackoverflow.com/questions/11770451/what-is-the-meaning-of-attribute-packed-aligned4)

[packed.c](/code_for_post/c-language/packed.c)


# pragma


The ‘#pragma’ directive is the method specified by the C standard for providing additional information to the compiler, beyond what is conveyed in the language itself. The forms of this directive (commonly known as pragmas) specified by C standard are prefixed with STDC. A C compiler is free to attach any meaning it likes to other pragmas. All GNU-defined, supported pragmas have been given a GCC prefix.

[pragma](https://gcc.gnu.org/onlinedocs/cpp/Pragmas.html)





# Reference






