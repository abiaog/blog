---
layout: post
title:  "Configure mutt and msmtp"
date:   2016-09-03 
categories: jekyll update
---

# 126.com

Enable smtp service and set a authorization code in web mail.

# install mutt and msmtp

# configure .muttrc
	set sendmail="/usr/bin/msmtp"   
	set use_from=yes 
	set realname="aBiaog"     
	set from=user@126.com    
	set envelope_from=yes   
	set rfc2047_parameters=yes   
	set charset="utf-8"   
	set send_charset="gb2312" 
	set send_charset="utf-8" 
	set send_charset="us-ascii:gbk:utf-8" 
	set pop_user="abiaog"     #设置POP收信用户名
	set pop_pass="ChangeThisToAuthorizationCode" #设置POP收信密码（邮箱的授权密码）
	set pop_host="pop.126.com"          #设置POP收信服务器
	set spoolfile=/home/peter/my_mailbox 

# configure .msmtprc
	account default 
	host smtp.126.com 
	from user@126.com 
	auth login 
	user user  
	password ChangeThisToAuthorizationCode  
	logfile ~/.msmtp.log 


# get server info
	peter@peter-ThinkPad-T430:~$ msmtp --host=smtp.126.com --serverinfo
	SMTP server at smtp.126.com (m15-114.126.com [220.181.15.114]), port 25:
	    126.com Anti-spam GT for Coremail System (126com[20140526])
	Capabilities:
	    PIPELINING:
		Support for command grouping for faster transmission
	    STARTTLS:
		Support for TLS encryption via the STARTTLS command
	    AUTH:
		Supported authentication methods:
		PLAIN LOGIN 
	This server might advertise more or other capabilities when TLS is active.

# Reference

http://huangrs.blog.51cto.com/2677571/967457/

http://blog.chinaunix.net/uid-20001048-id-1739353.html

