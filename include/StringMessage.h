#pragma once

#include <netlink/msg.h>
#include <iostream>
#include <cstring>
#include "Connection.h"

#define NLINK_MSG_LEN 1024

class StringMessage
{
public:
    /*
    * @brief Create a new message
    * @param message The message to send
    * @return A pointer to the message or nullptr if an error occurred
    */
    StringMessage(const std::string& message)
        : msg(nlmsg_alloc())
    {
        if (!msg)
        {
            std::cerr << "Failed to allocate netlink message.\n";
            return;
        }

        if (nlmsg_append(msg, (void *)message.c_str(), NLINK_MSG_LEN, NLMSG_ALIGNTO) < 0)
        {
            std::cerr << "Failed to append payload to netlink message.\n";
            nlmsg_free(msg);
            msg = nullptr;
        }
    }

    ~StringMessage()
    {
        if (msg)
        {
            nlmsg_free(msg);
        }
    }
    /*
    * @brief Send the message
    * @param sk The socket to send the message on
    * @return True if the message was sent successfully, false otherwise
    */
    bool send(nl_sock *sk)
    {
        if (!msg)
        {
            return false;
        }

        nl_socket_set_peer_groups(sk, 0);
        nl_socket_set_peer_port(sk, 2);

        int msgcode = nl_send_auto(sk, msg);
        if (msgcode < 0)
        {
            std::cerr << "code: " << msgcode << " Failed to send netlink message.\n";
            return false;
        }

        std::cout << "Sent message: " << (char *)nlmsg_data(nlmsg_hdr(msg)) << "\n";
        return true;
    }

    bool is_ok()
    {
        return msg != nullptr;
    }

private:
    nl_msg *msg;
};