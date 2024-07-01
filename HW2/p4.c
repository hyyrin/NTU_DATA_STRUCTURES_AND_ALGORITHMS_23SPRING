#include<stdio.h>
#include<stdlib.h>
int M, N;
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
struct MinHeap {
    int *arr;
    int size;
    int *time;
};

void createMinHeap(struct MinHeap *minHeap) {
    minHeap->arr = (int *)malloc(sizeof(int) * M);
    minHeap->size = 0;
    minHeap->time = (int *)malloc(sizeof(int) * M);
    //minHeap->capacity = capacity;
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

    if (left < minHeap->size && minHeap->arr[left] < minHeap->arr[smallest]) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->arr[right] < minHeap->arr[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&minHeap->arr[i], &minHeap->arr[smallest]);
        swap(&minHeap->time[i], &minHeap->time[smallest]);
        minHeapify(minHeap, smallest);
    }
}

void buildMinHeap(struct MinHeap *minHeap) {
    for (int i = minHeap->size / 2 - 1; i >= 0; i--) {
        minHeapify(minHeap, i);
    }
}

void insert(struct MinHeap *minHeap, int data, int day) {
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->arr[i] = data;
    minHeap->time[i] = day;

    while (i != 0 && minHeap->arr[(i - 1) / 2] > minHeap->arr[i]) {
        swap(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);
        swap(&minHeap->time[i], &minHeap->time[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void extractMin(struct MinHeap *minHeap) {

    minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
    minHeap->time[0] = minHeap->time[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    
}
int peekvalue(struct MinHeap *minHeap)
{
    return (minHeap->arr[0]);
}
int peekday(struct MinHeap *minHeap)
{
    return (minHeap->time[0]);
}
typedef struct node {
    int data;
    int num_children;
    struct node **children;
    struct node *next;
    struct node *previous;
} Node;
Node* create_node(int data, int num_children) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->num_children = num_children;
    new_node->next = NULL;
    new_node->previous = NULL;
    new_node->children = (Node**)malloc(num_children * sizeof(Node*));
    for (int i = 0; i < num_children; i++)
        new_node->children[i] = NULL;
    return new_node;
}
Node* search_node(Node *root, int data)
{
    if (root == NULL) {
        return NULL;
    }
    if (root->data == data) {
        return root;
    }
    for (int i = 0; i < root->num_children; i++) {
        Node *result = search_node(root->children[i], data);
        if (result != NULL) {
            return result;
        }
    }
    return NULL;
}
int nodenum1(Node *root)
{
    if (root == NULL)
        return 0;
    int count = 1;
    for (int i = 0; i < root->num_children; i++) {
        count += nodenum1(root->children[i]);
    }
    return count;
}
int nodenum(Node *root) {
    int count = 1;
    for (int i = 0; i < root->num_children; i++) {
        count += nodenum(root->children[i]);
    }
    return count;
}
long long totalprice(Node *root, int index, int minprice[N][M])
{
    /*if (root == NULL)
        return 0;*/
    long long sum = minprice[root->data - 1][index];
    for (int i = 0; i < root->num_children; i++) {
        sum += totalprice(root->children[i], index, minprice);
    }
    return sum;
}
int binarysearch(int arr[][2], int value, int N)
{
    int left = 0;
    int right = N - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid][0] > value)
            right = mid - 1;
        else if (arr[mid][0] < value)
            left = mid + 1;
        else
            return mid;
    }
    return right;
}
void add_child(Node *parent, Node *child) {
    for (int i = 0; i < parent->num_children; i++) {
        if (parent->children[i] == NULL) {
            parent->children[i] = child;
            break;
        }
    }
}
int compare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}
int compare2(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int C;
    scanf("%d%d%d", &N, &M, &C);
    int company[N];
    int childnum[N];
    int isline = 1;
    for (int i = 0; i < N; i++)
        childnum[i] = 0;
    int childcompany[N][100];
    for (int i = 0; i < N - 1; i++){
        ReadInt(&company[i]);
        childcompany[company[i] - 1][childnum[company[i] - 1]] = i;
        childnum[company[i] - 1]++;
        if (company[i] != i + 1)
            isline = 0;
    }
    struct MinHeap minheap[N];
    struct MinHeap *minHeap;
    int minprice[N][M];
    for (int i = 0; i < N; i++)
        createMinHeap(&minheap[i]);
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            minHeap = &minheap[j];
            int tmp, day;
            ReadInt(&tmp);
            ReadInt(&day);
            day = day + i + 1;
            insert(minHeap, tmp, day);
            if (peekday(minHeap) >= i + 1)
                minprice[j][i] = peekvalue(minHeap);
            else if (peekday(minHeap) < i + 1){
                while (peekday(minHeap) < i + 1)
                    extractMin(minHeap);
                minprice[j][i] = peekvalue(minHeap);
            }
        }
    }
    long long minpricee[N][M];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            minpricee[j][i] = minprice[j][i];
    Node *root, *newnode, *newroot, *child, *new;
    /*if (isline == 1){
        root = create_node(1, 1);
        newroot = root;
        for (int i = 0; i < N - 2; i++){
            newnode = create_node(i + 2, 1);
            add_child(root, newnode);
            root = newnode;
        }
        newnode = create_node(N, 0);
        add_child(root, newnode);
        root = newroot;
        long long lineprice[M];
        for (int  i = 0; i < M; i++){
            long long sum = 0;
            for (int j = 0; j < N; j++)
                sum += minprice[j][i];
            lineprice[i] = sum;
        }
        for (int i = 0; i < M; i++){
            int number = N;
            long long sumprice = lineprice[i];
            for (int j = 0; j < N; j++){
                if (sumprice <= C){
                    printf("%d\n", number);
                    break;
                }
                sumprice -= minprice[j][i];
                number--;
            }
        }
        return 0;
    }*/
    //else if (isline == 0){
        //Node *pre = NULL;
        int havebuild[N];
        for (int i = 0; i < N; i++)
            havebuild[i] = 0;
        root = create_node(1, childnum[0]);
        newroot = root;
        new = root;
        havebuild[0] = 1;
        int index = 0;
        int count = 1;
        int arr[N + 1];
        arr[0] = 0;
        //return 0;
        for (int k = 0; k < N; k++){
            int com = 0;
            int i = arr[index];
            index++;
            newnode = newroot;
            for (int u = 0; u < childnum[i]; u++){
                int j = childcompany[i][u];
                if (havebuild[j + 1] == 0){
                    child = create_node(j + 2, childnum[j + 1]);
                    add_child(newnode, child);
                    Node *temp = new;
                    new->next = child;
                    new = new->next;
                    new->previous = temp;
                    havebuild[j + 1] = 1;
                    arr[count] = j + 1;
                    count++;
                }
                else if (havebuild[j + 1] == 1){
                    child = search_node(root, j + 2);
                    add_child(newnode, child);
                    arr[count] = j + 1;
                    count++;
                }
            }
            //printf("%d\n", newroot->data);
            newroot = newroot->next;
        }
    
    Node *verynew = new;
    int total[N][2];
    for (int i = 0; i < N; i++)
        total[i][0] = 0;
    //verynew = new;
    for (int j = 0; j < N; j++){
        int sale = 1;
        for (int k = 0; k < verynew->num_children; k++)
            sale += total[verynew->children[k]->data - 1][0];
        total[verynew->data - 1][0] = sale;
        total[verynew->data - 1][1] = verynew->data - 1;
        verynew = verynew->previous;
    }
        //verynew = new;
    
    for (int i = 0; i < M; i++){
        verynew = new;
        for (int j = 0; j < N; j++){
            long long sales = minpricee[verynew->data - 1][i];
            //printf("%d\n", verynew->data - 1);
            for (int k = 0; k < verynew->num_children; k++)
                sales += minpricee[verynew->children[k]->data - 1][i];
            minpricee[verynew->data - 1][i] = sales;
            verynew = verynew->previous;
        }
    }
    
    /*for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            printf("%d ", minprice[i][j]);
        }
        printf("\n");
    }*/
    /*for (int i = 0; i < N; i++)
        printf("%d %d\n", total[i][0], total[i][1]);
    return 0;*/
    int sort[N];
    //newroot = root;
    /*for (int i = 0; i < N; i++){
        new = newroot;
        int record = nodenum(new);
        total[new->data - 1][0] = record;
        //sort[new->data - 1] = record;
        total[new->data - 1][1] = new->data - 1;
        newroot = newroot->next;
    }*/
    
    qsort(total, N, sizeof(total[0]), compare);
    for (int i = 0; i < N; i++)
        sort[total[i][1]] = i;
    
    /*Node *root1 = create_node(total[0][1] + 1, )
    Node *root2;
    for (int i = 0; i < N; i++){
        
    }*/
    
    Node *ptr[N];
    newroot = root;
    for (int i = 0; i < N; i++){
        new = newroot;
        ptr[sort[new->data - 1]] = new;
        newroot = newroot->next;
    }
    
    /*for (int i = 0; i < N; i++)
        printf("%d\n", total[i][0]);*/
    /*newroot = root;
    for (int i = 0; i < N; i++){
        new = newroot;
        int a = sort[new->data - 1];
        ptr[binarysearch(total, a, N)] = new;
        //printf("%d\n", ptr[binarysearch(total, a, N)]->data);
        newroot = newroot->next;
    }
    for (int i = 0; i < N; i++)
        printf("%d\n", ptr[i]->data);
    return 0;*/
    /*for (int i = 0; i < N; i++){
        int a = total[i][1];
        root1 = search_node(root, a + 1);
        ptr[i] = root1;
    }*/
    for (int i = 0; i < M; i++){
        int lemonsum = 0;
        //int pos = 1;
        long long sumprice;
        //Node *ans;
        //newroot = root;
        for (int j = 0; j < N; j++){
            Node *ans = ptr[j];
            //ans = search_node(root, total[j][1] + 1);
            //sumprice = totalprice(newroot, i, minprice);
            
            //sumprice = minprice[ptr[j]->data - 1][i];
            
            sumprice = minpricee[ans->data - 1][i];
            
            /*if (sumprice <= C){
                lemonsum = total[j][0];
                break;
            }*/
            /*if (sumprice > C){
                if (total[ans->data - 1] == lemonsum){
                    lemonsum = sort[pos];
                    pos++;
                }
            }*/
            if (sumprice <= C){
                lemonsum = total[j][0];
                break;
            }
            //newroot = newroot->next;
        }
        printf("%d\n", lemonsum);
    }
}
