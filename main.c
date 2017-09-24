#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

int main() {
	Linha *l = cria_linha();
	abrir_arquivo(l);
	printf("instrucao salva %s\n",l->instrucao);
	free(l);
}