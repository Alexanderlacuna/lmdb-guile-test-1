


```bash

 gcc -shared -o  guile_c_lmdb.so  -fPIC guile_c_lmdb.c

```

linking 
```bash

gcc -shared -o test.so guile_c_lmdb.o -Wl,-rpath,/usr/lib/x86_64-linux-gnu -lm -llmdb
```