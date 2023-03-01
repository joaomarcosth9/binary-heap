#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF 1123456789112

typedef struct s_pair {
    int first;
    long long second;
} pair;
pair def_pair = {0, 0};
pair neutral = {0, INF};
bool greater(pair* p1, pair* p2){
    return (p1->second > p2->second);
}
void swap(pair* x, pair* y){
    pair temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

typedef struct s_vector {
    int size, cap;
    pair def;
    pair* arr;
} vector;
vector vec(int sz, pair def_value){
    vector temp;
    temp.size = 0;
    temp.cap = 4;
    while(temp.cap < sz) temp.cap <<= 1;
    temp.cap <<= 1;
    temp.arr = (pair*)malloc(temp.cap*sizeof(pair));
    temp.def = def_value;
    for(int i = 0; i < temp.cap; i++) temp.arr[i] = temp.def;
    return temp;
}
void push_back(vector* v, pair a){
    if(v->size == (v->cap >> 1)){
        v->arr = (pair*)realloc(v->arr, 2*v->cap*sizeof(pair));
        v->cap <<= 1;
        for(int i = v->size; i < v->cap; i++){
            v->arr[i] = v->def;
        }
    }
    v->arr[v->size] = a;
    v->size++;
}
void pop_back(vector* v){
    if(v->size == 0) return;
    v->arr[v->size-1] = v->def;
    v->size--;
}

vector tree;
int le (int n) { return (n << 1)+1; }
int ri (int n) { return (n << 1)+2; }
int parent (int n) { return (n - 1|1)>>1; }

pair top(){ return tree.arr[0]; }

int size(){ return tree.size; }

void push(int u, long long val){
    pair temp = {u, val};
    push_back(&tree, temp);
    int pos = size()-1;
    while(pos != 0 && tree.arr[parent(pos)].second > tree.arr[pos].second){
        swap(&tree.arr[parent(pos)], &tree.arr[pos]);
        pos = parent(pos);
    }
}

void pop(){
    if(size() == 0) return;
    swap(&tree.arr[0], &tree.arr[size()-1]);
    pop_back(&tree);
    int pos = 0;
    while(tree.arr[pos].second > tree.arr[le(pos)].second ||
            tree.arr[pos].second > tree.arr[ri(pos)].second){
        if(tree.arr[ri(pos)].second > tree.arr[le(pos)].second){
            swap(&tree.arr[pos], &tree.arr[le(pos)]);
            pos = le(pos);
        } else {
            swap(&tree.arr[pos], &tree.arr[ri(pos)]);
            pos = ri(pos);
        }
    }
}

long long dis[100005];
long long from[100005];
vector adj[100005];

int main(){
    int n, m; scanf("%d %d", &n, &m);
    tree = vec(0, neutral);
    for(int i = 0; i <= n; i++){
        adj[i] = vec(0, def_pair);
        dis[i] = from[i] = INF;
    }
    for(int i = 0; i < m; i++){
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        pair temp1 = {v, w};
        pair temp2 = {u, w};
        push_back(&adj[u], temp1);
        push_back(&adj[v], temp2);
    }
    dis[1] = 0;
    push(1, 0);
    while(size() != 0){
        pair curr = top();
        int u = curr.first;
        long long w = curr.second;
        pop();
        for(int i = 0; i < adj[u].size; i++){
            pair* temp = &(adj[u].arr[i]);
            int v = temp->first;
            long long ww = temp->second;
            if(w+ww < dis[v]){
                from[v] = u;
                dis[v] = w+ww;
                push(v, w+ww);
            }
        }
    }
    long long arr[n+1];
    arr[0] = n;
    long long u = arr[0] = n;
    int id = 1;
    while(u != 1){
        arr[id++] = from[u];
        u = from[u];
        if(u == INF){
            printf("-1\n");
            return 0;
        }
    }
    for(int i = id-1; i >= 0; i--){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

