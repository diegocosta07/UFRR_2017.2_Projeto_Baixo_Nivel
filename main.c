#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

/*
*	Universidade Federal de Roraima
*	Disciplina: Baixo Nível
*	Aluno: Diego Santos Costa
*	Este projeto foi desenvolvido em ambiente windows compilado utilizando gcc.
*/

int main() {
	printf("Tamanho do tipo int nessa arquitetura: %d\n", sizeof(int));

	Linha* instruc = nova_linha();

	//primeira leitura é para resolver as labels
	marcador_labels();
	
	//segunda leitura é para codificar o arquivo em hex com as labels resolvidas
	abrir_arquivo(instruc);

	printf("Montagem concluida!\nCodigo hexadecimal salvo no arquivo resultado.txt\n");

	
	free(instruc);
	return 0;
}