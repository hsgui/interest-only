package com.hsgui.algorithms.priorityqueue;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-10-28
 * Time: 下午3:28
 * To change this template use File | Settings | File Templates.
 */
public class MaxPQ<Key extends Comparable<Key>> {
    private Key[] pq;
    private int N;

    public MaxPQ(int initCapacity){
        pq = (Key[]) new Comparable[initCapacity + 1];
        N = 0;
    }

    public MaxPQ(){
        this(1);
    }

    public boolean isEmpty(){
        return N == 0;
    }

    public int size(){
        return  N;
    }

    public Key max(){
        if (!isEmpty()){
            return pq[1];
        }
        return null;
    }

    public void insert(Key x){
        // double size of array if necessary
        if (N >= pq.length - 1) resize(2 * pq.length);

        // add x, and percolate it up to maintain heap invariant
        pq[++N] = x;
        swim(N);
    }

    public Key delMax(){
        if (!isEmpty()){
            Key max = pq[1];
            exch(1, N--);
            sink(1);
            pq[N + 1] = null;
            if ((N > 0) && (N == (pq.length - 1) / 4)) resize(pq.length / 2);
            assert isMaxHeap();
            return max;
        }

        return null;
    }

    /**
     * there is a fast way to do this.
     * @param capacity
     */
    private void resize(int capacity) {
        assert capacity > N;
        Key[] temp = (Key[]) new Comparable[capacity];
        for (int i = 1; i <= N; i++) temp[i] = pq[i];
        pq = temp;
    }

    private void swim(int k){
        while (k > 1 && less(k/2, k)){
            exch(k/2, k);
            k = k/2;
        }
    }

    private void sink(int k) {
        while (2*k <= N) {
            int j = 2*k;
            if (j < N && less(j, j+1)) j++;
            if (!less(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

    private boolean isMaxHeap(){
        return isMaxHeap(1);
    }

    private boolean isMaxHeap(int k){
        if ( k > N) return true;
        int left = 2*k, right = 2*k + 1;
        if (left < N && less(k, left)) return false;
        if (right < N && less(k, right)) return false;
        return isMaxHeap(left) && isMaxHeap(right);
    }

    private boolean less(int i, int j) {
        return ((Comparable<Key>) pq[i]).compareTo(pq[j]) < 0;
    }

    private void exch(int i, int j) {
        Key swap = pq[i];
        pq[i] = pq[j];
        pq[j] = swap;
    }

    public static void main(String[] args){
        MaxPQ<Integer> maxPQ = new MaxPQ<Integer>(100);
        for (int i = 1; i < 50; i++){
            maxPQ.insert(i);
        }
        for (int i = 1; i < 50; i++){
            System.out.println("max value in the pq: " + maxPQ.delMax());
        }
    }
}
