#include "listen_module.h"

int communication(int new_sock)
{
    char buf[BUFSIZE];
    int rval;
    printf("Connected\n");
    int CONNECTED = 1;

    while (CONNECTED)
    {
            memset(buf, 0, sizeof buf);
            if ((rval = read(new_sock,buf, BUFSIZE)) == -1)
            perror("reading stream message");

            if (rval == 0)
            {
                CONNECTED = 0;
            }
            else
            parse(buf, new_sock);

    }
    printf("Ending connection\n");
    return 0;
}
