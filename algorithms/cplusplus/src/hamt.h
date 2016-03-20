#pragma once

#include <iostream>
#include <assert.h>

using namespace std;

namespace algorithms {

    // http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
    // also known as SWAR (SIMD Within A Register) algorithm
    // http://www.playingwithpointers.com/swar.html
    // http://stackoverflow.com/questions/22081738/how-variable-precision-swar-algorithm-works
    inline unsigned int CountSetBits(unsigned int value)
    {
        value -= (value >> 1) & 0x55555555;
        value = (value & 0x33333333) + ((value >> 2) & 0x33333333);
        return ((value + (value >> 4) & 0x0F0F0F0F) * 0x01010101) >> 24;
    }

    // https://github.com/sile/cc-hamt/blob/master/include/hamt/map.hh
    
    const unsigned char c_perHAMTNodeBitLength = 5;

    const unsigned GOLDEN_RATIO_PRIME = 0x9e370001; //(2^31) + (2^29) - (2^25) + (2^22) - (2^19) - (2^16) + 1;

    unsigned hash(unsigned key, unsigned n) { return key * GOLDEN_RATIO_PRIME; }
    unsigned hash(int key, unsigned n) { return hash(static_cast<unsigned>(key), n); }
    unsigned hash(long key, unsigned n) { return hash(static_cast<unsigned>(key), n); }
    unsigned hash(const char* key, unsigned n) { return hash(reinterpret_cast<long>(key), n); }

    // universal hashing
    unsigned hash(const std::string& key) {
        unsigned a = 31415, b = 27183;
        unsigned h = 0;
        for (const char* c = key.c_str(); *c != 0; ++c, a *= b)
        {
            h = (a * h + (*c));
        }
        return h;
    }

    unsigned hash(const std::string& p_key, unsigned p_level)
    {
        unsigned a = 31415, b = 27183;
        unsigned h = 0;
        for (const char* c = p_key.c_str(); *c != 0; ++c, a *= b)
        {
            h = (a * h * p_level + (*c));
        }
        return h;
    }

    template<class Key>
    class hash_functor
    {
    public:
        hash_functor() {}

        unsigned operator()(const Key& p_key, unsigned n) const
        {
            return hash(p_key, n);
        }
    };

    template<class T>
    inline bool equal(const T& k1, const T& k2) {
        return k1 == k2;
    }

    template<class Key>
    class equal_functor {
    public:
        equal_functor() {}

        bool operator()(const Key& k1, const Key& k2) const {
            return equal(k1, k2);
        }
    };

    template<class Key, class Value>
    struct HAMTLeaf
    {
        HAMTLeaf(const Key& p_key, const Value& p_value)
            : m_key(p_key)
            , m_value(p_value)
        {}

        Key m_key;
        Value m_value;
    };

    typedef unsigned bitmap_t;
    typedef unsigned hashcode_t;

    template<class HAMTLeaf>
    class HAMTNode
    {
    public:
        union HAMTEntry
        {
            HAMTNode* m_subNode;
            HAMTLeaf* m_leaf;

            // if ptrval & 1 == 1, m_subNode is valid;
            // otherwise, m_leaf is valid;
            // if m_leaf is null, it's null entry.
            unsigned ptrval;

            bool isNode() const
            {
                return ptrval & 1;
            }

            bool isLeaf() const
            {
                return isNode() == false;
            }

            bool isNull() const
            {
                return m_leaf == nullptr;
            }

            static HAMTEntry fromNode(HAMTNode* p_node)
            {
                HAMTEntry entry;
                entry.m_subNode = p_node;
                entry.ptrval++;

                return entry;
            }

            HAMTNode* toNode()
            {
                HAMTEntry entry = *this;
                entry.ptrval--;
                return entry.m_subNode;
            }

            static HAMTEntry fromLeaf(HAMTLeaf* p_leaf)
            {
                HAMTEntry entry;
                entry.m_leaf = p_leaf;
                return entry;
            }

            HAMTLeaf* toLeaf() const
            {
                return m_leaf;
            }

            static HAMTEntry null()
            {
                return fromLeaf(nullptr);
            }
        };

        bool isValidEntry(unsigned p_index)
        {
            return (m_bitmap >> p_index) & 1;
        }

        unsigned entryIndex(unsigned p_index)
        {
            return CountSetBits(((1 << p_index) - 1) & m_bitmap);
        }

        HAMTEntry* getEntryOrSet(unsigned p_index)
        {
            if (!isValidEntry(p_index))
            {
                setEntry(p_index, HAMTEntry::null());
            }

            return &(m_children[entryIndex(p_index)]);
        }

