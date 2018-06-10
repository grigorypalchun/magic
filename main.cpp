
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>

using namespace std;

char msg1[] = "Hello there!\n";
char msg2[] = "Bye bye!\n";

int sendall(int s, char *buf, int len, int flags)
{
    int total = 0;
    int n;

    while(total < len)
    {
        n = send(s, buf+total, len-total, flags);
        if(n == -1) { break; }
        total += n;
    }

    return (n==-1 ? -1 : total);
}


int recvall(int s, char *buf, int len, int flags)
{
    int total = 0;
    int n;

    while(total < len)
    {
        n = recv(s, buf+total, len-total, flags);
        if(n == -1) { break; }
        total += n;
    }

    return (n==-1 ? -1 : total);
}

int main()
{
    int sock;
    struct sockaddr_in addr;
    int choice;
    char message[64*1024], echo[64*1024];
    //string message;



    cin >> choice;

    if (choice == 1)
    {
      sock = socket(AF_INET, SOCK_DGRAM, 0);
      if(sock < 0)
      {
         perror("socket");
         return 0;
      }

      fcntl(sock, F_SETFL, O_NONBLOCK);

      addr.sin_family = AF_INET;
      addr.sin_port = htons(3425);
      addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

      sockaddr_in from;
      socklen_t fromLength = sizeof(from);

      if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
      {
        perror("connect");
        return 0;
      }


      while (1)
      {
        cin >> message;
        sendall(sock, message, 1024, 0);
      //  recvall(sock, echo, strlen(message), 0);    //, (struct sockaddr *)&addr, &fromLength);
        cout << echo;
      }

      close(sock);
      return 0;
    }

    if (choice == 2)
    {
        int tcp;
        struct sockaddr_in addr;

        tcp = socket(AF_INET, SOCK_STREAM, 0);
        if (tcp < 0)
        {
          perror("socket");
          return 0;
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(3450); // или любой другой порт...
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        if(connect(tcp, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
           perror("connect");
           return 0;
        }

        send(tcp, msg1, sizeof(msg1), 0);
      //  recv(sock, buf, sizeof(message), 0);

      //  printf(buf);
        close(tcp);

        return 0;
    }
}

