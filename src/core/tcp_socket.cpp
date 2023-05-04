#include "tcp_socket.hpp"

#include "clients.hpp"
#include "request.hpp"
#include "threadpool.hpp"

#include <chrono>
#include <errno.h>
#include <fcntl.h>
#include <functional>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

static void process(clients::clients_s &clients, int num_fds)
{
    static bool status = false;
    for (int i = 0; (num_fds > 0) && (i < clients::MAX_CLIENTS); ++i) {
        if (clients.p_clients[i].revents & POLLIN) {
            if (clients.c_clients[i].is_processing) {
                num_fds--;
                continue;
            }

            clients.c_clients[i].is_processing = true;
            clients.p_clients[i].revents = 0;
            while (1) {
                if (threadpool::g_threadpool.get_q_size() > threadpool::MAX_QUEUE_SIZE) {
                    {
                        std::unique_lock lk(threadpool::mutex);
                        status = threadpool::cv.wait_for(lk, std::chrono::milliseconds(5),
                                                []{return (threadpool::tasks_in_queue < threadpool::MAX_QUEUE_SIZE);});
                        if (status) {
                            break;
                        }
                    }
                } else {
                    break;
                }
            }

            threadpool::g_threadpool.push(request::handle_request, i);
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
    }
}

void tcp_socket::do_poll()
{
    int num_fds;
    auto &clients = clients::clients_s::get_instance();

    while (1) {
		num_fds = poll(clients.p_clients,
                       clients::MAX_CLIENTS,
                       50); // timeout so when new clients connect they are polled
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