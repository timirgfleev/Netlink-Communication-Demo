#pragma once

#include <netlink/socket.h>
#include <memory>

class UnicastConnection
{
    friend std::unique_ptr<UnicastConnection> std::make_unique<UnicastConnection>();
public:
    /*
    * @brief Create a new socket
    * @param port The port to listen on
    * @return A pointer to the socket or nullptr if an error occurred
    */
    static std::unique_ptr<UnicastConnection> Create(int port)
    {
        auto c = std::make_unique<UnicastConnection>();
        
        //auto g = std::make_unique<UnicastConnection>(nullptr);

        if (c->initialize(port))
        {
            return nullptr;
        }
        return c;
    };

    ~UnicastConnection()
    {
    };

    nl_sock *getSocket()
    {
        return sk.get();
    }

private:
    UnicastConnection(): sk(nl_socket_alloc(), &nl_socket_free)
    {
        if (!sk.get())
        {
            std::cerr << "Failed to allocate netlink socket: " << nl_geterror(errno) << "\n";
        }
    };

    int initialize(int port)
    {

        int ret = 0;
        nl_socket_set_local_port(sk.get(), port);

        // Connect the socket
        if (nl_connect(sk.get(), NETLINK_GENERIC) < 0)
        {
            ret = -1;
            std::cerr << "Failed to connect the netlink socket: " << nl_geterror(errno) << "\n";
        }
        return ret;
    };
     std::unique_ptr<nl_sock, decltype(&nl_socket_free)> sk;
};
