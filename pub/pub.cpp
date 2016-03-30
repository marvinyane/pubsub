#include "pub.h"
#include "pubImpl.h"

namespace goni 
{
pub::pub()
{
    m_impl = new pubImpl();
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
