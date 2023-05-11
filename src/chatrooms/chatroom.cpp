#include "chatroom.hpp"

std::size_t chatroom::hash::operator() (const std::shared_ptr<chat_user::chat_user_t> &p) const 
{
    return std::hash<int>()(p->m_tcp_client_index);
}

std::size_t chatroom::compare::operator() (const std::shared_ptr<chat_user::chat_user_t> &a,
                                           const std::shared_ptr<chat_user::chat_user_t> &b) const 
{
    return (a->m_tcp_client_index == b->m_tcp_client_index);
}

bool chatroom::chatroom_t::add_user(std::shared_ptr<chat_user::chat_user_t> &user)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    auto status = m_users.insert(user);
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