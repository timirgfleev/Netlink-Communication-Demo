#include <cassert>
#include <Connection.h>
#include <ConfigConsts.h>

int main()
{
    //if something is wrong, it indicates that port cant be opened
    auto server_c = UnicastConnection::Create(SERVER_PORT);
    assert(server_c != nullptr);
    auto client_c = UnicastConnection::Create(CLIENT_PORT);
    assert(client_c != nullptr);
    return 0;
}