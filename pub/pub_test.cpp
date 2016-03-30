#include "msg.h"
#include "pub.h"

int main()
{
    pub p;
    MessageSp msg(new Message("hello", 6));


    for(int i = 0; i < 3; i++)
    {
        p.publish(msg);
        sleep(10);
    }

    return 0;
}
