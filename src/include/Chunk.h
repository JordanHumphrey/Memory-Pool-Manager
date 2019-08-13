#ifndef CHUNK_H
#define CHUNK_H

#ifndef NULL
#define NULL 0;
#endif

class Chunk
{
private:
    unsigned int mDataSize;
    bool mFree;
public:
    Chunk();
    Chunk(const unsigned int dataSize);
    
    unsigned int getDataSize() const;
    void setDataSize(const unsigned int dataSize);
    
    bool isFree() const;
    void setFree(const bool free);
    
    void read(const void* src);
    void write(void* dst);
    
    Chunk *pPrev;
    Chunk *pNext;
};

const int CHUNK_OVERHEAD = sizeof(Chunk);

#endif /* CHUNK_H */

