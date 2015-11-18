#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <set>
#include <algorithm>

class Utils
{
public:
    template<typename T> 
    static bool equalVectorVector(const std::vector<std::vector<T>>& a, const std::vector<std::vector<T>>& b)
    {
        if (a.size() != b.size())
        {
            return false;
        }
        for (int i = 0; i < a.size(); i++)
        {
            if (!equal(a[i].begin(), a[i].end(), b[i].begin()))
            {
                return false;
            }
        }
        return true;
    }

    static uint64_t align(uint64_t size, uint64_t alignment)
    {
        if (0 == size)
        {
            return alignment;
        }
        // 0 - alignment = 2^64 - alignment
        return (size + alignment - 1) & (0 - alignment);
    }

    static size_t mergeOrderedList(const std::vector<uint64_t>& firstList, 
                                   const std::vector<uint64_t>& secondList, 
                                   std::vector<uint64_t>& result)
    {
        size_t count = 0;
        std::vector<uint64_t>::const_iterator it1 = firstList.begin();
        std::vector<uint64_t>::const_iterator it2 = secondList.begin();

        while (it1 != firstList.end() && it2 != secondList.end())
        {
            if ((*it1) == (*it2))
            {
                result.push_back(*it1);
                count++;
                it1++;
                it2++;
            }
            else if ((*it1) > (*it2))
            {
                result.push_back(*it2);
                count++;
                it2++;
            }
            else
            {
                result.push_back(*it1);
                count++;
                it1++;
            }
        }
        if (it1 == firstList.end())
        {
            count += secondList.end() - it2;
            result.insert(result.end(), it2, secondList.end());
        }
        else
        {
            count += firstList.end() - it1;
            result.insert(result.end(), it1, firstList.end());
        }
        return count;
    }

    static void removeDuplicatedElementFromSortedVector(std::vector<int>& p_idList)
    {
        p_idList.erase(std::unique(p_idList.begin(), p_idList.end()), p_idList.end());
    }

    struct MultipleLevelVector
    {
        int m_version;
        std::vector<int> m_items;
    };

    static void dedupItemFromMultipleVectors(std::vector<MultipleLevelVector>& p_levelVectors)
    {
        auto versionCompare = [](MultipleLevelVector& a, MultipleLevelVector& b)
        {
            return a.m_version > b.m_version;
        };

        std::sort(p_levelVectors.begin(), p_levelVectors.end(), versionCompare);

        std::set<int> foundIdSet;
        for (size_t versionIndex = 0; versionIndex < p_levelVectors.size(); versionIndex++)
        {
            std::vector<int>& itemList = p_levelVectors[versionIndex].m_items;
            std::vector<int>::iterator dedupIt = itemList.begin();
            std::vector<int>::iterator forwardIt = dedupIt;
            while (forwardIt != itemList.end())
            {
                if (foundIdSet.find(*forwardIt) == foundIdSet.end())
                {
                    foundIdSet.insert(*forwardIt);
                    *dedupIt = *forwardIt;
                    dedupIt++;
                }
                forwardIt++;
            }

            size_t count = forwardIt - dedupIt;
            std::cout << "erase " << count << " from version: " << p_levelVectors[versionIndex].m_version << std::endl;

            itemList.erase(dedupIt, forwardIt);
        }

        return ;
    }
};

#endif
