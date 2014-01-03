#include "parser_module.h"

int fd;
int srvhndl;







void parse(void * buf, int new_sock)
{
    cast _cast;
    memcpy(&_cast, buf, sizeof(cast));

    printf("Kod funkcji: %d\n", _cast.command_code);

    switch (_cast.command_code)
    {
        case CODE_OPEN_SERVER:
        {
            open_server _open_server;
            memcpy(&_open_server, buf, sizeof(open_server));
            srvhndl = fs_open_serwer(_open_server.adres_serwera);

            /******wyslij odpowiedz******/
            open_server_res _open_server_res = get_open_server_res_struct();
            _open_server_res.srvhndl = srvhndl;

            char res_buf[BUFSIZE];
            memcpy(res_buf, &_open_server_res, sizeof(_open_server_res));

            if (write( new_sock, res_buf, BUFSIZE ) == -1)
            perror("writing on stream socket");

            break;
        }

        case CODE_CLOSE_SERVER:
        {
            close_server _close_server;
            memcpy(&_close_server, buf, sizeof(close_server));
            fs_close_serwer(_close_server.srvhndl);

            break;
        }

        case CODE_OPEN_FILE:
        {
            open_file _open_file;
            memcpy(&_open_file, buf, sizeof(open_file));
            fd = fs_open(_open_file.srvhndl, _open_file.path, _open_file.flags);

            /******wyslij odpowiedz******/
            open_file_res _open_file_res = get_open_file_res_struct();
            _open_file_res.fd = fd;

            char res_buf [BUFSIZE];
            memcpy(res_buf, &_open_file_res, sizeof(_open_file_res));

            if (write( new_sock, res_buf, BUFSIZE ) == -1)
            perror("writing on stream socket");

            break;
        }

        case CODE_WRITE_FILE:
        {
            write_file _write_file;
            memcpy(&_write_file, buf, sizeof(write_file));
            fs_write(_write_file.srvhndl, _write_file.fd, _write_file.buf , _write_file.len);

            /******wyslij odpowiedz******/
            write_file_res _write_file_res = get_write_file_res_struct();
            _write_file_res.result = _write_file.len;

            char res_buf [BUFSIZE];
            memcpy(res_buf, &_write_file_res, sizeof(_write_file_res));

            if (write( new_sock, res_buf, BUFSIZE ) == -1)
            perror("writing on stream socket");

            break;
        }

        case CODE_READ_FILE:
        {
            read_file _read_file;
            memcpy(&_read_file, buf, sizeof(read_file));
            fs_read(_read_file.srvhndl, _read_file.fd, _read_file.buf , _read_file.len);

            /******wyslij odpowiedz******/
            read_file_res _read_file_res = get_read_file_res_struct();
            _read_file_res.result = 1;
            _read_file_res.data_lenght = _read_file.len;
            strcpy(_read_file_res.data, "przeczytany_plik");

            char res_buf [BUFSIZE];
            memcpy(res_buf, &_read_file_res, sizeof(_read_file_res));

            if (write( new_sock, res_buf, BUFSIZE ) == -1)
            perror("writing on stream socket");

            break;
        }

        case CODE_LSEEK_FILE:
        {
            lseek_file _lseek_file;
            memcpy(&_lseek_file, buf, sizeof(lseek_file));
            fs_lseek(_lseek_file.srvhndl, _lseek_file.fd, _lseek_file.offset , _lseek_file.whence);

            /******wyslij odpowiedz******/
            lseek_file_res _lseek_file_res = get_lseek_file_res_struct();
            _lseek_file_res.new_offset = _lseek_file.offset;

            char res_buf [BUFSIZE];
            memcpy(res_buf, &_lseek_file_res, sizeof(_lseek_file_res));

            if (write( new_sock, res_buf, BUFSIZE ) == -1)
            perror("writing on stream socket");

            break;
        }

        case CODE_CLOSE_FILE:
        {
            close_file _close_file;
            memcpy(&_close_file, buf, sizeof(close_file));
            fs_close(_close_file.srvhndl, _close_file.fd);

            /******wyslij odpowiedz******/
            close_file_res _close_file_res = get_close_file_res_struct();

            char res_buf [BUFSIZE];
            memcpy(res_buf, &_close_file_res, sizeof(_close_file_res));

            if (write( new_sock, res_buf, BUFSIZE ) == -1)
            perror("writing on stream socket");

            break;
        }

        case CODE_FSTAT_FILE:
        {
            fstat_file _fstat_file;
            memcpy(&_fstat_file, buf, sizeof(fstat_file));
            fs_fstat(_fstat_file.srvhndl, _fstat_file.fd, 0); //popraw

            /******wyslij odpowiedz******/
            fstat_file_res _fstat_file_res = get_fstat_file_res_struct();
            strcpy(_fstat_file_res.data, "dane_opcjonalne");
            _fstat_file_res.data_lenght = strlen("dane_opcjonalne");

            char res_buf [BUFSIZE];
            memcpy(res_buf, &_fstat_file_res, sizeof(_fstat_file_res));

            if (write( new_sock, res_buf, BUFSIZE ) == -1)
            perror("writing on stream socket");

            break;
        }

        case CODE_LOCK_FILE:
        {
            lock_file _lock_file;
            memcpy(&_lock_file, buf, sizeof(lock_file));
            fs_lock(_lock_file.srvhndl, _lock_file.fd, _lock_file.mode);

            /******wyslij odpowiedz******/
            lock_file_res _lock_file_res = get_lock_file_res_struct();

            char res_buf [BUFSIZE];
            memcpy(res_buf, &_lock_file_res, sizeof(_lock_file_res));

            if (write( new_sock, res_buf, BUFSIZE ) == -1)
            perror("writing on stream socket");

            break;
        }

        default:
        break;
    }
}

