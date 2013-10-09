package com.hsgui.algorithms.digraph;

import java.util.ArrayList;
import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-10-9
 * Time: 下午12:25
 * To change this template use File | Settings | File Templates.
 */
public class Digraph {
    private final int V;
    private int E;
    private final ArrayList<Integer>[] adj;

    public Digraph(int v){
        this.V = v;
        this.E = 0;
        adj = (ArrayList<Integer>[])new ArrayList[v];
        for (int i = 0; i < v; i++){
            adj[i] = new ArrayList<Integer>();
        }
    }

    public void addEdge(int v, int w){
        adj[v].add(w);
        E++;
    }

    public Digraph reverse(){
        Digraph r = new Digraph(V);
        for (int v = 0; v < V; v++){
            for (int w : adj(v)){
                r.addEdge(w, v);
            }
        }
        return r;
    }

    public Iterable<Integer> adj(int v){
        return adj[v];
    }

    public int E(){
        return E;
    }

    public int V(){
        return V;
    }
}
