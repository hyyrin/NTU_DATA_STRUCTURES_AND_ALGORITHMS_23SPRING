#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int app;
    int index;
    struct node *next;
    struct node *previous;
}Node;
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
int faststart(int arr[][3], int value, int N)
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
            right = mid - 1;
    }
    return right + 1;
}
int fastlast(int arr[][3], int value, int N)
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
            left = mid + 1;
    }
    return left - 1;
}
int compare2(const void *a, const void *b)
{
    int *a1 = (int *)(a + sizeof(int));
    int *b1 = (int *)(b + sizeof(int));
    return (*a1 - *b1);
}
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
Node *create_node(int app, int index)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->app = app;
    new_node->index = index;
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}
int rbinarysearch(int arr[][3], int value, int li, int ri)
{
    int left = li;
    int right = ri;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid][1] > value)
            right = mid - 1;
        else if (arr[mid][1] < value)
            left = mid + 1;
        else
            return mid;
    }
    return left;
}
int binarysearch(int arr[], int value, int li, int ri)
{
    int left = li;
    int right = ri;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > value)
            right = mid - 1;
        else if (arr[mid] < value)
            left = mid + 1;
        else
            return mid;
    }
    return left;
}
int lbinarysearch(int arr[][3], int value, int li, int ri)
{
    int left = li;
    int right = ri;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid][1] > value)
            right = mid - 1;
        else if (arr[mid][1] < value)
            left = mid + 1;
        else
            return mid;
    }
    return right;
}
int mrbinarysearch(int arr[][3], int value, int li, int ri, int len, int start)
{
    int left = li;
    int right = ri;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[((mid % len) + len) % len + start][1] > value)
            right = mid - 1;
        else if (arr[((mid % len) + len) % len + start][1] < value)
            left = mid + 1;
        else
            return mid;
    }
    return left;
}
int mlbinarysearch(int arr[][3], int value, int li, int ri, int len, int start)
{
    int left = li;
    int right = ri;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[((mid % len) + len) % len + start][1] > value)
            right = mid - 1;
        else if (arr[((mid % len) + len) % len + start][1] < value)
            left = mid + 1;
        else
            return mid;
    }
    return right;
}
int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    int appetitie[N][3];
    int copy[N][2];
    for (int i = 0; i < N; i++){
        ReadInt(&appetitie[i][1]);
        copy[i][0] = appetitie[i][1];
        appetitie[i][2] = i;
        copy[i][1] = i;
    }
    for (int i = 0; i < N; i++){
        ReadInt(&appetitie[i][0]);
    }
    qsort(appetitie, N, sizeof(appetitie[0]), compare);
    int color[N];
    int count = 1;
    int colored = appetitie[0][0];
    color[0] = appetitie[0][0];
    for (int i = 1; i < N; i++){
        if (appetitie[i][0] == colored)
            continue;
        else{
            color[count] = appetitie[i][0];
            count++;
            colored = appetitie[i][0];
        }
    }
    int colorlen[count];
    int shift[count];
    int start[count];
    for (int i = 0; i < count; i++){
        int ll = faststart(appetitie, color[i], N);
        int rr = fastlast(appetitie, color[i], N);
        colorlen[i] = rr - ll + 1;
        start[i] = ll;
        shift[i] = 0;
        qsort(&appetitie[ll], rr - ll + 1, sizeof(appetitie[0]), compare2);
    }
    int index[N];
    for (int i = 0; i < N; i++){
        index[appetitie[i][2]] = i;
    }
    qsort(copy, N, sizeof(copy[0]), compare);
    Node *head = create_node(0, -1);
    Node *tail = create_node(0, -1);
    Node *ptr[N];
    Node *root = head;
    for (int i = 0; i < N; i++){
        Node *new = create_node(copy[i][0], copy[i][1]);
        ptr[copy[i][1]] = new;
        root->next = new;
        new->previous = root;
        root = root->next;
        if (i == N - 1){
            root->next = tail;
            tail->previous = root;
        }
    }
    for (int i = 0; i < M; i++){
        int situation, c, l, r, k, t, s;
        scanf("%d", &situation);
        if (situation == 1){
            scanf("%d%d%d", &c, &l, &r);
            int colorpos = binarysearch(color, c, 0, count - 1);
            if (color[colorpos] != c){
                printf("%d\n", 0);
                continue;
            }
            int left = mrbinarysearch(appetitie, l, shift[colorpos], shift[colorpos] + colorlen[colorpos] - 1, colorlen[colorpos], start[colorpos]);
            int right = mlbinarysearch(appetitie, r, shift[colorpos], shift[colorpos] + colorlen[colorpos] - 1, colorlen[colorpos], start[colorpos]);
            printf("%d\n", right - left + 1);
        }
        else if (situation == 2){
            scanf("%d", &k);
            Node *tmp = ptr[k];
            if (ptr[k]->next->index == -1)
                continue;
            int next = tmp->next->index;
            int first = index[k];
            int second = index[next];
            ptr[k]->index = next;
            ptr[next]->index = k;
            ptr[k] = tmp->next;
            ptr[next] = tmp;
            if (appetitie[first][0] != appetitie[second][0]){
                int str = appetitie[second][1];
                appetitie[second][1] = appetitie[first][1];
                appetitie[first][1] = str;
            }
            else if (appetitie[first][0] == appetitie[second][0]){
                appetitie[first][2] = next;
                appetitie[second][2] = k;
                index[k] = second;
                index[next] = first;
            }
        }
        else if (situation == 3){
            scanf("%d%d%d", &c, &s, &t);
            int colorpos = binarysearch(color, c, 0, count - 1);
            if (color[colorpos] != c)
                continue;
            int pos;
            int len = colorlen[colorpos];
            if (s == 1)
                pos = (((shift[colorpos] + colorlen[colorpos] - 1) % len ) + len) % len + start[colorpos];
            else if (s == 0)
                pos = ((shift[colorpos] % len) + len) % len + start[colorpos];
            if (t == 1){
                int link = appetitie[pos][2];
                int max = tail->previous->app;
                Node *tmp = ptr[link];
                tmp->app = max + 1;
                tmp->previous->next = tmp->next;
                tmp->next->previous = tmp->previous;
                tail->previous->next = tmp;
                tmp->previous = tail->previous;
                tmp->next = tail;
                tail->previous = tmp;
                appetitie[pos][1] = max + 1;
                if (s == 0)
                    shift[colorpos] += 1;
            }
            else if (t == 0){
                int link = appetitie[pos][2];
                int min = head->next->app;
                Node *tmp = ptr[link];
                tmp->app = min - 1;
                tmp->previous->next = tmp->next;
                tmp->next->previous = tmp->previous;
                head->next->previous = tmp;
                tmp->next = head->next;
                tmp->previous = head;
                head->next = tmp;
                appetitie[pos][1] = min - 1;
                if (s == 1)
                    shift[colorpos] -= 1;
            }
        }
    }
}
