#ifndef __SUBIMPL_H__
#define __SUBIMPL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <poll.h>
#include <pthread.h>

#include "sub.h"

class subImpl
{
    public:
        subImpl(subHandler* handler)
            : m_fd(-1)
            , m_pid(-1)
            , m_handler(handler)
        {
            m_fd = socket(AF_UNIX, SOCK_STREAM, 0);
        }

        bool subscribe(char* target)
        {
            struct sockaddr_un addr;
            bzero(&addr, sizeof addr);

            addr.sun_family = AF_UNIX;
            strcpy(addr.sun_path, "testPub1");

            int ret = connect(m_fd, (struct sockaddr*)&addr, sizeof addr);
            if (ret < 0)
            {
                perror("sub sonnect failed : ");
                return false;
            }

            pthread_create(&m_pid, NULL, subImpl::thread_run, this);

            return true;
        }

        ~subImpl()
        {
            if (m_fd)
            {
                close(m_fd);
            }
        }


        static void* thread_run(void* args)
        {
            subImpl* impl = (subImpl*)args;
            impl->run();
        }

        void run()
        {
            printf("sub thread running....\n");
            while (1)
            {
                struct pollfd fd[1];
                fd[0].fd = m_fd;
                fd[0].events = POLLIN;

                int ret = poll(fd, 1, -1);
                
                if (ret > 0)
                {
                    if (fd[0].revents & POLLIN)
                    {
                        char buf[512];
                        bzero(buf, sizeof buf);
                        int len = read(fd[0].fd, buf, sizeof buf);
                        if (len > 0) 
                        {
                            m_handler->handleMessage(std::string(buf, len));
                        }
                        else 
                        {
                            perror("read failed:");
                        }
                    }
                }
            }
        }


    private:
        int m_fd;
        pthread_t m_pid;
        subHandler* m_handler;
};


#endif