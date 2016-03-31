#ifndef __SUB_H__
#define __SUB_H__

#include <string>

#include "BroadMessage.h"
#include "BroadMessageFactory.h"

namespace goni 
{

class subImpl;
class subHandler
{
    public:
        virtual void handleMessage(BroadMessageSp msg) = 0;
};

class sub
{
    public:
        sub(BroadMessageFactorySp factory, subHandler* handler);
        ~sub();

        void subscribe(const char* target);
        
    private:
        subImpl* m_impl;
};

}
#endif
