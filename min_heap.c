#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifdef _WIN32
#define clear_screen system("cls")
#else
#define clear_screen system("clear")
#endif

const int neutral = INT_MAX;

typedef struct s_vector {
    int size, cap;
    int def;
    int* arr;
} vector;
vector vec(int sz, int def_value){
    vector temp;
    temp.size = 0;
    temp.cap = 1;
    while(temp.cap < sz) temp.cap <<= 1;
    temp.arr = (int*)malloc(temp.cap*sizeof(int));
    temp.def = def_value;
    for(int i = 0; i < sz; i++) temp.arr[i] = temp.def;
    return temp;
}
void push_back(vector* v, int a){
    if(v->size == v->cap){
        v->arr = (int*)realloc(v->arr, 2*v->cap*sizeof(int));
        v->cap <<= 1;
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
int le (int n) { return n << 1; }
int ri (int n) { return n << 1|1; }
int parent (int n) { return n >> 1; }
void swap(int* x, int* y);

int top(){ return tree.arr[1]; }

int size(){ return (tree.size-1 > 0 ? tree.size-1 : 0) ; }

void push(int val){
    push_back(&tree, val);
    int pos = size();
    while(parent(pos) != 0 && tree.arr[parent(pos)] > tree.arr[pos]){
        swap(&tree.arr[parent(pos)], &tree.arr[pos]);
        pos = parent(pos);
    }
}

void pop(){
    if(size() == 0) return;
    swap(&tree.arr[1], &tree.arr[size()]);
    pop_back(&tree);
    int pos = 1;
    while((le(pos) < tree.size && tree.arr[pos] > tree.arr[le(pos)]) ||
            (ri(pos) < tree.size && tree.arr[pos] > tree.arr[ri(pos)])){
        if(le(pos) < tree.size && ri(pos) < tree.size){
            if(tree.arr[ri(pos)] > tree.arr[le(pos)]){
                swap(&tree.arr[pos], &tree.arr[le(pos)]);
                pos = le(pos);
            } else {
                swap(&tree.arr[pos], &tree.arr[ri(pos)]);
                pos = ri(pos);
            }
        } else if (le(pos) < tree.size){
            swap(&tree.arr[pos], &tree.arr[le(pos)]);
            pos = le(pos);
        }
    }
}

void print_tree();
void placeholder();

int main(){
    clear_screen;
    tree = vec(2, neutral);
    push_back(&tree, tree.def);
    placeholder();
    while(1){
        int op;
        printf("(1) Insert\n");
        printf("(2) Get-Min\n");
        printf("(3) Extract-Min\n");
        printf("(4) Print tree\n");
        printf("(5) Exit\n");
        printf("Op: ");
        scanf("%d", &op);
        if( op == 1 ){
            clear_screen;
            placeholder();
            printf("Number to insert: ");
            int nu;
            scanf("%d", &nu);
            placeholder();
            if(1 || size() > 0){
                printf("Tree before insertion:\n");
                print_tree();
            }
            push(nu);
            placeholder();
            printf("Tree after insertion:\n");
            print_tree();
            placeholder();
        } else if ( op == 2 ){
            clear_screen;
            placeholder();
            if(size() == 0){
                printf("Empty tree!\n");
                placeholder();
                continue;
            }
            if(size() > 0){
                printf("Min: %d\n", top());
            } else {
                printf("Min: None\n");
            }
            placeholder();
        } else if ( op == 3 ){
            clear_screen;
            placeholder();
            if(size() == 0){
                printf("Empty tree!\n");
                placeholder();
                continue;
            }
            printf("Current min: %d\n\n", top());
            printf("Tree before removing:\n\n");
            print_tree();
            placeholder();
            pop();
            printf("Tree after removing:\n\n");
            print_tree();
            printf("\nNew min: %d\n", top());
            placeholder();
        } else if ( op == 4 ){
            clear_screen;
            placeholder();
            print_tree();
            placeholder();
        } else if ( op == 5 ){
            break;
        } else {
            clear_screen;
            placeholder();
            printf("Choose an option between [1, 5].\n");
            placeholder();
        }
    }
    return 0;
}

void print_tree(){
    int it = 1, idx = 0;
    int n = size();
    int ts = 1;
    while((ts << 1) <= n) ts <<= 1;
    int total = 1;
    for(int qt = 1; qt <= ts; qt <<= 1){
        for(int i = 0; i < qt; i++){
            if(total > n) printf("- ");
            else printf("%d ", tree.arr[total]);
            total++;
        }
        printf("\n");
    }
}

void swap(int* x, int* y){
    *(x) ^= *(y); *(y) ^= *(x); *(x) ^= *(y);
}

void placeholder(){ printf("\n-------------------------------------------\n\n"); }
