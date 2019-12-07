cc -c *.c
cp minilibx_macos/libmlx.a ./dgraph.a
ar rc dgraph.a *.o
ranlib dgraph.a
