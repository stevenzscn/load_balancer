#include "load_balancer.h"
#include <iostream>

using lb::backend;
using lb::lb_base;
using lb::lb_rr;

int main() {
    std::shared_ptr<backend> endpoint(new backend());
    endpoint->set_id(1);
    endpoint->set_name("test1");
    endpoint->set_host("192.168.1.1");
    endpoint->set_weight(1);
    endpoint->set_alive(true);

    std::shared_ptr<backend> ep2(new backend());
    ep2->set_id(2);
    ep2->set_name("test2");
    ep2->set_host("192.168.1.2");
    ep2->set_weight(1);
    ep2->set_alive(false);

    std::shared_ptr<backend> ep3(new backend());
    ep3->set_id(3);
    ep3->set_name("test3");
    ep3->set_host("192.168.1.3");
    ep3->set_weight(1);
    ep3->set_alive(true);

    std::shared_ptr<backend> ep4(new backend());
    ep4->set_id(4);
    ep4->set_name("test4");
    ep4->set_host("192.168.1.4");
    ep4->set_weight(1);
    ep4->set_alive(true);

    std::vector<std::shared_ptr<backend>> backends;
    backends.push_back(endpoint);
    backends.push_back(ep2);
    backends.push_back(ep3);
    backends.push_back(ep4);

    std::shared_ptr<lb_base> lb(new lb::lb_rr(backends));
    for (int i = 0; i < 50; ++i) {
        auto myep = lb->select();
        std::cout << "id: " << myep->id() << ", name: " << myep->name() << ", host: " << myep->host() << ", weight: " << myep->weight() << ", alive: " << myep->alive() << std::endl;
    }

   return 0;
}
