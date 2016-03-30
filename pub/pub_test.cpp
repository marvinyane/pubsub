#include "pub.h"
#include "StcBroadMessage.h"

using namespace goni;

int main()
{
    pub p;
    BroadMessageSp msg(new StcBroadMessageTest("marvin", 26));


    for(int i = 0; i < 3; i++)
    {
        p.publish(msg);
        sleep(10);
    }

    return 0;
}
