#pragma once

#include "chat_user.hpp"

#include <memory>
#include <mutex>
#include <unordered_set>

namespace chatroom {

struct hash {
    std::size_t operator() (std::shared_ptr<chat_user::chat_user_t> const &p) const;
};

struct compare {
    size_t operator() (const std::shared_ptr<chat_user::chat_user_t> &a,
                       const std::shared_ptr<chat_user::chat_user_t> &b) const;
};

class chatroom_t {
private:
    std::string m_name; // unique name of chatroom
    std::unordered_set<std::shared_ptr<chat_user::chat_user_t>, hash, compare> m_users;
    std::mutex m_mutex; // synchronize access to the chatroom

public:
    chatroom_t(const std::string &name);
    ~chatroom_t();

    bool add_user(std::shared_ptr<chat_user::chat_user_t> &user);
    bool remove_user(const int tcp_client_index);
};

}