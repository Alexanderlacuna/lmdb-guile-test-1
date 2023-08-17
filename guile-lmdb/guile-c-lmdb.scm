(define-module (guile-lmdb guile-c-lmdb)
  #:use-module (ice-9 ftw)
  #:use-module (ice-9 rdelim)
  #:use-module (system foreign-library)
  #:use-module (system  foreign)
  #:export (%lmdb-init-wrapper
            %lmdb-begin
            %lmdb-end
            %lmdb-write
            %lmdb-read
            %lmdb-close
            %lmdb-shared-lib            
    ))

;;fixing issue with loading path from different modules
(define %lmdb-shared-lib  "./guile-lmdb/test")


(define %lmdb-init
  (foreign-library-function %lmdb-shared-lib "scm_mdb_init"
    #:return-type '* ; Pointer to struct _mdb
    #:arg-types (list '*  int size_t '*)))

;; wrapper for scm_mdb-init
(define %lmdb-init-wrapper
    (foreign-library-function %lmdb-shared-lib "init_scm_mdb_wrapper"
    #:return-type '* ; Pointer to struct _mdb
    #:arg-types (list '*  int size_t))
  )
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
