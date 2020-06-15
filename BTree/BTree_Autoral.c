#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN 3

typedef struct key
{
    int val;
    char name[64], email[64];
} key;

typedef struct node
{
    key *keys[((2 * MIN) - 1)];
    int count, leaf;
    struct node *child[2 * MIN];
} node;

node *ROOT = NULL;
node *createnode(int isleaf);
void find_insert(node *mynode, key *newkey);
void splitchild(node *newroot, int i, node *mynode);
void insert(key *newkey);
void populate(node *mynode, key *newkey, int i);
void printar(node *mynode);
key *getant(node *mynode, int i);
key *getsuc(node *mynode, int i);
void deleteleaf(node *mynode, int i);
void deletenotleaf(node *mynode, int i);
void borrant(node *mynode, int i);
void borrsuc(node *mynode, int i);
void merge(node *mynode, int i);
void fill(node *mynode, int i);
void find_delete(node *mynode, int data);
void delete (int data);

int main()
{
    int stringIndex, key;
    char fileChar, strToInt[10], name[64], email[64];


    int arr[2000000], qtd = 0;

    FILE *fptr;
    fptr = fopen("DatasetPI-10k-Tele9Digitos.txt", "r");

    struct key *newkey;
    newkey = (struct key *)malloc(sizeof(struct key));

    fileChar = fgetc(fptr);
    while (fileChar != EOF)
    {

        if (fileChar == '*')
        {
            fileChar = fgetc(fptr);
            stringIndex = 0;
            while (fileChar != '+')
            {
                newkey->name[stringIndex++] = fileChar;
                fileChar = fgetc(fptr);
            }
            newkey->name[stringIndex] = '\0';

            fileChar = fgetc(fptr);
            stringIndex = 0;
            while (fileChar != '-')
            {
                newkey->email[stringIndex++] = fileChar;
                fileChar = fgetc(fptr);
            }
            newkey->email[stringIndex] = '\0';

            fileChar = fgetc(fptr);
            stringIndex = 0;
            while (fileChar != '\n' && fileChar != EOF)
            {
                strToInt[stringIndex++] = fileChar;
                fileChar = fgetc(fptr);
            }
            strToInt[stringIndex] = '\0';
            newkey->val = atoi(strToInt);
        }
        arr[qtd++] = newkey->val;

        insert(newkey);

        fileChar = fgetc(fptr);
    }
    
    printar(ROOT);
    
	int i;
	for (i=0;i<qtd;i++){
		printf("Deletando %d\n",arr[i]);
        delete(arr[i]);
	}
    printar(ROOT);
    return 0;
}

node *createnode(int isleaf)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->leaf = isleaf;
    newnode->count = 0;
    int i;
    for (i = 0; i < 2 * MIN - 1; i++)
    {
        newnode->keys[i] = NULL;
    }
    for (i = 0; i < 2 * MIN; i++)
    {
        newnode->child[i] = NULL;
    }
    return newnode;
}

void find_insert(node *mynode, key *newkey)
{
    int i = mynode->count - 1;

    if (mynode->leaf)
    {
        while (i >= 0 && mynode->keys[i]->val > newkey->val)
        {
            mynode->keys[i + 1] = mynode->keys[i];
            i--;
        }
        populate(mynode, newkey, i + 1);
    }
    else
    {
        while (i >= 0 && mynode->keys[i]->val > newkey->val)
        {
            i--;
        }
        if (mynode->child[i + 1]->count == ((2 * MIN) - 1))
        {
            splitchild(mynode, i + 1, mynode->child[i + 1]);
            if (mynode->keys[i + 1]->val < newkey->val)
            {
                i++;
            }
        }
        find_insert(mynode->child[i + 1], newkey);
    }
}

