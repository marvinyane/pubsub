#include <stdio.h>
#include <string>

#include "sub.h"
#include "subImpl.h"
#include "StcPubMessage.h"

namespace goni 
{
sub::sub(BroadMessageFactorySp factory, subHandler* handler)
    : m_impl(new subImpl(factory, handler))
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

}
