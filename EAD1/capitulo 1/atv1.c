#include <stdio.h>
int main() {
   int vida=100;
   int tesouro=0;//se tesouro for 0, o tesouro esta inativo
   int *pvida=&vida;
   int *ptesouro=&tesouro;
   //vida e tesouro inicializados
   printf("Vida inicial: %d\nTesouro inicial: %d",*pvida,*ptesouro);

   //Vida apos dano
   *pvida=*pvida-20;
   printf("\nVida apos dano: %d\nTesouro: %d",*pvida,*ptesouro);

   //vida apos cura
   *pvida=*pvida+10;
   printf("\nVida apos cura: %d\nTesouro: %d",*pvida,*ptesouro);

   //ativando tesouro
   *ptesouro=1;
   printf("\nVida: %d\nTesouro ativado: %d",*pvida,*ptesouro);

    return 0;
}