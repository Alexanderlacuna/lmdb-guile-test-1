(define-module (guile-lmdb-interface)
  #:use-module (ice-9 ftw)
  #:use-module (ice-9 rdelim)
  #:use-module (system foreign-library)
  #:use-module (system  foreign)
  #:use-module (guile-lmdb guile-c-lmdb)
    )



(define (lmdb->env db-name max-dbs map-size) ;;initiliaze mdb environment
  (define env-pointer (%lmdb-init-wrapper (string->pointer db-name) max-dbs  map-size))
 ;;match case for null pointers
  (display env-pointer)
  env-pointer
  )
(define results (lmdb->env  "./lmdb-test" 10 1048576))