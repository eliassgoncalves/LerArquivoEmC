#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<locale.h>
#define MAX_LINHAS 2 // Mudar conforme a quantidade de linha no seu arquivo

// Estrutura da tabela
struct covid19{
	char *regiao;	 // nome da cidade
	int sintomas;    // quantidade de pessoas
	int uti;		 // quantidade de pessoas
	int isolamento;  // quantidade de pessoas
	int positivas;   // quantidade de pessoas 
	int mortes;		 // quantidade de pessoas
	int curadas;     // quantidade de pessoas
};
typedef struct covid19 COVID19;


// Função para leitura de arquivo
void LerArquivo( COVID19 **italia, char *filepath ){
	FILE *arquivo = fopen(filepath, "rt");
	char *resultado, *regiao;	
	int sintomas, uti, isolamento, positivas, mortes, curadas, i;
	
	// Aloca memória para a região
	regiao = ( char* ) malloc( sizeof(char) );
	
	if( arquivo == NULL ){
		printf("Erro ao abrir o arquivo!\n");
	 	return;
	}

	i = 0; // Contador de linha

	// Lê linha formatada
	printf( "\nENQUANTO COLOCA O TXT NA STRUCT\n" );
	while( (fscanf(arquivo, "%s %d %d %d %d %d %d", regiao, &sintomas, &uti, &isolamento, &positivas, &mortes, &curadas)) != EOF ){
   		printf( "%s %d %d %d %d %d %d\n", regiao, sintomas, uti, isolamento, positivas, mortes, curadas ); // Antes de colocar na struct
   		italia[i] = ( COVID19* ) malloc( sizeof(COVID19) );
   		italia[i]-> sintomas = sintomas;
   		italia[i]-> uti = uti;
   		italia[i]-> isolamento = isolamento;
   		italia[i]-> positivas = positivas;
   		italia[i]-> mortes = mortes;
   		italia[i]-> curadas = curadas;
   		italia[i]-> regiao = ( char* ) malloc( sizeof(regiao) );
   		strcpy( italia[i]-> regiao, regiao );
   		i++;
	}
	
	fclose( arquivo );
}



// Função main
int main(){
	setlocale(LC_ALL, "Portuguese");
	int i;
	time_t inicio, fim;
	inicio = clock();
	COVID19 **italia;
	
	// Alocação de memória para ler o arquivo
	italia = ( COVID19** ) malloc( MAX_LINHAS * sizeof(COVID19*) );
	
	// Escrita do arquivo para a struct
	// EscreverArquivo( italia, "italia.txt" );

	// Leitura do arquivo para a struct
	LerArquivo( italia, "italia.txt" );

	// Imprime o que leu do arquivo direto da struct
	printf( "\nDEPOIS DE COLOCAR O TXT NA STRUCT\n" );
	for( i = 0; i < MAX_LINHAS; i++ ){
		
		// Depois de colocar na struct
		printf(
			"%s %d %d %d %d %d %d\n",
			italia[i]->regiao, 
			italia[i]->sintomas, 
			italia[i]->uti, 
			italia[i]->isolamento, 
			italia[i]->positivas, 
			italia[i]->mortes,
			italia[i]->curadas
		);
	}


	// Liberar memória
	for( i = 0; i<MAX_LINHAS; i++ ){
		free( italia[i] );
	}
	free(italia);

	// Calcula o tempo	
	fim = clock();
	printf("\n\nTempo: %.0f\n\n", difftime(fim, inicio));
	
	return 0;
}
