package com.hsgui.algorithms.graph;

/**
 * Created with IntelliJ IDEA.
 * User: v-shuhua
 * Date: 10/11/13
 * Time: 1:22 PM
 * To change this template use File | Settings | File Templates.
 */
public class CC {
    private boolean[] marked;
    private int[] id;
    private int[] size;
    private int count;

    public CC(Graph graph){
        marked = new boolean[graph.V()];
        id = new int[graph.V()];
        size = new int[graph.V()];

        for (int v = 0; v < graph.V(); v++){
            if (!marked[v]){
                dfs(graph, v);
                count++;
            }
        }
    }

    private void dfs(Graph graph, int s){
        marked[s] = true;
        id[s] = count;
        size[count]++;
        for (int v : graph.adj(s)){
            dfs(graph, v);
        }
    }

    public int count(){
        return count;
    }

    public boolean areConnected(int v, int w){
        return id[v] == id[w];
    }

    public int id(int w){
        return id[w];
    }
}
