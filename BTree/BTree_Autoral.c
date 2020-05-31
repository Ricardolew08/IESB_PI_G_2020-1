#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDEM 3 //máximo de 2 valores por nó

//FREES APÓS MALLOC

//FAZER TEMPO POR GRÁFICO -> EXCEL

//como fazer os testes? -> USAR BIBLIOTECA COM PRECISÃO DE MICROSEGUNDOS OU RODAR O PROGRAMA 1000X E DIVIDIR POR 1000 O TEMPO.

typedef struct key{
	long long int val; //INCLUIR ALGUM OUTRO VALOR COMO CHAVE, SE REPETIDO -> NEGAR
	char nome[65];  //CRIAR CREATEKEY
	char email[65];
	char telefone[17];
}key;

typedef struct node{
	key * keys[ORDEM]; //+1 PARA SPLIT CHILD
	int count; 
  	struct node * filhos[ORDEM + 1]; //+1 POR DEFINIÇÃO E +1 PARA SPLIT CHILD
  	struct node * pai;
}node;

node *createnode(){
	node * newnode;
	newnode = (node*)malloc(sizeof(node));
	newnode->count = 0;
	newnode->pai = NULL;
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
	int flag;
	
	if (!root){
		newnode = createnode();
		atribui_valores(pkey,newnode);
		newnode->keys[0]->val = pkey->val;
		root = newnode;
	}else{
		flag = find_add(pkey,root,0);
		if(!flag){ //arrumar isso
			printf ("Valor inserido");
		}
	}
}

int find_add(key * pkey, node * mynode, int pospai){
	int flag, pos;
	
	if (!mynode){
		return 1;
	}
	
	for (pos = 0; pos < mynode->count; pos++){
		if (pkey->val < mynode->keys[pos]->val){	
			break;
		}
	}
	
	flag = find_add(pkey,mynode->filhos[pos], pospai);
	
	if (flag){	
		atribui_valores(pkey, mynode);
	}
	
	if(mynode->count == ORDEM){
		split_child(mynode, pospai);
	}
	return 0;
}

int split_child(node * mynode, int pospai){
	node * newnode;
	newnode = createnode();
	int i, j = 0, mediana = ORDEM/2;
	
	for (i = 0; i < ORDEM; i++){ //POPULAR NOVO NÓ
		if (i > mediana){ 
			newnode->keys[j] = mynode->keys[i];
			newnode->count++;
			mynode->count--; //DAR FREE NA CHAVE RETIRADA
			j++;
		}
	}
	
	if(mynode->pai){	
		
		atribuir_valor(mynode->keys[mediana], mynode->pai);
		newnode->pai = mynode->pai;
	
		for (i = mynode->pai->count; i > pospai ; i--){ //i > posição que mediana assumiu no nó pai
			if (mynode->pai->filhos[i]){
				mynode->pai->filhos[i+1] = mynode->pai->filhos[i];
			}
		}
		
		newnode->pai->filhos[pospai+1] = newnode;
		
		j= 0;
		
		for (i = mediana+1; i < ORDEM; i++){ //ajustar filhos de novos nós
			newnode->filhos[j] = mynode->filhos[i];
			mynode->filhos[i] = NULL; //ou free?
			j++;
		}
		
	}else{
		
		node * newroot;
		newroot = createnode();
		
		atribuir_valor(mynode->keys[mediana], newroot);
		root = newroot;
		
		mynode->pai = newroot;
		
		newroot->filhos[0] = mynode;
		newroot->filhos[1] = newnode;
	}
}

void atribui_valores(key * pkey, node * mynode){
	int i, pos;
	
	for (i = mynode->count-1; i >= 0; i--){
		if (mynode->keys[i]->val < pkey->val){
			pos = i;
			break;
		}
		mynode->keys[i+1] = mynode->keys[i]; //MOVENDO CHAVES PARA POSIÇÕES MAIS AVANÇADAS DO NÓ
	}
	
	mynode->keys[i+1] = pkey; //*pkey
	mynode->count++;
}

int find_remove(long long int val, node *mynode){
	
	
	if (!mynode){
		return 1;
	}
	
	for (pos = 0; pos < mynode->count; pos++){ //se der merda, olhar o pos
	
		if (val == mynode->keys[pos]->val){
			remover_valores(val, mynode, pos);
			return 0;
		}
		
		if (val < mynode->keys[pos]->val){	
			break;
		}
	}
	
	flag = find_remove(val,mynode->filhos[pos]);

	if (flag){
		return 1;
	}

	return 0;
}

void remover_valores (long long int val, node * mynode, int pos){
	int i;
	for (i = pos; i < mynode->count; i++){
		mynode->keys[pos]=mynode->keys[pos+1];
	}
	mynode->count--;
	
	if(mynode->link[0]){
		
	}
	
	if(mynode->count < ORDEM/2){
		
	}
}


//printf("%d %d %s %s %s", i, mynode->keys[i]->val, mynode->keys[i]->nome, mynode->keys[i]->email, mynode->keys[i]->telefone);












