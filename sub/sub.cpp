#include <stdio.h>

#include "sub.h"
#include "subImpl.h"

sub::sub()
{
    m_impl = new subImpl(this);
}

sub::~sub()
{
    delete m_impl;
}

void sub::subscribe(char* target)
{
    m_impl->subscribe(target);
}

void sub::handleMessage(std::string data)
{
    // handle message
    printf("sub receive : %s \n", data.c_str());
}
