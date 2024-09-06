//DOM_Ativi01 - Projeto Domino - etapa 4
//28/08/2024 - Grupo: AGGP

//Alexandre Maciano de Oliveira 
//Gabriel Manganiello Terra
//Gabriel Mechi Lima
//Pedro Marinho Machado

#include "DOM_AGGP_Model.h"

//cria a estrutura Domino
struct Domino {
    int numberA;
    int numberB;
    char status;
};
struct Domino pieces[28];

//gera um array de 28 peças dessa estrutura (domino)
void gerarPecas(void) {
    int p, i, j;
    // gerar as 28 pecas
    p = 0;
    for (i = 0; i <= 6; i++) {
        for (j = i; j <= 6; j++) {
            pieces[p].numberA = i;		
            pieces[p].numberB = j;
            pieces[p].status = 'M';
            p++;
        }
    }
}

struct sitJogo{
	int sPeca;
	int jogadorAtual;
	int jogadorComp;
	int mesaDj;
	int mesaEj;
}; 
struct sitJogo sJogo;

//cria a estrutura Mesa

struct Mesa {
    int ladoE;
    int ladoD;
} mesa[28];
