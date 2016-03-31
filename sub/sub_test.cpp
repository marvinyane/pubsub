#include <string>

#include "sub.h"
#include "StcPubMessage.h"

using namespace goni;

class testSubMessageHandler : public subHandler
{
    public:
        virtual void handleMessage(BroadMessageSp msg)
        {
            if (msg->getId() == STC_BROADMESSAGE_TEST_1) 
            {
                StcBroadMessageTest* testMsg = (StcBroadMessageTest*)msg.get();
                printf("receive msg with name %s, age %d\n", testMsg->getName().c_str(), testMsg->getAge());
            }
        }
};

int main()
{
    testSubMessageHandler* handler = new testSubMessageHandler();
    sub s(std::make_shared<StcMessageFactory>(), handler);
    s.subscribe(STC_PUB_NAME);

    sleep(20);

    delete handler;

    return 0;
}
