#include "chatroom.hpp"

#include <core/clients.hpp>
#include <core/response.hpp>




std::size_t chatroom::hash::operator() (const std::shared_ptr<chat_user::chat_user_t> &p) const 
{
    return std::hash<int>()(p->m_tcp_client_index);
}



std::size_t chatroom::compare::operator() (const std::shared_ptr<chat_user::chat_user_t> &a,
                                           const std::shared_ptr<chat_user::chat_user_t> &b) const 
{
    return (a->m_tcp_client_index == b->m_tcp_client_index);
}



chatroom::chatroom_t::chatroom_t(std::string &&name) : m_name(std::move(name))
{

}



chatroom::chatroom_t::chatroom_t(const std::string &name) : m_name(name)
{

}



bool chatroom::chatroom_t::add_user(std::shared_ptr<chat_user::chat_user_t> &&user)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    auto status = m_users.emplace(std::move(user));
    return status.second;
}



bool chatroom::chatroom_t::remove_user(const int tcp_client_index)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    auto erased = m_users.erase(std::make_shared<chat_user::chat_user_t>("", tcp_client_index));
    if (erased) {
        return true;
    } else {
        return false;
    }
}



int chatroom::chatroom_t::get_num_users()
{
    std::lock_guard<std::mutex> lk(m_mutex);
    auto num_users = m_users.size();
    return num_users;
}



void chatroom::chatroom_t::send_msg_to_users(const std::string &msg)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    auto &clients = clients::clients_s::get_instance();
    for (const auto &user: m_users) {
        if (clients.p_clients[user->m_tcp_client_index].fd != -1) {
            response::send(user->m_tcp_client_index, msg);
        }
    }
}