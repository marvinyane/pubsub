#include "pub.h"
#include "pubImpl.h"
#include "StcPubMessage.h"

namespace goni 
{
pub::pub()
{
    m_impl = new pubImpl(STC_PUB_NAME);
}

void pub::publish(BroadMessageSp msg)
{
    m_impl->publish(msg->getData());
}

pub::~pub()
{
    delete m_impl;
}

}
