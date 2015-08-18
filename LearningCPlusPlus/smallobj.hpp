#pragma once

#include <iostream>
#include <cassert>
#include <vector>

#ifndef DEFAULT_CHUNK_SIZE
#define DEFAULT_CHUNK_SIZE 4096
#endif

#ifndef MAX_SMALL_OBJECT_SIZE
#define MAX_SMALL_OBJECT_SIZE 64
#endif

namespace ModernDeisgn {

	class FixedAllocator
	{
	public:
		class Chunk
		{
		private:
			friend class FixedAllocator;

			bool Init(std::size_t p_blockSize, unsigned char p_blocks);

			void * Allocate(std::size_t p_blockSize);

			void Deallocate(void * p_ptr, std::size_t p_blockSize);

			void Reset(std::size_t p_blockSize, unsigned char p_blocks);

			void Release();

			/*
			returns true if block at address p_ptr is inside this chunk
			*/
			inline bool HasBlock(void * p_ptr, std::size_t p_chunkLength) const
			{
				unsigned char* pc = static_cast<unsigned char*>(p_ptr);
				return (m_pData <= pc) && (pc < m_pData + p_chunkLength);
			}

			inline bool HasAvailable(unsigned char p_numBlocks) const
			{
				return (m_blocksAvailable == p_numBlocks);
			}

			inline bool IsFilled(void) const
			{
				return (0 == m_blocksAvailable);
			}

			/*
			pointer to array of allocated blocks
			*/
			unsigned char* m_pData;

			/*
			index of first empty block
			*/
			unsigned char m_firstAvailableBlock;

			/*
			count of empty blocks
			*/
			unsigned char m_blocksAvailable;
		};

		explicit FixedAllocator(std::size_t p_blockSize = 0);

		FixedAllocator(const FixedAllocator&);

		FixedAllocator& operator=(const FixedAllocator&);

		~FixedAllocator();

		void Swap(FixedAllocator& rhs);

		void * Allocate();

		void Deallocate(void * p_ptr);

		inline std::size_t BlockSize() const
		{
			return m_blockSize;
		}

		bool operator<(std::size_t p_rhs) const
		{
			return BlockSize() < p_rhs;
		}

	private:
		void DoDeallocate(void * p_ptr);

		Chunk* VicinityFind(void* p_ptr);

		typedef std::vector<Chunk> Chunks;

		typedef Chunks::iterator ChunkIter;

		typedef Chunks::const_iterator ChunkCIter;

		std::size_t m_blockSize;

		unsigned char m_numBlocks;

		/*
			Container of chunks
		*/
		Chunks m_chunks;

		/*
			pointer to chunk used for last or next allocation
		*/
		Chunk * m_allocateChunk;
		/*
			pointer to chunk used for last or next deallocation
		*/
		Chunk * m_deallocateChunk;

		mutable const FixedAllocator* m_previous;
		mutable const FixedAllocator* m_next;
	};


	bool FixedAllocator::Chunk::Init(std::size_t p_blockSize, unsigned char p_blocks)
	{
		assert(p_blocks > 0);
		assert(p_blockSize > 0);

		// Overflow check
		const std::size_t allocateSize = p_blocks * p_blockSize;
		assert(allocateSize / p_blockSize == p_blocks);

		m_pData = static_cast<unsigned char*>(::operator new (allocateSize));
		Reset(p_blockSize, p_blocks);

		return true;
	}

	void FixedAllocator::Chunk::Reset(std::size_t p_blockSize, unsigned char p_blocks)
	{
		assert(p_blockSize > 0);
		assert(p_blocks > 0);

		// Overflow check
		const std::size_t allocateSize = p_blocks * p_blockSize;
		assert(allocateSize / p_blockSize == p_blocks);

		m_firstAvailableBlock = 0;
		m_blocksAvailable = p_blocks;

		unsigned char index = 0;
		for (unsigned char* p = m_pData; index != p_blocks; p += p_blockSize)
		{
			*p = ++index;
		}
	}

	void FixedAllocator::Chunk::Release()
	{
		assert(nullptr != m_pData);
		::operator delete (m_pData);

		m_blocksAvailable = 0;
	}

	void * FixedAllocator::Chunk::Allocate(std::size_t p_blockSize)
	{
		if (IsFilled()) return nullptr;

		assert((m_firstAvailableBlock * p_blockSize) / p_blockSize == m_firstAvailableBlock);

		unsigned char* pAllocated = m_pData + (m_firstAvailableBlock * p_blockSize);
		m_firstAvailableBlock = *pAllocated;
		--m_blocksAvailable;

		return pAllocated;
	}

	void FixedAllocator::Chunk::Deallocate(void* p_ptr, std::size_t p_blockSize)
	{
		assert(p_ptr >= m_pData);

		unsigned char* toRelease = static_cast<unsigned char*>(p_ptr);
		// Alignment check
		assert((toRelease - m_pData) % p_blockSize == 0);
		unsigned char index = static_cast<unsigned char>((toRelease - m_pData) / p_blockSize);
		*toRelease = m_firstAvailableBlock;
		m_firstAvailableBlock = index;

		// Truncation check
		assert(m_firstAvailableBlock == (toRelease - m_pData) / p_blockSize);

		++m_blocksAvailable;
	}

	FixedAllocator::FixedAllocator(std::size_t p_blockSize)
		: m_blockSize (p_blockSize)
		, m_allocateChunk (nullptr)
		, m_deallocateChunk(nullptr)
	{
		assert(m_blockSize > 0);

		m_previous = this;
		m_next = this;

		std::size_t numBlocks = DEFAULT_CHUNK_SIZE / p_blockSize;
		if (numBlocks > UCHAR_MAX) numBlocks = UCHAR_MAX;
		else if (numBlocks == 0) numBlocks = 8 * p_blockSize;

		m_numBlocks = static_cast<unsigned char>(numBlocks);
		assert(m_numBlocks == numBlocks);
	}

	void * FixedAllocator::Allocate()
	{
		if (m_allocateChunk == nullptr || m_allocateChunk->m_blocksAvailable == 0)
		{
			ChunkIter i = m_chunks.begin();
			for (;; ++i)
			{
				if (i == m_chunks.end())
				{
					m_chunks.reserve(m_chunks.size() + 1);
					Chunk newChunk;
					newChunk.Init(m_blockSize, m_numBlocks);
					m_chunks.push_back(newChunk);
					m_allocateChunk = &m_chunks.back();
					m_deallocateChunk = &m_chunks.front();
					break;
				}
				if (i->m_blocksAvailable > 0)
				{
					m_allocateChunk = &*i;
					break;
				}
			}
		}

		assert(m_allocateChunk != nullptr);
		assert(m_allocateChunk->m_blocksAvailable > 0);

		return m_allocateChunk->Allocate(m_blockSize);
	}

	void FixedAllocator::Deallocate(void* p_ptr)
	{

	}
};