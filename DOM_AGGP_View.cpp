//DOM_Ativi01 - Projeto Domino - etapa 5
//28/08/2024 - Grupo: AGGP

//Alexandre Maciano de Oliveira 
//Gabriel Manganiello Terra
//Gabriel Mechi Lima
//Pedro Marinho Machado

#include <time.h>
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

void pausaTela(void){
	system("pause");
}

void limparTela(void){
	system("cls");
}

void espaco(int qntd){
	
	for(int i = 1; i <= qntd; i++){
		printf("\n");
	}
}

void errorMessage(int id){
	
	//Mostra a mensagens de erro correspondentes a variável de entrada ID
	
	switch(id){
		
		case 1:{
			printf("\n <ERRO> A opcao selecionada nao eh valida \n\n ");
			pausaTela();
			limparTela();
			break;
		}
		case 2:{
			printf("\n <ERRO> A peca selecionada nao pode ser inserida \n\n ");
			pausaTela();
			limparTela();
			break;
		}
		case 3:{
			printf("\n <ERRO> Peca selecionada nao existe \n\n ");
			pausaTela();
			limparTela();
			break;
		}
		
		//Erros de abertura
		
		case 41:{
			printf("O arquivo SAVE_GAME nao pode ser aberto para gravacao\n");
			break;
		}
		case 42:{
			printf("O arquivo SAVE_MESA nao pode ser aberto para gravacao\n");
			break;
		}
		case 43:{
			printf("O arquivo SAVE_ST nao pode ser aberto para gravacao\n");
			break;
		}
		
		//Erros de leitura
		
		case 51:{
			printf("O arquivo SAVE_GAME nao pode ser aberto para leitura\n");
			break;
		}
		case 52:{
			printf("O arquivo SAVE_MESA nao pode ser aberto para leitura\n");
			break;
		}
		case 53:{
			printf("O arquivo SAVE_STATUS nao pode ser aberto para leitura\n");
			break;
		}
		
		//Erros de gravacao
		
		case 61:{
			printf("Erro na gravacao de SAVE_GAME\n");
			break;
		}
		case 62:{
			printf("Erro na gravacao de SAVE_MESA\n");
			break;
		}
		case 63:{
			printf("Erro na gravacao de SAVE_STATUS\n");
			break;
		}
	
	    
	    //Erros de leitura
	    
	    case 71:{
	    	printf(" <Erro> O arquivo esta vazio, tente outro \n");
			break;
		}
		case 72:{
	    	printf("Erro na leitura de SAVE_MESA\n");
			break;
		}
		case 73:{
	    	printf("Erro na leitura de SAVE_STATUS\n");
			break;
		}
	
   }

}

void sucessMessage(int id){
	
	switch(id){
		
		case 1:{

			printf("\n < O jogo foi salvo com sucesso > \n\n");
			pausaTela();
			limparTela();
			break;
		}
		case 2:{
			
			printf("\n < O jogo foi carregado com sucesso > \n\n");
			pausaTela();
			limparTela();
			break;
		}
		
		
	}
}


void time_data(int num){
	
	//Usa a biblioteca <time.h> para determinar momento exato de um save e armazena no momento em que um save é gravado
	
	time_t now;
	struct tm *info_time;
	
	time(&now);
	
	info_time = localtime(&now);
	
	saves[num].timedata.second = info_time->tm_sec;
	saves[num].timedata.minute = info_time->tm_min;
	saves[num].timedata.hour = info_time->tm_hour;
	saves[num].timedata.day = info_time->tm_mday;
	saves[num].timedata.month = info_time->tm_mon + 1;
	saves[num].timedata.year = info_time->tm_year + 1900;  
	
}


int SaveSlots_view (int id, int num){
    
    //Permite a visualização dos slots de salvamento
    // 1 - SLOT VAZIO, 2 - SAVE PREENCHIDO
	
	int second = saves[num].timedata.second;
	int minute = saves[num].timedata.minute;
	int hour = saves[num].timedata.hour;
	int day = saves[num].timedata.day;
	int month = saves[num].timedata.month;
	int year = saves[num].timedata.year;
	
	 switch(id){
	 	
	 	    case 1:{
	 	    	  printf(" %d - [ SLOT VAZIO ]\n", num);
			}
			break;
			case 2:{
	 	    	  printf(" %d - [ SAVE PREENCHIDO %02d:%02d:%02d | %02d/%02d/%04d]\n", num, hour, minute, second, day, month, year);
			break;
			}
			
	  }
    
    return 0;
	}
	
