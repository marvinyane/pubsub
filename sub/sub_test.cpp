#include "sub.h"
#include "StcPubMessage.h"

using namespace goni;

int main()
{
    sub s(std::make_shared<StcMessageFactory>());
    s.subscribe(STC_PUB_NAME);

    sleep(20);

    return 0;
}
