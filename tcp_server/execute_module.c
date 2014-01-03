#include "execute_module.h"

int fs_open_serwer( char *adres_serwera )
{
    printf("fs_open_serwer, adres serwera: %s\n", adres_serwera);
    return 5;
}

int fs_close_serwer( int srvhndl )
{
    printf("fs_close_serwer, uchwyt: %d\n", srvhndl);
    return 1;
}

int fs_open( int srvhndl, char *name, int flags )
{
    printf("fs_open, uchwyt: %d, nazwa pliku: %s, flagi: %d\n", srvhndl, name, flags);
    return 777;
}

int fs_write( int srvhndl, int fd, void *buf, size_t len )
{
    printf("fs_write, uchwyt: %d, deskryptor pliku: %d, wartosc: %s, dlugosc: %d\n", srvhndl, fd, buf, len);
    return 1;
}

int fs_read( int srvhndl, int fd, void *buf, size_t len )
{
    printf("fs_read, uchwyt: %d, deskryptor pliku: %d, wartosc: %s, dlugosc: %d\n", srvhndl, fd, buf, len);
    return 1;
}

int fs_lseek( int srvhndl, int fd, long offset, int whence )
{
    printf("fs_lseek, uchwyt: %d, deskryptor pliku: %d, offset: %d, whence?: %d\n", srvhndl, fd, offset, whence);
    return 1;
}

int fs_close( int srvhndl, int fd )
{
    printf("fs_close, uchwyt: %d, deskryptor pliku: %d\n", srvhndl, fd);
    return 1;
}

int fs_fstat( int srvhndl, int fd, struct stat *buf)
{
    printf("fs_fstat, uchwyt: %d, deskryptor pliku: %d\n", srvhndl, fd);
    return 1;
}

int fs_lock( int srvhndl, int fd, int mode )
{
    printf("fs_lock, uchwyt: %d, deskryptor pliku: %d, blkada: %d\n", srvhndl, fd, mode);
    return 1;
}
