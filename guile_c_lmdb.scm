(use-modules (system foreign-library)
             (ice-9 rdelim)
             (system foreign)
  )
;;refactor code to load this shared library
(define %lmdb-shared-lib  "./test")

(define %scm-mdb-init
  (foreign-library-function %lmdb-shared-lib "scm_mdb_init"
    #:return-type '* ; Pointer to struct _mdb
    #:arg-types (list '*  int size_t '*)))

(define %lmdb-begin (foreign-library-function %lmdb-shared-lib "scm_mdb_begin"
  #:return-type int
  #:arg-types (list '* '* unsigned-int)
  ))

(define %lmdb-end
  (foreign-library-function %lmdb-shared-lib "scm_mdb_end"
    #:return-type int
    #:arg-types (list '*)))

(define %lmdb-abort
  (foreign-library-function %lmdb-shared-lib "scm_mdb_abort"
    #:return-type void
    #:arg-types (list '*)))

(define %lmdb-write
  (foreign-library-function %lmdb-shared-lib "scm_mdb_write"
    #:return-type int
    #:arg-types (list '* '*  int '* int)))

(define %lmdb-delete
  (foreign-library-function %lmdb-shared-lib "scm_mdb_read"
    #:return-type int
    #:arg-types (list '* '* int)))

(define %lmdb-close
  (foreign-library-function %lmdb-shared-lib "scm_mdb_close"
    #:return-type void
    #:arg-types (list '*)))

(define %scm-pointers
  (foreign-library-function %lmdb-shared-lib "scm_pointers"
  #:return-type int 
  #:arg-types (list '* '*)
  )
  )