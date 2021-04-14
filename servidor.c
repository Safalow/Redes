#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <arpa/inet.h>

#define MAX 1024

void escrever_arquivo(int socket_udp, struct sockaddr_in endereco)
{
    FILE *fp;
    char *filename = "servidor.txt";

    char buffer[MAX];
    socklen_t tamanho_endereco;

    fp = fopen(filename, "w");

    while (1)
    {

        tamanho_endereco = sizeof(endereco);
        recvfrom(socket_udp, buffer, MAX, 0, (struct sockaddr *)&endereco, &tamanho_endereco);

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

    int socket_udp;
    struct sockaddr_in endereco_servidor, endereco_cliente;

    socket_udp = socket(AF_INET, SOCK_DGRAM, 0);

    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_port = porta;
    endereco_servidor.sin_addr.s_addr = inet_addr(ip);

    bind(socket_udp, (struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor));

    printf("Servidor UDP iniciado. \n");
    escrever_arquivo(socket_udp, endereco_cliente);

    printf("\nTransferência de dados completa.\n");
    printf("Fechando o servidor.\n");

    close(socket_udp);

    return 0;
}