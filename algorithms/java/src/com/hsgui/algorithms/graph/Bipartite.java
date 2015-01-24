package com.hsgui.algorithms.graph;

/**
 * Created with IntelliJ IDEA.
 * User: v-shuhua
 * Date: 10/11/13
 * Time: 1:36 PM
 * To change this template use File | Settings | File Templates.
 */
public class Bipartite {
    private boolean[] marked;
    private boolean[] color;
    private int[] edgeTo;
    private boolean isBipartite;

    public Bipartite(Graph graph){
        marked = new boolean[graph.V()];
        color = new boolean[graph.V()];
        edgeTo = new int[graph.V()];
        isBipartite = true;
        for (int v = 0; v < graph.V(); v++){
            if (!marked[v]){
                bfs(graph, v);
            }
        }
    }

    private void bfs(Graph graph, int s){
        marked[s] = true;
        for (int v : graph.adj(s)){
            if (!marked[v]){
                edgeTo[v] = s;
                color[v] = !color[s];
                bfs(graph, v);
            }else{
                if (color[v] == color[s]) {
                    isBipartite = false;
                    return;
                }
            }
        }
    }

    public boolean isBipartite(){
        return isBipartite;
    }
}
