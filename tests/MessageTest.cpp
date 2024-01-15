#include <cassert>
#include <StringMessage.h>

int main()
{
    auto m = StringMessage("TestStr");
    assert(m.is_ok());
    return 0;
}