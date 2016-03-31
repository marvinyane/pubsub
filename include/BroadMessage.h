#ifndef __BROADMESSAGE_H__
#define __BROADMESSAGE_H__

#include <memory>
#include <string>

namespace goni {

class BroadMessageImpl;

class BroadMessage
{
    public:
        BroadMessage(int id) 
          : m_id(id)
        {
        }

        BroadMessage(int id, char* buf, int len)
          : m_id(id)
          , m_data(buf, len)
        {
        }

        virtual ~BroadMessage() 
        {
        }

        int getId() 
        {
             return m_id;
        }

        void setData(char* buf, int len)
        {
            m_data = std::string(buf, len);
        }

        const std::string& getData()
        {
            return m_data;
        }

    protected:
        int m_id;

    private:
        virtual void pack() = 0;
        virtual void unpack() = 0;

    private:
        std::string m_data;
        BroadMessageImpl* m_impl;

};

typedef std::shared_ptr<BroadMessage> BroadMessageSp;

}

#endif
