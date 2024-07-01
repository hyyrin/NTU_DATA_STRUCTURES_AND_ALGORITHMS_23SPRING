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
}Listnode;
int length;
Listnode *max;
Listnode *ptr;
Listnode *next;
Listnode *genListnode( int data, Listnode *next,  int index, Listnode *last)
{
    Listnode *node = (Listnode *)malloc(sizeof(Listnode));
    node->data = data;
    node->next = next;
    node->index = index;
    node->last = last;
    return node;
}
Listnode *insertlinkedlist(Listnode *head, int data, int index)
{
    Listnode *current = genListnode(data, NULL, index, NULL);
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
        printf("%d ",ptr->index);
        length--;
        free(ptr);
        ptr = next;
        /*if (ptr != NULL)
            ptr->last = NULL;*/
    }
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
    scanf("%d%d", &N, &M);
    Listnode *head = NULL;
    int power;
    /*if (M == 1){
        for (int i = 0; i < N; i++)
            scanf("%d", &power);
        printf("Round 1: \n");
        for (int i = 2; i <= N; i++)
            printf("Round %d: %d\n", i, i - 1);
        printf("Final: ");
        printf("%d", N);
        return 0;
    }*/
    for (int i = 1; i <= N; i++){
        //scanf("%d", &power);
        ReadInt(&power);
        printf("Round %d: ", i);
        head = insertlinkedlist(head, power, i);
        if (length > M){
            printf("%d", max->index);
            ptr = max->last;
            free(max);
            if (ptr != NULL){
                ptr->next = NULL;
                max = ptr;
            }
            /*else
                head = NULL;*/
            length--;
        }
        printf("\n");
    }
    printf("Final: ");
    for (int i = 0; i < length; i++){
        printf("%d ", head->index);
        head = head->next;
    }
    return 0;
}
