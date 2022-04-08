```
gcc mymath.c -fPIC -shared -o libmymath.so

readelf -h libmymath.so 

gcc main.c -L. -lmymath -o main

$ sudo cp libmymath.so /usr/lib/

$ ./main

k = 3

$ ldd main
        linux-vdso.so.1 (0x00007ffdba99b000)
        libmymath.so => /usr/lib/libmymath.so (0x00007fcd2a903000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fcd2a512000)
        /lib64/ld-linux-x86-64.so.2 (0x00007fcd2ad07000)

$ readelf -h main
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Shared object file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x650
  Start of program headers:          64 (bytes into file)
  Start of section headers:          6472 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         29
  Section header string table index: 28



$ od -Ax -t x1 -N 64 main
000000 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
000010 03 00 3e 00 01 00 00 00 50 06 00 00 00 00 00 00
000020 40 00 00 00 00 00 00 00 48 19 00 00 00 00 00 00
000030 00 00 00 00 40 00 38 00 09 00 40 00 1d 00 1c 00
000040

```
