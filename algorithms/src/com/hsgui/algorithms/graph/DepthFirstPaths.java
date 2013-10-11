package com.hsgui.algorithms.graph;

import java.util.Stack;

/**
 * Created with IntelliJ IDEA.
 * User: v-shuhua
 * Date: 10/11/13
 * Time: 1:04 PM
 * To change this template use File | Settings | File Templates.
 */
public class DepthFirstPaths {
    private boolean[] marked;
    private int[] edgeTo;
    private final int s;

    public DepthFirstPaths(Graph graph, int s){
        this.s = s;
        marked = new boolean[graph.V()];
        edgeTo = new int[graph.V()];
        edgeTo[s] = s;      //for the start point, the parent node is itself.
        dfs(graph, s);
    }

    private void dfs(Graph graph, int s){
        marked[s] = true;
        for (int w : graph.adj(s)){
            if (!marked[w]){
                edgeTo[w] = s;
                dfs(graph, w);
            }
        }
    }

    public boolean hasPathTo(int w){
        return marked[w];
    }

    public Iterable<Integer> pathTo(int w){
        if (!hasPathTo(w)) return null;
        Stack<Integer> path = new Stack<Integer>();
        for (int v = w; v != s; v = edgeTo[v]){
            path.push(v);
        }
        path.push(s);
        return path;
    }
}
