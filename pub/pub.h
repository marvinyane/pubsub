#ifndef __PUB_H__
#define __PUB_H__

#include <vector>
#include "msg.h"

class pubImpl;

class pub
{
    public:
        pub();
        ~pub();

        void publish(MessageSp msg);

    private:
        pubImpl* m_impl;
};

#endif
