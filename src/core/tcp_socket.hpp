#pragma once

#include <netinet/in.h>
#include <string>

namespace tcp_socket {

constexpr int TCP_PORT = 42125;

int  start(struct sockaddr_in *addr);
void do_accept(const int sockfd, struct sockaddr_in *addr);
void do_poll();

} // END namespace tcp_server