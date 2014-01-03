#include "listen_module.h"

void run_tcp_server()
{
    int sock, length;
    struct sockaddr_in server;
    int new_sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("opening stream socket");
        exit(1);
    }

    /* dowiaz adres do gniazda */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    if (bind(sock, (struct sockaddr *) &server, sizeof server) == -1)
    {
        perror("binding stream socket");
        exit(1);
    }

    /* wydrukuj na konsoli przydzielony port */
    length = sizeof server;
    if (getsockname(sock,(struct sockaddr *) &server,&length)== -1)
    {
        perror("getting socket name");
        exit(1);
    }
    printf("Socket port #%d\n", ntohs(server.sin_port));
    /* zacznij przyjmować polaczenia... */
    listen(sock, QLEN);

    do
    {
        new_sock = accept(sock,(struct sockaddr *) 0,(int *) 0);
        if (new_sock < 0 )
        {
            perror("accept");
            continue;
        }

        else
        {
            switch (fork())
            {
                case -1:     /*bląd*/
                    exit(1);
                case 0:     /*proces potomny*/
                    close(sock);
                    exit(communication(new_sock));
                default:
                    close(new_sock);
                    break;
            }
        }

    } while(TRUE);

exit(0);


}

