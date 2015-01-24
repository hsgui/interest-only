package com.hsgui.algorithms.uf;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-15
 * Time: 下午5:34
 * To change this template use File | Settings | File Templates.
 */
public class QuickUnionPathCompressionUnionFind {
    private int[] id;
    private int n;
    private int count;

    public QuickUnionPathCompressionUnionFind(int n){
        this.n = n;
        id = new int[n];
        for (int i = 0; i < n; i++){
            id[i] = i;
        }
    }

    public void union(int p, int q){
        int rp = id[p];
        int rq = id[q];
        if (rp == rq) return;
        id[p] = q;
        count--;
    }

    public int find(int p){
        int root = p;
        while (root != id[root])
            root = id[root];
        while (p != root) {
            int newp = id[p];
            id[p] = root;
            p = newp;
        }
        return root;
    }

    public boolean connected(int p, int q){
        return find(p) == find(q);
    }

    public int count(){
        return count;
    }
}
