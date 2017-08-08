---
layout: post
title:  "spinlock, seqlock, RCU, PER CPU Variables"
date:   2016-10-20 
categories: jekyll update
---

# spinlock 

# seqlock
	typedef struct {
		struct seqcount seqcount;
		spinlock_t lock;
	} seqlock_t;

# RCU(Read-Copy-Update)

# PER CPU Variables
	DEFINE_PER_CPU()
	per_cpu(var,cpu)
	get_cpu_var(), put_cpu_var()

# Reference
[seq-locks-vs-rcu-vs-per-cpu-use-cases](http://stackoverflow.com/questions/26761905/seq-locks-vs-rcu-vs-per-cpu-use-cases)

