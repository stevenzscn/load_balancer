#ifndef _LOAD_BALANCER_H_
#define _LOAD_BALANCER_H_

#include <string>
#include <inttypes.h>
#include <vector>
#include <memory>

namespace lb {

class backend {
public:
    backend() {}
    backend(const uint32_t id, const std::string &name, const std::string &host, const uint32_t weight, const bool alive)
        : id_(id), name_(name), host_(host), weight_(weight), alive_(alive) {}

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

class lb_base {
public:
    lb_base() {}
    lb_base(const std::vector<std::shared_ptr<backend>> backends) : backends_(backends) {}
    virtual ~lb_base() {}

    const std::shared_ptr<backend> select() {
        uint32_t idx = do_select();
        if (backends_.empty() || idx >= backends_.size()) {
            return nullptr;
        }

        if (!backends_.at(idx)->alive())
            return select();
        else
            return backends_.at(idx);
    }

protected:
    virtual uint32_t do_select() {
        return cur_idx;
    }
    
    uint32_t cur_idx = 0;
    std::vector<std::shared_ptr<backend>> backends_;
};

class lb_rr final : public lb_base {
public:
    lb_rr() {}
    lb_rr(const std::vector<std::shared_ptr<backend>> backends)
        : lb_base::lb_base(backends) {}
    ~lb_rr() {}

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