        void setEntry(unsigned p_index, HAMTEntry p_entry)
        {
            const unsigned index = entryIndex(p_index);
            m_children = reinterpret_cast<HAMTEntry*>(realloc(m_children, sizeof(HAMTEntry) * (m_entriesCount + 1)));

            for (unsigned i = m_entriesCount; i > index; --i)
            {
                m_children[i] = m_children[i - 1];
            }

            m_children[index] = p_entry;
            m_bitmap |= (1 << p_index);
            ++m_entriesCount;
        }

        HAMTEntry getEntry(unsigned p_index)
        {
            if (isValidEntry(p_index) == false)
            {
                return HAMTEntry::null();
            }
            return m_children[entryIndex(p_index)];
        }

    private:
        bitmap_t m_bitmap;
        HAMTEntry* m_children;
        unsigned char m_entriesCount;
    };

    template<class Key, class Hash>
    class ArcStream
    {
    public:
        ArcStream(const Key& p_key)
            : m_key(p_key)
            , m_rehashCount (0)
            , m_hashCode(m_hash(m_key, m_rehashCount))
            , m_currentBitPosition(0)
        {}

        ArcStream(const Key& p_key, const ArcStream& p_other)
            : m_key(p_key)
            , m_rehashCount(p_other.m_rehashCount)
            , m_hashCode(m_hash(m_key, m_rehashCount))
            , m_currentBitPosition(p_other.m_currentBitPosition)
        {}

        unsigned read()
        {
            return readNext(c_perHAMTNodeBitLength);
        }

        unsigned readNext(unsigned p_nextBitCount)
        {
            if (m_currentBitPosition > sizeof(hashcode_t) * 8)
            {
                ++m_rehashCount;
                m_hashCode = hash(m_key, m_rehashCount);
                m_currentBitPosition = 0;
            }

            unsigned mask = (1 << p_nextBitCount) - 1;
            unsigned arc = (m_hashCode >> m_currentBitPosition) & mask;
            m_currentBitPosition += p_nextBitCount;

            return arc;
        }

    private:
        const Key& m_key;
        uint32_t m_rehashCount;
        hashcode_t m_hashCode;
        unsigned m_currentBitPosition;

        Hash m_hash;
    };

    template<class Key, class Value,
             class Hash = hash_functor<Key>,
             class Equal = equal_functor<Key>>
    class HAMT
    {
        typedef ArcStream<Key, Hash> arcstream_t;
        typedef HAMTLeaf<Key, Value> leaf_t;
        typedef HAMTNode<leaf_t> node_t;
        typedef typename node_t::HAMTEntry entry_t;

    public:
        HAMT()
            : m_rootEntries(nullptr)
            , m_rootBitLength(3)
            , m_entriesSize(1 << m_rootBitLength)
            , m_entriesCount(0)
        {
            const unsigned initSize = m_entriesSize;
            m_rootEntries = new entry_t[initSize];
            for (unsigned i = 0; i < initSize; ++i)
            {
                m_rootEntries[i] = entry_t::null();
            }
        }

        ~HAMT()
        {
            delete[] m_rootEntries;
        }

        void set(const Key& p_key, const Value& p_value)
        {
            arcstream_t in(p_key);
            entry_t* place = findAndCreateNewIfNotFound(in);
            if (place->isNull())
            {
                *place = entry_t::fromLeaf(new leaf_t(p_key, p_value));
            }
            else
            {
                leaf_t* entry = place->toLeaf();
                if (equal(p_key, entry->m_key))
                {
                    entry->m_value = p_value;
                    return;
                }
                else
                {
                    return;
                }
            }
            ++m_entriesCount;
        }

        Value* find(const Key& p_key) const
        {
            arcstream_t in(p_key);
            entry_t entry = findInternal(in);
            if (entry.isNull() || (s_equal(p_key, entry.toLeaf()->m_key) == false))
            {
                return nullptr;
            }

            return &(entry.toLeaf()->m_value);
        }

    private:
        entry_t* findAndCreateNewIfNotFound(arcstream_t& p_in) const
        {
            entry_t* place;
            unsigned arc = p_in.readNext(m_rootBitLength);

            place = &m_rootEntries[arc];
            while (!(place->isNull() || place->isLeaf()))
            {
                arc = p_in.read();
                place = place->toNode()->getEntryOrSet(arc);
            }

            return place;
        }

        entry_t findInternal(arcstream_t& p_in) const
        {
            entry_t place;
            unsigned arc = p_in.readNext(m_rootBitLength);
            place = m_rootEntries[arc];
            while (!(place.isNull() || place.isLeaf()))
            {
                arc = p_in.read();
                place = place.toNode()->getEntry(arc);
            }

            return place;
        }
    private:
        entry_t* m_rootEntries;

        unsigned m_rootBitLength;
        unsigned m_entriesCount;
        unsigned m_entriesSize;

        Equal s_equal;
    };
}