#include <netlink/socket.h>
#include <netlink/msg.h>
#include <iostream>
#include <cstring>

#define NLINK_MSG_LEN 1024

// Define the callback function
int my_recv_msg(nl_msg *msg, void *arg)
{
    // Print the received message
    std::cout << "Received message: " << (char *)nlmsg_data(nlmsg_hdr(msg)) << "\n";
    return NL_OK;
}

int main()
{
    //std::cin.get();
    // Create a new socket
    nl_sock *sk = nl_socket_alloc();
    if (!sk)
    {
        std::cout << "Failed to allocate netlink socket: " << nl_geterror(errno) << "\n";
        return -1;
    }

    nl_socket_set_local_port(sk, 2);

    // Connect the socket
    if (nl_connect(sk, NETLINK_GENERIC) < 0)
    {
        std::cout << "Failed to connect the netlink socket: " << nl_geterror(errno) << "\n";
        nl_socket_free(sk);
        return -1;
    }

    // Set the local (source) address of the socket
    

    int skb = nl_socket_modify_cb(sk, NL_CB_VALID, NL_CB_CUSTOM, my_recv_msg, NULL);
    if(skb < 0)
    {
        std::cout << "Failed to set callback: " << nl_geterror(skb) << "\n";
        nl_socket_free(sk);
        return -1;
    }
    std::cout << "work on port: " << nl_socket_get_local_port(sk) << "\n";

    // Receive messages in a loop
    //nl_socket_disable_seq_check(sk);
    while (true)
    {
        int ret = nl_recvmsgs_default(sk);
        if (ret < 0)
        {
            std::cout << "Failed to receive netlink message: " << nl_geterror(ret) << "\n";
            break;
        }
    }

    nl_socket_free(sk);

    return 0;
}