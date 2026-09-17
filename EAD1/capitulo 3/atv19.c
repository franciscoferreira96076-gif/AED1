#include <stdio.h>
#include <stdlib.h>

void intercalar(int *v1, int n1, int *v2, int n2, int *v_out, int *comparacoes) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        (*comparacoes)++;
        if (v1[i] <= v2[j]) {
            v_out[k++] = v1[i++];
        } else {
            v_out[k++] = v2[j++];
        }
    }

    while (i < n1) {
        v_out[k++] = v1[i++];
    }

    while (j < n2) {
        v_out[k++] = v2[j++];
    }
}

void merge_sort_dividir(int *v, int inicio, int fim) {
    if (inicio >= fim) {
        // ETAPA: Resolver (caso base)
        return;
    }

    // ETAPA: Dividir (calcula o ponto médio)
    int meio = inicio + (fim - inicio) / 2;

    // ETAPA: Resolver (chamadas recursivas)
    merge_sort_dividir(v, inicio, meio);
    merge_sort_dividir(v, meio + 1, fim);

    // ETAPA: Combinar (a intercalação final será concluída na próxima atividade)
}

int main() {
    int v1[] = {1, 3, 5, 7};
    int v2[] = {2, 4, 6, 8};
    int n1 = 4, n2 = 4;
    int v_out[8];
    int comparacoes = 0;

    intercalar(v1, n1, v2, n2, v_out, &comparacoes);

    for (int i = 0; i < n1 + n2; i++) {
        printf("%d ", v_out[i]);
    }
    printf("\nComparacoes: %d\n", comparacoes);

    int v_busca[] = {10, 20, 30, 40};
    merge_sort_dividir(v_busca, 0, 3);

    return 0;
}