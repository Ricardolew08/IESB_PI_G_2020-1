#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3

//como fazer os testes?

typedef struct key{
	long long int val;
	char nome[64];
	char email[64];
	char telefone[13];
};

typedef struct btreeNode{
	struct key keys[MAX + 1], count;
  	struct btreeNode *link[MAX + 1];
};

int main(){
	char c;
	int cont;
	long long int contador_global = 1;
	struct key * pkey;
	pkey = (struct key*)malloc(sizeof(struct key));
	
	FILE *fptr;
	fptr = fopen("a.txt", "r");
	
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
			while (c!='.'){
				pkey->telefone[cont] = c;
				cont++;	
				c = getc(fptr);
			}
			pkey->telefone[cont] = '\0';
			
		}
		//inserir(pkey->valor, root);
		
		contador_global++;
		
		c = getc(fptr);
	}
	
	//printf("%s %s %s", no.nome, no.email, no.telefone);
}
