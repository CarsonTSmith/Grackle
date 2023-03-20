#include "voice_chat.hpp"

#include "udp_socket.hpp"
#include "voice_clients.hpp"

#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

static void send_to_one(const int udp_sockfd,
                        const char *msg,
                        const struct sockaddr *addr,
                        socklen_t addr_size)
{
    if (sendto(udp_sockfd, msg, udp_socket::UDP_MESSAGE_SIZE, 0,
         (struct sockaddr*)addr, addr_size) < 0) {
        printf("Can't send udp msg\n");
        return;
    }
}

static void send_to_all(const int udp_sockfd,
                        const char *msg,
                        socklen_t addr_size)
{
    for (const auto &client: voice_clients::clients) {
        send_to_one(udp_sockfd, msg, &client.addr, addr_size);
    }
}

void voice_chat::process(const int udp_sockfd)
{
    static char msg[udp_socket::UDP_MESSAGE_SIZE];
    struct sockaddr addr;
    socklen_t addr_size = sizeof(struct sockaddr);

    while (1) {
        if (recvfrom(udp_sockfd, msg, sizeof(msg), 0,
            (struct sockaddr*)&addr, &addr_size) < 0) {
            printf("Couldn't receive udp message\n");
        }

        send_to_all(udp_sockfd, msg, addr_size); //TODO: use client addr
        memset(msg, 0, sizeof(msg));
    }
}