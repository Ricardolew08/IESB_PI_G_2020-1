#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
NOME - E-MAIL - TELEFONE
GERAR NOME
- mínimo de 4 e máximo 8 letras
- gerar sobrenome
- nome completo = primeiro nome + primeiro nome
GERAR E-MAIL
- e-mail vai ser nome (nome completo) + @GRUPOG.iesb
GERAR TELEFONE
- 55XX9XXXXXXXX
*nome_completo+e_mail-telefone/n
*/

typedef struct nome_completo{
	char * nome1;
	char * nome2;
}nome_completo;

void gerar_telefone(int * n){

	n[0] = 9; 
	
	for (int i = 1; i < 9; i++){
		int x = rand() % 10;
		n[i] = x; 
	}
}

void gerar_nome(char * c, int tam){
	int letra;
	for (int i = 0; i < tam; i++){
		letra = rand() % 26 + 65;
		c[i] = letra;
	}
}


int main(){
	srand (time(NULL));
	FILE *fptr;
	fptr = fopen("DatasetPI-10kv2.txt","w");
	
	nome_completo c;
	int tam1, tam2;
	
	char * email;
	char dominio[12] = {'@','g','r','u','p','o','G','.','i','e','s','b'};
	int tamemail;
	
	int *n;
	
	
	int l;
	unsigned long long k = 0;
	
	while(k < 10000){
	l = 0;
	/* NOME COMPLETO */
	fprintf (fptr,"*");
	
	tam1 = rand() % 5 + 4;
	c.nome1 = (char *)malloc(sizeof(char) * tam1);
	gerar_nome(c.nome1, tam1);
	
	tam2 = rand() % 5 + 4;
	c.nome2 = (char *)malloc(sizeof(char) * tam2);
	gerar_nome(c.nome2, tam2);
	
	for (int i = 0; i < tam1; i++){
		fprintf (fptr,"%c", c.nome1[i]);
	}
	
	fprintf (fptr,"_");
	
	for (int i = 0; i < tam2; i++){
		fprintf (fptr,"%c", c.nome2[i]);
	}
	
	/* E-MAIL */
	
	fprintf (fptr,"+");
	tamemail = tam1 + tam2 + 12;
	
	email = (char *)malloc( sizeof(char) * tamemail );
	
	
	for (int i = 0; i < tam1; i++){
		email[l] = c.nome1[i];
		l++;
	}
	for (int i = 0; i < tam2; i++){
		email[l] = c.nome2[i];
		l++;
	}
	for (int i = 0; i < 12; i++){
		email[l] = dominio[i];
		l++;
	}

	//strcpy(email, c.nome1);
	//strcat(email, c.nome2);
	//strcat(email, "@grupoG.iesb");
	
	for (int i = 0; i < tamemail; i++){
		fprintf (fptr,"%c", email[i]);
	}
	
	/* NUMERO DE TELEFONE */
	fprintf (fptr,"-");
	
	n = (int *)malloc(sizeof(int) * 10);
	gerar_telefone(n);
	
	for (int i = 0; i < 9; i++){
		fprintf (fptr,"%d", n[i]);
	}
	fprintf (fptr,"\n");
	
	free(n);
	free(email);
	free(c.nome1);
	free(c.nome2);
	k++;
	}
	fclose(fptr);
	return 0;
}

/*
while (true){
		
	}
*/
