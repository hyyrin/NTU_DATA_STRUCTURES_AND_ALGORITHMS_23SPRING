
#include<stdio.h>
#include<string.h>
#define base 256
int count;
int arr[19260817];
int arr1[17260871];
int arr2[84957929];
int N;
int M;
long long hash(char P[])
{
    int mode = 19260817;
    long long hash = 0;
    for (int i = 0; i < M; i++)
        hash = ((hash * base) + (long long)P[i]) % mode;
    return hash;
}
long long hash1(char P[])
{
    int mode = 17260871;
    long long hash = 0;
    for (int i = 0; i < M; i++)
        hash = ((hash * base) + (long long)P[i]) % mode;
    return hash;
}
long long hash2(char P[])
{
    int mode = 84957929;
    long long hash = 0;
    for (int i = 0; i < M; i++)
        hash = ((hash * base) + (long long)P[i]) % mode;
    return hash;
}
void rotate(char P[], long long target, long long given, char S[], long long target1, long long given1, long long target2, long long given2)
{
    int mode = 19260817;
    int mode1 = 17260871;
    int mode2 = 84957929;
    long long pow = 1;
    for (int i = 0; i < M - 1; i++)
        pow = (pow * base) % mode;
    
    long long pow1 = 1;
    for (int i = 0; i < M - 1; i++)
        pow1 = (pow1 * base) % mode1;
    
    long long pow2 = 1;
    for (int i = 0; i < M - 1; i++)
        pow2 = (pow2 * base) % mode2;
    
    for (int i = 1; i < M; i++){
        target = (base * (target - (long long)P[i - 1] * pow) + P[i + M - 1]) % mode;
        if (target < 0)
            target = target + mode;
        target1 = (base * (target1 - (long long)P[i - 1] * pow1) + P[i + M - 1]) % mode1;
        if (target1 < 0)
            target1 = target1 + mode1;
        target2 = (base * (target2 - (long long)P[i - 1] * pow2) + P[i + M - 1]) % mode2;
        if (target2 < 0)
            target2 = target2 + mode2;
        arr[target] = 1;
        arr1[target1] = 1;
        arr2[target2] = 1;
    }
    if (arr[given] == 1 && arr1[given1] == 1 && arr2[given2] == 1)
        count++;
    for (int i = 1; i <= N - M; i++){
        given = (base * (given - (long long)S[i - 1] * pow) + S[i + M - 1]) % mode;
        if (given < 0)
            given += mode;
        given1 = (base * (given1 - (long long)S[i - 1] * pow1) + S[i + M - 1]) % mode1;
        if (given1 < 0)
            given1 += mode1;
        given2 = (base * (given2 - (long long)S[i - 1] * pow2) + S[i + M - 1]) % mode2;
        if (given2 < 0)
            given2 += mode2;
        if (arr[given] == 1 && arr1[given1] == 1 && arr2[given2] == 1)
            count++;
    }
    return;
}
int main()
{
    scanf("%d%d", &N, &M);
    char S[N + 1];
    char P[2 * M + 1];
    scanf("%s", S);
    S[N] = '\0';
    scanf("%s", P);
    P[M] = '\0';
    char tmp[M + 1];
    strcpy(tmp, P);
    strcat(P, tmp);
    P[2 * M] = '\0';
    long long target = hash(P);
    arr[target] = 1;
    long long given = hash(S);
    count = 0;
    long long target1 = hash1(P);
    long long given1 = hash1(S);
    arr1[target1] = 1;
    long long target2 = hash2(P);
    long long given2 = hash2(S);
    arr2[target2] = 1;
    rotate(P, target, given, S, target1, given1, target2, given2);
    printf("%d", count);
    return 0;
}

