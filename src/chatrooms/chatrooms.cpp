#include "chatrooms.hpp"



bool chatrooms::chatrooms_t::add_chatroom(std::shared_ptr<chatroom::chatroom_t> &&chatroom)
{
    std::lock_guard<std::recursive_mutex> lk(m_mutex);
    auto status = m_rooms.emplace(std::move(chatroom));
    return status.second;
}



bool chatrooms::chatrooms_t::remove_chatroom(const std::string &chatroom_name)
{
    std::lock_guard<std::recursive_mutex> lk(m_mutex);
    auto erased = m_rooms.erase(std::make_shared<chatroom::chatroom_t>(chatroom_name));
    if (erased) {
        return true;
    } else {
        return false;
    }
}



bool chatrooms::chatrooms_t::add_user(const std::string &chatroom_name, 
                                      std::shared_ptr<chat_user::chat_user_t> &&user)
{
    std::lock_guard<std::recursive_mutex> lk(m_mutex);
    auto result = find_chatroom(chatroom_name);
    if (result == m_rooms.end()) {
        return false;
    }

    auto ret = result->get()->add_user(std::move(user));
    return ret;
}



bool chatrooms::chatrooms_t::remove_user(const std::string &chatroom_name, 
                                         const int tcp_client_index)
{
    std::lock_guard<std::recursive_mutex> lk(m_mutex);
    auto result = find_chatroom(chatroom_name);
    if (result == m_rooms.end()) {
        return false;
    }

    auto ret = result->get()->remove_user(tcp_client_index);
    return ret;
}



chatrooms::chatrooms_t::rooms_it chatrooms::chatrooms_t::find_chatroom(const std::string &chatroom_name)
{
    std::lock_guard<std::recursive_mutex> lk(m_mutex);
    auto result = m_rooms.find(std::make_shared<chatroom::chatroom_t>(chatroom_name));
    return result;
}



int chatrooms::chatrooms_t::get_num_users_in_chatroom(const std::string &chatroom_name)
{
    std::lock_guard<std::recursive_mutex> lk(m_mutex);
    auto result = find_chatroom(chatroom_name);
    if (result == m_rooms.end()) {
        return false;
    }

    auto num_users = result->get()->get_num_users();
    return num_users;
}



void chatrooms::chatrooms_t::send_msg_to_chatroom(const std::string &chatroom_name,
                                                  const std::string &msg)
{
    std::lock_guard<std::recursive_mutex> lk(m_mutex);
    auto result = find_chatroom(chatroom_name);
    if (result == m_rooms.end()) {
        return;
    }

    result->get()->send_msg_to_users(msg);
}