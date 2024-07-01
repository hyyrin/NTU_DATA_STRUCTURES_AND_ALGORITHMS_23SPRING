#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define base 1361
bool hashvalue[84957923];
bool hashvalue1[1000639];
bool hashvalue2[19260817];
long long count;
int forever;
int num[84957923];
int num2[19260817];
int num1[1000639];
bool com1[1000639];
bool com[84957923];
bool com2[19260817];
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
long long hash(char S[][forever], int index)
{
    long long mode = 84957923;
    long long hash = 0;
    for (int i = 0; i < strlen(S[index]); i++)
        hash = ((hash * base) + (long long)S[index][i]) % mode;
    return hash;
}
long long directhash(char S[])
{
    long long mode = 84957923;
    long long hash = 0;
    for (int i = 0; i < strlen(S); i++)
        hash = ((hash * base) + (long long)S[i]) % mode;
    return hash;
}
long long hash1(char S[][forever], int index)
{
    long long mode = 1000639;
    long long hash = 0;
    for (int i = 0; i < strlen(S[index]); i++)
        hash = ((hash * base) + (long long)S[index][i]) % mode;
    return hash;
}
long long directhash1(char S[])
{
    long long mode = 1000639;
    long long hash = 0;
    for (int i = 0; i < strlen(S); i++)
        hash = ((hash * base) + (long long)S[i]) % mode;
    return hash;
}
long long hash2(char S[][forever], int index)
{
    long long mode = 19260817;
    long long hash = 0;
    for (int i = 0; i < strlen(S[index]); i++)
        hash = ((hash * base) + (long long)S[index][i]) % mode;
    return hash;
}
long long directhash2(char S[])
{
    long long mode = 19260817;
    long long hash = 0;
    for (int i = 0; i < strlen(S); i++)
        hash = ((hash * base) + (long long)S[i]) % mode;
    return hash;
}
int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}
void rotate(char ptr[], long long value, long long value1, long long value2, int M)
{
    long long mode = 84957923;
    long long mode1 = 1000639;
    long long mode2 = 19260817;
    long long pow = 1;
    long long pow1 = 1;
    long long pow2 = 1;
    for (int i = 0; i < M - 1; i++)
        pow = (pow * base) % mode;
    for (int i = 0; i < M - 1; i++)
        pow1 = (pow1 * base) % mode1;
    for (int i = 0; i < M - 1; i++)
        pow2 = (pow2 * base) % mode2;
    long long target = value;
    long long target1 = value1;
    long long target2 = value2;
    long long a[M];
    long long b[M];
    long long c[M];
    for (int i = 1; i < M; i++){
        target = (base * (target - (long long)ptr[i - 1] * pow) + ptr[i + M - 1]) % mode;
        if (target < 0)
            target = target + mode;
        target1 = (base * (target1 - (long long)ptr[i - 1] * pow1) + ptr[i + M - 1]) % mode1;
        if (target1 < 0)
            target1 = target1 + mode1;
        target2 = (base * (target2 - (long long)ptr[i - 1] * pow2) + ptr[i + M - 1]) % mode2;
        if (target2 < 0)
            target2 = target2 + mode2;
        long long minimum = min(num2[target2], min(num[target], num1[target1]));
        if (hashvalue[target] == true && target != value && hashvalue1[target1] == true && target1 != value1 && com[target] == false && com1[target1] == false && hashvalue2[target2] == true && target2 != value2 && com2[target2] == false)
            count += minimum;
        if (num[target] == minimum)
            com[target] = true;
        if (num1[target1] == minimum)
            com1[target1] = true;
        if (num2[target2] == minimum)
            com2[target2] = true;
        a[i - 1] = target;
        c[i - 1] = target2;
        b[i - 1] = target1;
    }
    for (int i = 0; i < M - 1; i++){
        com[a[i]] = false;
        com1[b[i]] = false;
        com2[c[i]] = false;
    }
}
void delete(char ptr[], long long value, long long value1, long long value2, int M)
{
    long long mode = 84957923;
    long long mode1 = 1000639;
    long long mode2 = 19260817;
    long long pow2 = 1;
    long long pow1 = 1;
    long long pow = 1;
    for (int i = 0; i < M - 1; i++)
        pow = (pow * base) % mode;
    for (int i = 0; i < M - 1; i++)
        pow1 = (pow1 * base) % mode1;
    for (int i = 0; i < M - 1; i++)
        pow2 = (pow2 * base) % mode2;
    long long target2 = value2;
    long long target = value;
    long long target1 = value1;
    long long a[M];
    long long b[M];
    long long c[M];
    for (int i = 1; i < M; i++){
        target = (base * (target - (long long)ptr[i - 1] * pow) + ptr[i + M - 1]) % mode;
        if (target < 0)
            target = target + mode;
        target1 = (base * (target1 - (long long)ptr[i - 1] * pow1) + ptr[i + M - 1]) % mode1;
        if (target1 < 0)
            target1 = target1 + mode1;
        target2 = (base * (target2 - (long long)ptr[i - 1] * pow2) + ptr[i + M - 1]) % mode2;
        if (target2 < 0)
            target2 = target2 + mode2;
        long long minimum = min(num2[target2], min(num[target], num1[target1]));
        if (hashvalue[target] == true && target != value && hashvalue1[target1] == true && target1 != value1 && com[target] == false && com1[target1] == false && hashvalue2[target2] == true && target2 != value2 && com2[target2] == false)
            count -= minimum;
        if (num[target] == minimum)
            com[target] = true;
        if (num1[target1] == minimum)
            com1[target1] = true;
        if (num2[target2] == minimum)
            com2[target2] = true;
        a[i - 1] = target;
        b[i - 1] = target1;
        c[i - 1] = target2;
    }
    for (int i = 0; i < M - 1; i++){
        com[a[i]] = false;
        com1[b[i]] = false;
        com2[c[i]] = false;
    }
}
int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);
    char record[1000002];
    scanf("%s", record);
    forever = strlen(record) + 1;
    char S[N][strlen(record) + 1];
    strcpy(S[0], record);
    long long value[N];
    long long value1[N];
    long long value2[N];
    value[0] = directhash(record);
    hashvalue[value[0]] = true;
    value2[0] = directhash2(record);
    hashvalue2[value2[0]] = true;
    value1[0] = directhash1(record);
    hashvalue1[value1[0]] = true;
    num[value[0]] += 1;
    num1[value1[0]] += 1;
    num2[value2[0]] += 1;
    for (int i = 1; i < N; i++){
        scanf("%s", S[i]);
        value[i] = hash(S, i);
        value1[i] = hash1(S, i);
        value2[i] = hash2(S, i);
        hashvalue[hash(S, i)] = true;
        hashvalue2[hash2(S, i)] = true;
        hashvalue1[hash1(S, i)] = true;
        num1[value1[i]] += 1;
        num2[value2[i]] += 1;
        num[value[i]] += 1;
        //printf("%lld\n", count);
    }
    count = 0;
    for (int i = 0; i < N; i++){
        char ptr[2 * strlen(S[i]) + 1];
        strcpy(ptr, S[i]);
        strcat(ptr, S[i]);
        ptr[2 * strlen(S[i])] = '\0';
        rotate(ptr, value[i], value1[i], value2[i],strlen(S[i]));
        //printf("%lld\n", count);
    }
    count = count / 2;
    for (int i = 0; i < N; i++){
        long long minimum;
        if (num[value[i]] > 1 && com[value[i]] == false && num1[value1[i]] > 1 && com1[value1[i]] == false && num2[value2[i]] > 1 && com2[value2[i]] == false){
            minimum = min(num2[value2[i]], min(num[value[i]], num1[value1[i]]));
            for (int j = 1; j < minimum; j++)
                count += j;
        }
        //printf("%lld\n", count);
        if (num[value[i]] == minimum)
            com[value[i]] = true;
        if (num1[value1[i]] == minimum)
            com1[value1[i]] = true;
        if (num2[value2[i]] == minimum)
            com2[value2[i]] = true;
    }
    for (int i = 0; i < N; i++){
        com[value[i]] = false;
        com1[value1[i]] = false;
        com2[value2[i]] = false;
    }
    printf("%lld\n", count);
    for (int i = 0; i < Q; i++){
        int situation;
        ReadInt(&situation);
        //scanf("%d", &situation);
        char str[forever];
        scanf("%s", str);
        if (situation == 1){
            long long insert = directhash(str);
            long long insert2 = directhash2(str);
            long long insert1 = directhash1(str);
            if (hashvalue[insert] == true && hashvalue1[insert1] == true && hashvalue2[insert2] == true){
                char ptr[2 * strlen(str) + 1];
                strcpy(ptr, str);
                strcat(ptr, str);
                ptr[2 * strlen(str)] = '\0';
                rotate(ptr, insert, insert1, insert2, strlen(str));
                count += min(num2[insert2], min(num[insert], num1[insert1]));
                num[insert] += 1;
                num2[insert2] += 1;
                num1[insert1] += 1;
            }
            else{
                hashvalue[insert] = true;
                hashvalue2[insert2] = true;
                hashvalue1[insert1] = true;
                char ptr[2 * strlen(str) + 1];
                strcpy(ptr, str);
                strcat(ptr, str);
                ptr[2 * strlen(str)] = '\0';
                rotate(ptr, insert, insert1, insert2, strlen(str));
                num[insert] += 1;
                num2[insert2] += 1;
                num1[insert1] += 1;
            }
            printf("%lld\n", count);
        }
        else if (situation == 2){
            long long remove = directhash(str);
            long long remove2 = directhash2(str);
            long long remove1 = directhash1(str);
            int minimum = min(num2[remove2], min(num[remove], num1[remove1]));
            if (hashvalue[remove] == true && hashvalue1[remove1] == true && num1[remove1] > 1 && num[remove] > 1 && hashvalue2[remove2] == true && num2[remove2] > 1){
                char ptr[2 * strlen(str) + 1];
                strcpy(ptr, str);
                strcat(ptr, str);
                ptr[2 * strlen(str)] = '\0';
                delete(ptr, remove, remove1, remove2, strlen(str));
                num[remove] -= 1;
                num2[remove2] -= 1;
                num1[remove1] -= 1;
                count -= min(num2[remove2], min(num[remove], num1[remove1]));
            }
            else if (hashvalue[remove] == true && hashvalue1[remove1] == true && minimum == 1 && hashvalue2[remove2]){
                if (num[remove] == minimum)
                    hashvalue[remove] = false;
                if (num1[remove1] == minimum)
                    hashvalue1[remove1] = false;
                if (num2[remove2] == minimum)
                    hashvalue2[remove2] = false;
                char ptr[2 * strlen(str) + 1];
                strcpy(ptr, str);
                strcat(ptr, str);
                ptr[2 * strlen(str)] = '\0';
                delete(ptr, remove, remove1, remove2, strlen(str));
                num[remove] -= 1;
                num1[remove1] -= 1;
                num2[remove2] -= 1;
            }
            printf("%lld\n", count);
        }
    }
}
