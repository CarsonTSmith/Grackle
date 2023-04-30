#include "clients.hpp"

#include <unistd.h>

clients::clients_s::clients_s()
{
    for (auto &p_client: p_clients) {
        p_client.fd     = -1;
        p_client.events = POLLIN | POLLPRI;
    }
}

clients::clients_s &clients::clients_s::get_instance()
{
    static clients::clients_s s;
    return s;
}

void clients::init()
{
    clients::clients_s::get_instance();
}

// return the new client's index
int clients::add(const int fd)
{
    auto &clients = clients_s::get_instance();
    if (clients.number_of_clients > MAX_CLIENTS) {
        return -1;
    }

    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (clients.p_clients[i].fd == -1) {
            clients.p_clients[i].fd = fd;
            //clients.p_clients[i].events = POLLIN | POLLPRI;
            clients.number_of_clients++;
            return i;
        }
    }

    return -1;
}

// reset tcp connection and reset client
void clients::reset(const int index) 
{
    auto &clients = clients_s::get_instance();
    close(clients.p_clients[index].fd);
    clients.p_clients[index].fd      = -1;
    //clients.p_clients[index].events  = 0;
    clients.p_clients[index].revents = 0;

    clients.c_clients[index].reset();
    
    clients.number_of_clients--;
}