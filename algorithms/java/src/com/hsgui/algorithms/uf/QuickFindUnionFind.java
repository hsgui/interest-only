package com.hsgui.algorithms.uf;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-15
 * Time: 下午5:12
 * To change this template use File | Settings | File Templates.
 */
public class QuickFindUnionFind {

    private int[] id;
    private int n;
    private int count;

    public QuickFindUnionFind(int n){
        this.n = n;
        id = new int[n];
        count = n;
        for (int i = 0; i < n; i++){
            id[i] = i;
        }
    }

    public int find(int p){
        return id[p];
    }

    public boolean connected(int p, int q){
        return find(p) == find(q);
    }

    /**
     * union is time consuming. O(n)
     * @param p
     * @param q
     */
    public void union(int p, int q){
        if (connected(p, q)) return;
        int pid = id[p];
        int qid = id[q];
        for (int i = 0; i < n;i++){
            if (id[i] == pid) {
                id[i] = qid;
            }
        }
        count--;
    }

    public int count(){
        return count;
    }
}
