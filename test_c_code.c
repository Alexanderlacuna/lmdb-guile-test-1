//this code test working of lmdb using c
//include the library here
int main() {
    int rc;
    
    // Initialize LMDB environment
    struct _mdb *mdb = _mdb_init("./test", 10, 1048576, &rc); // 1MB map size
    if (mdb == NULL) {
        fprintf(stderr, "Failed to initialize LMDB environment: %s\n", mdb_strerror(rc));
        return 1;
    }
    
    // Begin a transaction and open the database
    rc = _mdb_begin(mdb, "./test", 0);
    if (rc != 0) {
        fprintf(stderr, "Failed to begin transaction and open database: %s\n", mdb_strerror(rc));
        _mdb_close(mdb);
        return 1;
    }
    
    unsigned char key[] = "my_key";
    unsigned char value[] = "my_value";
    rc = _mdb_write(mdb, key, sizeof(key), value, sizeof(value));
    if (rc != 0) {
        fprintf(stderr, "Failed to write data to database: %s\n", mdb_strerror(rc));
        _mdb_abort(mdb);
        _mdb_close(mdb);
        return 1;
    }
    
    // Read data from the database
    unsigned char read_value[256]; 
    rc = _mdb_read(mdb, key, sizeof(key));
    if (rc != 0) {
        fprintf(stderr, "Failed to read data from database: %s\n", mdb_strerror(rc));
        _mdb_abort(mdb);
        _mdb_close(mdb);
        return 1;
    }
    _mdb_value(mdb, read_value);
    printf("Read value: %s\n", read_value);
    
    rc = _mdb_end(mdb);
    if (rc != 0) {
        fprintf(stderr, "Failed to commit transaction and close database: %s\n", mdb_strerror(rc));
        _mdb_close(mdb);
        return 1;
    }
    
    // Close the LMDB environment
    _mdb_close(mdb);
    
    return 0;
}
