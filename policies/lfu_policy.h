#ifndef LFU_POLICY_H
#define LFU_POLICY_H

#include "eviction_policy.h"
#include <unordered_map>
#include <list>

template<typename Key>
class LFUPolicy : public EvictionPolicy<Key> {
private:
    std::unordered_map<Key, int> frequencyMap;
    std::unordered_map<int, std::list<Key>> frequencyListMap;
    std::unordered_map<Key, typename std::list<Key>::iterator> keyIterMap;
    int minFreq = 0;
public:
    void keyAccessed(const Key& key) override {
        int freq = frequencyMap[key];
        frequencyListMap[freq].erase(keyIterMap[key]);
        if (frequencyListMap[freq].empty() && freq == minFreq) {
            minFreq++;
        }
        frequencyMap[key]++;
        frequencyListMap[freq + 1].push_back(key);
        keyIterMap[key] = --frequencyListMap[freq + 1].end();
    }
    
    void keyAdded(const Key& key) override {
        frequencyMap[key] = 1;
        frequencyListMap[1].push_back(key);
        keyIterMap[key] = --frequencyListMap[1].end();
        minFreq = 1;
    }
    
    void keyRemoved(const Key& key) override {
        int freq = frequencyMap[key];
        frequencyListMap[freq].erase(keyIterMap[key]);
        if (frequencyListMap[freq].empty() && freq == minFreq) {
            minFreq++;
        }
        frequencyMap.erase(key);
        keyIterMap.erase(key);
    }
    
    Key evict() override {
        Key key = frequencyListMap[minFreq].front();
        frequencyListMap[minFreq].pop_front();
        if (frequencyListMap[minFreq].empty()) {
            minFreq++;
        }
        frequencyMap.erase(key);
        keyIterMap.erase(key);
        return key;
    }
};

#endif // LFU_POLICY_H
