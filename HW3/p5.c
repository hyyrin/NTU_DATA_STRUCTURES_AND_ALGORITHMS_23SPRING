#include<stdio.h>
#include<stdlib.h>
int ReadInt(int *num){
    char c, negative;
    while ((c = getchar()) < '-')
    {
        if(c == EOF)
        {
            return 0;
        }
    }
    *num = c - '0';
    while ((c = getchar()) >= '0')
    {
        *num = (*num << 3) + (*num << 1) + c - '0';
    }
    return 1;
}
typedef struct {
    int *parent;
    int size;
} DisjointSet;

void init(DisjointSet *set, int size) {
    set->parent = (int *)malloc(size * sizeof(int));
    set->size = size;
    for (int i = 0; i < size; i++)
        set->parent[i] = i;
}

int find(DisjointSet *set, int element) {
    if (set->parent[element] != element)
        set->parent[element] = find(set, set->parent[element]);
    return set->parent[element];
}

void unionSet(DisjointSet *set, int element1, int element2) {
    int root1 = find(set, element1);
    int root2 = find(set, element2);
    if (root1 != root2)
        set->parent[root1] = root2;
}
void unionSet1(DisjointSet *set, int element1, int element2) {
    int root1 = find(set, element1);
    int root2 = find(set, element2);
    if (root1 != root2)
        set->parent[root2] = root1;
}
struct MinHeap {
    int *health;
    int *index;
    int *attack;
    int *count;
    int size;
};
void createMinHeap(struct MinHeap *minHeap) {
    minHeap->health = (int *)malloc(sizeof(int) * 2);
    minHeap->count = (int *)malloc(sizeof(int) * 2);
    minHeap->index = (int *)malloc(sizeof(int) * 2);
    minHeap->attack = (int *)malloc(sizeof(int) * 2);
    minHeap->size = 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct MinHeap *minHeap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < minHeap->size && minHeap->health[left] < minHeap->health[smallest]) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->health[right] < minHeap->health[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&minHeap->health[i], &minHeap->health[smallest]);
        swap(&minHeap->attack[i], &minHeap->attack[smallest]);
        swap(&minHeap->count[i], &minHeap->count[smallest]);
        swap(&minHeap->index[i], &minHeap->index[smallest]);
        minHeapify(minHeap, smallest);
    }
}

void buildMinHeap(struct MinHeap *minHeap) {
    for (int i = minHeap->size / 2 - 1; i >= 0; i--) {
        minHeapify(minHeap, i);
    }
}

