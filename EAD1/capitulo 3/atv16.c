#include <stdio.h>

typedef struct {
    char nome[30];
    int nivel;
    int vida;
} Personagem;

void copiar_texto(char *destino, const char *origem, int tamanho_max) {
    int i = 0;
    while (origem[i] != '\0' && i < tamanho_max - 1) {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

Personagem criar_personagem(const char *nome, int nivel, int vida) {
    Personagem p;
    copiar_texto(p.nome, nome, 30);
    p.nivel = nivel;
    p.vida = vida;
    return p;
}

void alterar_nome(Personagem *p) {
    char novo_nome[30];
    int i = 0;
    char c;

    while (i < 29) {
        c = getchar();
        if (c == '\n' || c == EOF) {
            break;
        }
        novo_nome[i] = c;
        i++;
    }
    novo_nome[i] = '\0';

    copiar_texto(p->nome, novo_nome, 30);
}

int main() {
    Personagem p1 = {"Heroi", 1, 100};

    Personagem p2 = criar_personagem("Guerreiro", 5, 250);

    alterar_nome(&p2);

    printf("%s %d %d\n", p2.nome, p2.nivel, p2.vida);

    return 0;
}