void splitchild(node *newroot, int i, node *mynode)
{
    node *newnode = createnode(mynode->leaf);
    newnode->count = MIN - 1;

    int j;
    for (j = 0; j < MIN - 1; j++)
    {
        //newnode->keys[j] = (key *)malloc(sizeof(key));
        newnode->keys[j] = mynode->keys[j + MIN];
        mynode->keys[j + MIN] = NULL;
    }

    if (!mynode->leaf)
    {
        for (j = 0; j < MIN; j++)
        {
            //newnode->child[j] = (node *)malloc(sizeof(node));
            newnode->child[j] = mynode->child[j + MIN];
            mynode->child[j + MIN] = NULL;
        }
    }
    mynode->count = MIN - 1;

    for (j = newroot->count; j >= i + 1; j--)
    {
        newroot->child[j + 1] = newroot->child[j];
    }

    newroot->child[i + 1] = newnode;

    for (j = newroot->count - 1; j >= i; j--)
    {
        newroot->keys[j + 1] = newroot->keys[j];
    }
    populate(newroot, mynode->keys[MIN - 1], i);
    //newroot->keys[i] = mynode->keys[MIN - 1];
    //newroot->count++;
}

void populate(node *mynode, key *mykey, int i)
{

    mynode->keys[i] = (key *)malloc(sizeof(key));

    mynode->keys[i]->val = mykey->val;
    strcpy(mynode->keys[i]->name, mykey->name);
    strcpy(mynode->keys[i]->email, mykey->email);

    mynode->count++;
}

void insert(key *newkey)
{
    if (!ROOT)
    {
        ROOT = createnode(1);
        populate(ROOT, newkey, 0);
    }
    else
    {
        if (ROOT->count == (((2 * MIN) - 1)))
        {
            node *newroot = createnode(0);
            newroot->child[0] = ROOT;
            splitchild(newroot, 0, ROOT);
            int i = 0;
            if (newroot->keys[0]->val < newkey->val)
            {
                i++;
            }

            find_insert(newroot->child[i], newkey);

            ROOT = newroot;
        }
        else
        {
            find_insert(ROOT, newkey);
        }
    }
}

void printar(node *mynode)
{
    int i;
    if (!ROOT)
    {
        printf("Arvore Vazia.");
        return;
    }
    for (i = 0; i < mynode->count; i++)
    {
        if (!mynode->leaf)
        {
            printar(mynode->child[i]);
        }
        // printf("%d\t%p", i, mynode);
        printf("%d\t%s\t%s\n", mynode->keys[i]->val, mynode->keys[i]->name, mynode->keys[i]->email);
    }
    if (!mynode->leaf)
    {
        printar(mynode->child[i]);
    }
}

int find(node *mynode, int data)
{
    int i = 0;
    while (i < mynode->count && mynode->keys[i]->val < data)
    {
        i++;
    }
    return i;
}

key *getant(node *mynode, int i)
{
    node *ptr = mynode->child[i];
    while (!ptr->leaf)
    {
        ptr = ptr->child[ptr->count];
    }
    return ptr->keys[ptr->count - 1];
}

key *getsuc(node *mynode, int i)
{
    node *ptr = mynode->child[i + 1];
    while (!ptr->leaf)
    {
        ptr = ptr->child[0];
    }
    return ptr->keys[0];
}

void deleteleaf(node *mynode, int i)
{
    int j;
    for (j = i + 1; j < mynode->count; ++j)
    {
        mynode->keys[j - 1] = mynode->keys[j];
    }
    mynode->count--;
}

void deletenotleaf(node *mynode, int i)
{
    int k = mynode->keys[i]->val;

    if (mynode->child[i]->count >= MIN)
    {
        key *ant = getant(mynode, i);
        mynode->keys[i] = ant; //*ant???
        find_delete(mynode->child[i], ant->val);
    }

    else if (mynode->child[i + 1]->count >= MIN)
    {
        key *suc = getsuc(mynode, i);
        mynode->keys[i] = suc;
        find_delete(mynode->child[i+1], suc->val);
    }

    else
    {
        merge(mynode, i);
        find_delete(mynode->child[i], k);
    }
}

