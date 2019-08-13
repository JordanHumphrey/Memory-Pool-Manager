#include "Chunk.h"

#ifdef _GLIBCXX_CSTDLIB
void Chunk::read(const void* src)
{
    std::memcpy(this,src,CHUNK_OVERHEAD);
}
void Chunk::write(void* dst)
{
    std::memcpy(dst,this,CHUNK_OVERHEAD);
}
#else
void memcpy(void* dst,const void *src,const unsigned int n);

void Chunk::read(const void* src)
{
    memcpy(this,src,CHUNK_OVERHEAD);
}
void Chunk::write(void* dst)
{
    memcpy(dst,this,CHUNK_OVERHEAD);    
}

void memcpy(void* dst, const void* src, const unsigned int n)
{
    for(unsigned int offset = 0;offset < n;offset++)
    {
        static_cast<unsigned char*>(dst)[offset] = static_cast<const unsigned char*>(src)[offset];
    }
}
#endif

Chunk::Chunk()
{
    //Default
}

Chunk::Chunk(const unsigned int dataSize)
{
    mDataSize = dataSize;
    mFree = true;
    pPrev = NULL;
    pNext = NULL;
}

unsigned int Chunk::getDataSize() const
{
    return mDataSize;
}

void Chunk::setDataSize(const unsigned int dataSize)
{
    mDataSize = dataSize;
}

bool Chunk::isFree() const
{
    return mFree;
}

void Chunk::setFree(const bool free)
{
    mFree = free;
}