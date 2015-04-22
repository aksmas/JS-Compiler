// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>

#define START 101
int count = 1;
int label_cnt = 1;
int nextquad = START;
int array_cnt;
char* params[10];

typedef enum {ASSIGN, GOTO, GOTO_L, IF_GOTO, IF_GOTOL, RETURN, CHANGE_TYPE, PARAM, FCALL, ARRAY, ARRAY1, ARRAY2, INC, DEC, PRINT, PRINT1, SCAN, SCAN1} INSTR_TYPE;

typedef struct tac
{
	INSTR_TYPE type;
	char* dest;
	char* opnd1;
	char* op;
	char* opnd2;
	int label;
	int quad;
	char* code;
	struct tac *next;
	int assignLabel;
}tac;

tac* create_node(INSTR_TYPE i, char* dest, char* opnd1, char* op, char* opnd2, int label, int quad)
{
	tac *temp = malloc(sizeof(tac));
	temp->dest = (char*)malloc(sizeof(char)*10);
	temp->opnd1 = (char*)malloc(sizeof(char)*10);
	temp->op = (char*)malloc(sizeof(char)*7);
	temp->opnd2 = (char*)malloc(sizeof(char)*10);
	temp->code = (char*)malloc(sizeof(char)*20);
	temp->type = i;
	strcpy(temp->dest, dest);
	strcpy(temp->opnd1, opnd1);
	strcpy(temp->op, op);
	strcpy(temp->opnd2, opnd2);
	temp->label = label;
	temp->quad = quad;
	temp->assignLabel = 0;
	if (i == GOTO)
	{
		sprintf(temp->code, "goto ");
	}
	if (i == IF_GOTO)
	{
		sprintf(temp->code, "if %s %s %s goto ", temp->opnd1, temp->op, temp->opnd2);
	}
	return temp;
}


void append(INSTR_TYPE i,char* dest, char* opnd1, char* op, char* opnd2, int label, int quad, tac *head)
{
	tac* temp = create_node(i, dest, opnd1, op, opnd2, label, quad);

	//check for first insertion
    if(head == NULL){
        head = malloc(sizeof(tac));
        head = temp;
    }

    tac *ptr = head;

	while(ptr->next != NULL)
	{
		ptr = ptr->next;
	}
		ptr->next = temp;
		ptr = temp;
		ptr->next = NULL;
}

 char* newtmp()
 {
 	// static int count = 1;
 	char* ch = (char *)malloc(sizeof(char)*50);
 	sprintf(ch, "t%d", count++);
 	return ch;
 }

int* makelist(int i)
{
	int *list = (int *)malloc(sizeof(int)*15);
	list[0] = i;
	list[1] = 0;
	return list;
}

int* merge(int* p1, int* p2)
{
	int *list = (int *)malloc(sizeof(int)*15);
	int ctr1, ctr2;
	int ctr = 0;
	
	for (ctr1 = 0; p1[ctr1]!=0; ctr1++)
	{
		list[ctr] = p1[ctr1];
		ctr++;
	}

	for (ctr2 = 0; p2[ctr2]!=0; ctr2++)
	{
		list[ctr] = p2[ctr2];
		ctr++;
	}
	list[ctr] = 0;
	return list;
}

void backpatch(int *p, int i, tac* head)
{
	char target[10];
	int ctr ;
	// int index;
	sprintf(target, "%d", i);

	// printf("\nHere\n");

	for (ctr=0; p[ctr]!=0; ctr++)
	{
		tac *ptr = head;
		while(ptr != NULL)
		{
			if (ptr->quad == p[ctr])
			{
				strcat (ptr->code, target);
				// printf("\n%d OKAY:%s\n", ptr->quad,ptr->code);
				// ctr++;
			}
			ptr = ptr->next;
		}
	}
	p[0] = 0;
}

void gen()
{
	nextquad++;
}

