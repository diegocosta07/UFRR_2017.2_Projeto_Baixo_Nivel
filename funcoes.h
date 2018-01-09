typedef struct
{
	int op; //opereção basica da instrução
	int rs; //registrador do primeiro operando fonte
	int rt; //registrador do segundo operando fonte
	int rd; //registrador do operando de destino
	int shamt; //shift amount(quantidade de deslocamento)
	int funct; //variante específica da operação op 
	long int endereco; //endereço de branch, jump, load ou store
	int imediato; //valor imediato
} Linha;

void linha_result(Linha* instruc,char* linha,int addr);
Linha* nova_linha();
void marcador_labels();
void abrir_arquivo(Linha* lin);
int identificador_tokens(char* linha, Linha* lin, int addr, FILE* res);
void salvar_arquivo(Linha* lin, int addr, FILE* res);
void registrador(int* reg, char* token);
void linkador(Linha* lin, char* l);