#include <iostream>
#include "policies/fifo_policy.h"
#include "policies/lru_policy.h"
#include "policies/lfu_policy.h"
#include "policies/lifo_policy.h"
#include "cache.h"

int main() {
    auto fifoPolicy = std::make_unique<FIFOPolicy<int>>();
    Cache<int, std::string> fifoCache(3, std::move(fifoPolicy));

    fifoCache.put(1, "one");
    fifoCache.put(2, "two");
    fifoCache.put(3, "three");

    std::string value;
    if (fifoCache.get(1, value)) {
        std::cout << "Get 1 (FIFO): " << value << std::endl;
    } else {
        std::cout << "Get 1 (FIFO): not found" << std::endl;
    }

    fifoCache.put(4, "four");

    if (fifoCache.get(2, value)) {
        std::cout << "Get 2 (FIFO): " << value << std::endl;
    } else {
        std::cout << "Get 2 (FIFO): not found" << std::endl;
    }

    auto lruPolicy = std::make_unique<LRUPolicy<int>>();
    Cache<int, std::string> lruCache(3, std::move(lruPolicy));

    lruCache.put(1, "one");
    lruCache.put(2, "two");
    lruCache.put(3, "three");

    if (lruCache.get(1, value)) {
        std::cout << "Get 1 (LRU): " << value << std::endl;
    } else {
        std::cout << "Get 1 (LRU): not found" << std::endl;
    }

    lruCache.put(4, "four");

    if (lruCache.get(2, value)) {
        std::cout << "Get 2 (LRU): " << value << std::endl;
    } else {
        std::cout << "Get 2 (LRU): not found" << std::endl;
    }

    auto lfuPolicy = std::make_unique<LFUPolicy<int>>();
    Cache<int, std::string> lfuCache(3, std::move(lfuPolicy));

    lfuCache.put(1, "one");
    lfuCache.put(2, "two");
    lfuCache.put(3, "three");

    if (lfuCache.get(1, value)) {
        std::cout << "Get 1 (LFU): " << value << std::endl;
    } else {
        std::cout << "Get 1 (LFU): not found" << std::endl;
    }

    lfuCache.put(4, "four");

    if (lfuCache.get(2, value)) {
        std::cout << "Get 2 (LFU): " << value << std::endl;
    } else {
        std::cout << "Get 2 (LFU): not found" << std::endl;
    }

    auto lifoPolicy = std::make_unique<LIFOPolicy<int>>();
    Cache<int, std::string> lifoCache(3, std::move(lifoPolicy));

    lifoCache.put(1, "one");
    lifoCache.put(2, "two");
    lifoCache.put(3, "three");

    if (lifoCache.get(1, value)) {
        std::cout << "Get 1 (LIFO): " << value << std::endl;
    } else {
        std::cout << "Get 1 (LIFO): not found" << std::endl;
    }

    lifoCache.put(4, "four");

    if (lifoCache.get(2, value)) {
        std::cout << "Get 2 (LIFO): " << value << std::endl;
    } else {
        std::cout << "Get 2 (LIFO): not found" << std::endl;
    }

    return 0;
}
