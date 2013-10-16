package com.hsgui.algorithms.graph;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

/**
 * Created with IntelliJ IDEA.
 * User: v-shuhua
 * Date: 10/11/13
 * Time: 1:11 PM
 * To change this template use File | Settings | File Templates.
 */
public class BreadthFirstPaths {
    private boolean[] marked;
    private int[] edgeTo;
    private int[] distTo;
    private final int s;

    public BreadthFirstPaths(Graph graph, int s){
        this.s = s;
        marked = new boolean[graph.V()];
        edgeTo = new int[graph.V()];
        distTo = new int[graph.V()];
        edgeTo[s] = s;
        bfs(graph, s);
    }

    private void bfs(Graph graph, int s){
        Queue<Integer> queue = new LinkedList<Integer>();
        marked[s] = true;
        queue.add(s);
        while (!queue.isEmpty()){
            int v = queue.poll();
            for (int w : graph.adj(v)){
                if (!marked[w]){
                    marked[w] = true;
                    edgeTo[w] = v;
                    distTo[w] = distTo[v] + 1;
                    queue.add(w);
                }
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
