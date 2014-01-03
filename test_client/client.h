
#define PORT 2022
#define MAXWORD 50

#define N 1024

#define CODE_OPEN_SERVER        10
#define CODE_OPEN_SERVER_RES    20
#define CODE_CLOSE_SERVER       30
#define CODE_OPEN_FILE          40
#define CODE_OPEN_FILE_RES      50
#define CODE_WRITE_FILE         60
#define CODE_WRITE_FILE_RES     70
#define CODE_READ_FILE          80
#define CODE_READ_FILE_RES      90
#define CODE_LSEEK_FILE         100
#define CODE_LSEEK_FILE_RES     110
#define CODE_CLOSE_FILE         120
#define CODE_CLOSE_FILE_RES     130
#define CODE_FSTAT_FILE         140
#define CODE_FSTAT_FILE_RES     150
#define CODE_LOCK_FILE          160
#define CODE_LOCK_FILE_RES      170

/*rzutowanie*/
typedef struct
{
    short command_code;
} cast;
/************************do serwera*************************/
typedef struct
{
    short command_code;             /* kod_funkcji */
    unsigned data_lenght;           /* ilość danych o zmiennej długości */
    char adres_serwera[N];          /* IP serwera */
} open_server;

typedef struct
{
    short command_code;             /* kod_funkcji */
    int srvhndl;                    /* uchwyt serwera */
} close_server;


typedef struct
{
    short command_code;             /* kod_funkcji */
    int data_lenght;                /* ilość danych o zmiennej długości */
    int srvhndl;                    /* uchwyt serwera */
    int flags;                      /* falgi */
    char path[N];                   /* ścieżka do pliku */
} open_file;


typedef struct
{
    short command_code;             /* kod_funkcji */
    int srvhndl;                    /* uchwyt serwera */
    int fd;                         /* deskryptor pliku */
    int len;                        /* wielkość bufora */
    char buf[N];                    /* bufor */
} write_file;

typedef struct
{
    short command_code;             /* kod_funkcji */
    int srvhndl;                    /* uchwyt serwera */
    int fd;                         /* deskryptor pliku */
    int len;                        /* wielkość bufora */
    char buf[N];                    /* bufor */
} read_file;

typedef struct
{
    short command_code;             /* kod_funkcji */
    int srvhndl;                    /* uchwyt serwera */
    int fd;                         /* deskryptor pliku */
    long offset;                    /* przesunięcie */
    int whence;                     /* spodób przesuwania wskaźnika */
} lseek_file;

typedef struct
{
    short command_code;             /* kod_funkcji */
    int srvhndl;                    /* uchwyt serwera */
    int fd;                         /* deskryptor pliku */
} close_file;

typedef struct
{
    short command_code;             /* kod_funkcji */
    int data_lenght;                /* ilość danych o zmiennej długości */
    int srvhndl;                    /* uchwyt serwera */
    int fd;                         /* deskryptor pliku */
    char buf[N];                    /* bufor na strukturę stat */
} fstat_file;

typedef struct
{
    short command_code;             /* kod_funkcji */
    int srvhndl;                    /* uchwyt serwera */
    int fd;                         /* deskryptor pliku */
    int mode;                       /* numer blokady */
} lock_file;

/************************do klienta*************************/
typedef struct
{
    short command_code;             /* kod_funkcji */
    int error_code;                  /* kod błędu */
    int srvhndl;                    /* uchwyt serwera */
} open_server_res;

typedef struct
{
    short command_code;/* kod_funkcji */
    int error_code;/* kod błędu */
    int fd; /* deskryptor pliku */
} open_file_res;

typedef struct
{
    short command_code;/* kod_funkcji */
    int error_code;/* kod błędu */
    int result;/* ilość bajtów zapisanych */
} write_file_res;

typedef struct
{
    short command_code;/* kod_funkcji */
    int error_code;/* kod błędu */
    int result;/* integer zwrócony przez read()*/
    int data_lenght;/* ilosc bajtow w tej paczce */
    char data[N];/* część / całość pliku czytanego */
} read_file_res;

typedef struct
{
    short command_code;/* kod_funkcji */
    int error_code;/* kod błędu */
    long new_offset;/* nowy offset */
} lseek_file_res;

typedef struct
{
    short command_code;/* kod_funkcji */
    int error_code;/* kod błędu */
    int result;/* 0 jeśli poprawnie */
} close_file_res;

typedef struct
{
    short command_code;/* kod_funkcji */
    int error_code;/* kod błędu */
    unsigned int data_lenght; /* ilość danych o zmiennej długości */
    char data[N];/* (opcjonalnie)dodatkowe dane / parametry */
} fstat_file_res;

typedef struct
{
    short command_code;/* kod_funkcji */
    int error_code;/* kod błędu */
    int result;/* 0 jeśli poprawnie */
} lock_file_res;
