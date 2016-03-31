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
        virtual void handleMessage(std::string data) = 0;
};

class sub : public subHandler
{
    public:
        sub(BroadMessageFactorySp factory);
        ~sub();

        void subscribe(const char* target);
        
        virtual void handleMessage(std::string data);

    private:
        subImpl* m_impl;
        BroadMessageFactorySp m_factory;
};

}
#endif
