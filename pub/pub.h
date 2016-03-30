#ifndef __PUB_H__
#define __PUB_H__

#include <vector>
#include "BroadMessage.h"

namespace goni 
{
class pubImpl;

class pub
{
    public:
        pub();
        ~pub();

        void publish(BroadMessageSp msg);

    private:
        pubImpl* m_impl;
};

}

#endif
