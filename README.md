# Introduction

[LMDB](https://en.wikipedia.org/wiki/Lightning_Memory-Mapped_Database) is a software library that provides an embedded transactional database in the form of a key-value store. 

*This repo* is indevelopment Idiomatic and safe APIs for interacting with the Symas Lightning Memory-Mapped Database (LMDB)  using guile.

## Building 

creating a shared library

```bash

 gcc -c -fPIC <path>/guile_c_lmdb.c -o guile_c_lmdb.o
 gcc -shared -o test.so guile_c_lmdb.o -Wl,-rpath,/usr/lib/x86_64-linux-gnu -lm -llmdb


```

build the guile module

```bash

guile -L . guile_c_lmdb.scm 

```

