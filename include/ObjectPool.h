#pragma once
#include "main.h"

template<typename T>
class ObjectPool{
    public:
        ObjectPool(size_t allocSizeBytes = 4 * 1024);

        size_t m_count = 0;
        size_t m_numInUse = 0;
        size_t m_numAllocations = 0;

        T* Get();

        void Free(T* obj);

    private:
        struct TLinked {
            T m_data;
            TLinked* m_next = nullptr;
        };

        // We need each element to be 8 byte aligned, or else the data won't be
        // safe to access from multiple threads.
        //
        static_assert(alignof(TLinked) % 8 == 0);

        bool AllocateNew();
        void Insert(TLinked* obj);

        TLinked* m_freeObjectsHead = nullptr;
        size_t m_allocSizeBytes;
};


