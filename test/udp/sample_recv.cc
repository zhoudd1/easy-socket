#include "udp_stream.h"
#include "udp_epoll_receiver.h"
#include "address.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

void test() {
    eys::udp_epoll_receiver epoller(200);

    eys::udp_receiver r1(eys::address("0.0.0.0", 1234), 1024);
    eys::udp_receiver r2(eys::address("0.0.0.0", 1234), 1024);

    epoller.reg(r1, eys::epoll_event_readable);
    epoller.reg(r2, eys::epoll_event_readable);

    int i = 100;
    while(i--) {
        size_t waiting_count = epoller.await();
        if (waiting_count == 0) {
            continue;
        }

        while(waiting_count--) {
            eys::udp_receiver &r = epoller.take();
            int a;
            eys::udp_visitor visitor = r.get_visitor();
            
            visitor >> a;
            std::cout << visitor.get_fd() << ':' << a << std::endl;
        }
    }
}

int main() {
    test();
    return 0;
}