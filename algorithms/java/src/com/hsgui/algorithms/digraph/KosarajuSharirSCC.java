package com.hsgui.algorithms.digraph;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-10-9
 * Time: 下午2:09
 * To change this template use File | Settings | File Templates.
 *
 * cite: http://algs4.cs.princeton.edu/42directed/KosarajuSharirSCC.java.html
 */
public class KosarajuSharirSCC {

    private boolean[] marked;
    private int[] id;
    private int count;
    public KosarajuSharirSCC(Digraph digraph){
        marked = new boolean[digraph.V()];
        id = new int[digraph.V()];
        count = 0;

        DepthFirstOrder order = new DepthFirstOrder(digraph);
        for (int v : order.reversePost()){
            if (!marked[v]){
                dfs(digraph, v);
                count++;
            }
        }
    }

    private void dfs(Digraph digraph, int v){
        marked[v] = true;
        id[v] = count;
        for (int w : digraph.adj(v)){
            if (!marked[w]){
                dfs(digraph, w);
            }
        }
    }

    public boolean stronglyConnected(int v, int w){
        return id[v] == id[w];
    }

    public int count(){
        return count;
    }
}
