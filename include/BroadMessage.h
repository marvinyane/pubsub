#ifndef __BROADMESSAGE_H__
#define __BROADMESSAGE_H__

#include <memory>
#include <string>

namespace goni {

class BroadMessageImpl;

class BroadMessage
{
    public:
        BroadMessage(int id);
        BroadMessage(int id, char* buf, int len);

        virtual ~BroadMessage();

        int getId() 
        {
             return m_id;
        }

        void setData(char* buf, int len);

        const std::string& getData();

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
