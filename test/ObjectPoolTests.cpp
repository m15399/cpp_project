#include "main.h"

TEST(ObjectPool, Basic){
    constexpr int numInts = 4;
    ObjectPool<int> pool(numInts * 16);

    ASSERT_EQ(pool.m_count, numInts);
    ASSERT_EQ(pool.m_numInUse, 0);
    ASSERT_EQ(pool.m_numAllocations, 1);

    // Get an integer. Should have numInUse == 1.
    //
    int* anInteger = pool.Get();
    ASSERT_EQ(pool.m_count, numInts);
    ASSERT_EQ(pool.m_numInUse, 1);
    ASSERT_EQ(pool.m_numAllocations, 1);

    pool.Free(anInteger);
    ASSERT_EQ(pool.m_numInUse, 0);

    // Get numInts more integers, shouldn't see any more allocations
    // (assuming numInts < default count / 2).
    //
    int* moreInts[numInts];
    for(int i = 0; i < numInts; i++){
        moreInts[i] = pool.Get();
        *moreInts[i] = numInts;
    }
    ASSERT_EQ(pool.m_count, numInts);
    ASSERT_EQ(pool.m_numInUse, numInts);
    ASSERT_EQ(pool.m_numAllocations, 1);
    for(int i = 0; i < numInts; i++){
        pool.Free(moreInts[i]);
    }

    // Get more integers and set them to some value. numAllocations should
    // increase.
    //
    constexpr int lots = 16;
    int* lotsOfIntegers[lots];
    for(int i = 0; i < lots; i++){
        lotsOfIntegers[i] = pool.Get();
        *lotsOfIntegers[i] = 42;
    }
    ASSERT_GTE(pool.m_count, lots);
    ASSERT_EQ(pool.m_numInUse, lots);
    ASSERT_GT(pool.m_numAllocations, 1);

    for(int i = 0; i < lots; i++){
        pool.Free(lotsOfIntegers[i]);
    }

    // We happen to know this works, but it might not work if the
    // implementation changes.
    //
    anInteger = pool.Get();
    ASSERT_EQ(*anInteger, 42);
}

TEST(ObjectPool, SmallObjects){
    ObjectPool<char> pool(1);

    // Get a few char's.
    //
    constexpr int numChars = 8;
    char* someChars[numChars];
    for(int i = 0; i < numChars; i++){
        someChars[i] = pool.Get();
    }

    // Each char object should be 8 byte aligned.
    //
    for(int i = 0; i < numChars; i++){
        ASSERT_EQ(reinterpret_cast<uintptr_t>(someChars[i]) % 8, 0);
        pool.Free(someChars[i]);
    }
}

using allocSignature = uint64_t* (*) (ObjectPool<uint64_t>* pool);
using freeSignature = void (*) (ObjectPool<uint64_t>* pool, uint64_t*);

uint64_t* NoopAlloc(ObjectPool<uint64_t>* pool){ return nullptr; }
void NoopFree(ObjectPool<uint64_t>* pool,uint64_t*){}

uint64_t* CppAlloc(ObjectPool<uint64_t>* pool){ return new uint64_t; }
void CppFree(ObjectPool<uint64_t>* pool,uint64_t* o){ delete o;}

uint64_t* PoolAlloc(ObjectPool<uint64_t>* pool){ return pool->Get(); }
void PoolFree(ObjectPool<uint64_t>* pool,uint64_t* o){ pool->Free(o); }



void Bench(int version){
    ObjectPool<uint64_t> pool;
    std::vector<uint64_t*> objects;
    objects.reserve(10000000);

    allocSignature allocFunc;
    freeSignature freeFunc;

    switch(version){
        case 0:
            allocFunc = NoopAlloc;
            freeFunc = NoopFree;
            break;
        case 1:
            allocFunc = CppAlloc;
            freeFunc = CppFree;
            break;
        case 2:
            allocFunc = PoolAlloc;
            freeFunc = PoolFree;
            break;

    }

    uint64_t startTime = GetMonotonicTimeInNanos();

    for(int i = 0; i < 10000000; i++){
        for(int j = 0; j < 2; j++){
            uint64_t* object = allocFunc(&pool);
           // *object = i;
            objects.push_back(object);
        }
        
        //int indexToRemove = RandomInt(0, objects.size() - 1);
        int indexToRemove = i;
        uint64_t* replace = objects[indexToRemove];
        freeFunc(&pool, replace);
        objects[indexToRemove] = allocFunc(&pool);
    }

    uint64_t endTime = GetMonotonicTimeInNanos();
    printf("Millis elapsed: %f\n", (endTime - startTime) / 1000000.f);
    if (version == 2)
        printf("  %lu allocations\n", pool.m_numAllocations);

   
}

TEST(ObjectPool, DISABLED_Benchmark){
    for(int i = 0; i < 3; i++){
        printf("\nVersion %d\n", i); 
        Bench(i);
        Bench(i);
        Bench(i);
    }
}

TEST(ObjectPool, DISABLED_Interactive){
    ObjectPool<bool> pool(1);

    std::vector<bool*> bools;

    while(true){
        printf("[");
        for(size_t i = 0; i < pool.m_numInUse; i++){
            printf("o");
        }
        for(size_t i = 0; i < pool.m_count - pool.m_numInUse; i++){
            printf("-");
        }
        printf("]\n");

        char c = getchar();
        if (c == 'd'){
            pool.Free(bools.back());
            bools.pop_back();
        } else if (c != '\n') {
            bools.push_back(pool.Get());
        }
    }
}


