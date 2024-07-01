#include<stdio.h>
#include<stdlib.h>
int ReadInt(int *num)
{
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
typedef struct listnode{
    int data;
    struct listnode *next;
    int index;
    struct listnode *last;
    int rank;
    int area;
    int count;
}Listnode;
int length;
Listnode *max;
Listnode *ptr;
Listnode *next;
int totalarea;
int height;
Listnode *genListnode( int data, Listnode *next,  int index, Listnode *last, int count, int area, int rank)
{
    Listnode *node = (Listnode *)malloc(sizeof(Listnode));
    node->data = data;
    node->next = next;
    node->index = index;
    node->last = last;
    node->count = count;
    node->area = area;
    node->rank = rank;
    return node;
}
Listnode *insertlinkedlist(Listnode *head, int data, int index, int M)
{
    Listnode *current = genListnode(data, NULL, index, NULL, height, totalarea, 0);
    length++;
    if (head == NULL){
        max = current;
        return (current);
    }
    if (current->data > max->data)
        max = current;
    ptr = head;
    while (ptr != NULL && ptr->data < data){
        next = ptr->next;
        printf("%d,%d ",ptr->index, totalarea - ptr->area - ptr->count * (index - ptr->index) + (index - ptr->index) * (M - ptr->rank));
        length--;
        free(ptr);
        ptr = next;
    }
    current->rank = length - 1;
    current->next = ptr;
    if (ptr != NULL)
        ptr->last = current;
    return (current);
}
int main()
{
    int N;
    int M;
    length = 0;
    totalarea = 0;
    height = 0;
    scanf("%d%d", &N, &M);
    Listnode *head = NULL;
    int power;
    for (int i = 1; i <= N; i++){
        ReadInt(&power);
        printf("Round %d: ", i);
        head = insertlinkedlist(head, power, i, M);
        if (length > M){
            height++;
            printf("%d,%d", max->index, totalarea - max->area - max->count * (i - max->index) + (i - max->index) * (M - max->rank));
            ptr = max->last;
            free(max);
            if (ptr != NULL){
                ptr->next = NULL;
                max = ptr;
            }
            length--;
        }
        totalarea += height;
        printf("\n");
    }
    printf("Final: ");
    for (int i = 0; i < length; i++){
        printf("%d,%d ", head->index, totalarea - head->area - head->count * (N - head->index + 1) + (N - head->index + 1) * (M - head->rank));
        head = head->next;
    }
    return 0;
}
