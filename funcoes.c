#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include "mips.h"

/*
*	Universidade Federal de Roraima
*	Disciplina: Baixo Nível
*	Aluno: Diego Santos Costa
*	Este projeto foi desenvolvido em ambiente windows compilado utilizando gcc.
*/

Linha* nova_linha() {
	Linha* lin = (Linha*) malloc(sizeof(Linha));
	return lin;
}

int identificador_tokens(char* linha, Linha* lin, int addr, FILE* res) {
	/*"reinicia" os campos para a receber a nova linha de instrução*/
	lin->op = 0;
	lin->rs = 0;
	lin->rt = 0;
	lin->rd = 0;
	lin->shamt = 0;
	lin->funct = 0;
	lin->endereco = 0;
	lin->imediato = 0;

	const char idop[2] = " "; //delimitador da operacao
	const char idreg[2] = ","; //delimitador dos registradores
	const char idend[2] = "("; //delimitador do endereco
	char* token;

	/*primeiramente identifica a opereção*/
	token = strtok(linha,idop);

	/*instrução do formato R add*/
	if(strcmp("add",token) == 0 || strcmp("\tadd",token) == 0) {
		lin->op = ADD;
		lin->shamt = 0;
		lin->funct = 32;
		/*então separa os tokens*/
		
		token = strtok(NULL,idreg);
		//printf("%s\n", token);
		registrador(&lin->rd,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rs,token);
		token = strtok(NULL,"\n");
		registrador(&lin->rt,token);

		salvar_arquivo(lin,addr,res);
	}

	/*instrução do formato R addi*/
	else if(strcmp("addi",token) == 0 || strcmp("\taddi",token) == 0) {
		lin->op = ADDI;
		/*então separa os tokens*/

		token = strtok(NULL,idreg);
		registrador(&lin->rt,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rs,token);
		token = strtok(NULL,"\n");
		lin->imediato = atoi(token);

		salvar_arquivo(lin,addr,res);
	} 

	else if(strcmp("mult",token) == 0 || strcmp("\tmult",token) == 0) {
		lin->op = MULT;
		lin->shamt = 0;
		lin->funct = 24;
		/*então separa os tokens*/
		
		token = strtok(NULL,idreg);
		registrador(&lin->rs,token);
		token = strtok(NULL,"\n");
		registrador(&lin->rt,token);

		salvar_arquivo(lin,addr,res);
	}

	/*instrução do formato R sub*/
	else if(strcmp("sub",token) == 0  || strcmp("\tsub",token) == 0) {
		lin->op = SUB;
		lin->shamt = 0;
		lin->funct = 34;
		/*então separa os tokens*/
		
		token = strtok(NULL,idreg);
		registrador(&lin->rd,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rs,token);
		token = strtok(NULL,"\n");
		registrador(&lin->rt,token);

		salvar_arquivo(lin,addr,res);
	}

	/*instrução do formato R slt*/
	else if(strcmp("slt",token) == 0 || strcmp("\tslt",token) == 0) {
		lin->op = SLT;
		lin->shamt = 0;
		lin->funct = 42;
		/*então separa os tokens*/
		
		token = strtok(NULL,idreg);
		registrador(&lin->rd,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rs,token);
		token = strtok(NULL,"\n");
		registrador(&lin->rt,token);

		salvar_arquivo(lin,addr,res);
	}

	else if(strcmp("slti",token) == 0 || strcmp("\tslti",token) == 0) {
		lin->op = SLTI;
		/*então separa os tokens*/
		
		token = strtok(NULL,idreg);
		registrador(&lin->rt,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rs,token);
		token = strtok(NULL,"\n");
		lin->imediato = atoi(token);

		salvar_arquivo(lin,addr,res);
	}

	/*instrução do formato R sll*/
	else if(strcmp("sll",token) == 0 || strcmp("\tsll",token) == 0) {
		lin->op = SLL;
		lin->funct = 000000;
		lin->rs = 00000;
		/*então separa os tokens*/
		
		token = strtok(NULL,idreg);
		registrador(&lin->rd,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rt,token);
		token = strtok(NULL,"\n");
		lin->shamt = atoi(token);
		
		salvar_arquivo(lin,addr,res);
	}

	/*instrução do formato R srl*/
	else if(strcmp("srl",token) == 0 || strcmp("\tsrl",token) == 0) {
		lin->op = SRL;
		lin->funct = 2;
		/*então separa os tokens*/
		
		token = strtok(NULL,idreg);
		registrador(&lin->rd,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rt,token);
		token = strtok(NULL,"\n");
		lin->shamt = atoi(token);

		salvar_arquivo(lin,addr,res);
	}

	/*instrução do formato i lw*/
	else if(strcmp("lw",token) == 0 || strcmp("\tlw",token) == 0) {
		lin->op = LW;

		token = strtok(NULL,idreg);
		registrador(&lin->rt,token);
		token = strtok(NULL,idend);
		lin->endereco = atoi(token);//converte inteiro em string
		token = strtok(NULL,")");
		registrador(&lin->rs,token);

		salvar_arquivo(lin,addr,res);
	}

	/*instrução do formato i sw*/
	else if(strcmp("sw",token) == 0 || strcmp("\tsw",token) == 0) {
		lin->op = SW;
		
		token = strtok(NULL,idreg);
		registrador(&lin->rt,token);
		token = strtok(NULL,idend);
		lin->endereco = atoi(token);
		token = strtok(NULL,")");
		registrador(&lin->rs,token);

		salvar_arquivo(lin,addr,res);
	} 

	/*instrução do formato i j*/
	else if(strcmp("j",token) == 0 || strcmp("\tj",token) == 0) {
		lin->op = J;
		char* l  = strtok(NULL,"\n");
		linkador(lin,l);

		salvar_arquivo(lin,addr,res);
	}

	else if(strcmp("jal",token) == 0 || strcmp("\tjal",token) == 0) {
		lin->op = JAL;
		char* l  = strtok(NULL,"\n");
		linkador(lin,l);

		salvar_arquivo(lin,addr,res);
	}

	else if(strcmp("beq",token) == 0 || strcmp("\tbeq",token) == 0) {
		lin->op = BEQ;
		token = strtok(NULL,idreg);
		registrador(&lin->rs,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rt,token);
		char* l  = strtok(NULL,"\n");
		linkador(lin,l);

		salvar_arquivo(lin,addr,res);
	}

	else if(strcmp("bne",token) == 0 || strcmp("\tbne",token) == 0) {
		lin->op = BNE;
		token = strtok(NULL,idreg);
		registrador(&lin->rs,token);
		token = strtok(NULL,idreg);
		registrador(&lin->rt,token);
		char* l  = strtok(NULL,"\n");
		linkador(lin,l);

		salvar_arquivo(lin,addr,res);
	}

	else if (strcmp("jr",token) == 0 || strcmp("\tjr",token) == 0) {
		lin->op = JR;
		lin->funct = 8;
		token = strtok(NULL,"\n");
		registrador(&lin->rs,token);

		salvar_arquivo(lin,addr,res);
	}
	else {
		return 0;
	}
	return 1;

}

