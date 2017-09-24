#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

Linha* cria_linha() {
	Linha* l = (Linha*) malloc(sizeof(Linha));
	l->instrucao = NULL;
	l->regSRC = NULL;
	l->reg1 = NULL;
	l->reg2 = NULL;
	return l;
}

void salvar(char str[],Linha* l) {
	if (strcmp(str,"add")) {
		l->instrucao = str;
	}
}

sep_inst(char lin[],Linha* l) {
	int i,j;
	char lido[5];
	int marcador = 0; //variavel usada para marcar onde parou a leitura da palavra
	for(i=0; i<strlen(lin);i++) {
		if(lin[i] == ' ') {
			for(j=marcador;j<i;j++)
				lido[j] = lin[j];
			lido[j] = '\0';
			marcador = i+1;
			salvar(lido,l);
		}
	}
}

void abrir_arquivo(Linha* l) {
	char linha[20];
	FILE* arq;
	arq = fopen("teste.txt", "r");
	while(!feof(arq)) {
		fgets(linha,20,arq);
		sep_inst(linha,l);
		printf("%s\n",linha);
	}
	fclose(arq);
}