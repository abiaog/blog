 gcc mymath.c -fPIC -shared -o libmymath.so
 readelf -h libmymath.so 
gcc main.c -L. -lmymath -o main
