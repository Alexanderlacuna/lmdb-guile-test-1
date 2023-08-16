#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <lmdb.h>


struct _mdb {
  MDB_env *env;
  MDB_dbi dbi;
  MDB_val key, value;
  MDB_txn *txn;
  MDB_cursor *cursor;
  char *dbname;
};
struct _mdb *scm_mdb_init(char *fname, int maxdbs, size_t mapsize, int *rc)
{


  struct _mdb *m = (struct _mdb *)malloc(sizeof(struct _mdb));
  if ((*rc = mdb_env_create(&m->env)) != 0) 
  {
     return NULL;
  }
  if (maxdbs > 0) 
  {
     if ((*rc = mdb_env_set_maxdbs(m->env, maxdbs)) != 0)
     {
        return NULL;
     }
  }
  if (mapsize > 0) 
  {
     if ((*rc = mdb_env_set_mapsize(m->env, mapsize)) != 0)
     {
        return NULL;
     }
  }
  if ((*rc = mdb_env_open(m->env, fname, 0, 0664)) != 0)
  {
     return NULL;
  }
  m->cursor=NULL;
  m->dbname=NULL;
  return m;
}

int scm_mdb_begin(struct _mdb *m, char *dbname, unsigned int flags)
{
  int rc, n;
  if ((rc = mdb_txn_begin(m->env, NULL, flags, &(m->txn))) != 0)
  {
     return rc;
  }
  if ((rc = mdb_open(m->txn, dbname, (flags & MDB_RDONLY) ? 0 : MDB_CREATE, &m->dbi)) != 0)
  {
     return rc;
  }
  m->cursor=NULL;
  if (dbname != NULL)
  {
     n = strnlen(dbname,256);
     m->dbname = malloc(n+1);
     strncpy(m->dbname, dbname, n);
     m->dbname[n] = 0;
  }
  return rc;
}

int scm_mdb_end(struct _mdb *m)
{
  int rc;
  if ((rc = mdb_txn_commit(m->txn)) != 0) 
  {
     return rc;
  }
  mdb_close(m->env, m->dbi);
  return rc;
}


void scm_mdb_abort(struct _mdb *m)
{
  mdb_txn_abort(m->txn);
  mdb_close(m->env, m->dbi);
}


int scm_mdb_write(struct _mdb *m, unsigned char *k, int klen, unsigned char *v, int vlen)
{
  int rc;
  m->key.mv_size = klen;
  m->key.mv_data = k;
  m->value.mv_size = vlen;
  m->value.mv_data = v;
  if ((rc = mdb_put(m->txn, m->dbi, &(m->key), &(m->value), 0)) != 0)
  {
     switch (rc) 
     {
      case MDB_BAD_TXN:
        mdb_txn_abort(m->txn);
        mdb_close(m->env, m->dbi);
        assert ((rc = scm_mdb_begin(m, m->dbname, 0)) == 0);
        if ((rc = mdb_put(m->txn, m->dbi, &(m->key), &(m->value), 0)) != 0)
        {
          return rc;
        };
        break;
      default:
        mdb_txn_commit(m->txn);
        mdb_close(m->env, m->dbi);
     }
  }
  return rc;
}

int scm_mdb_read(struct _mdb *m, unsigned char *k, int klen)
{
  int rc;
  m->key.mv_size = klen;
  m->key.mv_data = k;
  if ((rc = mdb_get(m->txn,m->dbi,&m->key, &m->value)) != 0)
  {
     return rc;
  }
  return rc;
}


int scm_mdb_del(struct _mdb *m, unsigned char *k, int klen)
{
  int rc;
  m->key.mv_size = klen;
  m->key.mv_data = k;
  if ((rc = mdb_del(m->txn, m->dbi, &m->key, &m->value)) != 0)
  {
     return rc;
  }
  return rc;
}

void scm_mdb_close(struct _mdb *m)
{
  mdb_env_close(m->env);
  if (m->dbname != NULL)
  {
     free(m->dbname);
     m->dbname = NULL;
  }
  free(m);
}

//ignore below general linker test functions

int scm_fibonacci() {
  return 1;
}

int scm_pointers(char *fname, int *name2){
  printf("%s\n", fname);
  printf("the fname is %d and",*(name2));
  return 3;
}