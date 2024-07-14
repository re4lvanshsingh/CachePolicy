#ifndef LRU_POLICY_H
#define LRU_POLICY_H

#include "eviction_policy.h"
#include <list>
#include <unordered_map>

template<typename Key>
class LRUPolicy : public EvictionPolicy<Key> {
private:
    std::list<Key> order;
    std::unordered_map<Key, typename std::list<Key>::iterator> keyIterMap;
public:
    void keyAccessed(const Key& key) override {
        if (keyIterMap.find(key) != keyIterMap.end()) {
            order.erase(keyIterMap[key]);
            order.push_front(key);
            keyIterMap[key] = order.begin();
        }
    }
    
    void keyAdded(const Key& key) override {
        order.push_front(key);
        keyIterMap[key] = order.begin();
    }
    
    void keyRemoved(const Key& key) override {
        if (keyIterMap.find(key) != keyIterMap.end()) {
            order.erase(keyIterMap[key]);
            keyIterMap.erase(key);
        }
    }
    
    Key evict() override {
        Key key = order.back();
        order.pop_back();
        keyIterMap.erase(key);
        return key;
    }
};

#endif // LRU_POLICY_H
