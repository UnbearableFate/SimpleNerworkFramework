extern "C" {
#include"unpthread.h"
#include"unp.h"
}

void* copyto(void*);

static int sockfd;
static FILE* fp;

void str_cli(FILE* fp_arg, int sockfd_arg) {
    char recvline[MAXLINE];
    pthread_t tid;
    sockfd = sockfd_arg;
    fp = fp_arg;
    Pthread_create(&tid, NULL, copyto, NULL);
    while (Readline(sockfd, recvline, MAXLINE)>0) {
        Fputs(recvline, stdout);
    }
}

void* copyto(void*) {
    char sendline[MAXLINE];
    while (Fgets(sendline, MAXLINE, fp)!=NULL)
    {
        Writen(sockfd, sendline, strlen(sendline));
    }
    Shutdown(sockfd, SHUT_WR);
    return nullptr;
}

int main()
{
    auto sfd = Socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr) != 1) {
        err_sys("address translate error");
    }
    servAddr.sin_port = htons(11223);
    Connect(sfd, (SA*)&servAddr, sizeof(servAddr));
    str_cli(stdin, sfd);
}