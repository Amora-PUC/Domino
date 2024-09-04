//DOM_Ativi01 - Projeto Domino - etapa 4
//15/08/2024 - Grupo: AGGP

//Alexandre Maciano de Oliveira 
//Gabriel Manganiello Terra
//Gabriel Mechi Lima
//Pedro Marinho Machado

#include <ctime>
#include <cstdlib>
#include "DOM_AGGP_Controller.h"
#include "DOM_AGGP_View.cpp"
#include "DOM_AGGP_Model.h" 

char turno;
int op=1;
int atual=14;
int jog;
int pecasnamesa=1;
int a;

int verificarJogada(int ladoA, int ladoB) {
    if (ladoA == mesa[pecasnamesa-1].ladoE || ladoA == mesa[pecasnamesa-1].ladoD) {
        return 1;  //jogada valida
    }
    else if (ladoB == mesa[pecasnamesa-1].ladoE || ladoB == mesa[pecasnamesa-1].ladoD) {
        return 1;  //jogada valida
    }
    else{
    	return 0;  //jogada invalida
	}

}

int jogada(void){
	int jog=jogadaOption();
	switch(jog){
		case 1:
			pieces[atual].status=turno;
			atual++;
			return jog;
		case 2:
			jogarPeca();
			if(verificarJogada(ladoA, ladoB)==1){
				pecasnamesa++;
				mesa[pecasnamesa-1].ladoE=ladoA;
				mesa[pecasnamesa-1].ladoD=ladoB;
				for(int i=0;i<28;i++){
						if(pieces[i].numberA==ladoA&&pieces[i].numberB==ladoB){
							pieces[i].status='M';
						}
				}
			}		
		case 3:
			retornarMenu();
			return -2;
	
	}
	return jog;	
}

void embaralharPecas(void){
	struct Domino copia;
	int seed=time(0);
    srand(seed);
    int x=200;
    for (int y=0;y<x;y++){
        int a=rand()%28;
        int b=rand()%28;
        copia.numberA=pieces[a].numberA;
        copia.numberB=pieces[a].numberB;
        pieces[a].numberA=pieces[b].numberA;
        pieces[a].numberB=pieces[b].numberB;
        pieces[b].numberA=copia.numberA;
        pieces[b].numberB=copia.numberB;
	}
}
void prepararPartida(void){
	//embaralha
	embaralharPecas();
	//distribui pro p1
	for(int i=0; i<7; i++)
		pieces[i].status='1';
	//distribui pro p2
	for(int i=7; i<14; i++)
		pieces[i].status='2';
	//define a primeira peça (maior peça)
	mesa[0].ladoE=-1;
	mesa[0].ladoD=-1;
	//procura uma peça [y|y]
	for (int c=0;c<7;c++){
		for (int i=0; i<14; i++){
			if(pieces[i].numberA==c && pieces[i].numberB==c){
				mesa[0].ladoE=pieces[i].numberA;
				mesa[0].ladoD=pieces[i].numberB;
				turno=pieces[i].status;
			}
		}
	}
	//se nao houver uma [y|y]...
	if (mesa[0].ladoE==-1 && mesa[0].ladoD==-1){
		for (int c=0;c<7;c++){
			for (int i=0; i<14; i++){
				if(pieces[i].numberA>=mesa[i].ladoE && pieces[i].numberB>=mesa[i].ladoD){
					mesa[0].ladoE=pieces[i].numberA;
					mesa[0].ladoD=pieces[i].numberB;
				}
			}
		}
	}
	
	mostrarPecas();
	//joga a primeira peça
	primeiraPeca(turno);
	for(int i=0;i<28;i++){
		if(pieces[i].numberA==mesa[0].ladoE&&pieces[i].numberB==mesa[0].ladoD){
			pieces[i].status='M';
		}
	}
	//partida
	do{
		if(turno=='1'){
			turno='2';
			jog=1;
			do{
				a=pecasnamesa;
				mostrarMesa(pecasnamesa);
				showPlayerPieces(turno);
				jog=jogada();
				if (jog == -2) 
				 	return;
			}while(jog==1);
		}
		else if(turno=='2'){
			turno='1';
			jog=1;
			do{
				a=pecasnamesa;
				mostrarMesa(pecasnamesa);
				showPlayerPieces(turno);
				jog=jogada();
				if (jog == -2) 
					return;	
			}while(jog==1);
		}
		else{
			op=0;
		}
	} while(op==1);
}
void arcade(void){
	prepararPartida();
}
void pvp(){
	prepararPartida();
}

void jogar(void){
	//Inicia o Jogo de Domino
	//Chama o menu inicial do jogo e determine a opçao
	
	int option;
	
	do{
	
	option=menuInicial();
	switch(option){
		case 1:
			ShowRules();
			arcade();
			break;
		case 2:
			ShowRules();
			pvp();
			break;
		case 3:
			mostrarPecas();
			break;	
		case 4:
			encerrarPrograma();
			exit(0);
			break;
		default:
			errorMessage();
			break;
	} 

     } while (option != 4);
	//mostra as peças como geradas
}
