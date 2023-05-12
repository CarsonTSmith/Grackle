#include "clients.hpp"

#include "tcp_socket.hpp"
#include "udp_socket.hpp"
#include "voice_chat.hpp"
#include "voice_clients.hpp"

#include <chatrooms/chatroom_singleton.hpp>

#include <netinet/in.h>
#include <signal.h>
#include <thread>



static void grackle_exit(int signum)
{
    exit(-1);
}



static void register_signals()
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, grackle_exit);
}



static void init_singletons()
{
    clients::init();
    chatrooms::init();
}



int main(int argc, char *argv[])
{
    int tcp_sockfd, udp_sockfd;
    struct sockaddr_in addr;

    register_signals();
    init_singletons();
    
    tcp_sockfd = tcp_socket::start(&addr);
    udp_sockfd = udp_socket::start();

    // std::thread udp_prune_thread(voice_clients::do_prune_clients);
    // udp_prune_thread.detach();

    std::thread voicechat_thread(voice_chat::process, udp_sockfd);
    voicechat_thread.detach();

    std::thread accept_thread(tcp_socket::do_accept, tcp_sockfd, &addr);
    accept_thread.detach();

    tcp_socket::do_poll();
    return 0;
}