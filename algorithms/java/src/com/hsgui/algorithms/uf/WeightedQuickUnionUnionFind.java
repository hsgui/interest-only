package com.hsgui.algorithms.uf;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-15
 * Time: 下午5:27
 * To change this template use File | Settings | File Templates.
 */
public class WeightedQuickUnionUnionFind {

    private int[] id;
    private int[] sz;
    private int n;
    private int count;

    public WeightedQuickUnionUnionFind(int n){
        this.n = n;
        id = new int[n];
        sz = new int[n];
        for (int i = 0; i < n; i++){
            id[i] = i;
            sz[i] = 1;
        }
    }

    public void union(int p, int q){
        int rp = id[p];
        int rq = id[q];
        if (rp == rq) return;
        if (sz[p] < sz[q]){
            id[p] = q;
            sz[q] += sz[p];
        }else {
            id[q] = p;
            sz[p] += sz[q];
        }
        count--;
    }

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
