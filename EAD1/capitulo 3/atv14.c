#include <stdio.h>
#include <stdlib.h>

int main() {
    int cap = 3;
    int *vetor = (int *)calloc(cap, sizeof(int));

    if (vetor == NULL) {
        return 1;
    }

    for (int i = 0; i < cap; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    int nova_cap;
    scanf("%d", &nova_cap);

    if (nova_cap <= 0) {
        free(vetor);
        return 1;
    }

    int *temp = (int *)realloc(vetor, nova_cap * sizeof(int));

    if (temp == NULL) {
        free(vetor);
        return 1;
    }

    vetor = temp;

    if (nova_cap > cap) {
        for (int i = cap; i < nova_cap; i++) {
            vetor[i] = 0;
        }
    }

    printf("%d -> %d\n", cap, nova_cap);

    for (int i = 0; i < nova_cap; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    free(vetor);
    return 0;
}