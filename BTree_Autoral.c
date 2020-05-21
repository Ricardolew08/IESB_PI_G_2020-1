#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

//como fazer os testes?

typedef struct{
	long long int val;
	char nome[65];
	char email[65];
	char telefone[17];
}key;

typedef struct{
	key keys[MAX + 1], count;
  	struct btreeNode *link[MAX + 1];
}btreeNode;

int main(){
	char c;
	int cont;
	long long int contador_global = 1;
	key * pkey;
	pkey = (key*)malloc(sizeof(key));
	
	FILE *fptr;
	fptr = fopen("DatasetPITeste.txt", "r");
	
	c = getc(fptr);
	while(c != EOF){
		
		pkey->val = contador_global;
		
		if (c == '*'){
			c = getc(fptr);
			cont = 0;
			while (c!='+'){	
				pkey->nome[cont] = c;
				cont++;
				c = getc(fptr);
			}
			pkey->nome[cont] = '\0';
			
			c = getc(fptr);
			cont = 0;
			while (c!='-'){
				pkey->email[cont] = c;	
				cont++;
				c = getc(fptr);
			}
			pkey->email[cont] = '\0';
			
			c = getc(fptr);
			cont = 0;
			while (c != '\n' && c != EOF){
				pkey->telefone[cont] = c;
				cont++;	
				c = getc(fptr);
			}
			pkey->telefone[cont] = '\0';
			
		}
		printf("%d-%s-%s-%s\n", pkey->val, pkey->nome, pkey->email, pkey->telefone);
		//inserir(pkey->valor, root);
		
		contador_global++;
		
		c = getc(fptr);
	}
	
	//printf("%s %s %s", no.nome, no.email, no.telefone);
}



