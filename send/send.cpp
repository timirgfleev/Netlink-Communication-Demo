#include <netlink/socket.h>
#include <netlink/msg.h>
#include <iostream>
#include <cstring>

#define NLINK_MSG_LEN 1024


#include <Connection.h>
#include <StringMessage.h>
int main()
{
    // Create a new socket
    auto c = UnicastConnection::Create(1);

    if(!c)
    {
        std::cout << "Failed to create socket\n";
        return -1;
    }
    nl_sock *sk = c->getSocket();

    // Set the destination address of the message and no groups
    nl_socket_set_peer_groups(sk, 0);
    nl_socket_set_peer_port(sk, 2);

    // Create a new message
    auto message = std::make_unique<StringMessage>("desu~~~");
    message->send(sk);
    return 0;
}