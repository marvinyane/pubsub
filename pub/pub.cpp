#include "pub.h"
#include "pubImpl.h"

pub::pub()
{
    m_impl = new pubImpl();
}

void pub::publish(MessageSp msg)
{
    m_impl->publish(msg->getData());
}

pub::~pub()
{
    delete m_impl;
}
