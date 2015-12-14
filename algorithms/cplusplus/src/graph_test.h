#pragma once

#include "graph.h"

namespace UnitTest
{
    namespace GraphUnitTest
    {
        void testBFS()
        {
            Graph::Graph g(4);
            g.AddEdge(0, 1);
            g.AddEdge(0, 2);
            g.AddEdge(1, 2);
            g.AddEdge(2, 0);
            g.AddEdge(2, 3);
            g.AddEdge(3, 3);

            std::cout << "testBFS(): " << std::endl;
            g.BFS(0);
        }
        void test()
        {
            testBFS();
        }
    }
}