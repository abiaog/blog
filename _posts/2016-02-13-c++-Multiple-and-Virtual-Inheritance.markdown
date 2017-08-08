---
layout: post
title:  "C++ Multiple Inheritance"
date:   2016-02-13 
categories: jekyll update
---
# Construct Order In Multiple Inheritance
The order in which base classes are constructed depends on the order in which they
appear in the class derivation list. The order in which they appear in the constructor
initializer list is irrelevant.

[Panda.cpp](/code_for_post/Panda.cpp)   

Output as below, 

	ZooAnimal constructor called!
	Bear constructor called!
	Endangered constructor called!
	Panda constructor called!
	~Panda called!
	~Endangered called!
	~Bear called!
	~ZooAnimal called

A Panda object is initialized as follows

*   `ZooAnimal`, the ultimate base class up the hierarchy from `Panda`’s first direct base class, `Bear`, is initialized first.
*   `Bear`, the first direct base class, is initialized next.
*   `Endangered`, the second direct base, is initialized next.
*   `Panda`, the most derived part, is initialized last.

# How a Virtually Inherited Object Is Constructed
The construction order for an object with a virtual base is slightly modified from the
normal order: The virtual base subparts of the object are initialized first, using
initializers provided in the constructor for the most derived class. Once the virtual base
subparts of the object are constructed, the direct base subparts are constructed in the
order in which they appear in the derivation list.

For example, when a Panda object is created:
 
-   The (virtual base class) `ZooAnimal` part is constructed first, using the initializers specified in the `Panda` constructor initializer list.
-   The `Bear` part is constructed next.
-   The `Raccoon` part is constructed next.
-   The third direct base, `Endangered`, is constructed next.
-   Finally, the `Panda` part is constructed.

**Note:**
Virtual base classes are always constructed prior to nonvirtual base classes
regardless of where they appear in the inheritance hierarchy.

[virtual-inheritance.cpp](/code_for_post/virtual-inheritance.cpp)   

	class Panda : public Bear,
		public Raccoon,
		public Endangered
	//class Panda : public Endangered, // !!!
	//	public Bear,
	//	public Raccoon

Output as below,

	ZooAnimal constructor called!
	Bear constructor called!
	Raccoon constructor called!
	Endangered constructor called!
	Panda constructor called!
	~Panda called!
	~Endangered called!
	~Raccoon called!
	~Bear called!
	~ZooAnimal called!

Change the order,

	//class Panda : public Bear,
	//	public Raccoon,
	//	public Endangered
	class Panda : public Endangered, // !!!
		public Bear,
		public Raccoon

Output as below,

	ZooAnimal constructor called!
	Endangered constructor called!
	Bear constructor called!
	Raccoon constructor called!
	Panda constructor called!
	~Panda called!
	~Raccoon called!
	~Bear called!
	~Endangered called!
	~ZooAnimal called!

