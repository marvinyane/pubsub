#include "msg.h"
#include "sub.h"

int main()
{
    sub s;
    s.subscribe("testPub1");

    sleep(20);

    return 0;
}
