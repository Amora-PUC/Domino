//DOM_Ativi01 - Projeto Domino - etapa 5
//28/08/2024 - Grupo: AGGP

//Alexandre Maciano de Oliveira 
//Gabriel Manganiello Terra
//Gabriel Mechi Lima
//Pedro Marinho Machado

#define MAX_SAVES 11

#include <ctime>
#include <cstdlib>
#include "DOM_AGGP_Controller.h"
#include "DOM_AGGP_View.cpp"
#include "DOM_AGGP_Model.h" 


FILE *save_file;

char turno;
int op=1;
int atual=14;
int jog;
int pecasnamesa=1;
int a;
int type_game;

void versusIA(void){
	pecasnamesa=1;
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
	
	//partida contra Inteligencia Artificial
	do{
		do{		
				if(turno=='2'){
					turno='1';
					rodadaIA();
				}
				else{
					turno='1';
					a=pecasnamesa;
					mostrarMesa(pecasnamesa);
					showPlayerPieces('1');
					jog=jogada();
					if (jog == -2){
						return;
					}
					rodadaIA();
			}while(jog==1);
	} while(op==1);
	
	
	
} //fechamento funcao versusIA

void rodadaIA(void){
	int control;
	control=0;
	while(control!=-1){
		if(verificarJogada(pieces[control].numberA, pieces[control].numberB)!=0 && pieces[control].status=='2'){
			pecasnamesa++;
			mesa[pecasnamesa-1].ladoE=pieces[control].numberA;
			mesa[pecasnamesa-1].ladoD=pieces[control].numberB;
			control=-1;
		}
		else if (control>=28){
			control=0;
			pieces[atual].status='2';
			atual++;  
		}
	}
}

int verificarJogada(int ladoA, int ladoB) {
	
  
    if (ladoA == mesa[pecasnamesa-1].ladoD && ladoA<=6 && ladoA>=0 && ladoB>=0 &&ladoB<=6) {
        return 1;  //jogada valida
    }
    else if (ladoB == mesa[pecasnamesa-1].ladoD && ladoA<=6 && ladoA>=0 && ladoB>=0 &&ladoB<=6) {
        return 1;  //jogada valida
    }
    else if (ladoA == -1 || ladoB == -1) {
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
			return 1;
			break;
	    }
		case 2:{
			jogarPeca();
			
			if(verificarJogada(ladoA, ladoB)==1){
				InvertePeca(&ladoA, &ladoB);
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
				jog = 1;
				return jog;
			}
			limparTela();
			break;
	    }
		case 3:{
			mainSaveWrite();
			jog = 1;
			return jog;
			break;
	    }
		case 4:{
			mainSaveRead();
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
	versusIA();
}
void pvp(){
	prepararPartida();
}

void InvertePeca(int *ladoA, int *ladoB){
	
	//Inverte peças de LADO A PARA LADO B e vice e versa
	
	int aux;
	if (*ladoA != mesa[pecasnamesa-1].ladoD && *ladoB == mesa[pecasnamesa-1].ladoD){
		   aux = *ladoA;
		   *ladoA = *ladoB;
		   *ladoB = aux;
    } 
    
}

void jogar(void){
	
	//Inicia o Jogo de Domino
	//Chama o menu inicial do jogo e determine a opçao
	
	//InicialReadSave(); 
	
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
			 mainSaveRead();
			 arcade();
			 break;
		case 5:
			encerrarPrograma();
			exit(0);
			break;      
		default:
			errorMessage(1);
			break;
	} 
	   fClear();

     } while (option != 5);
	
}

void mainSaveRead(){

	int op;
	
	//Reune toda operação de 'Carregar jogo', carregando dependendo de SAVE, o arquivo do jogo indicado pelo usuario
	
	do{
	          check_memory_view();
	          op = Saveop();
	          
	          if(check_memory(op) == true){
  	                if(op != 0){
  	                	
  	                	
  	                	  pecasnamesa = sJogo.sPeca;
                          atual = sJogo.jogadorAtual ;
                          type_game = sJogo.jogadorComp;
    
                         for (int i = 0; i < 28; i++) {
                            pieces[i] = saves[op].pieces[i];
                            mesa[i] = saves[op].mesa[i];
                         }

  	                	
	                      readsave(op);
	                      sucessMessage(2);
	                      limparTela();
	                } else {
	                	  limparTela();
	                	  errorMessage(71);
					} 	
			  } else {
			  	    errorMessage(71);
					espaco(2);
					limparTela();   
			  }
	
      } while (op == -1);
      
}