void insert(struct MinHeap *minHeap, int health, int attack, int index, int count) {
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->health[i] = health;
    minHeap->attack[i] = attack;
    minHeap->index[i] = index;
    minHeap->count[i] = count;

    while (i != 0 && minHeap->health[(i - 1) / 2] > minHeap->health[i]) {
        swap(&minHeap->health[i], &minHeap->health[(i - 1) / 2]);
        swap(&minHeap->attack[i], &minHeap->attack[(i - 1) / 2]);
        swap(&minHeap->index[i], &minHeap->index[(i - 1) / 2]);
        swap(&minHeap->count[i], &minHeap->count[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void extractMin(struct MinHeap *minHeap) {

    minHeap->health[0] = minHeap->health[minHeap->size - 1];
    minHeap->attack[0] = minHeap->attack[minHeap->size - 1];
    minHeap->index[0] = minHeap->index[minHeap->size - 1];
    minHeap->count[0] = minHeap->count[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    
}
int peekhealth(struct MinHeap *minHeap)
{
    return (minHeap->health[0]);
}
int peekcount(struct MinHeap *minHeap)
{
    return (minHeap->count[0]);
}
int peekindex(struct MinHeap *minHeap)
{
    return (minHeap->index[0]);
}
int peekattack(struct MinHeap *minHeap)
{
    return (minHeap->attack[0]);
}
int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    int health[N];
    int attack[N];
    for (int i = 0; i < N; i++)
        ReadInt(&health[i]);
    for (int i = 0; i < N; i++)
        ReadInt(&attack[i]);
    struct MinHeap minheap[N];
    struct MinHeap *minHeap;
    for (int i = 0; i < N; i++)
        createMinHeap(&minheap[i]);
    for (int i = 0; i < N; i++){
        minHeap = &minheap[i];
        insert(minHeap, health[i], attack[i], i, 0);
    }
    DisjointSet set;
    init(&set, N);
    int ans[N];
    int totalattack[N];
    int totalhealth[N];
    for (int i = 0; i < N; i++){
        totalhealth[i] = 0;
        ans[i] = 0;
    }
    for (int i = 0; i < N; i++)
        totalattack[i] = attack[i];
    int isdead[N];
    int totalcount[N];
    for (int i = 0; i < N; i++){
        isdead[i] = 0;
        totalcount[i] = 0;
    }
    int Ka, Ks;
    for (int i = 0; i < M; i++){
        ReadInt(&Ka);
        ReadInt(&Ks);
        Ka = Ka - 1;
        Ks = Ks - 1;
        if (isdead[Ka] == 1 || isdead[Ks] == 1)
            continue;
        if (find(&set, Ka) == find(&set, Ks))
            continue;
        int roota = find(&set, Ka);
        int roots = find(&set, Ks);
        struct MinHeap *a = &minheap[roota];
        struct MinHeap *s = &minheap[roots];
        if (a->size <= s->size){
            totalcount[roota] += 1;
            while (peekhealth(s) - totalattack[roota] - totalhealth[roots] <= 0 && s->size > 0){
                isdead[peekindex(s)] = 1;
                ans[peekindex(s)] = peekcount(s) + totalcount[roots];
                totalattack[roots] -= peekattack(s);
                extractMin(s);
            }
            s->health = realloc(s->health, 4 * (a->size + s->size));
            s->count = realloc(s->count, 4 * (a->size + s->size));
            s->attack = realloc(s->attack, 4 * (a->size + s->size));
            s->index = realloc(s->index, 4 * (a->size + s->size));
            totalhealth[roots] += totalattack[roota];
            totalattack[roots] += totalattack[roota];
            unionSet(&set, Ka, Ks);
            for (int j = 0; j < a->size; j++){
                insert(s, a->health[j] + totalhealth[roots]  - totalhealth[roota], a->attack[j], a->index[j], a->count[j] + totalcount[roota] - totalcount[roots]);
            }
            free(a->health);
            free(a->attack);
            free(a->count);
            free(a->index);
            a->size = 0;
            continue;
        }
        else if (a->size > s->size){
            totalcount[roota]++;
            a->health = realloc(a->health, 4 * (a->size + s->size));
            a->count = realloc(a->count, 4 * (a->size + s->size));
            a->attack = realloc(a->attack, 4 * (a->size + s->size));
            a->index = realloc(a->index, 4 * (a->size + s->size));
            while (peekhealth(s) - totalattack[roota] - totalhealth[roots] <= 0 && s->size > 0){
                isdead[peekindex(s)] = 1;
                ans[peekindex(s)] = peekcount(s) + totalcount[roots];
                totalattack[roots] -= peekattack(s);
                extractMin(s);
            }
            for (int j = 0; j < s->size; j++){
                    insert(a, s->health[j] + totalhealth[roota] - totalhealth[roots] - totalattack[roota], s->attack[j], s->index[j], s->count[j] - totalcount[roota] + totalcount[roots] );
            }
            totalattack[roota] += totalattack[roots];
            unionSet1(&set, Ka, Ks);
            free(s->health);
            free(s->attack);
            free(s->count);
            free(s->index);
            s->size = 0;
        }
    }
    for (int i = 0; i < N; i++){
        minHeap = &minheap[i];
        if (minHeap->size == 0)
            continue;
        for (int j = 0; j < minHeap->size; j++){
            ans[minHeap->index[j]] = minHeap->count[j] + totalcount[i];
        }
    }
    for (int i = 0; i < N; i++)
        printf("%d ", ans[i]);
}