void linkador(Linha* lin, char* l) {
	FILE* label = fopen("labels.txt","r"); //ponteiro do arquivo com as labels
	char linha[100]; // linha lida do arquivo das labels
	char* tok; //token para ler as labels dos arquivo
	char* adr; //token para ler o endereço da label
	fgets(linha,100,label);
	while(!feof(label)) {
		
		tok = strtok(linha,"[");
		if(strcmp(tok,l) == 0) {
			adr = strtok(NULL,"]");
			lin->endereco = strtol(adr,'\0',16);//converter a string para hexadecimal
			break;
		}
		fgets(linha,20,label);
	}
	fclose(label);
}

void salvar_arquivo(Linha* lin,int addr, FILE* res) {
	char salvar[100] = ""; //variavel do codigo mips em hexadecimal
	char addr_s[9]; //variavel do endereço de memoria
	linha_result(lin,salvar,addr);//passa a linha para uma string
	fputc('[',res);
	sprintf(addr_s,"%x",addr);
	fputs(addr_s,res);//salva o endereço de memória 
	fputs("] ",res);
	strcat(salvar,"\n");
	fputs(salvar,res);//salva o codigo da instrução no arquivo resultado.txt
}

void linha_result(Linha* instruc,char* linha, int addr) {
	int b; // variavel para armazenar o codigo binario

	if(instruc->op == 0) {
		b = (instruc->op << 26);
		b |= (instruc->rs << 21);
		b |= (instruc->rt << 16);
		b |= (instruc->rd << 11);
		b |= (instruc->shamt << 6);
		b |= (instruc->funct << 0);
		itoa(b,linha,16);
	} else if (instruc->op == LW) {
		b = (LW << 26);
		b |= (instruc->rs << 21);
		b |= (instruc->rt << 16);
		b |= (instruc->endereco << 0);
		itoa(b,linha,16);
	} else if (instruc->op == SW) {
		b = (SW << 26);
		b |= (instruc->rs << 21);
		b |= (instruc->rt << 16);
		b |= (instruc->endereco << 0);
		itoa(b,linha,16);
	} else if (instruc->op == ADDI) {
		b = (ADDI << 26);
		b |= (instruc->rs << 21);
		b |= (instruc->rt << 16);
		b |= (instruc->imediato << 0);
		itoa(b,linha,16); // conversão para hexadecimal
	} else if (instruc->op == SLTI) { 
		b = (SLTI << 26);
		b |= (instruc->rs << 21);
		b |= (instruc->rt << 16);
		b |= (instruc->imediato << 0);
		itoa(b,linha,16);
	} else if (instruc->op == BEQ) {
		int end = instruc->endereco - addr; // quantidade de bytes a saltar (label - [endereço atual])
		
		b = (BEQ << 26);
		b |= (instruc->rs << 21);
		b |= (instruc->rt << 16);
		b |= (end >> 2); //offset precisa ser deslocado 2 bits para a direita nas instruções de branch
		itoa(b,linha,16);
	} else if (instruc->op == BNE) {
		int end = instruc->endereco - addr; // quantidade de bytes a saltar (label - [endereço atual])
		
		b = (BNE << 26);
		b |= (instruc->rs << 21);
		b |= (instruc->rt << 16);
		b |= (end >> 2);
		itoa(b,linha,16);
	} else if (instruc->op == J) {
		b = (J << 26);
		b |= (instruc->endereco >> 2);
		itoa(b,linha,16);
	} else if (instruc->op == JAL) {
		b = (JAL << 26);
		b |= (instruc->endereco >> 2);
		itoa(b,linha,16);
	}
	printf("%s\n", linha);

}


