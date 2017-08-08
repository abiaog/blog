---
layout: post
title:  "The Plain Text Tools Introduction"
date:   2016-02-12 
categories: jekyll update
---
# Text Editor
[VIM](http://www.vim.org)   
emacs   
[Atom](https://atom.io/)   
Sublime Text   

# VIM

[Offical site of vim](http://www.vim.org)

[Plugins](http://vim-scripts.org/)


# emacs
Emacs Tutorial

# How to view code in vim?
	ctags
	cscope
	cflow
	calltree

	zt			Like "z<CR>", but leave the cursor in the same
				column.  {not in Vi}
	zz			Like "z.", but leave the cursor in the same column.
				Careful: If caps-lock is on, this command becomes
				"ZZ": write buffer and exit!  {not in Vi}
	zb			Like "z-", but leave the cursor in the same column.
				{not in Vi}

# cflow





# Plugins
~/.vimrc

	Plugin 'VundleVim/Vundle.vim'
	Plugin 'tpope/vim-fugitive'
	Plugin 'vimwiki'
	Plugin 'sotte/presenting.vim'
	Plugin 'plantuml-syntax'
	Plugin 'L9'
	Plugin 'Conque-Shell'
	Plugin 'Mark'
	Plugin 'pathogen.vim'
	Plugin 'mileszs/ack.vim'
	Plugin 'c.vim'
	Plugin 'git://git.wincent.com/command-t.git'
	Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}

# vim script 
Your first experience with Vim scripts is the vimrc file.
Syntax files are also Vim scripts.

colon command: commands that start with a ":"; these are sometimes referred to as Ex commands or command-line commands.

Quick way to learn vim script

	:h script


Let's start with a simple example: 

	:let i = 1
	:while i < 5
	:  echo "count is" i
	:  let i += 1
	:endwhile
You can try out the examples by yanking the lines from the text here
and executing them with :@"


The ":while" command starts a loop.  The generic form is: 

	:while {condition}
	:  {statements}
	:endwhile


# vim script (Variables)

   These variables are global.  To see a list of currently defined variables
use this command: >
	:let

	let @"=expand("%:p")


# tutor 
	:h tutor

# PlantUML

[Free UML Diagram Tool](http://plantuml.com/)

# taskjuggler
[The TaskJuggler Project Management Software](http://www.taskjuggler.org/)

# Question:

	How to push employees use free sofeware instead of commecial sofeware(payware)?
	Answer1: uninstall ******
	Answer2: pay ******

# The End


**Thanks!**