void borrant(node *mynode, int i)
{
    node *filho = mynode->child[i];
    node *irm = mynode->child[i - 1];

    int j;
    for (j = filho->count - 1; j >= 0; --j)
    {
        filho->keys[j + 1] = filho->keys[j];
    }
    if (!filho->leaf)
    {
        for (j = filho->count; j >= 0; --j)
        {
            filho->child[j + 1] = filho->child[j];
        }
    }
    filho->keys[0] = mynode->keys[i - 1];

    if (!filho->leaf)
    {
        filho->child[0] = irm->child[irm->count];
    }

    mynode->keys[i - 1] = irm->keys[irm->count - 1];

    filho->count++;
    irm->count--;
}

void borrsuc(node *mynode, int i)
{
    node *filho = mynode->child[i];
    node *irm = mynode->child[i + 1];

    filho->keys[filho->count] = mynode->keys[i];

    if (!filho->leaf)
    {
        filho->child[filho->count + 1] = irm->child[0];
    }

    mynode->keys[i] = irm->keys[0];

    int j;
    for (j = 1; j < irm->count; ++j)
    {
        irm->keys[j - 1] = irm->keys[j];
    }

    if (!irm->leaf)
    {
        for (j = 1; j <= irm->count; ++j)
        {
            irm->child[j - 1] = irm->child[j];
        }
    }

    filho->count++;
    irm->count--;
}

void merge(node *mynode, int i)
{
    node *filho = mynode->child[i];
    node *irm = mynode->child[i + 1];

    filho->keys[MIN - 1] = mynode->keys[i];

    int j;
    for (j = 0; j < irm->count; ++j)
    {
        filho->keys[j + MIN] = irm->keys[j];
    }

    if (!filho->leaf)
    {
        for (j = 0; j <= irm->count; ++j)
        {
            filho->child[j + MIN] = irm->child[j];
        }
    }

    for (j = i + 1; j < mynode->count; ++j)
    {
        mynode->keys[j - 1] = mynode->keys[j];
    }

    for (j = i + 2; j <= mynode->count; ++j)
    {
        mynode->child[j - 1] = mynode->child[j];
    }

    filho->count += irm->count + 1;
    mynode->count--;

    free (irm);
}

void fill(node *mynode, int i)
{
    if (i != 0 && mynode->child[i - 1]->count >= MIN)
    {
        borrant(mynode, i);
    }

    else if (i != mynode->count && mynode->child[i + 1]->count >= MIN)
    {
        borrsuc(mynode, i);
    }

    else
    {
        if (i != mynode->count)
        {
            merge(mynode, i);
        }
        else
        {
            merge(mynode, i - 1);
        }
    }
}

void find_delete(node *mynode, int data)
{
    int i = find(mynode, data); 

    if (i < mynode->count && mynode->keys[i]->val == data) //NÃO TÁ ENTRANDO AQUI E DEVERIA, PROVAVEL PROBLEMA NO FIND -> TALVEZ ALGUMA FUNÇÃO ESTEJA FAZENDO O COUNT ERRADO
    {
        if (mynode->leaf)
        {
            deleteleaf(mynode, i);
        }
        else
        {
            deletenotleaf(mynode, i);
        }
    }
    else
    {
        if (mynode->leaf)
        {
            printf("A chave %d nao existe.\n", data);
            return;
        }

        int flag;
        if (i == mynode->count)
        {
            flag = 1;
        }
        else
        {
            flag = 0;
        }

        if (mynode->child[i]->count < MIN)
        {
            fill(mynode, i);
        }

        if (flag && i > mynode->count)
        {
            find_delete(mynode->child[i - 1], data);
        }
        else
        {
            find_delete(mynode->child[i], data);
        }
    }
}

void delete (int data)
{
    if (!ROOT)
    {
        printf("Arvore Vazia.\n");
        return;
    }
    find_delete(ROOT, data);

    if (!ROOT->count)
    {
        node *ptr = ROOT;
        if (ROOT->leaf)
        {
            ROOT = NULL;
        }
        else
        {
            ROOT = ROOT->child[0];
        }
        free(ptr);
    }
}
