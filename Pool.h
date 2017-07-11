#ifndef POOL_H
#define POOL_H
#include "Chunk.h"

template<unsigned int N> class Pool
{
private:
    unsigned int mFreeSize;
    unsigned char mData[N];
public:
    const unsigned int MINIMUM_FREE_BLOCK_SIZE = CHUNK_OVERHEAD;
    Pool()
    {
        mFreeSize = N - CHUNK_OVERHEAD;
        Chunk firstChunk(mFreeSize);
        firstChunk.write(mData);
    }
    
    void *allocate(const unsigned int size)
    {
        unsigned int requiredSize,freeDataSize;
        unsigned char *blockData;
        Chunk *block;
        
        requiredSize = size + CHUNK_OVERHEAD;
        block = reinterpret_cast<Chunk*>(mData);
        
        while(block && ((block->getDataSize() < requiredSize) || !block->isFree()))
        {
            block = block->pNext;
        }
        
        if(!block)
        {
            return NULL;
        }
        
        blockData = reinterpret_cast<unsigned char*>(block);
        
        freeDataSize = block->getDataSize() - requiredSize;
        
        if(freeDataSize > MINIMUM_FREE_BLOCK_SIZE)
        {
            Chunk freeBlock(freeDataSize),*freeBlockData;
            freeBlock.pNext = block->pNext;
            freeBlock.pPrev = block;
            freeBlockData = reinterpret_cast<Chunk*>(blockData + requiredSize);
            freeBlock.write(freeBlockData);
            if(freeBlock.pNext)
            {
                freeBlock.pNext->pPrev = reinterpret_cast<Chunk*>(freeBlockData);
            }
            block->pNext = freeBlockData;
            block->setDataSize(size);
        }
        mFreeSize -= block->getDataSize();
        block->setFree(false);
        return blockData + CHUNK_OVERHEAD;
    }
    
    void deallocate(void* pointer)
    {
        Chunk *block;
        
        if(!pointer)
        {
            return;
        }
        
        block = reinterpret_cast<Chunk*>(static_cast<unsigned char*>(pointer) - CHUNK_OVERHEAD);
        
        if(block->isFree())
        {
            return;
        }
        
        block->setFree(true);
        mFreeSize += block->getDataSize();
        
        if(block->pNext && block->pNext->isFree())
        {
            block->setDataSize(block->getDataSize() + block->pNext->getDataSize() + CHUNK_OVERHEAD);
            block->pNext = block->pNext->pNext;
            if(block->pNext)
            {
                block->pNext->pPrev = block;
            }
        }
        
        if(block->pPrev && block->pPrev->isFree())
        {
            block->pPrev->setDataSize(block->pPrev->getDataSize() + block->getDataSize() + CHUNK_OVERHEAD);
            if(block->pNext)
            {
                block->pNext->pPrev = block->pPrev;
            }
            if(block->pPrev)
            {
                block->pPrev->pNext = block->pNext;
            }
        }
    }
    
    unsigned int getFreeSize() const
    {
        return mFreeSize;
    }
    
    unsigned int getSize() const
    {
        return N;
    }
    
    unsigned int getMaxAllocationSize() const
    {
        unsigned int result = 0;
        Chunk headBlock(0);
        headBlock.read(mData);
        Chunk *pBlock = &headBlock;
        while(pBlock)
        {
            if(pBlock->isFree() && pBlock->getDataSize() > result)
            {
                result = pBlock->getDataSize();
            }
            pBlock = pBlock->pNext;
        }
        return result;
    }
};


#endif

