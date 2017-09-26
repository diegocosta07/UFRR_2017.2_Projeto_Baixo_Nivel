typedef struct
{
	int op; //opereção basica da instrução
	int rs; //registrador do primeiro operando fonte
	int rt; //registrador do segundo operando fonte
	int rd; //registrador do operando de destino
	int shamt; //shift amount(quantidade de deslocamento)
	int funct; //variante específica da operação op 
	int endereco; 
} Linha;

Linha* nova_linha();
void abrir_arquivo(Linha* lin);
void identificador_tokens(char* linha, Linha* lin);
void registrador(int* reg, char* token);