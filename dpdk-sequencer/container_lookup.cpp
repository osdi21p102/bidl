// build with g++ -std=c++11

#include <iostream>
#include <unordered_set>
#include <inttypes.h>
#define BILLION 1000000000L

int main()
{  
    std::unordered_set<uint64_t> set;
    int numKeys = 500000;
    uint64_t *keys = new uint64_t[numKeys];
    for (int i = 0; i < numKeys; i++) {
        keys[i] = rand();
        set.insert(keys[i]);
    }
    
    struct timespec start, end;
    int count = 100;
    uint64_t sum = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < numKeys; j++) {
            if (set.find(keys[j]) != set.end()) {
                sum++;
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    uint64_t diff;
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    delete[] keys;
    
    printf("sum is %" PRIu64 ", %d elements, lookup takes %ld nanoseconds\n", sum, numKeys, diff / (count * numKeys));
}