/************************do serwera*************************/
open_server get_open_server_struct()
{
    open_server _open_server = { .command_code = CODE_OPEN_SERVER, };
    return _open_server;
}

close_server get_close_server_struct()
{
    close_server _close_server = { .command_code = CODE_CLOSE_SERVER, };
    return _close_server;
}

open_file get_open_file_struct()
{
    open_file _open = { .command_code = CODE_OPEN_FILE, };
    return _open;
}

write_file get_write_file_struct()
{
    write_file _write = { .command_code = CODE_WRITE_FILE, };
    return _write;
}

read_file get_read_file_struct()
{
    read_file _read = { .command_code = CODE_READ_FILE, };
    return _read;
}

lseek_file get_lseek_file_struct()
{
    lseek_file _lseek = { .command_code = CODE_LSEEK_FILE, };
    return _lseek;
}

close_file get_close_file_struct()
{
    close_file _close = { .command_code = CODE_CLOSE_FILE, };
    return _close;
}

fstat_file get_fstat_file_struct()
{
    fstat_file _fstat = { .command_code = CODE_FSTAT_FILE, };
    return _fstat;
}

lock_file get_lock_file_struct()
{
    lock_file _lock = { .command_code = CODE_LOCK_FILE, };
    return _lock;
}

/************************do klienta*************************/
open_server_res get_open_server_res_struct()
{
    open_server_res _open_server_res = { .command_code = CODE_OPEN_SERVER_RES, };
    return _open_server_res;
}

open_file_res get_open_file_res_struct()
{
    open_file_res _open_file_res = { .command_code = CODE_OPEN_FILE_RES, .error_code = 0 };
    return _open_file_res;
}

write_file_res get_write_file_res_struct()
{
    write_file_res _write_file_res = { .command_code = CODE_WRITE_FILE_RES, .error_code = 0 };
    return _write_file_res;
}

read_file_res get_read_file_res_struct()
{
    read_file_res _read_file_res = { .command_code = CODE_READ_FILE_RES, .error_code = 0 };
    return _read_file_res;
}

lseek_file_res get_lseek_file_res_struct()
{
    lseek_file_res _lseek_file_res = { .command_code = CODE_LSEEK_FILE_RES, .error_code = 0 };
    return _lseek_file_res;
}

close_file_res get_close_file_res_struct()
{
    close_file_res _close_file_res = { .command_code = CODE_CLOSE_FILE_RES, .error_code = 0, .result = 0 };
    return _close_file_res;
}

fstat_file_res get_fstat_file_res_struct()
{
    fstat_file_res _fstat_file_res = { .command_code = CODE_FSTAT_FILE_RES, .error_code = 0 };
    return _fstat_file_res;
}

lock_file_res get_lock_file_res_struct()
{
    lock_file_res _lock_file_res = { .command_code = CODE_LOCK_FILE_RES, .error_code = 0, .result = 0};
    return _lock_file_res;
}


