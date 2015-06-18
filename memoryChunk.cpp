#include "memoryChunk.h"
memChunk::memChunk(int count,int size)
{
    m_size=size;
	m_memList=NULL;
	memBlock* pBlock=NULL;
    for(int i=0; i<count; i++)
    {
        pBlock=createBlock();
		if(!pBlock)
	    {
	       continue;
	    }
		pBlock->data.pNext=m_memList;
		m_memList=pBlock;
		m_count++;
    }
}
memChunk::~memChunk()
{
    memBlock* temp=NULL;
    for(int i=0; i<m_count; i++)
    {
        temp=m_memList;
		m_memList=temp->data.pNext;
		delBlock(temp);
		m_count--;
    }
	m_size=0;
}

memBlock* memChunk::createBlock()
{
    memBlock* pBlock=(memBlock*)::malloc(m_size+sizeof(memHeader));
    if(!pBlock)
    {
        return NULL;
    }
    pBlock->head.pMemChunk=this;
    pBlock->head.size=m_size;
    pBlock->data.pNext=NULL;
}

void* memChunk::malloc()
{
    if(!m_memList)
    {
       m_memList=createBlock();
    }
    memBlock* pBlock=m_memList;
    m_memList=pBlock->data.pNext;
    m_count--;
    return (void *)&pBlock->data.pNext;
}

void memChunk::free(void * pMem)
{
    if(!pMem)
    {
       return;
    }
    memBlock* pBlock=(memBlock*)((char*)pMem-sizeof(memHeader));
    pBlock->head.pMemChunk->free(pBlock);
}

void memChunk::free(memBlock* pBlock)
{
    if(!pBlock)
    {
        return;
    }
    pBlock->data.pNext=m_memList;
    m_memList=pBlock;
    m_count++;
}

void memChunk::delBlock(memBlock * pBlock)
{
   pBlock->head.pMemChunk=NULL;
   pBlock->head.size=0;
   free(pBlock);
}
