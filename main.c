#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

int main() {
	printf("Tamanho do tipo int nessa arquitetura: %d\n", sizeof(int));

	Linha* instruc = nova_linha();
	abrir_arquivo(instruc);

	printf("op %d\n rs %d\n rt %d\n rd %d\n",instruc->op, instruc->rs, instruc->rt, instruc->rd);

	free(instruc);
}