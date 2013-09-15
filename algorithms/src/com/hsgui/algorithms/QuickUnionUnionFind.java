package com.hsgui.algorithms;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-15
 * Time: 下午5:21
 * To change this template use File | Settings | File Templates.
 */
public class QuickUnionUnionFind {

    private int[] id;
    private int n;
    private int count;

    public QuickUnionUnionFind(int n){
        this.n = n;
        id = new int[n];
        count = n;
        for (int i = 0; i < n; i++) id[i] = i;
    }

    public void union(int p, int q){
        int rp = id[p];
        int rq = id[q];
        if (rp == rq) return;
        id[p] = q;
        count--;
    }

    /**
     * the worst case: O(n)
     * @param p
     * @return
     */
    public int find(int p){
        while (p != id[p]){
            p = id[p];
        }
        return p;
    }

    public boolean connected(int p, int q){
        return find(p) == find(q);
    }

    public int count(){
        return count;
    }
}
