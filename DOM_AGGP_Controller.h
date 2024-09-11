//DOM_Ativi01 - Projeto Domino - etapa 5
//28/08/2024 - Grupo: AGGP

//Alexandre Maciano de Oliveira 
//Gabriel Manganiello Terra
//Gabriel Mechi Lima
//Pedro Marinho Machado

#include <iostream>
int verificarJogada(int ladoA, int ladoB);
void rodadaIA(void);
int jogada(void);
void embaralharPecas(void);
void jogar(void);
void InvertePeca(int *ladoA, int *ladoB);

int check_memory_view();
int check_memory(int save);

int readsave(int save);
int writesave(int save);

void mainSaveRead();
void mainSaveWrite();
int InicialReadSave();
