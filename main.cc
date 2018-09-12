#include "load_balancer.h"
#include <iostream>

using lb::backend;
using lb::load_balancer;

int main() {
    std::shared_ptr<backend> endpoint(new backend());

    return 0;
}
