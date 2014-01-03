#ifndef EXECUTE_MODULE_H_INCLUDED
#define EXECUTE_MODULE_H_INCLUDED

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

/***************biblioteka***************/
int fs_open_serwer( char *adres_serwera );
int fs_close_serwer( int srvhndl );
int fs_open( int srvhndl, char *name, int flags );
int fs_write( int srvhndl, int fd, void *buf, size_t len );
int fs_read( int srvhndl, int fd, void *buf, size_t len );
int fs_lseek( int srvhndl, int fd, long offset, int whence );
int fs_close( int srvhndl, int fd );
int fs_fstat( int srvhndl, int fd, struct stat *buf);
int fs_lock( int srvhndl, int fd, int mode );

/***************pomocnicze***************/
int check_read_lock(int fd);
int check_write_lock(int fd);
int lock(int fd, int mode);

#endif // EXECUTE_MODULE_H_INCLUDED
