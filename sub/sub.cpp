#include <stdio.h>
#include <string>

#include "sub.h"
#include "subImpl.h"
#include "StcPubMessage.h"

namespace goni 
{
sub::sub(BroadMessageFactorySp factory)
    : m_impl(new subImpl(this))
    , m_factory(factory)
{
}

sub::~sub()
{
    delete m_impl;
}

void sub::subscribe(const char* target)
{
    m_impl->subscribe(target);
}

void sub::handleMessage(std::string data)
{
    BroadMessageSp msg = m_factory->createBroadMessage((char*)data.data(), data.length());

    int id = msg->getId();
    switch(id)
    {
        case STC_BROADMESSAGE_TEST_1:
        {
            StcBroadMessageTest* testMsg = (StcBroadMessageTest*)msg.get();
            printf("name is %s, age is %d\n", testMsg->getName().c_str(), testMsg->getAge());
            break;
        }
    }
}

}
