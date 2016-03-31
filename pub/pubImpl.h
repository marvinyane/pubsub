#ifndef __PUBIMPL_H__
#define __PUBIMPL_H__

#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <poll.h>

#include <vector>
#include <string>
#include <algorithm>
//#include <thread>
#include <pthread.h>

namespace goni 
{

class pubImpl
{
    public:
        pubImpl(const char* name)
          : m_serverFd(-1)
          , m_clients()
          , m_pid(-1)
          , m_running(true)
          , m_pubName(name)
        {
            m_serverFd = socket(AF_UNIX, SOCK_STREAM, 0);
            sockaddr_un addr;
            bzero(&addr, sizeof addr);
            addr.sun_family = AF_UNIX;
            strcpy(addr.sun_path, name);

            // delete file that going to bind
            unlink(name);

            int ret = bind(m_serverFd, (struct sockaddr*)&addr, sizeof addr);
            if (ret < 0)
            {
                perror("bind error:");
                return ;
            }

            listen(m_serverFd, 64);

            // start thread to listen
            //m_thread = std::thread(&pubImpl::run, this);
            pthread_create(&m_pid, NULL, pubImpl::thread_run, this);
        }

        ~pubImpl()
        {
            m_running = false;
            pthread_join(m_pid, NULL);
            close(m_serverFd);

            unlink("testPub1");

            for (auto it = m_clients.begin(); it != m_clients.end(); it++)
            {
                close(*it);
            }
        }

        void publish(const std::string& data)
        {
            for (auto it = m_clients.begin(); it != m_clients.end(); it++)
            {
               int len =write(*it, data.data(), data.length());
               printf("write len is %d - total length %d \n", len, (int)data.length());
            }

        }

        static void* thread_run(void* args)
        {
            pubImpl* m_impl = (pubImpl*)args;
            m_impl->run();

            return NULL;
        }

        void run()
        {
            printf("thread running....\n");
            while (m_running)
            {
                struct pollfd *fd;
                int count = m_clients.size() + 1;
                fd = (struct pollfd*)malloc(sizeof(struct pollfd) * count);
                bzero(fd, sizeof(struct pollfd) * count);

                fd[0].fd = m_serverFd;
                fd[0].events = POLLIN;

                // TODO: lock m_clients?
                for (int i = 1; i < count; i++)
                {
                    fd[i].fd = m_clients[i-1];
                    fd[i].events = POLLIN;
                }

                int ret = poll(fd, count, 500);
                if (ret > 0)
                {
                    printf("fd[0].revnts %d, pollin is %d\n", fd[0].revents, POLLIN);
                    if (fd[0].revents & POLLIN)
                    {
                        // connection come
                        sockaddr_un cli_addr;
                        socklen_t len = 0;
                        printf("start to accept...\n");
                        int fd = accept(m_serverFd, (struct sockaddr*)&cli_addr, &len);
                        printf("accpet result is %d \n", fd);
                        if (fd == -1)
                        {
                            perror("accpet connection failed:");
                            continue;
                        }

                        m_clients.push_back(fd);
                        printf("connection ok with fd : %d \n", fd);
                    }

                    for (int i = 1; i < count; i++)
                    {
                        if (fd[i].revents & POLLIN)
                        {
                            // socket event...
                            char buf[512];
                            bzero(buf, sizeof buf);
                            int ret = read(m_clients[i-1], buf, sizeof buf);
                            if (ret == 0) 
                            {
                                printf("socket %d disconnect.\n", fd[i].fd);
                                m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), fd[i].fd), m_clients.end());
                                close(fd[i].fd);
                            }
                        }
                    }
                }
            }
        }

    private:
        int m_serverFd;
        std::vector<int> m_clients;
        pthread_t       m_pid;
        bool        m_running;
        std::string m_pubName;
};

}

#endif
