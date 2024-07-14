#ifndef LIFO_POLICY_H
#define LIFO_POLICY_H

#include "eviction_policy.h"
#include <list>

template<typename Key>
class LIFOPolicy : public EvictionPolicy<Key> {
private:
    std::list<Key> order;
public:
    void keyAccessed(const Key& key) override {}
    
    void keyAdded(const Key& key) override {
        order.push_front(key);
    }
    
    void keyRemoved(const Key& key) override {
        order.remove(key);
    }
    
    Key evict() override {
        Key key = order.front();
        order.pop_front();
        return key;
    }
};

#endif // LIFO_POLICY_H
