#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <cassert>

namespace Graph {

    struct DefaultGraphVisitor
    {
        void operator()(int p_visitingNode)
        {
            std::cout << p_visitingNode << std::endl;
        }
    };

    class Graph
    {
    public:
        Graph(size_t p_verticesCount);
        void AddEdge(int p_node1, int p_node2);

        template<typename Visitor = DefaultGraphVisitor>
        void BFS(int p_startNode, Visitor p_visitor = Visitor());

    private:
        size_t m_verticesCount;
        std::unique_ptr<std::list<int>[]> m_adj;
    };

    Graph::Graph(size_t p_verticesCount)
        : m_verticesCount(p_verticesCount)
    {
        m_adj = std::make_unique<std::list<int>[]>(m_verticesCount);
    }

    void Graph::AddEdge(int p_node1, int p_node2)
    {
        assert((size_t)p_node1 < m_verticesCount);
        assert((size_t)p_node2 < m_verticesCount);

        m_adj[p_node1].push_back(p_node2);
    }

    template<typename Visitor>
    void Graph::BFS(int p_startNode, Visitor p_visitor)
    {
        assert((size_t)p_startNode < m_verticesCount);

        std::vector<bool> isSeen;
        isSeen.reserve(m_verticesCount);
        isSeen.assign(m_verticesCount, false);

        std::list<int> seenNotVisited;
        seenNotVisited.push_back(p_startNode);
        isSeen[p_startNode] = true;

        while (!seenNotVisited.empty())
        {
            int visitingNode = seenNotVisited.front();

            p_visitor(visitingNode);

            seenNotVisited.pop_front();
            for (auto i = m_adj[visitingNode].begin(); i != m_adj[visitingNode].end(); ++i)
            {
                if (!isSeen[*i])
                {
                    seenNotVisited.push_back(*i);
                    isSeen[*i] = true;
                }
            }
        }
    }
}
