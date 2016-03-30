#ifndef __BROADMESSAGEFACTORY_H__
#define __BROADMESSAGEFACTORY_H__

#include "BroadMessage.h"

namespace goni {

class BroadMessageFactory
{
    public:
        virtual BroadMessageSp createBroadMessage(char* buf, int len) = 0;
};

typedef std::shared_ptr<BroadMessageFactory> BroadMessageFactorySp;
}

#endif
