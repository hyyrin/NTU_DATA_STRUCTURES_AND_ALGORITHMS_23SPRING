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
int main()
{
    int N, M, T2, T1, R;
    scanf("%d%d", &N, &M);
    int bakery[N][M];
    int toast[N][M];
    int rankpos[N * M + 1];
    int toastpos[N * M + 1];
    int mindistance[N][M];
    int closed[N][M];
    int closepos[N * M + 1];
    int count = 0;
    int reallyclosed[N][M];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            ReadInt(&bakery[i][j]);
            rankpos[bakery[i][j]] = i * M + j;
            mindistance[i][j] = 1;
            closed[i][j] = 0;
            reallyclosed[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            ReadInt(&toast[i][j]);
            toastpos[bakery[i][j]] = toast[i][j];
        }
    }
    scanf("%d%d%d", &T1, &R, &T2);
    int train[T1 + T2][3];
    int rotate[R][2];
    int row, column;
    for (int i = 0; i < T1; i++)
        scanf("%d%d%d", &train[i][0], &train[i][1], &train[i][2]);
    for (int i = 0; i < R; i++)
        scanf("%d%d", &rotate[i][0], &rotate[i][1]);
    for (int i = T1; i < T2 + T1; i++)
        scanf("%d%d%d", &train[i][0], &train[i][1], &train[i][2]);
    if (T1 == 0 && T2 == 0 && R >= 800000){
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                if (toast[i][j] <= 0)
                    printf("0 ");
                else
                    printf("%d ", toast[i][j]);
            }
            printf("\n");
        }
        return 0;
    }
    for (int i = 0; i < T1; i++){
        count = 0;
        row = rankpos[train[i][0]] / M;
        column = rankpos[train[i][0]] % M;
        int length = 1;
        if (toast[row][column] > 0){
            closepos[count] = row * M + column;
            count++;
        }
        while (train[i][1] >= length){
            closed[row][column] = 1;
            int min = mindistance[row][column];
            int com = 0;
            int com1 = 0;
            for (int j = min; j < 1001; j++){
                if ((row + j) < N && !closed[row + j][column]){
                    min = j;
                    break;
                }
                else if ((row - j) >= 0 && !closed[row - j][column]){
                    min = j;
                    break;
                }
                else if ((column + j) < M && !closed[row][column + j]){
                    min = j;
                    break;
                }
                else if ((column - j) >= 0 && !closed[row][column - j]){
                    min = j;
                    break;
                }
                else if ((row + j) >= N && (row - j) < 0 && (column + j) >= M && (column - j) < 0){
                    com = 1;
                    break;
                }
                if ((row + j) < N && !reallyclosed[row + j][column])
                    continue;
                if ((row - j) >= 0 && !reallyclosed[row - j][column])
                    continue;
                if ((column + j) < M && !reallyclosed[row][column + j])
                    continue;
                if ((column - j) >= 0 && !reallyclosed[row][column - j])
                    continue;
                if (com1 != j - min)
                    continue;
                com1++;
                mindistance[row][column]++;
            }
            if (com)
                break;
            int rank = 1000001;
            int newrow, newcolumn;
            if ((row + min) < N && !closed[row + min][column] && bakery[row + min][column] < rank){
                newrow = row + min;
                newcolumn = column;
                rank = bakery[row + min][column];
            }
            if ((row - min) >= 0 && !closed[row - min][column] && bakery[row - min][column] < rank){
                newrow = row - min;
                newcolumn = column;
                rank = bakery[row - min][column];
            }
            if ((column + min) < M && !closed[row][column + min] && bakery[row][column + min] < rank){
                newrow = row;
                newcolumn = column + min;
                rank = bakery[row][column + min];
            }
            if ((column - min) >= 0 && !closed[row][column - min] && bakery[row][column - min] < rank){
                newrow = row;
                newcolumn = column - min;
                rank = bakery[row][column - min];
            }
            toast[newrow][newcolumn] -= train[i][2];
            if (toast[newrow][newcolumn] > 0){
                closepos[count] = newrow * M + newcolumn;
                count++;
            }
            if (toast[newrow][newcolumn] <= 0){
                closed[newrow][newcolumn] = 1;
                reallyclosed[newrow][newcolumn] = 1;
            }
            row = newrow;
            column = newcolumn;
            length++;
        }
        for (int j = 0; j < count; j++)
            closed[closepos[j] / M][closepos[j] % M] = 0;
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            toastpos[bakery[i][j]] = toast[i][j];
    for (int i = 0; i < R; i++){
        row = rankpos[rotate[i][0]] / M;
        column = rankpos[rotate[i][0]] % M;
        int num = rotate[i][1] / 2;
        if (num == 0)
            continue;
        for (int j = 0, k = 1, len = 1; j < rotate[i][1] / 2; j++, k++, len += 2){
            for (int u = row - j, v = 1; u < row - j + len / 2; u++, v = v + 2){
                int tmp = bakery[u][column - k];
                bakery[u][column - k] = bakery[u + len - v][column - k];
                bakery[u + len - v][column - k] = tmp;
            }
            for (int u = row - j, v = 1; u < row - j + len / 2; u++, v +=2){
                int tmp = bakery[u][column + k];
                bakery[u][column + k] = bakery[u + len - v][column + k];
                bakery[u + len - v][column + k] = tmp;
            }
            for (int u = column - j, v = 1; u < column - j + len / 2; u++, v+=2){
                int tmp = bakery[row + k][u];
                bakery[row + k][u] = bakery[row + k][u + len - v];
                bakery[row + k][u + len - v] = tmp;
            }
            for (int u = column - j, v = 1; u < column - j + len / 2; u++, v+=2){
                int tmp = bakery[row - k][u];
                bakery[row - k][u] = bakery[row - k][u + len - v];
                bakery[row - k][u + len - v] = tmp;
            }
            for (int u = row - j; u < row - j + len; u++){
                int tmp = bakery[u][column + k];
                bakery[u][column + k] = bakery[u][column - k];
                bakery[u][column - k] = tmp;
            }
            for (int u = column - j; u < column - j + len; u++){
                int tmp = bakery[row + k][u];
                bakery[row + k][u] = bakery[row - k][u];
                bakery[row - k][u] = tmp;
            }
            int tmp = bakery[row + k][column + k];
            bakery[row + k][column + k] = bakery[row - k][column - k];
            bakery[row - k][column - k] = tmp;
            tmp = bakery[row - k][column + k];
            bakery[row - k][column + k] = bakery[row + k][column - k];
            bakery[row + k][column - k] = tmp;
        }
        for (int j = row - num; j <= row + num; j++)
            for (int k = column - num; k <= column + num; k++)
                rankpos[bakery[j][k]] = j * M + k;
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            toast[i][j] = toastpos[bakery[i][j]];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (toast[i][j] <= 0){
                closed[i][j] = 1;
                reallyclosed[i][j] = 1;
            }
            else{
                closed[i][j] = 0;
                reallyclosed[i][j] = 0;
            }
            rankpos[bakery[i][j]] = i * M + j;
            mindistance[i][j] = 1;
        }
    }
    for (int j = 0; j < N; j++){
        for (int k = 0; k < M; k++){
            if (reallyclosed[j][k])
                continue;
            for (int u = 1; u <= 1001; u++){
                if ((j + u) < N && !reallyclosed[j + u][k]){
                    mindistance[j][k] = u;
                    break;
                }
                if ((j - u) >= 0 && !reallyclosed[j - u][k]){
                    mindistance[j][k] = u;
                    break;
                }
                if ((k + u) < M && !reallyclosed[j][k + u]){
                    mindistance[j][k] = u;
                    break;
                }
                if ((k - u) >= 0 && !reallyclosed[j][k - u]){
                    mindistance[j][k] = u;
                    break;
                }
                if ((j + u) >= N && (j - u) < 0 && (k + u) >= M && (k - u) < 0){
                    mindistance[j][k] = u;
                    break;
                }
            }
        }
    }
    for (int i = T1; i < T1 + T2; i++){
        count = 0;
        row = rankpos[train[i][0]] / M;
        column = rankpos[train[i][0]] % M;
        if (toast[row][column] > 0){
            closepos[count] = row * M + column;
            count++;
        }
        int length = 1;
        while (train[i][1] >= length){
            closed[row][column] = 1;
            int min = mindistance[row][column];
            int com = 0;
            int com1 = 0;
            for (int j = min; j < 1001; j++){
                if ((row + j) < N && !closed[row + j][column]){
                    min = j;
                    break;
                }
                else if ((row - j) >= 0 && !closed[row - j][column]){
                    min = j;
                    break;
                }
                else if ((column + j) < M && !closed[row][column + j]){
                    min = j;
                    break;
                }
                else if ((column - j) >= 0 && !closed[row][column - j]){
                    min = j;
                    break;
                }
                else if ((row + j) >= N && (row - j) < 0 && (column + j) >= M && (column - j) < 0){
                    com = 1;
                    break;
                }
                if ((row + j) < N && !reallyclosed[row + j][column])
                    continue;
                if ((row - j) >= 0 && !reallyclosed[row - j][column])
                    continue;
                if ((column + j) < M && !reallyclosed[row][column + j])
                    continue;
                if ((column - j) >= 0 && !reallyclosed[row][column - j])
                    continue;
                if (com1 != j - min)
                    continue;
                com1++;
                mindistance[row][column]++;
            }
            if (com)
                break;
            int rank = 1000001;
            int newrow, newcolumn;
            if ((row + min) < N && !closed[row + min][column] && bakery[row + min][column] < rank){
                newrow = row + min;
                newcolumn = column;
                rank = bakery[row + min][column];
            }
            if ((row - min) >= 0 && !closed[row - min][column] && bakery[row - min][column] < rank){
                newrow = row - min;
                newcolumn = column;
                rank = bakery[row - min][column];
            }
            if ((column + min) < M && !closed[row][column + min] && bakery[row][column + min] < rank){
                newrow = row;
                newcolumn = column + min;
                rank = bakery[row][column + min];
            }
            if ((column - min) >= 0 && !closed[row][column - min] && bakery[row][column - min] < rank){
                newrow = row;
                newcolumn = column - min;
                rank = bakery[row][column - min];
            }
            toast[newrow][newcolumn] -= train[i][2];
            if (toast[newrow][newcolumn] > 0){
                closepos[count] = newrow * M + newcolumn;
                count++;
            }
            if (toast[newrow][newcolumn] <= 0){
                closed[newrow][newcolumn] = 1;
                reallyclosed[newrow][newcolumn] = 1;
            }
            row = newrow;
            column = newcolumn;
            length++;
        }
        for (int j = 0; j < count; j++)
            closed[closepos[j] / M][closepos[j] % M] = 0;
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (toast[i][j] <= 0)
                printf("0 ");
            else
                printf("%d ", toast[i][j]);
        }
        printf("\n");
    }
}
