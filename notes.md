


```bash

 gcc guile_c_lmdb.c  -o   guile_c_lmdb -llmdb

 //see

 gcc -c -fPIC guile_c_lmdb.c -o guile_c_lmdb.o

```

linking 
```bash

gcc -shared -o test.so guile_c_lmdb.o -Wl,-rpath,/usr/lib/x86_64-linux-gnu -lm -llmdb
```

guile usage 
``` bash

guile -L . guile_c_lmdb.scm 

```