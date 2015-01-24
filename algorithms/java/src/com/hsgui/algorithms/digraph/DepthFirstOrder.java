package com.hsgui.algorithms.digraph;

import java.util.Stack;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-10-9
 * Time: 下午1:26
 * To change this template use File | Settings | File Templates.
 */
public class DepthFirstOrder {
    private boolean[] marked;
    private Stack<Integer> reversePost;

    public DepthFirstOrder(Digraph graph){
        reversePost = new Stack<Integer>();
        marked = new boolean[graph.V()];
        for (int v = 0; v < graph.V(); v++){
            if (!marked[v]){
                dfs(graph, v);
            }
        }
    }

    public void dfs(Digraph graph, int v){
        marked[v] = true;
        for (int w : graph.adj(v)){
            if (!marked[w]){
                dfs(graph, v);
            }
        }
        reversePost.push(v);
    }

    public Iterable<Integer> reversePost(){
        return reversePost;
    }
}
