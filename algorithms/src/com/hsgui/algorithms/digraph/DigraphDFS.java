package com.hsgui.algorithms.digraph;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-10-9
 * Time: 下午12:52
 * To change this template use File | Settings | File Templates.
 *
 * This could be used to find the dead-code and detect the infinite-loop.
 * 1. Reachability application.
 * 2. Path finding
 * 3. Topological sort
 * 4. Directed cycle detection.
 */
public class DigraphDFS {
    private boolean[] marked;

    public DigraphDFS(Digraph graph, Iterable<Integer> sources){
        marked = new boolean[graph.V()];
        for (int s : sources){
            dfs(graph, s);
        }
    }

    public DigraphDFS(Digraph graph, int s){
        marked = new boolean[graph.V()];
        dfs(graph, s);
    }

    private void dfs(Digraph graph, int s){
        marked[s] = true;
        for (int v : graph.adj(s)){
            if (!marked[v]){
                dfs(graph, v);
            }
        }
    }

    public boolean visited(int v){
        return marked[v];
    }
}
