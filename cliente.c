#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#define MAX 1024

void enviar_dados(FILE *fp, int socket_udp, struct sockaddr_in endereco)
{
    int n;
    char buffer[MAX];

    while (fgets(buffer, MAX, fp) != NULL)
    {
        printf("Enviando dados: %s", buffer);

        n = sendto(socket_udp, buffer, MAX, 0, (struct sockaddr *)&endereco, sizeof(endereco));
        if (n == -1)
        {
            perror("ERRO ao enviar dados ao servidor.");
            exit(1);
        }
        bzero(buffer, MAX);
    }

    strcpy(buffer, "END");
    sendto(socket_udp, buffer, MAX, 0, (struct sockaddr *)&endereco, sizeof(endereco));

    fclose(fp);
    return;
}

int main()
{

    char *ip = "127.0.0.1";
    int porta = 3000;

    int socket_udp;
    struct sockaddr_in endereco_servidor;
    FILE *fp;
    char *filename = "cliente.txt";

    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);

    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_port = porta;
    endereco_servidor.sin_addr.s_addr = inet_addr(ip);

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("ERRO ao ler o arquivo");
        exit(1);
    }

    enviar_dados(fp, socket_udp, endereco_servidor);

    printf("\nTransferência de dados completa.\n");
    printf("Desconectando do servidor.\n");

    close(socket_udp);

    return 0;
}