void print_line(tac* ptr)
{
	if (ptr->type == ASSIGN)
	{
		if(ptr->quad != 0)
		{
			printf("\n%d: ", ptr->quad);
			printf("%s = %s %s %s",ptr->dest, ptr->opnd1, ptr->op, ptr->opnd2);
		}
	}
	else if (ptr->type == ARRAY)
	{
		printf("\n%d: ", ptr->quad);
		printf("%s[%d] = %s",ptr->dest, ptr->label, ptr->opnd1);
	}
	else if (ptr->type == ARRAY1)
	{
		printf("\n%d: ", ptr->quad);
		// printf("\nI am here\n");
		printf("%s = %s[%d]",ptr->dest, ptr->opnd1, ptr->label);
	}
	else if (ptr->type == ARRAY2)
	{
		printf("\n%d: ", ptr->quad);
		// printf("\nI am here\n");
		printf("%s = %s[%s]",ptr->dest, ptr->opnd1, ptr->opnd2);
	}
	else if (ptr->type == INC)
	{
		printf("\n%d: ", ptr->quad);
		printf("inc %s", ptr->opnd1);
	}
	else if (ptr->type == DEC)
	{
		printf("\n%d: ", ptr->quad);
		printf("dec %s", ptr->opnd1);
	}
	else if (ptr->type == GOTO_L)
	{
		printf("\n%d: ", ptr->quad);
		printf("goto %d", ptr->label);
	}
	else if (ptr->type == RETURN)
	{
		printf("\n%d: ", ptr->quad);
		printf("return %s", ptr->opnd1);
	}
	else if (ptr->type == PRINT)
	{
		printf("\n%d: ", ptr->quad);
		printf("print %s", ptr->opnd1);
	}
	else if (ptr->type == PRINT1)						//print array element
	{
		printf("\n%d: ", ptr->quad);
		printf("print %s[%s]", ptr->opnd1, ptr->opnd2);
	}
	else if (ptr->type == SCAN)
	{
		printf("\n%d: ", ptr->quad);
		printf("scan %s", ptr->opnd1);
	}
	else if (ptr->type == SCAN1)						//print array element
	{
		printf("\n%d: ", ptr->quad);
		printf("scan %s[%s]", ptr->opnd1, ptr->opnd2);
	}
	else if (ptr->type == IF_GOTOL)						//IF_GOTO
	{
		printf("\n%d: ", ptr->quad);
		printf("if %s %s %s goto %d", ptr->opnd1, ptr->op, ptr->opnd2, ptr->label);
	}
	else if (ptr->type == IF_GOTO)						//IF_GOTO
	{
		printf("\n%d: ", ptr->quad);
		printf("%s", ptr->code);
	}
	else if (ptr->type == GOTO)						//IF_GOTO
	{
		printf("\n%d: ", ptr->quad);
		printf("%s", ptr->code);
	}
	else if (ptr->type == PARAM)
	{
		printf("\n%d: ", ptr->quad);
		printf("param %s", ptr->opnd1);
	}
	else if (ptr->type == FCALL)
	{
		printf("\n%d: ", ptr->quad);
		printf("%s = call %s, %d", ptr->dest, ptr->opnd1, ptr->label);
	}
	else									//CHANGE_TYPE
	{
		printf("\n%d: ", ptr->quad);
		printf("%s = int_to_real %s", ptr->dest, ptr->opnd1);
	}
}

print_tac(tac* head)
{
	if (head == NULL)
	{
		printf("\nNo TAC");
	}

	// else if (head->next == NULL)
	// {
	// 	print_line(head);
	// }

	else
	{
		tac* ptr = head;
		while(ptr != NULL)
		{	
			// printf("Here!!!!");
			print_line(ptr);
			ptr = ptr -> next;
		}
	}
	printf("\n");
}

void print_list(int *list)
{
	int i;
	for (i=0; list[i]!=0; i++)
	{
		printf("%d\n",list[i]);
	}
}

void insert_param(char* ch)
{
	// printf("\n%s\n", ch);
	// array_cnt = 0;
	params[array_cnt] = (char*) malloc(sizeof(char)*10);
	strcpy(params[array_cnt],ch);
	array_cnt++;
}

