#include <stdio.h>

typedef struct {
    char nome[30];
    int vida;
    int posicao;
    int pontuacao;
} Personagem;

void alterar_vida(Personagem *p, int nova_vida) {
    if (p == NULL) return;
    if (nova_vida < 0) nova_vida = 0;
    if (nova_vida > 100) nova_vida = 100;
    p->vida = nova_vida;
}

void avançar_posicao(Personagem *p, int passos) {
    if (p == NULL) return;
    if (passos < 0) return;
    p->posicao += passos;
}

void adicionar_pontos(Personagem *p, int pontos) {
    if (p == NULL) return;
    if (pontos < 0) return;
    (*p).pontuacao += pontos;
}

int main() {
    Personagem p = {"Heroi", 100, 0, 0};

    alterar_vida(&p, 80);
    avançar_posicao(&p, 5);
    adicionar_pontos(&p, 150);

    printf("%s %d %d %d\n", p.nome, p.vida, p.posicao, p.pontuacao);

    return 0;
}