#include "execute_module.h"

int fd;

int fs_open_serwer( char *adres_serwera ) //do wyrzucenia
{
    printf("fs_open_serwer, adres serwera: %s\n", adres_serwera);
    return 1;
}

int fs_close_serwer( int srvhndl ) //do wyrzucenia
{
    printf("fs_close_serwer, uchwyt: %d\n", srvhndl);
    return 1;
}

int fs_open( int srvhndl, char *name, int flags )
{
    printf("fs_open, uchwyt: %d, nazwa pliku: %s, flagi: %d\n", srvhndl, name, flags);
    if (flags == O_CREAT)
    fd = open(name, flags, 0666); //kiepsko
    else
    fd = open(name, flags);

    return fd;
}

int fs_write( int srvhndl, int fd, void *buf, size_t len )
{
    printf("fs_write, uchwyt: %d, deskryptor pliku: %d, wartosc: %s, dlugosc: %d\n", srvhndl, fd, buf, len);
    int ret = write(fd, buf, len);
    return ret;
}

int fs_read( int srvhndl, int fd, void *buf, size_t len )
{
    printf("fs_read, uchwyt: %d, deskryptor pliku: %d, wartosc: %s, dlugosc: %d\n", srvhndl, fd, buf, len);
    int ret = read(fd, buf, len);
    return ret;
}

int fs_lseek( int srvhndl, int fd, long offset, int whence )
{
    printf("fs_lseek, uchwyt: %d, deskryptor pliku: %d, offset: %d, whence: %d\n", srvhndl, fd, offset, whence);
    int ret = lseek(fd, offset, whence);
    return ret;
}

int fs_close( int srvhndl, int fd )
{
    printf("fs_close, uchwyt: %d, deskryptor pliku: %d\n", srvhndl, fd);
    int ret = close(fd);

    return ret;
}

int fs_fstat( int srvhndl, int fd, struct stat *buf)
{
    printf("fs_fstat, uchwyt: %d, deskryptor pliku: %d\n", srvhndl, fd);
    struct stat _stat;
    fstat(fd, &_stat);
    memcpy(buf, &_stat, sizeof(struct stat));

    return sizeof(struct stat);
}

int fs_lock( int srvhndl, int fd, int mode )
{
    printf("fs_lock, uchwyt: %d, deskryptor pliku: %d, blkada: %d\n", srvhndl, fd, mode);
    int ret = lock(fd, mode);
    return ret;
}

/***************pomocnicze***************/
int check_read_lock(int fd)
{
    struct flock lock, savelock;

    lock.l_type    = F_WRLCK;   /* Test for any lock on any part of file. */
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    savelock = lock;
    fcntl(fd, F_GETLK, &lock);  /* Overwrites lock structure with preventors. */
    if (lock.l_type == F_RDLCK)
    {
        return 1;
    }
    return 0;
}

int check_write_lock(int fd)
{
    struct flock lock, savelock;

    lock.l_type    = F_WRLCK;   /* Test for any lock on any part of file. */
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    savelock = lock;
    fcntl(fd, F_GETLK, &lock);  /* Overwrites lock structure with preventors. */
    if (lock.l_type == F_WRLCK)
    {
        return 1;
    }
    return 0;
}

int lock(int fd, int mode)
{
    struct flock lock;
    memset (&lock, 0, sizeof(lock));

    switch (mode)
    {
        case 0:
        {
            if (check_write_lock(fd) == 0)
            {
                 lock.l_type = F_RDLCK;
                 printf("Read lock set\n");
            }
            else
            {
                printf("Read lock error, write lock exists\n");
                return 1;
            }
        }
        break;

        case 1:
        {
            if (check_read_lock(fd) == 0 && check_write_lock(fd) == 0)
            {
                lock.l_type = F_WRLCK;
                printf("Write lock set\n");
            }
            else
            {
                printf("Write lock error, read or write lock exists\n");
                return 2;
            }

        break;
        }
        case 2:
        {
                lock.l_type = F_UNLCK;
                printf("Unlock file\n");
        break;
        }
        default:
        break;
    }

    fcntl (fd, F_SETLKW, &lock);

    return 0;
}
