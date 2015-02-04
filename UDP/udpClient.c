#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
    int sock;
    struct sockaddr_in addr;
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    int retval = 0;

    if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("socket error\n");
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sprintf(sendbuf, "%s\n", "Hello World!");
    sendto(sock, sendbuf, sizeof(sendbuf), 0, (struct sockaddr*) &addr, sizeof(addr));

    retval = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
    if(retval == -1)
    {
      printf("recvfrom error!\n");
    }
    else if(retval > 0)
    {
      printf("%s\n", recvbuf);
    }

    close(sock);

    return 0;
}
