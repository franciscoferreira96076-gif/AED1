#include <stdio.h>


struct Personagem {
    int identificador;
    char nome[50];
    int vida;
    int pontuacao;
    int posicao;
};


void mostrarPersonagem(struct Personagem p) {
    printf("\n--- Personagem ---\n");
    printf("ID: %d\n", p.identificador);
    printf("Nome: %s\n", p.nome);
    printf("Vida: %d\n", p.vida);
    printf("Pontuacao: %d\n", p.pontuacao);
    printf("Posicao: %d\n", p.posicao);
}

int main() {


    struct Personagem jogador = { 1,"Guerreiro",100,0,10};

    
    printf("Estado inicial:");
    mostrarPersonagem(jogador);

    jogador.vida -= 20;
    jogador.pontuacao += 150;
    jogador.posicao += 5;

    if (jogador.vida < 0) {
        jogador.vida = 0;
    }

    if (jogador.vida > 100) {
        jogador.vida = 100;
    }

    if (jogador.pontuacao < 0) {
        jogador.pontuacao = 0;
    }

    if (jogador.posicao < 0) {
        jogador.posicao = 0;
    }

    
    printf("\nEstado apos as alteracoes:");
    mostrarPersonagem(jogador);

    return 0;
}