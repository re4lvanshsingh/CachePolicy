#ifndef CACHE_H
#define CACHE_H

#include "policies/eviction_policy.h"
#include <unordered_map>
#include <memory>
#include <mutex>

template<typename Key, typename Value>
class Cache {
private:
    std::unordered_map<Key, Value> cache;
    std::unique_ptr<EvictionPolicy<Key>> evictionPolicy;
    size_t capacity;
    std::mutex mtx;

public:
    Cache(size_t cap, std::unique_ptr<EvictionPolicy<Key>> policy)
        : capacity(cap), evictionPolicy(std::move(policy)) {}

    void put(const Key& key, const Value& value) {
        std::lock_guard<std::mutex> lock(mtx);

        if (cache.size() >= capacity) {
            Key evictedKey = evictionPolicy->evict();
            cache.erase(evictedKey);
            evictionPolicy->keyRemoved(evictedKey);
        }

        cache[key] = value;
        evictionPolicy->keyAdded(key);
    }

    bool get(const Key& key, Value& value) {
        std::lock_guard<std::mutex> lock(mtx);

        auto it = cache.find(key);
        if (it != cache.end()) {
            evictionPolicy->keyAccessed(key);
            value = it->second;
            return true;
        }

        return false;
    }
};

#endif // CACHE_H
