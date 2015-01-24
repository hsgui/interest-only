package com.hsgui.algorithms.graph;

/**
 * Created with IntelliJ IDEA.
 * User: v-shuhua
 * Date: 10/11/13
 * Time: 12:58 PM
 * To change this template use File | Settings | File Templates.
 */
public class DepthFirstSearch {

    private boolean marked[];
    private int count;

    public DepthFirstSearch(Graph graph, int s){
        marked = new boolean[graph.V()];
        count = 0;
        dfs(graph, s);
    }

    private void dfs(Graph graph, int s){
        marked[s] = true;
        count++;
        for (int v : graph.adj(s)){
            if (!marked[v]){
                dfs(graph, v);
            }
        }
    }

    public boolean marked(int w){
        return marked[w];
    }

    public int count(){
        return count;
    }
}
