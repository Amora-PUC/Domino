//DOM_Ativi01 - Projeto Dominó - etapa 3
//15/08/2024 - Grupo: AGGP

//Alexandre Maciano de Oliveira 
//Gabriel Manganiello Terra
//Gabriel Mechi Lima
//Pedro Marinho Machado

#include <iostream>
#include "DOM_AGGP_View.h"
#include "DOM_AGGP_Model.h"

int ladoA,ladoB;

void printWinMessage(int turno){
	printf("PARABENS JOGADOR %d!!", turno);
}

void fClear(){
    char carac;
    while ((carac = fgetc(stdin)) != EOF && carac != '\n') {}
}
void mostrarMesa(int pecasnamesa){
	printf("\n\nMESA:\n");
	for(int i=0;i<pecasnamesa;i++){
		printf("[%d|%d]", mesa[i].ladoE,mesa[i].ladoD);
	}
}

void limparTela(void){
	system("cls");
}

void jogarPeca(void){
	printf("\nDigite a peca que deseja jogar (formato [a|b])([-1|-1] para sair):");
	fClear();
	scanf("[%d|%d]", &ladoA, &ladoB);
 
    if(ladoA > 6 || ladoA < -1 || ladoB > 6 || ladoB < -1)
	{
       printf("A peca nao existe, tente outra!");
	   return;

	}


}
int jogadaOption(void){
	printf("\n\nO que deseja fazer?\n");
	printf("\n");
	printf("1. Comprar peca");
	printf("\n");
	printf("2. Jogar uma peca");
	printf("\n");
	printf("3. Encerrar o jogo e retornar para o menu");
	printf("\n");
	fClear();
	
	int jogadaop;
	scanf("%d", &jogadaop);
	return jogadaop;
}

void showPlayerPieces(char turno){
	printf("\n\nVEZ DO JOGADOR %c: (pecas disponiveis)\n", turno);
	for (int i=0;i<28;i++){
		if (pieces[i].status==turno){
			printf("[%d|%d]",pieces[i].numberA,pieces[i].numberB);
		}
	}
}

void primeiraPeca(char turno){
	printf("\n\nMESA: (Jogador %c)\n", turno);
	printf("[%d|%d]", mesa[0].ladoE, mesa[0].ladoD);
}

int mostrarPecas(void){
	for (int i=0; i<28; i++)
		printf("[%d|%d]", pieces[i].numberA, pieces[i].numberB);
	return 0;
}

void encerrarPrograma()
{
	printf("\n\nEncerrando o programa!\n");
}


void errorMessage(void){
	printf("ERROR");
}

void retornarMenu()
{
	printf("\nRetornando para o menu!\n");
}
 
void espaco(void){
	printf("\n");
}

int menuInicial(void){
	int option;
	printf("\nBEM VINDO(A) AO JOGO DE DOMINO!\n");
	printf("=========================================\n");
	printf("\nSelecione uma das seguintes opcoes:\n");
	printf("\n1. Iniciar jogo modo Arcade.\n");
	printf("2. Iniciar jogo multiplayer (2 jogadores).\n");
	printf("3. Mostrar embaralhamento atual.\n");
    printf("4. Sair do jogo\n");
	printf("\n=========================================\n");
	scanf("%d", &option);

	return option;
}

void opcaoinvalida()
  {
	printf("\nOpcao invalida, tente novamente!\n");
  }


int ShowRules(){
	
	system("cls");
	const char* rules[]
	{
		" ====================================   REGRAS ====================================== ",
        "                  									                                   ",
        " Adotaremos as regras mais simples do jogo: cada jogador inicia com sete pecas obtidas ",
        " aleatoriamente e pode comprar quantas vezes for necessario sempre que precisar de     ",
        " uma peca para poder jogar ou se quiser blefar. O jogo inicia-se com o jogador que     ",
        " tiver a peca seis-seis.                                                               ",
        "  Caso ninguem tenha essa peca, o jogo inicia-se com o jogador que tiver a peca com os  ",
        " numeros repetidos mais altos, ou seja, cinco-cinco, quatro-quatro, e assim suce-      ",
        " ssivamente. O jogo acontece no sentido anti-horario e os jogadores devem colocar pecas",
        " que tenham os mesmos numeros das pecas que se encontram nas 2 extremidades da mesa do ",
        " jogo. Um conceito importante para a estrategia do domino eh que o jogador que comeca a",
        " partida leva vantagem. Antes de cada jogada o jogador pode comprar quantas pecas      ",
        " quiser do deposito de pecas ainda disponiveis, lembrando sempre que perde a partida   ",
        " aquele que no final tiver maior quantidade de pecas.                                  ",
        "  Cada jogador, no seu turno, deve colocar uma das suas pecas em uma das 2 extremidades",
        " abertas na mesa, de forma que os pontos de um dos lados coincidam com os pontos da    ",
        " extremidade onde esta sendo colocada. As pecas dobradas sao colocadas de maneira      ",
        " transversal para facilitar sua localizacao. Quando o jogador coloca sua peca sobre a  ",
        " mesa, seu turno se acaba e passa-se então ao proximo jogador.  Se um jogador nao puder",
        " jogar, devera comprar do monte disponivel tantas pecas                                ",
        " quanto forem necessarias.                                                             ",
		"                                                                                      ",      
    };
        int linhas = sizeof(rules) / sizeof(rules[0]);
	
	    for (int i = 0; i < linhas; i++) {
            printf("%s\n", rules[i]);
        }
	
	 system("pause");
	 system("cls");
}