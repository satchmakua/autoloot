// Written in C

// Satchel Hamilton
// CS 450
// Project 4 - Autoloot

#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct {
    char item[128];
    int weight;
    int value;
} Loot;

int max(int a, int b) { return (a > b) ? a : b; }

int main()
{
    clock_t start = clock();
    char input[200];
    Loot loot[200];
    Loot ordered[200];
    int i, w, totalWeight, line = 0, sum = 0, sumw = 0;
    scanf("%d", &totalWeight);
    fgets(input, 200, stdin); 
    while (scanf("%100[^;];%d;%d", loot[line].item, &loot[line].weight, &loot[line].value) > 0) {
        fgets(input, 200, stdin); 
        ++line;
    }

    int K[line + 1][totalWeight + 1];
    for (i = 0; i <= line; i++) {
        for (w = 0; w <= totalWeight; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (loot[i - 1].weight <= w)
                K[i][w] = max(loot[i - 1].value +
                K[i - 1][w - loot[i - 1].weight], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    int res = K[line][totalWeight];
    w = totalWeight;

    for (i = line; i > 0 && res > 0; i--) {
        if (res == K[i - 1][w]){
            continue;
        } else {
            strcpy(ordered[i - 1].item, loot[i - 1].item);
            ordered[i - 1].weight = loot[i - 1].weight;
            ordered[i - 1].value = loot[i - 1].value;
            sumw += loot[i - 1].weight;
            sum +=  loot[i - 1].value;
            res = res - loot[i - 1].value;
            w = w - loot[i - 1].weight;
        }
    }

    for (i = 0; i < line; i++) {
        if (ordered[i].value != 0 && ordered[i].weight != 0)
            printf("%s, %d, %d\n", ordered[i].item, ordered[i].weight, ordered[i].value);
    }


    printf("final weight: %d\n", sumw);
    printf("final value: %d\n", sum);

    double time_taken_in_seconds = (double)( clock() - start ) / CLOCKS_PER_SEC;
    double time_taken_in_microseconds = time_taken_in_seconds * 1000000.0;
    
    printf("time taken in microseconds: %f\n", time_taken_in_microseconds);
    return 0;
}