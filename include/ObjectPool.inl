
template<typename T>
ObjectPool<T>::ObjectPool(size_t allocSizeBytes){
    m_allocSizeBytes = allocSizeBytes;
    AllocateNew();
}

template<typename T>
T* ObjectPool<T>::Get(){
    TLinked* t = nullptr;

    if (!m_freeObjectsHead){

        // Attempt to allocate some new objects.
        //
        AllocateNew();
    }

    if (m_freeObjectsHead){
        t = m_freeObjectsHead;
        m_freeObjectsHead = m_freeObjectsHead->m_next;

        m_numInUse++;
    }

    return &t->m_data;
}

template<typename T>
void ObjectPool<T>::Free(T* obj){
    // Get the TLinked back from the T.
    //
    TLinked* tl = (TLinked*)(obj - offsetof(TLinked, m_data));
    Insert(tl);
    m_numInUse--;
}

template<typename T>
bool ObjectPool<T>::AllocateNew(){

    size_t linkedSize = sizeof(TLinked);
    assert(linkedSize % 8 == 0);

    size_t allocSize = std::max(m_allocSizeBytes, linkedSize);
    size_t count = allocSize / linkedSize;

    TLinked* objects = (TLinked*) malloc(allocSize);
    if (objects){
        m_numAllocations++;
        m_count += count;

        for(size_t i = 0; i < count; i++){
            Insert(objects + i);
        }
    }

    return objects != nullptr;
}

template<typename T>
void ObjectPool<T>::Insert(TLinked* obj){
    obj->m_next = m_freeObjectsHead;
    m_freeObjectsHead = obj;
}


