#include <stdio.h>
#include <string.h>

#include "BroadMessage.h"

namespace goni {

BroadMessage::BroadMessage(int id)
    : m_id (id)
    , m_data()
{
}

BroadMessage::BroadMessage(int id, char* buf, int len)
    : m_id (id)
    , m_data(buf, len)
{
}

BroadMessage::~BroadMessage()
{
}

const std::string& BroadMessage::getData()
{
    return m_data;
}

void BroadMessage::setData(char* buf, int len)
{
    m_data = std::string(buf, len);
}

}
