#include "chatrooms.hpp"


bool chatrooms::chatrooms_t::add_chatroom(std::shared_ptr<chatroom::chatroom_t> &&chatroom)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    auto status = m_rooms.emplace(std::move(chatroom));
    return status.second;
}



bool chatrooms::chatrooms_t::remove_chatroom(const std::string &chatroom_name)
{
    std::lock_guard<std::mutex> lk(m_mutex);
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
    auto result = find_chatroom(chatroom_name);
    if (result == m_rooms.end()) {
        return false;
    }

    auto ret = result->get()->remove_user(tcp_client_index);
    return ret;
}



chatrooms::chatrooms_t::rooms_it chatrooms::chatrooms_t::find_chatroom(const std::string &chatroom_name)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    auto result = m_rooms.find(std::make_shared<chatroom::chatroom_t>(chatroom_name));
    return result;
}
