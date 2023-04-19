#include "udp_socket.hpp"

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int udp_socket::start()
{
    struct sockaddr_in addr;
    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            fprintf(stderr, "udp socket failed");
            exit(errno);
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(udp_socket::UDP_PORT);

    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
            fprintf(stderr, "udp bind failed");
            exit(errno);
    }

    printf("UDP Server started\n");
    return sockfd;
}