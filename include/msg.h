#ifndef __MSG_H__
#define __MSG_H__

#include <memory>
#include <string>

class Message
{
    public:
        Message(char* buf, int len)
            : m_data(std::string(buf, len))
        {
        }

        ~Message()
        {
        }

        const std::string& getData()
        {
            return m_data;
        }

    private:
        std::string m_data;
};

typedef std::shared_ptr<Message> MessageSp;

#endif
