typedef struct {
	char instrucao[5];
	char regSRC[3];
	char reg1[3];
	char reg2[3];
} Linha;

void abrir_arquivo(Linha);
Linha* cria_linha();
void salvar(char str[],Linha* l);
sep_inst(char lin[],Linha* l);