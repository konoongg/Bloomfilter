#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define CountBsha_1 21
#define SIZE_HASHTABLE 100000

int CreateHash(char* sha_1Hash, int k) {
    int hash = 0;
    for (int i = 0; i < CountBsha_1; ++i) {
        hash = ((23 + k) * (sha_1Hash[i] + hash)) % 5381;
    }
    return hash % SIZE_HASHTABLE;
}


void AddToFilter(char* sha_1Hash, char* filter) {
    int firstHash = CreateHash(sha_1Hash, 1);
    int secondHash = CreateHash(sha_1Hash, 2);
    filter[firstHash / 8] |= 1 << (firstHash % 8);
    filter[secondHash / 8] |= 1 << (secondHash % 8);
}

void CheckIsInFilter(char* sha_1Hash, char* filter) {
    int firstHash = CreateHash(sha_1Hash, 1);
    int secondHash = CreateHash(sha_1Hash, 2);
    int firstArrayKey = filter[firstHash / 8] >> (firstHash % 8);
    int secondArrayKey = filter[secondHash / 8] >> (secondHash % 8);
    printf("%d", (firstArrayKey & 1) * (secondArrayKey & 1));
}

int main(void) {
    int countInBd, countCheckInBd;
    scanf("%d %d", &countInBd, &countCheckInBd);
    char* filter = (char*)calloc(SIZE_HASHTABLE * 2, sizeof(char));
    char sha_1Hash[CountBsha_1] = { 0 };
    for (int i = 0; i < countInBd; ++i) {
        scanf("%s", &sha_1Hash);
        AddToFilter(sha_1Hash, filter);
    }
    for (int i = 0; i < countCheckInBd; ++i) {
       scanf("%s", &sha_1Hash);
       CheckIsInFilter(sha_1Hash, filter);
    }
    return 0;
}

