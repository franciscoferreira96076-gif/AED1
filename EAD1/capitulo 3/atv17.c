#include <stdio.h>

typedef struct {
    char nome[30];
    int nivel;
    int vida;
} Personagem;

void exibir_personagem(Personagem p) {
    printf("%s %d %d\n", p.nome, p.nivel, p.vida);
}

void tentar_alterar(Personagem p) {
    p.vida = 0;
    p.nivel = 99;
    printf("%s %d %d\n", p.nome, p.nivel, p.vida);
}

int main() {
    Personagem p1 = {"Heroi", 1, 100};

    exibir_personagem(p1);

    tentar_alterar(p1);

    exibir_personagem(p1);

    return 0;
}