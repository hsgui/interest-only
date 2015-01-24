package com.hsgui.algorithms.graph;

import java.util.ArrayList;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-10-9
 * Time: 下午2:34
 * To change this template use File | Settings | File Templates.
 *
 * cite: @link(http://algs4.cs.princeton.edu/41undirected/Graph.java.html)
 */
public class Graph {

    private int V;
    private int E;
    private ArrayList<Integer>[] adj;

    public Graph(int v){
        this.V = v;
        this.E = 0;
        adj = (ArrayList<Integer>[])new ArrayList[v];
        for (int i = 0; i < v; i++){
            adj[i] = new ArrayList<Integer>();
        }
    }

    public int V(){
        return V;
    }

    public int E(){
        return E;
    }

    public void addEdge(int v, int w){
        adj[v].add(w);
        adj[w].add(v);
        E++;
    }

    public Iterable<Integer> adj(int v){
        return adj[v];
    }
}
