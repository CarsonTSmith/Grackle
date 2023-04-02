#include "tcp_socket.hpp"

#include "clients.hpp"
#include "request.hpp"

#include <errno.h>
#include <fcntl.h>
#include <functional>
#include <future>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

static void process(clients::clients_s &clients, int num_fds) {
    for (int i = 0; (num_fds > 0) && (i < clients::MAX_CLIENTS); ++i) {
        if (clients.p_clients[i].revents & POLLIN) {
            // TODO: delegate handle_request to threadpool in the future
            // for now spin off a thread
            std::thread handle_request_thread(request::handle_request, i);
            handle_request_thread.detach();
            num_fds--;
        }
    }
}

int tcp_socket::start(struct sockaddr_in *addr)
{
    int sockfd, opt = 1;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "tcp socket failed");
        exit(errno);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        fprintf(stderr, "tcp setsockopt failed");
        exit(errno);
    }

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(TCP_PORT);

    if (bind(sockfd, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        fprintf(stderr, "tcp bind failed");
        exit(errno);
    }

    if (listen(sockfd, clients::MAX_CLIENTS) < 0) {
        fprintf(stderr, "tcp listen failed");
        exit(errno);
    }

    printf("TCP Server started\n");
    return sockfd;
}

void tcp_socket::do_accept(const int sockfd, struct sockaddr_in *addr)
{
    socklen_t addrsz = sizeof(*addr);
    int clientfd, flags, index;

    while (1) {
        clientfd = accept(sockfd, (struct sockaddr *)addr, &addrsz);
        if (clientfd < 0) {
            fprintf(stderr, "tcp_server::do_accept() failed");
            exit(-1);
        }

        flags = fcntl(clientfd, F_GETFL, 0);
        fcntl(clientfd, F_SETFL, flags | O_NONBLOCK);

        index = clients::add(clientfd);
        if (index < 0) {
            close(clientfd);
        }
        //else {
        //    std::thread send_history_thread(chatlog::send_history, index);
        //    send_history_thread.detach();
        //}
    }
}

void tcp_socket::do_poll()
{
    int num_fds;
    auto &clients = clients::clients_s::get_instance();

    while (1) {
		num_fds = poll(clients.p_clients,
                       clients::MAX_CLIENTS,
                       500); // timeout so when new clients connect they are polled
		if (num_fds > 0) {
			process(clients, num_fds);
		} else if (num_fds < 0) { // poll error
			fprintf(stderr, "rd_from_clients() poll error\n%d", errno);
			exit(errno);
		} else if (num_fds == 0) { // no data sent yet, poll again
			continue;
		}
	}
}