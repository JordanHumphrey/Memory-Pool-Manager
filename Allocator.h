#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#ifndef POOL_H
#include "Pool.h"
#endif

template<class T, unsigned int N>
struct Allocator
{
    Pool<N> pool;
    typedef T value_type;
    Allocator() = default;
    template <class U,unsigned int M> Allocator(const Allocator<U,M>&) {}
    T* allocate(unsigned int n)
    {
        return static_cast<T*>(pool.allocate(n * sizeof(T)));
    }
    void deallocate(T* pointer,const unsigned int size = 0)
    {
        pool.deallocate(pointer);
    }
    template<class U>
    struct rebind { using other = Allocator<U, N>; }; 
};

template<class U, unsigned int M,class T,unsigned int N>
bool operator==(const Allocator<U,M>,const Allocator<T,N>)
{
    return M == N;
}

template<class U, unsigned int M,class T,unsigned int N>
bool operator!=(const Allocator<U,M>,const Allocator<T,N>)
{
    return M != N;
}

#endif /* ALLOCATOR_H */

