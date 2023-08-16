


```bash

 gcc guile_c_lmdb.c  -o   guile_c_lmdb

```

linking 
```bash

gcc -shared -o test.so guile_c_lmdb.o -Wl,-rpath,/usr/lib/x86_64-linux-gnu -lm -llmdb
```