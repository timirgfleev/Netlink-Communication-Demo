#include <Connection.h>
#include <StringMessage.h>
#include <ConfigConsts.h>

#include <iostream>
#include <cstring>

int main()
{
    // Create a new socket
    auto c = UnicastConnection::Create(CLIENT_PORT);

    if(!c)
    {
        std::cout << "Failed to create socket\n";
        return -1;
    }
    nl_sock *sk = c->getSocket();

    // Set the destination address of the message and no groups
    nl_socket_set_peer_groups(sk, 0);
    nl_socket_set_peer_port(sk, SERVER_PORT);

    // Create a new message
    auto message = std::make_unique<StringMessage>("desu~~~");
    message->send(sk);
    return 0;
}