int Saveop() {
	
    // Coleta a opção de save pelo usuário
    int op;

    do {
        printf("\n\nSelecione o save desejado (1 a 10) ou 0 para cancelar:\n> ");
        scanf("%d", &op);
        
        if (op == 0) {
            // O usuário decidiu cancelar
            return 0;
        } else if (op >= 1 && op <= 10) {
            // Entrada válida
            limparTela();
            return op;
        } else {
            // Entrada inválida, mostra uma mensagem de erro e pede novamente
            errorMessage(1);
        }

    } while (op < 1 || op > 10); // Continua pedindo enquanto o valor não for entre 1 e 10 ou 0

    return op;
}

int Saveop2() {
    int resposta;

    // Pergunta ao usuário
    espaco(1);
    printf("Save ja existente, deseja sobrescrever esse save? (1 para Sim, 0 para Nao): ");
    
    // Lê a resposta do usuário
    scanf("%d", &resposta);

    
    if (resposta == 1) {
        return 1; // Deseja sobrescrever
    } else if (resposta == 0) {
        return 0; // Não deseja sobrescrever
    } else {
        printf("Entrada inválida! Por favor, insira 1 para Sim ou 0 para Nao.\n");
        return Saveop2(); 
    }
}



void jogarPeca(void){
	
	//Exibe a seleção de peça para a jogada 
	
	printf("\nDigite a peca que deseja jogar ( OBS: formato [a|b] ) ([-1|-1] para sair): \n > ");
	fClear();
	scanf("[%d|%d]", &ladoA, &ladoB);
 
    if(ladoA > 6 || ladoA < -1 || ladoB > 6 || ladoB < -1)
	{
	   errorMessage(3);
	   return;
	}
}
int jogadaOption(void){
	
	//Exibe o menu durante o jogo
	printf("\n\nO que deseja fazer?\n");
	printf("1. Comprar peca\n");
	printf("2. Jogar uma peca\n");
	printf("3. Salvar jogo\n");
	printf("4. Carregar jogo\n");
	printf("5. Encerrar o jogo e retornar para o menu \n\n> ");
	fClear();
	
	int jogadaop;
	scanf("%d", &jogadaop);
	espaco(1);
	return jogadaop;
	
}

void showPlayerPieces(char turno){
	
	//Exibe as peças respectivas aos jogadores
	
	printf("\n\nVEZ DO JOGADOR %c: (pecas disponiveis)\n", turno);
	for (int i=0;i<28;i++){
		if (pieces[i].status==turno){
			printf("[%d|%d]",pieces[i].numberA,pieces[i].numberB);
		}
	}
}



void primeiraPeca(char turno){
	
	//Exibe a primeira peça na mesa
	
	printf("\n\nMESA: (Jogador %c)\n", turno);
	printf("[%d|%d]", mesa[0].ladoE, mesa[0].ladoD);
}

int mostrarPecas(void){
	
	//Exibe as peças
	
	for (int i=0; i<28; i++)
		printf("[%d|%d]", pieces[i].numberA, pieces[i].numberB);
	return 0;
}

void encerrarPrograma()
{
	//Exibe encerramento do programa
	printf("\n\nEncerrando o programa!\n");
	
}

void retornarMenu()
{
	//Exibe o retorno para o menu
	printf("\nRetornando para o menu!\n");
}
 

int menuInicial(void){
	
	printf("\033[32m"); //Muda a cor da fonte para verde
	int option;
	
	
	printf("\nBEM VINDO(A) AO JOGO DE DOMINO!\n");
	printf("=========================================\n");
	printf("\nSelecione uma das seguintes opcoes:\n");
	printf("\n1. Iniciar jogo modo Arcade.\n");
	printf("2. Iniciar jogo multiplayer (2 jogadores).\n");
	printf("3. Mostrar embaralhamento atual.\n");
	printf("4. Carregar jogo salvo.\n");
    printf("5. Sair do jogo\n");
	printf("\n=========================================\n\n> ");
	scanf("%d", &option);
	return option;
}

int ShowRules(){
	
	
	//Exibe as regras do jogo
	
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
	 return 0;
}