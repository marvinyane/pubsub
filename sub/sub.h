#ifndef __SUB_H__
#define __SUB_H__

#include <string>

class subImpl;

class subHandler
{
    public:
        virtual void handleMessage(std::string data) = 0;
};

class sub : public subHandler
{
    public:
        sub();
        ~sub();

        void subscribe(char* target);
        
        virtual void handleMessage(std::string data);

    private:
        subImpl* m_impl;
};

#endif