void mainSaveWrite(){
	
	int op;
	
	do{
	check_memory_view();
	op = Saveop();
      } while (op == -1);
      
      
    sJogo.sPeca = pecasnamesa;
    sJogo.jogadorAtual = atual;
    sJogo.jogadorComp = type_game;
    
    	
	for (int i = 0; i < 28; i++) {
        saves[op].pieces[i] = pieces[i];
        saves[op].mesa[i] = mesa[i];
    }
    saves[op].sJogo.jogadorAtual = atual;
      
      
      
	 if(check_memory(op) == true){	
	 	if(Saveop2() == true){
	 		saves[op].null = false;
	 		time_data(op);
	 		writesave(op);
	 		sucessMessage(1);
		 } 
		 
	 } else {
	 	saves[op].null = false;
	 	time_data(op);
	 	writesave(op);
	 	sucessMessage(1);
	 }
	 
}

int writesave(int save){
	
	FILE *save_file = NULL;

    switch(save) {
        case 1: save_file = fopen("save1.bin", "wb"); break;
        case 2: save_file = fopen("save2.bin", "wb"); break;
        case 3: save_file = fopen("save3.bin", "wb"); break;
        case 4: save_file = fopen("save4.bin", "wb"); break;
        case 5: save_file = fopen("save5.bin", "wb"); break;
        case 6: save_file = fopen("save6.bin", "wb"); break;
        case 7: save_file = fopen("save7.bin", "wb"); break;
        case 8: save_file = fopen("save8.bin", "wb"); break;
        case 9: save_file = fopen("save9.bin", "wb"); break;
        case 10: save_file = fopen("save10.bin", "wb"); break;
        default: 
            printf("Numero de save invalido.\n");
            return false;
    }
    

    if (save_file == NULL) {
        printf("Erro ao abrir o arquivo para gravacao.\n");
        
    }

    if (fwrite(&saves[save], sizeof(struct save_data), 1, save_file) != 1) {
        printf("Erro ao gravar os dados no arquivo.\n");
        
    }

    fclose(save_file);
	return 0;
}

int readsave(int save) {
	
	//le cada save separadamente de cada jogador dependo do retorno de SAVE
	//Se save = 1, abre o save1.bin e le seu conteudo
    

    switch(save) {
        case 1: save_file = fopen("save1.bin", "rb"); break;
        case 2: save_file = fopen("save2.bin", "rb"); break;
        case 3: save_file = fopen("save3.bin", "rb"); break;
        case 4: save_file = fopen("save4.bin", "rb"); break;
        case 5: save_file = fopen("save5.bin", "rb"); break;
        case 6: save_file = fopen("save6.bin", "rb"); break;
        case 7: save_file = fopen("save7.bin", "rb"); break;
        case 8: save_file = fopen("save8.bin", "rb"); break;
        case 9: save_file = fopen("save9.bin", "rb"); break;
        case 10: save_file = fopen("save10.bin", "rb"); break;
        default: 
            printf(" numero de save invalido.\n ");
            
    }
    
         if (save_file == NULL) {
          }
             printf(" < Carregando saves > \n");

          if (fread(&saves[save], sizeof(struct save_data), 1, save_file) != 1) {
              printf(" < Carregando saves > \n");
          }
    
    fclose(save_file);
    return 0;
}


int check_memory_view(){
	int i;
	
	//Mostra os dados de salvamento (SLOT VAZIO OU PREENCHIDO)
	
	   for(i = 1; i <= MAX_SAVES - 1; i++)
		    if(saves[i].null == 1){	
		  	    SaveSlots_view (1,i);
		   } else{
		   	    SaveSlots_view (2,i);
		   }
	return 0;
}
int check_memory(int save){
	
	//Verifica se o slot de save é nulo ou não
	
		 if(saves[save].null == false){
		  	   return true;
		  } 
		   
  return false;	      
}

int InicialReadSave(){
	
	pecasnamesa = sJogo.sPeca;
    atual = sJogo.jogadorAtual ;
    type_game = sJogo.jogadorComp;
    
    for(int j = 1; j <= 10; j++){
     for (int i = 0; i < 28; i++) {
        pieces[i] = saves[j].pieces[i];
        mesa[i] = saves[j].mesa[i];
    }
      
   }
	readsave(1);
	return 0;	
}
