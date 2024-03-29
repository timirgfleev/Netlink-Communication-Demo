#include <netlink/msg.h>
#include <iostream>
#include <cstring>

#include <Connection.h>
#include <ConfigConsts.h>



// Define the callback function
int my_recv_msg(nl_msg *msg, void *arg)
{
    // Print the received message
    std::cout << "Received message: " << (char *)nlmsg_data(nlmsg_hdr(msg)) << "\n";
    return NL_OK;
}

int main()
{
    // Create a new socket
    auto c = UnicastConnection::Create(SERVER_PORT);

    if(!c)
    {
        std::cout << "Failed to create socket\n";
        return -1;
    }

    nl_sock *sk = c->getSocket();
    int skb = nl_socket_modify_cb(sk, NL_CB_VALID, NL_CB_CUSTOM, my_recv_msg, NULL);
    if(skb < 0)
    {
        std::cout << "Failed to set callback: " << nl_geterror(skb) << "\n";
        return -1;
    }
    std::cout << "work on port: " << nl_socket_get_local_port(sk) << "\n";

    // Receive messages in a loop
    nl_socket_disable_seq_check(sk);
    while (true)
    {
        int ret = nl_recvmsgs_default(sk);
        if (ret < 0)
        {
            std::cout << "Failed to receive netlink message: " << nl_geterror(ret) << "\n";
            break;
        }

        // If the return value is 0, it means that message has been received
        if (ret == 0)
        {
            std::cout << "Message received, exiting...\n";
            break;
        }
    }
    return 0;
}