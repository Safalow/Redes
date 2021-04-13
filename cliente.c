#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 1024

void enviar_dados(FILE *fp, int sockfd, struct sockaddr_in addr)
{
    int n;
    char buffer[MAX];

    while (fgets(buffer, MAX, fp) != NULL)
    {
        printf("Enviando dados: %s", buffer);

        n = sendto(sockfd, buffer, MAX, 0, (struct sockaddr *)&addr, sizeof(addr));
        if (n == -1)
        {
            perror("ERRO ao enviar dados ao servidor.");
            exit(1);
        }
        bzero(buffer, MAX);
    }

    strcpy(buffer, "END");
    sendto(sockfd, buffer, MAX, 0, (struct sockaddr *)&addr, sizeof(addr));

    fclose(fp);
    return;
}

int main()
{

    char *ip = "127.0.0.1";
    int porta = 3000;

    int server_sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "cliente.txt";

    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = porta;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("ERRO ao ler o arquivo");
        exit(1);
    }

    enviar_dados(fp, server_sockfd, server_addr);

    printf("\nTransferência de dados completa.\n");
    printf("Desconectando do servidor.\n");

    close(server_sockfd);

    return 0;
}