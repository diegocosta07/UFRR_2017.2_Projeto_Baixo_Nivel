#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

/*
*	Universidade Federal de Roraima
*	Disciplina: Baixo Nível
*	Aluno: Diego Santos Costa
*	Este projeto foi desenvolvido em ambiente windows compilado utilizando gcc.
*/

int main(int argc, char* argv[]) {
	printf("Tamanho do tipo int nessa arquitetura: %d\n", sizeof(int));

	Linha* instruc = nova_linha();

	//primeira leitura é para resolver as labels
	marcador_labels(argv[1]);
	
	//segunda leitura é para codificar o arquivo em hex com as labels resolvidas
	abrir_arquivo(instruc,argv[1],argv[2]);

	printf("Montagem do arquivo %s concluida!\nCodigo hexadecimal salvo no arquivo %s\n",argv[1],argv[2]);

	
	free(instruc);
	return 0;
}