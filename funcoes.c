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
		lin->op = ADD;

		/*então separa os tokens*/
		
		token = strtok(NULL,idreg);
		//printf("%s\n", token);
		registrador(&lin->rd,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rs,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rt,token);
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

void registrador(int* reg, char* token) {
	if (strcmp("$t0",token) == 0)
		*reg = $t0;
	else if (strcmp("$t1",token) == 0)
		*reg = $t1;
	else if (strcmp("$t2",token) == 0)
		*reg = $t2;
	else if (strcmp("$t3",token) == 0)
		*reg = $t3;
	else if (strcmp("$t4",token) == 0)
		*reg = $t4;
	else if (strcmp("$t5",token) == 0)
		*reg = $t5;
	else if (strcmp("$t6",token) == 0)
		*reg = $t6;
	else if (strcmp("$t7",token) == 0)
		*reg = $t7;

	else if (strcmp("$s0",token) == 0)
		*reg = $s0;
	else if (strcmp("$s1",token) == 0)
		*reg = $s1;
	else if (strcmp("$s2",token) == 0)
		*reg = $s2;
	else if (strcmp("$t3",token) == 0)
		*reg = $s3;
	else if (strcmp("$s4",token) == 0)
		*reg = $s4;
	else if (strcmp("$s5",token) == 0)
		*reg = $s5;
	else if (strcmp("$s6",token) == 0)
		*reg = $s6;
	else if (strcmp("$s7",token) == 0)
		*reg = $s7;
}