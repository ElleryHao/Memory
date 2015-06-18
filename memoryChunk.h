#ifndef   __MEMORYCHUNK__H_
#define   __MEMORYCHUNK__H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class memChunk;
struct memHeader
{
   int size;
   memChunk* pMemChunk;
};

struct memData
{
   memChunk* pNext;
};


struct memBlock
{
   memHeader head;
   memData  data;
};

class memChunk
{
public:
	memChunk(int count,int size);
	~memChunk();
	void* malloc();
	static void free(void* pMem);
	void free(memBlock* pBlock);
private:
	memBlock* createBlock();
	void delBlock(memBlock* pBlock);
	int m_count;
	int m_size;
	memBlock* m_memList;
};
#endif
