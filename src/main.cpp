#include "clients.hpp"

#include "tcp_socket.hpp"
#include "udp_socket.hpp"
#include "voice_chat.hpp"

#include <netinet/in.h>
#include <signal.h>
#include <thread>

int main(int argc, char *argv[])
{
    int tcp_sockfd, udp_sockfd;
    struct sockaddr_in addr;

    signal(SIGPIPE, SIG_IGN);
    clients::init();
    tcp_sockfd = tcp_socket::start(&addr);
    udp_sockfd = udp_socket::start();
    std::thread voicechat_thread(voicechat::process, udp_sockfd);
    std::thread accept_thread(tcp_socket::do_accept, tcp_sockfd, &addr); // TCP accept
    tcp_socket::do_poll(); // Poll TCP client fds
    return 0;
}