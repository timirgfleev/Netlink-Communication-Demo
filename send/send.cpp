#include <netlink/socket.h>
#include <netlink/msg.h>
#include <iostream>
#include <cstring>

#define NLINK_MSG_LEN 1024

int main()
{
    // Create a new socket
    nl_sock *sk = nl_socket_alloc();
    if (!sk)
    {
        std::cerr << "Failed to allocate netlink socket.\n";
        return -1;
    }
    //std::cin.get();
    // Connect the socket
    if (nl_connect(sk, NETLINK_GENERIC) < 0)
    {
        std::cerr << "Failed to connect the netlink socket.\n";
        nl_socket_free(sk);
        return -1;
    }

    // Set the local (source) address of the socket
    nl_socket_set_local_port(sk, 1);

    // Create a new netlink message
    nl_msg *msg = nlmsg_alloc();
    if (!msg)
    {
        std::cerr << "Failed to allocate netlink message.\n";
        nl_socket_free(sk);
        return -1;
    }

    // Set the PID of the message
    // Create a sockaddr_nl structure
    struct sockaddr_nl src_addr;

    // Clear the structure
    memset(&src_addr, 0, sizeof(src_addr));

    // Set the family and pid fields
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = nl_socket_get_local_port(sk);

    // Set the source address of the message
    nlmsg_set_src(msg, &src_addr);

    // Add the message payload
    if (nlmsg_append(msg, (void *)"Hello World !", NLINK_MSG_LEN, NLMSG_ALIGNTO) < 0)
    {
        std::cerr << "Failed to append payload to netlink message.\n";
        nlmsg_free(msg);
        nl_socket_free(sk);
        return -1;
    }

    // Set the destination address of the message
    nl_socket_set_peer_groups(sk, 0);
    nl_socket_set_peer_port(sk, 2);

    // Send the message
    // Set the sequence number of the message
   // nlmsg_set_seq(msg, 1);

    // Set the PID of the message
    nlmsg_set_src(msg, &src_addr);

    int msgcode = nl_send_auto(sk, msg);
    if (msgcode < 0)
    {
        std::cerr << "code: " << msgcode << " Failed to send netlink message.\n";
        nlmsg_free(msg);
        nl_socket_free(sk);
        return -1;
    }

    std::cout << "Sent message: Hello World !\n";

    // Free the message and the socket
    nlmsg_free(msg);
    nl_socket_free(sk);

    return 0;
}