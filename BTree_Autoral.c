#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDEM 3

//como fazer os testes?

typedef struct{
	long long int val;
	char nome[65];
	char email[65];
	char telefone[17];
}key;

typedef struct{
	key * keys[ORDEM + 1]; //+1 PARA SPLIT CHILD
	int count; 
  	struct node * filhos[ORDEM + 1];
}node;

node *createnode(){
	node * newnode;
	newnode = (node*)malloc(sizeof(node));
	newnode->count = 0;
	/*
	int i;
	for (i = 0; i <= ORDEM; i++){
		newnode->keys[i] = (key*)malloc(sizeof(key)); 
	}
	*/
	return newnode;
}

node * root = NULL;

int main(){
	char c;
	int cont;
	long long int contador_global = 1;
	key * pkey;
	pkey = (key*)malloc(sizeof(key));
	
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
			while (c != '\n' && c != EOF){
				pkey->telefone[cont] = c;
				cont++;	
				c = getc(fptr);
			}
			pkey->telefone[cont] = '\0';
			
		}
		printf("%d-%s-%s-%s\n", pkey->val, pkey->nome, pkey->email, pkey->telefone);
		inserir(pkey, root);
		
		contador_global++;
		
		c = getc(fptr);
	}
	return 0;
	//printf("%s %s %s", no.nome, no.email, no.telefone);
}

void inserir(key * pkey, node * root){
	node * newnode;
	
	if (!root){
		newnode = createnode();
		atribui_valores(pkey,newnode);
		newnode->keys[0]->val = pkey->val;
		root = newnode;
	}
	
	find_node(pkey,root);
	
}

void find_node(key * pkey, node * mynode){
	int flag;
	if(pkey->valor < mynode->keys[0]->valor){
		find_node()
	}
}

void atribui_valores(key * pkey, node * mynode){
	int i, pos;
	
	for (i = 0; i <= ORDEM; i++){
		if (pkey->val < mynode->keys[i]->val){
			pos = i;
			break;
		}
	}
	mynode->keys[i+1] = mynode->keys[i];
	
	mynode->keys[i] = pkey;
	mynode->count++;
	
	if (mynode->count == ORDEM+1){
		//splitchild(mynode);
	}
}


	//printf("%d %d %s %s %s", i, mynode->keys[i]->val, mynode->keys[i]->nome, mynode->keys[i]->email, mynode->keys[i]->telefone);












