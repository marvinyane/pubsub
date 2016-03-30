#include "sub.h"
#include "StcBroadMessage.h"

using namespace goni;

int main()
{
    sub s(std::make_shared<StcMessageFactory>());
    s.subscribe("testPub1");

    sleep(20);

    return 0;
}