void marcador_labels() {
	FILE* labels = fopen("labels.txt","w"); //arquivo para salvar as labels e seus endereços
	FILE* arq = fopen("mips.txt", "r"); // arquivo com codigo mips

	int m_addr = 0x400024; //endereço da instrução
	char linha[100];
	char* token;
	char aux[15];
	/*primeira leitura do arquivo para resolver as labels*/
	while(!feof(arq)) {
		fgets(linha,100,arq); //lê uma linha por vez do arquivo
		token = strtok(linha,":"); //identifica uma label se esta termina em ':'
		if(strtok(NULL,":")) {
			//m_addr = m_addr + 4;
			fputs(token,labels); // salva a label
			sprintf(aux,"%x",m_addr); //converte o endereço para string
			fputc('[',labels);
			fputs(aux,labels); // salva o endereço de memoria da label
			fputs("]\n",labels);
		} else {
			m_addr = m_addr + 0x4;
		}
		
	}

	fclose(arq);
	fclose(labels);
	/*fim da primeira leitura*/
	
} 

void abrir_arquivo(Linha* lin) {
	char linha[100];
	int n_linha = 0x400024;//endereço da instrução
	int aux;
	FILE* arq;
	FILE* res;

	/*segunda leitura do arquivo para a codificação das instruções com a labels resolvidas*/
	arq = fopen("mips.txt", "r"); // arquivo com codigo mips
	res = fopen("resultado.txt","w"); //arquivo para ser salvo a codificação hex das intruções

	while(!feof(arq)) {
		fgets(linha,100,arq); //lê uma linha por vez do arquivo
		printf("%s\n",linha);
		aux = identificador_tokens(linha,lin,n_linha,res); //separa os tokens da instrução
		if (aux == 1)
			n_linha = n_linha + 0x4;
	}
	fclose(arq);
	fclose(res);
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
	else if (strcmp("$t8",token) == 0)
		*reg = $t8;
	else if (strcmp("$t9",token) == 0)
		*reg = $t9;
	else if (strcmp("$s0",token) == 0)
		*reg = $s0;
	else if (strcmp("$s1",token) == 0)
		*reg = $s1;
	else if (strcmp("$s2",token) == 0)
		*reg = $s2;
	else if (strcmp("$s3",token) == 0)
		*reg = $s3;
	else if (strcmp("$s4",token) == 0)
		*reg = $s4;
	else if (strcmp("$s5",token) == 0)
		*reg = $s5;
	else if (strcmp("$s6",token) == 0)
		*reg = $s6;
	else if (strcmp("$s7",token) == 0)
		*reg = $s7;
	else if (strcmp("$zero",token) == 0)
		*reg = $zero;
	else if (strcmp("$0",token) == 0)
		*reg = $0;
	else if (strcmp("$at",token) == 0)
		*reg = $at;
	else if (strcmp("$v0",token) == 0)
		*reg = $v0;
	else if (strcmp("$v1",token) == 0)
		*reg = $v1;
	else if (strcmp("$a0",token) == 0)
		*reg = $a0;
	else if (strcmp("$a1",token) == 0)
		*reg = $a1;
	else if (strcmp("$a1",token) == 0)
		*reg = $a1;
	else if (strcmp("$a1",token) == 0)
		*reg = $a1;
	else if (strcmp("$k0",token) == 0)
		*reg = $k0;
	else if (strcmp("$k1",token) == 0)
		*reg = $k1;
	else if (strcmp("$gp",token) == 0)
		*reg = $gp;
	else if (strcmp("$sp",token) == 0)
		*reg = $sp;
	else if (strcmp("$fp",token) == 0)
		*reg = $fp;
	else if (strcmp("$ra",token) == 0)
		*reg = $ra;
}