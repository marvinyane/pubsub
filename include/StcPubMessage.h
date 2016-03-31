#ifndef __STCBROADMESSAGETEST1_H__
#define __STCBROADMESSAGETEST1_H__

#include <string.h>
#include <string>
#include <memory>

#include "BroadMessage.h"
#include "BroadMessageFactory.h"
#include "script/StcBroadMessageTest_generated.h"

#define STC_PUB_NAME            "testPub1"

#define STC_BROADMESSAGE_TEST_1         (0x0001)

namespace goni {

class StcBroadMessageTest : public BroadMessage
{
    public:
        // this is for writer
        StcBroadMessageTest(std::string name, int age)
              : BroadMessage(STC_BROADMESSAGE_TEST_1) 
              , m_name(name)
              , m_age(age)
        {
            pack();
        }

        // this is for reader!
        StcBroadMessageTest(int id, char* buf, int len)
            : BroadMessage(id, buf, len)
            , m_name()
            , m_age(0)
        {
            unpack();
        }

        ~StcBroadMessageTest()
        {
        }

        // to get?
        const std::string& getName()
        {
            return m_name;
        }

        int getAge()
        {
            return m_age;
        }

    private:
        void pack()
        {
            flatbuffers::FlatBufferBuilder builder;
            auto name = builder.CreateString(m_name);
            auto flat = BroadFlat::CreateStcBroadMessageTest(builder, m_id, name, m_age);
            builder.Finish(flat);


            char* buf = (char*) builder.GetBufferPointer();
            int len = builder.GetSize();

            setData(buf, len);
        }

        void unpack()
        {
            const std::string& data = getData();
            flatbuffers::Verifier verifier((const uint8_t*)data.data(), data.length());
            if (!verifier.VerifyBuffer<BroadFlat::StcBroadMessageTest>()) {
                return;
            }
            const BroadFlat::StcBroadMessageTest* obj = flatbuffers::GetRoot<BroadFlat::StcBroadMessageTest>(data.data());

            m_id = obj->id();
            m_name = obj->name()->c_str();
            m_age = obj->age();
        }

    private:
        std::string     m_name;
        int             m_age;

};

typedef std::shared_ptr<StcBroadMessageTest> StcBroadMessageTestSp;


class StcMessageFactory : public BroadMessageFactory
{
    public:
        virtual BroadMessageSp createBroadMessage(char* buf, int len)
        {
            const BroadFlat::StcBroadMessageHeader* msg = flatbuffers::GetRoot<BroadFlat::StcBroadMessageHeader>(buf);

            switch (msg->id())
            {
                case STC_BROADMESSAGE_TEST_1:
                    return std::make_shared<StcBroadMessageTest>(msg->id(), buf, len);

            }

            return NULL;
        }
};

}
#endif
