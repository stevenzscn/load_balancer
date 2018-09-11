#ifndef _LOAD_BALANCER_H_
#define _LOAD_BALANCER_H_

#include <string>
#include <inttypes.h>
#include <vector>

namespace load_balancer {

class backend {
public:
    uint32_t id() const { return id_; }
    void set_id(const uint32_t id) { id_ = id; }

    std::string name() const { return name_; }
    void set_name(const std::string &name) { name_ = name; }

    std::string host() const { return host_; }
    void set_host(const std::string &host) { host_ = host; }

    uint32_t weight() const { return weight_; }
    void set_weight(const uint32_t weight) { weight_ = weight; }

    bool alive() const { return alive_; }
    void set_alive(const bool alive) { alive_ = alive; }

private:
    uint32_t id_ = 0;
    std::string name_;
    std::string host_;
    uint32_t weight_ = 1;
    bool alive_ = true;
};

class load_balancer {
public:
    load_balancer() {}
    virtual ~load_balancer() {}

    const backend* select() {
        if (backends_.empty() || do_select() >= backends_.size()) {
            return nullptr;
        }

        return backends_.at(do_select());
    }

protected:
    virtual uint32_t do_select() {
        return cur_idx;
    }
    
    uint32_t cur_idx = 0;
    std::vector<backend*> backends_;
};

class lb_rr final : public load_balancer {
protected:
    uint32_t do_select() {
        if (cur_idx >= backends_.size()) {
            cur_idx = 0;
        }
        return cur_idx++;
    }
};

};
#endif
