/*
 * Ponteiros + Alocação Dinâmica (vetor e matriz) com Raylib
 * ---------------------------------------------------------
 * 1: Redimensionamento em tempo real com realloc (ESPAÇO / BACKSPACE).
 * 2: Matriz como mapa de calor ao passar as bolas + contador de células visitadas.
 */

#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600
#define TAM_CELULA 40

typedef struct
{
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;


/* =========================
   MATRIZ
   ========================= */

int **criarMatriz(int linhas, int colunas){
    int **matriz = (int **)malloc(linhas * sizeof(int *));

    if (matriz == NULL){
        return NULL;
    }

    for (int i = 0; i < linhas; i++){
        matriz[i] = (int *)malloc(colunas * sizeof(int));

        if (matriz[i] == NULL) {
            // Libera as linhas que já foram alocadas
            for (int j = 0; j < i; j++)
            {
                free(matriz[j]);
            }

            free(matriz);
            return NULL;
        }

        for (int j = 0; j < colunas; j++){
            matriz[i][j] = 0;
        }
    }

    return matriz;
}


void liberarMatriz(int **matriz, int linhas)
{
    if (matriz == NULL)
    {
        return;
    }

    for (int i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }

    free(matriz);
}


void desenharMatriz(int **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            Color cor;

            if (matriz[i][j] == 1)
            {
                // Células visitadas
                cor = (Color){60, 100, 150, 255};
            }
            else
            {
                // Células não visitadas
                cor = (Color){15, 30, 55, 255};
            }

            DrawRectangle(
                j * TAM_CELULA,
                i * TAM_CELULA,
                TAM_CELULA - 2,
                TAM_CELULA - 2,
                cor
            );
        }
    }
}


/* =========================
   BOLAS
   ========================= */

void inicializarBola(Bola *b)
{
    b->pos = (Vector2){
        (float)GetRandomValue(50, LARGURA_JANELA - 50),
        (float)GetRandomValue(50, ALTURA_JANELA - 50)
    };

    // Evita velocidade zero
    float vx = 0;
    float vy = 0;

    while (vx == 0)
    {
        vx = (float)GetRandomValue(-4, 4);
    }

    while (vy == 0)
    {
        vy = (float)GetRandomValue(-4, 4);
    }

    b->vel = (Vector2){vx, vy};

    b->raio = (float)GetRandomValue(10, 25);

    b->cor = (Color){
        (unsigned char)GetRandomValue(100, 255),
        (unsigned char)GetRandomValue(100, 255),
        (unsigned char)GetRandomValue(100, 255),
        255
    };
}


Bola *criarBolas(int quantidade)
{
    Bola *bolas = (Bola *)malloc(quantidade * sizeof(Bola));

    if (bolas == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < quantidade; i++)
    {
        inicializarBola(&bolas[i]);
    }

    return bolas;
}


void atualizarBola(Bola *b)
{
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    // Colisão com as paredes laterais
    if (b->pos.x - b->raio < 0)
    {
        b->pos.x = b->raio;
        b->vel.x *= -1;
    }

    if (b->pos.x + b->raio > LARGURA_JANELA)
    {
        b->pos.x = LARGURA_JANELA - b->raio;
        b->vel.x *= -1;
    }

    // Colisão com as paredes superior/inferior
    if (b->pos.y - b->raio < 0)
    {
        b->pos.y = b->raio;
        b->vel.y *= -1;
    }

    if (b->pos.y + b->raio > ALTURA_JANELA)
    {
        b->pos.y = ALTURA_JANELA - b->raio;
        b->vel.y *= -1;
    }
}


/* =========================
   MAIN
   ========================= */

int main(void)
{
    srand((unsigned int)time(NULL));

    InitWindow(
        LARGURA_JANELA,
        ALTURA_JANELA,
        "Ponteiros e Alocacao Dinamica - Raylib"
    );

    SetTargetFPS(60);

    int linhas = ALTURA_JANELA / TAM_CELULA;
    int colunas = LARGURA_JANELA / TAM_CELULA;

    // Cria a matriz
    int **grade = criarMatriz(linhas, colunas);

    if (grade == NULL)
    {
        CloseWindow();
        return 1;
    }

    // Quantidade inicial de bolas
    int quantidadeBolas = 12;

    Bola *bolas = criarBolas(quantidadeBolas);

    if (bolas == NULL)
    {
        liberarMatriz(grade, linhas);
        CloseWindow();
        return 1;
    }

    int celulasVisitadas = 0;


    /* =========================
       LOOP PRINCIPAL
       ========================= */

    while (!WindowShouldClose())
    {
        /* -------------------------
           ADICIONAR BOLA
           ESPAÇO
           ------------------------- */

        if (IsKeyPressed(KEY_SPACE))
        {
            int novaQuantidade = quantidadeBolas + 1;

            Bola *temp = (Bola *)realloc(
                bolas,
                novaQuantidade * sizeof(Bola)
            );

            if (temp != NULL)
            {
                bolas = temp;
                quantidadeBolas = novaQuantidade;

                // Inicializa a nova bola
                inicializarBola(&bolas[quantidadeBolas - 1]);
            }
        }


        /* -------------------------
           REMOVER BOLA
           BACKSPACE
           ------------------------- */

        if (IsKeyPressed(KEY_BACKSPACE) && quantidadeBolas > 0)
        {
            int novaQuantidade = quantidadeBolas - 1;

            if (novaQuantidade == 0)
            {
                free(bolas);
                bolas = NULL;
                quantidadeBolas = 0;
            }
            else
            {
                Bola *temp = (Bola *)realloc(
                    bolas,
                    novaQuantidade * sizeof(Bola)
                );

                if (temp != NULL)
                {
                    bolas = temp;
                    quantidadeBolas = novaQuantidade;
                }
            }
        }


        /* -------------------------
           ATUALIZA AS BOLAS
           ------------------------- */

        for (int i = 0; i < quantidadeBolas; i++)
        {
            atualizarBola(&bolas[i]);

            // Descobre a célula da matriz onde a bola está
            int lin = (int)(bolas[i].pos.y / TAM_CELULA);
            int col = (int)(bolas[i].pos.x / TAM_CELULA);

            // Verifica se está dentro da matriz
            if (lin >= 0 &&
                lin < linhas &&
                col >= 0 &&
                col < colunas)
            {
                // Se ainda não visitou a célula
                if (grade[lin][col] == 0)
                {
                    grade[lin][col] = 1;
                    celulasVisitadas++;
                }
            }
        }


        /* =========================
           DESENHO
           ========================= */

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Desenha a matriz
        desenharMatriz(grade, linhas, colunas);

        // Desenha as bolas
        for (int i = 0; i < quantidadeBolas; i++)
        {
            DrawCircleV(
                bolas[i].pos,
                bolas[i].raio,
                bolas[i].cor
            );
        }

        // Informações na tela
        DrawText(
            TextFormat(
                "Bolas Ativas: %d  (ESPACO: +1 | BACKSPACE: -1)",
                quantidadeBolas
            ),
            10,
            10,
            18,
            GREEN
        );

        DrawText(
            TextFormat(
                "Celulas Visitadas: %d / %d",
                celulasVisitadas,
                linhas * colunas
            ),
            10,
            32,
            18,
            YELLOW
        );

        DrawText(
            "Pressione ESC para sair",
            10,
            ALTURA_JANELA - 25,
            16,
            WHITE
        );

        EndDrawing();
    }


    /* =========================
       LIBERA MEMORIA
       ========================= */

    if (bolas != NULL)
    {
        free(bolas);
    }

    liberarMatriz(grade, linhas);

    CloseWindow();

    return 0;
}