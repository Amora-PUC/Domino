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

FILE *save_game;   //Arquivo estado das peças dos jogadores
FILE *save_mesa;   //Arquivo estado das peças da mesa
FILE *save_status;     //Arquivo estado da situação do jogo

char turno;
int op=1;
int atual=14;
int jog;
int pecasnamesa=1;
int a;
int type_game;


void write_save(){
	
	sJogo.sPeca = a;
    sJogo.jogadorAtual = atual;
    sJogo.jogadorComp = type_game;
	
	//Abre arquivos de save para gravação/leitura estado do jogo
	
	
	int cont_error1 = 0;
	int cont_error2 = 0;
	int i;
	
	//Abre FILE SAVE_GAME
	
	if((save_game = fopen("save_game","w") ) == NULL){
        cont_error1++;
	}
	
	//Abre FILE SAVE_MESA
	
	if((save_mesa = fopen("save_mesa","w")) == NULL){
        cont_error1++;
	}
	
	//Abre FILE SAVE_STATUS
	
	if((save_status = fopen("save_status","w")) == NULL){
        cont_error1++;
	}
	
	
	//Grava em SAVE_GAME as peças dos jogadores
	
	for(i = 0; i < 28; i++){
		
		if(fwrite(&pieces[i], sizeof(struct Domino), 1, save_game) != 1){
			cont_error2++;
		}
		
    }
    
    //Grava em SAVE_MESA as peças na mesa do jogo
		
	for(i = 0; i < 28; i++){
		
		if(fwrite(&mesa[i], sizeof(struct Domino), 1, save_mesa) != 1){
			cont_error2++;
		}
		
    }
	
	//Grava em SAVE_STATUS a situação do jogo	
		
	if(fwrite(&sJogo, sizeof(struct Domino), 1, save_status) != 1){
			cont_error2++;
	}	
		

	//Verifica se há erros
	
	

	if(cont_error1 == 0 && cont_error2 == 0){
		sucessMessage(1);
	} else {
		errorMessage(41);
		errorMessage(51);
		errorMessage(42);
		errorMessage(52);
		errorMessage(43);
		errorMessage(53);
	}
	
	fclose(save_game);
	fclose(save_mesa);
	fclose(save_status);
 

}

void read_save(){
	
	sJogo.sPeca = pecasnamesa;
    sJogo.jogadorAtual = atual;
    sJogo.jogadorComp = type_game;
	
	int cont_error1 = 0;
	int cont_error2 = 0;
	
	//Carrega estado das peças do jogo
	
	int i = 0;
	if((save_game = fopen("save_game","r")) == NULL){
       cont_error1++;
	}
	
	//Carrega estado das peças da mesa
	
	if((save_mesa = fopen("save_mesa","r")) == NULL){
        cont_error1++;
	}
	
	//Carrega estado das peças da situação
	
	if((save_status = fopen("save_status","r")) == NULL){
        cont_error1++;
	}
	
	  for(i = 0; i < 28; i++){
	    if(fread(&pieces[i], sizeof(struct Domino), 1, save_game) != 1){
			   cont_error2++;
		    }
      }
	  
	  for(i = 0; i < 28; i++){
	    if(fread(&mesa[i], sizeof(struct Domino), 1, save_mesa) != 1){
			   cont_error2++;
		    }
      }
      
        if(fread(&sJogo, sizeof(struct Domino), 1, save_status) != 1){
			   cont_error2++;
		    }

	
	if(cont_error1 == 0 && cont_error2 == 0){
		sucessMessage(2);
	} else {
		errorMessage(71);
		errorMessage(72);
		errorMessage(73);
	}
	
	fclose(save_game);
	fclose(save_mesa);
	fclose(save_status);
}

int verificarJogada(int ladoA, int ladoB) {
    if (ladoA == mesa[pecasnamesa-1].ladoE || ladoA == mesa[pecasnamesa-1].ladoD) {
        return 1;  //jogada valida
    }
    else if (ladoB == mesa[pecasnamesa-1].ladoE || ladoB == mesa[pecasnamesa-1].ladoD) {
        return 1;  //jogada valida
    }
    else if (ladoB == -1 || ladoB == -1) {
        return 2;  //Voltar
    }
    else{
    	return 0;  //jogada invalida
	}

}

int jogada(void){
	int jog=jogadaOption();
	
	switch(jog){
		case 1:{
			pieces[atual].status=turno;
			atual++;
			limparTela();
			return jog;
			break;
	    }
		case 2:{
			jogarPeca();
			if(verificarJogada(ladoA, ladoB)==1){
				pecasnamesa++;
				mesa[pecasnamesa-1].ladoE=ladoA;
				mesa[pecasnamesa-1].ladoD=ladoB;
				for(int i=0;i<28;i++){
						if(pieces[i].numberA==ladoA&&pieces[i].numberB==ladoB){
							pieces[i].status='M';
						}
				limparTela();		
				}
			} else if (verificarJogada(ladoA, ladoB)== 2){
				jog = 1;
				limparTela();
				return jog;
			} else {
				errorMessage(2);
			}
			limparTela();
			break;
	    }
		case 3:{
			write_save();
			jog = 1;
			return jog;
			break;
	    }
		case 4:{
			read_save();
			jog = 1;
			return jog;
			break;
		}
		case 5:{
			limparTela();
			retornarMenu();
			return -2;
			break;
		}
	    default:{
	    errorMessage(1);
	    jog = 1;
	    return jog;
	    break;
	    }
	
	return jog;	
   }
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
	
	//joga a primeira peça
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
	option = 0;	
	option=menuInicial();
	switch(option){
		case 1:
			ShowRules();
			arcade();
			type_game = 1;
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
			errorMessage(1);
			break;
	} 
	   fClear();

     } while (option != 4);
	//mostra as peças como geradas
}
