#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include "mips.h"

Linha* nova_linha() {
	Linha* lin = (Linha*) malloc(sizeof(Linha));
	return lin;
}

void identificador_tokens(char* linha, Linha* lin) {
	const char idop[2] = " "; //delimitador da operacao
	const char idreg[2] = ","; //delimitador dos registradores
	char* token;

	/*primeiramente identifica a opereção*/
	token = strtok(linha,idop);

	/*instrução do formato R*/
	if((strcmp("add",token) == 0) || strcmp("sub",token) == 0) {
		lin->op = 0;

		/*então separa os tokens*/
		
		token = strtok(NULL,idreg);
		printf("%d\n", token);
		lin->rd = token;
		token = strtok(NULL,idreg);
		lin->rs = token;
		token = strtok(NULL,idreg);
		lin->rt = token;
	}
}

void abrir_arquivo(Linha* lin) {
	char linha[20];
	FILE* arq;
	arq = fopen("teste.txt", "r");
	while(!feof(arq)) {
		fgets(linha,20,arq); //lê uma linha por vez do arquivo
		//printf("%s\n",linha);
		identificador_tokens(linha,lin); //separa os tokens da instrução
	}
	fclose(arq);
}