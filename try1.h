// #include <iostream>
// #include <map>
#include <string.h>
#include "tac.h"
// using namespace std;

union value 
{
	int val_i;
	float val_f;
	char* val_s;
};


/*Symbol Table Entry*/
typedef struct STEntry{ 
     // string name;
     char* type;
     int size;     
     struct sym_tab * child;
     int offset;
     union value val;
     int no_elements;
     char* name;
     int isDone;
     int isTemp;
     // int paramCount;
}STEntry;

// int ctr = 0;
// typedef map <string, STEntry> ST;				//maps an identifier to its properties

//Structure for symbol table
typedef struct sym_tab
{
	char* name;
	int ctr;
	char *key[100];
	STEntry value[100];
	int paramCount;
	//struct tac *tac_list;
	int width;
	struct sym_tab * parent;

}sym_tab;



sym_tab* mktable(sym_tab *previous, char* name)
{
	sym_tab *temp = (sym_tab*) malloc(sizeof(sym_tab));
	temp->ctr = 0;
	temp->name = (char*)malloc(sizeof(char)*15);
	strcpy(temp->name, name);
	// printf("%d", temp->ctr);
	temp->parent = previous;
	temp->width = 0;
	return temp;
}


int lookup(sym_tab *t, char* id)
{
	int i;
	// printf("\n%d\n",t->ctr);
	// printf("\n%s\n", id);
	for (i=0; i<t->ctr; i++)
	{
		if (strcmp(t->key[i],id) == 0)
		{
			// printf("\ni = %d\n", i);
			return i;
		}
	}
	// printf("\ni = -1\n");
	return -1;
	
}

void enter(sym_tab *t, char* id, char* type, int size, int tcase)
{
	//check for already existing
	// printf("Here");
	int offset;
	offset = t->width;
	if (lookup(t,id) == -1)
	{
		// printf("Here");
		STEntry temp = {type, size, NULL,offset};
		temp.isDone = 0;
		temp.isTemp = tcase;
		// temp.paramCount = 0;
		t->key[t->ctr] = id;
		t->value[t->ctr] = temp;
		(t->ctr)++;
		// t->table[id] = temp;
		t->width = t->width + size;
	}
}

void enterproc (sym_tab *t, char* id, sym_tab *newtable)
{
	int size = newtable->width;
	int offset = t->width;
	STEntry temp = {NULL,size,newtable,offset};
	temp.isDone = 0;
	temp.isTemp = 0;
	// temp.paramCount = i;
	// t->table[id] = temp;
	t->key[t->ctr] = id;
	t->value[t->ctr] = temp;
	(t->ctr)++;
	t->width = t->width + size;
}

void setValue (sym_tab *t, char* v, char* id)
{
	int i;
	i = lookup(t,id);
	char *type = (char *) malloc(sizeof(char)*10);
	//printf("\n%s\n", t->value[i].type);
	strcpy(type, t->value[i].type);//printf("\n%s\n", type);
	// union value temp;
	// temp = t->value[i]->val;
	if (strcmp(type, "int") == 0)
		t->value[i].val.val_i = atoi(v);
	else if (strcmp(type, "float") == 0)
		t->value[i].val.val_f = atof(v);
	else
	{
		t->value[i].val.val_s = (char*) malloc(sizeof(char)*100);
		strcpy(t->value[i].val.val_s,v);
	}
	// printf("ASDSDFDFGFGGFGGHHGH");
}

void setElements (sym_tab *t, int v, char* id)
{
	int i;

	i = lookup(t,id);
	t->value[i].no_elements = v;
	// printf("ASDSDFDFGFGGFGGHHGH");
}

void print_st(sym_tab *t)
{
	printf("\n");
	int i;
	int a;
	a = t->ctr;
	for (i=0; i<(t->ctr); i++)
	{
		printf("Key:%s\n", t->key[i]);
		printf("Value:%d\n", t->value[i].offset);
	}
	printf("Size:%d\n", t->width);
}