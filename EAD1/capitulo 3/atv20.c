#include <stdio.h>
#include <stdlib.h>

typedef enum {
    GUERREIRO = 1,
    MAGO,
    ARQUEIRO
} Classe;

typedef struct {
    int x;
    int y;
} Posicao;

typedef struct {
    int id;
    char nome[30];
    Classe classe;
    Posicao pos;
} Personagem;

typedef struct {
    Personagem *membros;
    int qtd;
    int cap;
} Equipe;

const char* classe_para_texto(Classe c) {
    switch (c) {
        case GUERREIRO: return "Guerreiro";
        case MAGO: return "Mago";
        case ARQUEIRO: return "Arqueiro";
        default: return "Desconhecido";
    }
}

void inicializar_equipe(Equipe *eq) {
    eq->cap = 2;
    eq->qtd = 0;
    eq->membros = (Personagem *)calloc(eq->cap, sizeof(Personagem));
}

void cadastrar(Equipe *eq) {
    if (eq->qtd == eq->cap) {
        int nova_cap = eq->cap * 2;
        Personagem *temp = (Personagem *)realloc(eq->membros, nova_cap * sizeof(Personagem));
        if (temp == NULL) return;
        eq->membros = temp;
        eq->cap = nova_cap;
    }

    Personagem *p = &eq->membros[eq->qtd];
    p->id = eq->qtd + 1;

    int i = 0;
    char c;
    getchar();
    while (i < 29) {
        c = getchar();
        if (c == '\n' || c == EOF) break;
        p->nome[i++] = c;
    }
    p->nome[i] = '\0';

    int cl;
    scanf("%d", &cl);
    p->classe = (Classe)cl;

    scanf("%d %d", &p->pos.x, &p->pos.y);

    eq->qtd++;
}

void listar(Equipe *eq) {
    for (int i = 0; i < eq->qtd; i++) {
        printf("ID: %d | Nome: %s | Classe: %s | Pos: (%d, %d)\n",
               eq->membros[i].id,
               eq->membros[i].nome,
               classe_para_texto(eq->membros[i].classe),
               eq->membros[i].pos.x,
               eq->membros[i].pos.y);
    }
}

int buscar(Equipe *eq, int id) {
    for (int i = 0; i < eq->qtd; i++) {
        if (eq->membros[i].id == id) return i;
    }
    return -1;
}

void alterar(Equipe *eq) {
    int id;
    scanf("%d", &id);
    int idx = buscar(eq, id);
    if (idx != -1) {
        scanf("%d %d", &eq->membros[idx].pos.x, &eq->membros[idx].pos.y);
    }
}

int main() {
    Equipe eq;
    inicializar_equipe(&eq);
    int opcao;

    do {
        scanf("%d", &opcao);
        if (opcao == 1) {
            cadastrar(&eq);
        } else if (opcao == 2) {
            listar(&eq);
        } else if (opcao == 3) {
            int id;
            scanf("%d", &id);
            int idx = buscar(&eq, id);
            if (idx != -1) {
                printf("ID: %d | Nome: %s | Classe: %s | Pos: (%d, %d)\n",
                       eq.membros[idx].id,
                       eq.membros[idx].nome,
                       classe_para_texto(eq.membros[idx].classe),
                       eq.membros[idx].pos.x,
                       eq.membros[idx].pos.y);
            }
        } else if (opcao == 4) {
            alterar(&eq);
        }
    } while (opcao != 0);

    free(eq.membros);
    return 0;