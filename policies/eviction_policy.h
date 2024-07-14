#ifndef EVICTION_POLICY_H
#define EVICTION_POLICY_H

template<typename Key>
class EvictionPolicy {
public:
    virtual void keyAccessed(const Key& key) = 0;
    virtual void keyAdded(const Key& key) = 0;
    virtual void keyRemoved(const Key& key) = 0;
    virtual Key evict() = 0;
    virtual ~EvictionPolicy() = default;
};

#endif // EVICTION_POLICY_H
