#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include "client.h"

/************************do serwera*************************/
open_server get_open_server_struct(unsigned data_l, char * adres_s)
{
    	open_server _open_server = { .command_code = 10, .data_lenght = data_l, };
	strncpy(_open_server.adres_serwera, adres_s, data_l);
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
    open_server_res _open_server_res = { .command_code = CODE_OPEN_SERVER_RES, .error_code = 0 };
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


int chars_in_array(char* array)
{
 	int numberOfChars = 0;
   	while (*array++){
       		numberOfChars++;
   	}
   return numberOfChars;
}

int connectedToAServer(int serverhndl)
{
                if(serverhndl==-1)
            {
                printf("Musisz sie najpierw polaczyc z serwerem!\n");
                return 0;
            }
            return 1;
}
//Returns the first spot with a non-allocated value.
int findNextEmptyInArray(struct filepath *this_filepath)
{
    int i;
    for(i=0;i<MAXWORD+1;i++)
    {
        if(this_filepath[i].file_path==0) return i;
    }
    return -1; //obsluz
}

int findFileInArray(struct filepath *this_filepath,int file_descript)
{
    int i;
    for(i=0;i<MAXWORD+1;i++)
    {
        if(this_filepath[i].file_descriptor==file_descript) return i;
    }
    return -1; // Not found
}

void listFileDescriptorList();

int fs_open_serwer( char *adres_serwera );
int fs_close_serwer( int srvhndl );
int fs_open( int srvhndl, char *name, int flags );
int fs_write( int srvhndl, int fd, void *buf, size_t len );
int fs_read( int srvhndl, int fd, void *buf, size_t len );
int fs_lseek( int srvhndl, int fd, long offset, int whence );
int fs_close( int srvhndl, int fd );
int fs_fstat( int srvhndl, int fd, struct stat *buf);
int fs_lock( int srvhndl, int fd, int mode );

int command (char *cmd,char *word, char *word2, char *word3,char * word4);
void help();

int main(int argc, char *argv[])
{
	//open_server _open_server;

	int srvhndl=-1; // -1 jesli nie jestesmy polaczeni z zadnym serwerem
	char serwer_ip [MAXWORD + 1];
    struct filepath filepaths[MAXWORD + 1]; // Tu trzymamy pary filepath+file descriptor

	int fd;
	char cmd;			//litera komendy
	char word [MAXWORD + 1];	//parametr komendy
	char word2 [MAXWORD + 1];	//parametr komendy
	char word3 [MAXWORD + 1];	//parametr komendy
	char word4 [MAXWORD + 1];	//parametr komendy
	int wordlen = 0;
	help();
	while (1)
	{
		memset(word, 0, sizeof word);
		memset(word2, 0, sizeof word);
		memset(word3, 0, sizeof word);
		memset(word4, 0, sizeof word);
		wordlen = command(&cmd,word,word2,word3,word4);

		switch (cmd)
		{

			case 'c':
            if(srvhndl!=-1)
            {
                printf("Juz jestes polaczony z serwerem, najpierw zerwij polaczenie! \n");
                break;
            } //Nie laczymy sie z wiecej niz 1 serwerem naraz
			srvhndl = fs_open_serwer(word);
			//printf("Polaczono z serwerem: %s\n", word);
			strncpy(serwer_ip, word,15);
			break;

			case 'e':
			fs_close_serwer(srvhndl);
			srvhndl=-1;
			break;

            case 'ls':
            listFileDescriptorList();
            break;
			case 'o':


            if(connectedToAServer(srvhndl)==0) break; //Nie mozemy prowadzic operacji na pliku jesli nie jestesmy polaczeni z serwerem
			switch (atoi(word2))
			{
				case 0:
					fd = fs_open(srvhndl, word, O_RDONLY);
				break;
				case 1:
					fd = fs_open(srvhndl, word, O_WRONLY);
				break;
				case 2:
					fd = fs_open(srvhndl, word, O_CREAT);
				break;
				case 3:
					fd = fs_open(srvhndl, word, O_APPEND);
				break;
			}

			break;

			case 'w':
			{
                if(connectedToAServer(srvhndl)==0) break; //Nie mozemy prowadzic operacji na pliku jesli nie jestesmy polaczeni z serwerem
				int fd_send = open (word2, O_RDONLY);
				int data_size = atoi(word3);
				//int file_size = lseek(fd_send, 0, SEEK_END);
				//lseek(fd_send, 0, SEEK_SET); //na poczatek;
				char buforek[10];

				int parts = ceil((double)data_size/sizeof(buforek));
				//file_size/sizeof(buforek) + 1;
				int i;
				int read_num;
				int buf_size = sizeof(buforek);

				for(i = 0; i < parts; i++)
				{
					read_num = read(fd_send, buforek, buf_size);
					fs_write(srvhndl, atoi(word), buforek, read_num);
					data_size -= read_num;
					if (data_size - buf_size < 0)
					{
						buf_size = data_size;
					}

				}


			//fs_write(atoi(word),atoi(word2), word3, strlen(word3));
			//fs_write(atoi(word),fd_send, word3, strlen(word3));
				close(fd_send);
			break;
			}
			case 'r':
			{
			    if(connectedToAServer(srvhndl)==0) break; //Nie mozemy prowadzic operacji na pliku jesli nie jestesmy polaczeni z serwerem
				int fd_local = open(word2, O_WRONLY);

				int data_size = atoi(word3);
				char buforek[10];
				int parts = ceil((double)data_size/sizeof(buforek));

				int i, rea;
				int buf_size = sizeof(buforek);
				for (i = 0; i < parts; i++)
				{

					rea = fs_read(srvhndl,atoi(word),buforek, buf_size);
					write(fd_local, buforek, rea);
					data_size -= rea;
					if (data_size - buf_size < 0)
					{
						buf_size = data_size;
					}

				}
				close(fd_local);

				//memset(buff_dane, 0, sizeof buff_dane);
				//fs_read(atoi(word),atoi(word2),buff_dane, atoi(word3));
				//printf("W buforze zew: %s\n", buff_dane);
			break;
			}
			case 's':
			if(connectedToAServer(srvhndl)==0) break; //Nie mozemy prowadzic operacji na pliku jesli nie jestesmy polaczeni z serwerem
			switch (atoi(word3))
			{
				case 0:
					fs_lseek(srvhndl,atoi(word), atoi(word2), SEEK_SET);
				break;
				case 1:
					fs_lseek(srvhndl,atoi(word), atoi(word2), SEEK_CUR);
				break;
				case 2:
					fs_lseek(srvhndl,atoi(word), atoi(word2), SEEK_END);
				break;
			}



			break;

			case 'a':
			if(connectedToAServer(srvhndl)==0) break; //Nie mozemy prowadzic operacji na pliku jesli nie jestesmy polaczeni z serwerem
			fs_close(srvhndl,atoi(word));

			break;

			case 'f':
			if(connectedToAServer(srvhndl)==0) break; //Nie mozemy prowadzic operacji na pliku jesli nie jestesmy polaczeni z serwerem
			fs_fstat(srvhndl,atoi(word), 0); //popraw
			break;

			case 'l':
			if(connectedToAServer(srvhndl)==0) break; //Nie mozemy prowadzic operacji na pliku jesli nie jestesmy polaczeni z serwerem
			fs_lock(srvhndl,atoi(word), atoi(word2));
			printf("result: 0 - OK, 1 - blokada WRITE juz istnieje, 2 - blokada READ/WRITE juz istnieje.\n");
			break;

			case 'x':
			if(srvhndl!=-1) fs_close_serwer(srvhndl); // Zamykamy polaczenie jesli nie zamknelismy
          		exit(0);
         		break;

			case 'h':
          		help();
         		break;

			default:
          		printf("'h'-pomoc : 'e'-wyjscie z programu.\n");
         		 break;
		}
	}
}



int fs_open_serwer(char *adres_serwer)
{
	int sock; //aktualny socket
	struct sockaddr_in server;
	struct hostent *hp, *gethostbyname();
	char buf[4096];
	/* Create socket. */
	sock = socket( AF_INET, SOCK_STREAM, 0 );
	if (sock == -1)
	{
	perror("opening stream socket");
	exit(1);
	}

	/* uzyskajmy adres IP z nazwy ... */
	server.sin_family = AF_INET;
	hp = gethostbyname(adres_serwer);
	/* hostbyname zwraca strukture zawierajaca adres danego hosta */
	if (hp == (struct hostent *) 0)
	{
		fprintf(stderr, "%s: unknown host\n", adres_serwer);
		exit(2);
	}

	memcpy((char *) &server.sin_addr, (char *) hp->h_addr,
	hp->h_length);
	server.sin_port = htons(PORT);
	if (connect(sock, (struct sockaddr *) &server, sizeof server)== -1)
	{
		perror("connecting stream socket");
		exit(1);
	}

	open_server _open_server = get_open_server_struct(chars_in_array(adres_serwer), adres_serwer);
	char buffor_tmp [4096];
	memcpy(buffor_tmp, &_open_server, sizeof(_open_server));

	if (write( sock, buffor_tmp, 4096 ) == -1)
	perror("writing on stream socket");


	char buffor_tmp2 [4096];
	if ((read(sock,buffor_tmp2, 4096)) == -1)
            perror("reading stream message");
	open_server_res _open_server_res;
	memcpy(&_open_server_res, buffor_tmp2, sizeof(open_server_res));

	printf("Odpowiedz z serwera, fs_open_serwer, error code: %d, srvhndl: %d\n", _open_server_res.error_code, sock);
	return sock;
}

int fs_close_serwer( int srvhndl )
{
	close_server _close_server = get_close_server_struct();
	_close_server.srvhndl = srvhndl;
	char buffor_tmp [4096];
	memcpy(buffor_tmp, &_close_server, sizeof(_close_server));

	if (write( srvhndl, buffor_tmp, 4096 ) == -1)
	perror("writing on stream socket");

	close(srvhndl);
}

void listFileDescriptorList()
{

}

int fs_open( int srvhndl, char *name, int flags )
{
	open_file _open_file = get_open_file_struct();

	_open_file.srvhndl = srvhndl;
	strncpy(_open_file.path, name, strlen(name));
	_open_file.flags = flags;

	char buffor_tmp [4096];
	memcpy(buffor_tmp, &_open_file, sizeof(_open_file));

	if (write( srvhndl, buffor_tmp, 4096 ) == -1)
	perror("writing on stream socket");



	char buffor_tmp2 [4096];
	if ((read(srvhndl,buffor_tmp2, 4096)) == -1)
            perror("reading stream message");
	else
	{
		open_file_res _open_file_res;
		memcpy(&_open_file_res, buffor_tmp2, sizeof(open_file_res));

		printf("Odpowiedz z serwera, fs_open, error code: %d, fd: %d\n", _open_file_res.error_code, _open_file_res.fd);

		return _open_file_res.fd;
	}
	printf("Zly uchwyt serwera\n");
	return -1;
}

int fs_write( int srvhndl, int fd, void *buf, size_t len )
{

	write_file _write_file = get_write_file_struct();
	_write_file.srvhndl = srvhndl;
	_write_file.fd = fd;
	_write_file.len = len;
	strncpy(_write_file.buf, buf, len);
	char buffor_tmp [4096];
	memcpy(buffor_tmp, &_write_file, sizeof(_write_file));

	if (write( srvhndl,buffor_tmp, 4096 ) == -1)
	perror("writing on stream socket");



	char buffor_tmp2 [4096];
	if ((read(srvhndl,buffor_tmp2, 4096)) == -1)
            perror("reading stream message");
	else
	{
		write_file_res _write_file_res;
		memcpy(&_write_file_res, buffor_tmp2, sizeof(write_file_res));

		printf("Odpowiedz z serwera, fs_write, error code: %d, result: %d\n", _write_file_res.error_code, _write_file_res.result);
		return 0;
	}
	printf("Zly uchwyt serwera\n");
}

int fs_read( int srvhndl, int fd, void *buf, size_t len )
{
	read_file _read_file = get_read_file_struct();
	_read_file.srvhndl = srvhndl;
	_read_file.fd = fd;
	_read_file.len = len;
	strncpy(_read_file.buf, buf, len);
	char buffor_tmp [4096];
	memcpy(buffor_tmp, &_read_file, sizeof(_read_file));

	if (write( srvhndl,buffor_tmp, 4096 ) == -1)
	perror("writing on stream socket");



	char buffor_tmp2 [4096];
	if ((read(srvhndl,buffor_tmp2, 4096)) == -1)
            perror("reading stream message");
	else
	{
		read_file_res _read_file_res;
		memcpy(&_read_file_res, buffor_tmp2, sizeof(read_file_res));

		printf("Odpowiedz z serwera, fs_read, error code: %d, result: %d, data_lenght %d, data: %s\n", _read_file_res.error_code, _read_file_res.result, _read_file_res.data_lenght, _read_file_res.data);
		memcpy(buf, _read_file_res.data, _read_file_res.data_lenght);
	return _read_file_res.data_lenght;
	}
	printf("Zly uchwyt serwera\n");
}

int fs_lseek( int srvhndl, int fd, long offset, int whence )
{
	lseek_file _lseek_file = get_lseek_file_struct();
	_lseek_file.srvhndl = srvhndl;
	_lseek_file.fd = fd;
	_lseek_file.offset = offset;
	_lseek_file.whence = whence;

	char buffor_tmp [4096];
	memcpy(buffor_tmp, &_lseek_file, sizeof(_lseek_file));

	if (write( srvhndl,buffor_tmp, 4096 ) == -1)
	perror("writing on stream socket");


	char buffor_tmp2 [4096];
	if ((read(srvhndl,buffor_tmp2, 4096)) == -1)
            perror("reading stream message");
	else
	{
	lseek_file_res _lseek_file_res;
	memcpy(&_lseek_file_res, buffor_tmp2, sizeof(_lseek_file_res));

	printf("Odpowiedz z serwera, fs_lseek, error code: %d, new_offset: %d\n", _lseek_file_res.error_code, _lseek_file_res.new_offset);
	return 0;

	}
	printf("Zly uchwyt serwera\n");
}

int fs_close( int srvhndl, int fd )
{
	close_file _close_file = get_close_file_struct();
	_close_file.srvhndl = srvhndl;
	_close_file.fd = fd;

	char buffor_tmp [4096];
	memcpy(buffor_tmp, &_close_file, sizeof(_close_file));

	if (write( srvhndl,buffor_tmp, 4096 ) == -1)
	perror("writing on stream socket");



	char buffor_tmp2 [4096];
	if ((read(srvhndl,buffor_tmp2, 4096)) == -1)
            perror("reading stream message");
	else
	{
	close_file_res _close_file_res;
	memcpy(&_close_file_res, buffor_tmp2, sizeof(_close_file_res));

	printf("Odpowiedz z serwera, fs_close, error code: %d, result: %d\n", _close_file_res.error_code, _close_file_res.result);
	return 0;

	}
	printf("Zly uchwyt serwera\n");
}

int fs_fstat( int srvhndl, int fd, struct stat *buf)
{
	fstat_file _fstat_file = get_fstat_file_struct();
	_fstat_file.srvhndl = srvhndl;
	_fstat_file.fd = fd;

	char buffor_tmp [4096];
	memcpy(buffor_tmp, &_fstat_file, sizeof(_fstat_file));

	if (write( srvhndl,buffor_tmp, 4096 ) == -1)
	perror("writing on stream socket");


	char buffor_tmp2 [4096];
	if ((read(srvhndl,buffor_tmp2, 4096)) == -1)
            perror("reading stream message");
	else
	{

	fstat_file_res _fstat_file_res;
	memcpy(&_fstat_file_res, buffor_tmp2, sizeof(_fstat_file_res));
	struct stat _stat;
	memcpy(&_stat, _fstat_file_res.data, sizeof(struct stat));

	printf("Odpowiedz z serwera, fs_fstat, error code: %d, data_lenght: %d\n", _fstat_file_res.error_code, _fstat_file_res.data_lenght);
	printf("ID: %d\n", _stat.st_dev);
    	printf("Inode number: %d\n", _stat.st_ino);
    	printf("Protection: %d\n", _stat.st_mode);
    	printf("Number of hard links: %d\n", _stat.st_nlink);
    	printf("user ID of owner: %d\n", _stat.st_uid);
    	printf("group ID of owner %d\n", _stat.st_gid);
    	printf("device ID: %d\n", _stat.st_rdev);
    	printf("total size, in bytes : %d\n", _stat.st_size);
    	printf("blocksize for file system I/O: %d\n", _stat.st_blksize);
    	printf("number of 512B blocks allocated: %d\n", _stat.st_blocks);
    	char* c_time_string1;
    	char* c_time_string2;
    	char* c_time_string3;
    	c_time_string1 = ctime(&_stat.st_atime);
    	printf("time of last access: %s", c_time_string1);
    	c_time_string2 = ctime(&_stat.st_mtime);
    	printf("time of last modification: %s", c_time_string2);
    	c_time_string3 = ctime(&_stat.st_ctime);
    	printf("time of last status change: %s", c_time_string3);

	return 0;

	}
	printf("Zly uchwyt serwera\n");
}

int fs_lock( int srvhndl, int fd, int mode )
{
	lock_file _lock_file = get_lock_file_struct();
	_lock_file.srvhndl = srvhndl;
	_lock_file.fd = fd;
	_lock_file.mode = mode;

	char buffor_tmp [4096];
	memcpy(buffor_tmp, &_lock_file, sizeof(_lock_file));

	if (write( srvhndl,buffor_tmp, 4096 ) == -1)
	perror("writing on stream socket");


	char buffor_tmp2 [4096];
	if ((read(srvhndl,buffor_tmp2, 4096)) == -1)
            perror("reading stream message");
	else
	{

	lock_file_res _lock_file_res;
	memcpy(&_lock_file_res, buffor_tmp2, sizeof(_lock_file_res));

	printf("Odpowiedz z serwera, fs_lock, error code: %d, result: %d\n", _lock_file_res.error_code, _lock_file_res.result);
	return 0;

	}
	printf("Zly uchwyt serwera\n");
}



int command (char *cmd,char *word, char *word2, char *word3,char * word4)
{
	int i, ch;

	printf("> ");
    	fflush(stdout);

	ch = getc(stdin);
	while (ch == ' ')
	ch = getc(stdin);

	if (ch == EOF)
	return -1;

	*cmd = (char) ch;
	ch = getc(stdin);
	if (ch==EOF)
	return -1;
	while (ch == ' ')
	ch = getc(stdin);

	if (ch == EOF)
	return -1;
	if (ch == '\n')
	return 0;
	i = 0;
	while ((ch != ' ') && (ch != '\n'))
	{
		if (++i > MAXWORD)
		{
		exit(1);
		}
		*word++ = ch;
		ch = getc(stdin);
	}

	if (ch == EOF)
	return -1;
	if (ch == '\n')
	return 0;
	i = 0;
	ch = getc(stdin);
	while (ch == ' ')
	ch = getc(stdin);

	while ((ch != ' ') && (ch != '\n'))
	{
		if (++i > MAXWORD)
		{
		exit(1);
		}
		*word2++ = ch;
		ch = getc(stdin);
	}

	if (ch == EOF)
	return -1;
	if (ch == '\n')
	return 0;
	i = 0;
	ch = getc(stdin);
	while (ch == ' ')
	ch = getc(stdin);
	while ((ch != ' ') && (ch != '\n'))
	{
		if (++i > MAXWORD)
		{
		exit(1);
		}
		*word3++ = ch;
		ch = getc(stdin);
	}

	if (ch == EOF)
	return -1;
	if (ch == '\n')
	return 0;
	i = 0;
	ch = getc(stdin);
	while (ch == ' ')
	ch = getc(stdin);
	while ((ch != ' ') && (ch != '\n'))
	{
		if (++i > MAXWORD)
		{
		exit(1);
		}
		*word4++ = ch;
		ch = getc(stdin);
	}


	return i;
}


void help()
{
	printf("Dostepne polecenia :\n");
        printf(" c <ip>						- polacz z serwerem.\n");
        printf(" e 				            - zakoncz polaczenie.\n");
        printf(" ls 				        - wylistuj pliki i ich file-descriptor.\n");
        printf(" o <nazwa pliku> <tryb>		- otworz plik, tryb 0 - O_RDONLY, 1 - O_WRONLY, 2 - 0_CREAT, 3 - O_APPEND.\n");
        printf(" w <naz pli lok> <ile bajtow> - zapisz do pliku.\n");
       	printf(" r <desk pli na serw> <naz pli lok> <ile bajtow> - odczytaj z pliku.\n");
       	printf(" s <desk pliku> <offset> <whence> 	- przesun wskaznik w pliku, whence: 0 - SEEK_SET, 1 - SEEK_CUR, 2 - SEEK_END\n");
       	printf(" a <desk pliku>			- zamknij plik.\n");
        printf(" f <desk pliku>			- daj fstat\n");
       	printf(" l <desk pliku> <mode>		- lock pliku, mode: 0 - READ_LOCK, 1 - WRITE_LOCK, 2 - UNLOCK\n");
	printf(" x 						- wyjscie z programu\n");
	printf(" h 						- help.\n");
}
