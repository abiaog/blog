
# make 
## /usr/bin/x86_64-linux-gnu-ld: cannot find -lbsd
install libbsd-dev

## How to build reread manually
 2025  gcc -I ../include/ reread.c ./single.c ../advio/lockfile.c -L ../lib/ -lapue -lpthread 
 2026  ll
 2027  ./a.out 

## a daemon example
exercises/getlogin.c

