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

/*função para gerar o codigo hexadecimal das intruções*/
void linha_result(Linha* instruc,char* linha,int addr);

/*função para função para organizar uma linha de codigo do arquivo mips*/
Linha* nova_linha();

/*função para salvar os endereços das labels*/
void marcador_labels(char* cod);

/*função para abrir o arquivo mips*/
void abrir_arquivo(Linha* lin, char* cod, char* save);

/*função para separar as intruções de acordo com os opcode*/
int identificador_tokens(char* linha, Linha* lin, int addr, FILE* res);

/*função para salvar o codigo hexadecimal gerado pela linha_result em um arquivo de texto*/
void salvar_arquivo(Linha* lin, int addr, FILE* res);

/*função para identificar os registradores nos tokens*/
void registrador(int* reg, char* token);

/*função para resolver os endereços das labels nas instruções*/
void linkador(Linha* lin, char* l);