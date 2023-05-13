#include "chat_user.hpp"

chat_user::chat_user_t::chat_user_t(std::string &&username, const int index) : 
                                    m_username(username), m_tcp_client_index(index) 
{

}