//DOM_Ativi01 - Projeto Domino - etapa 4
//28/08/2024 - Grupo: AGGP

//Alexandre Maciano de Oliveira 
//Gabriel Manganiello Terra
//Gabriel Mechi Lima
//Pedro Marinho Machado

/*Nessa estapa iremos permetir que o jogador visualize as regras do jogo e que possa finalizar o mesmo
assim que desejar. Tambem sera possivel comprar pecas e sua mão estara escondida para que apenas ele possa
visualizar durante seu turno.
*/

#include "DOM_AGGP_Model.cpp"
#include "DOM_AGGP_Controller.cpp"
int main()
{
	gerarPecas();
	jogar();
	
	return 0;
}
