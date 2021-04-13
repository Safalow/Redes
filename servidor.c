#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 1024

void escrever_arquivo(int sockfd, struct sockaddr_in addr)
{
    FILE *fp;
    char *filename = "servidor.txt";
    int n;
    char buffer[MAX];
    socklen_t addr_size;

    fp = fopen(filename, "w");

    while (1)
    {

        addr_size = sizeof(addr);
        n = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr *)&addr, &addr_size);

        if (strcmp(buffer, "END") == 0)
        {
            break;
            return;
        }

        printf("Recebendo dados: %s", buffer);
        fprintf(fp, "%s", buffer);
        bzero(buffer, MAX);
    }

    fclose(fp);
    return;
}

int main()
{

    char *ip = "127.0.0.1";
    int porta = 3000;

    int server_sockfd;
    struct sockaddr_in server_addr, client_addr;
    int e;

    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = porta;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Servidor UDP iniciado. \n");
    escrever_arquivo(server_sockfd, client_addr);

    printf("\nTransferência de dados completa.\n");
    printf("Fechando o servidor.\n");

    close(server_sockfd);

    return 0;
}