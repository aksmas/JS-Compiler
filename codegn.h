
typedef struct x86_instr
{
	int id;
	char* code;
	struct x86_instr* next;
}instr;

instr* head;
instr* temp1;
int label_ctr = 1;
char* str;

int labels_array[100];
int labarrcnt = 0;

char *param_name[20];
int param_loc[20];
int locals;						//no. of locals

int printDone = 0;
int dpc =0;
int scanDone = 0;
int dsc = 0;

instr* x86_create_node(int i, char* s)							//create a node for a x86 instruction
{
	instr *temp = malloc(sizeof(instr));
	temp->code = (char*)malloc(sizeof(char)*200);
	temp->id = i;
	strcpy(temp->code, s);
	return temp;
}

int param_search(sym_tab* t, char* s)							//Return the parameter offset in the stack given its name
{
	int i;
	for (i=0; i<t->ctr; i++)
	{
		if (strcmp(param_name[i], s) == 0)
			return param_loc[i];
	}
}

int lab_search(int label)
{
	int i;
	for (i=0; i<labarrcnt; i++)
	{
		if (labels_array[i] == label)
			return 1;
	}
	return 0;
}

void initialize(sym_tab* t)										//mapping of parameters and local var to offsets in stack
{
	// printf("\nPrameters-%d\n", t->paramCount);	
	int i;
	int j = 0;
	// printf("\nSTART\n");
	for (i=1; i<t->paramCount+1; i++)
	{
		
		param_name[j] = t->key[i];
		param_loc[j] = t->value[i].offset + t->value[i].size + 4;
		j++;
		// printf("\n%s\n", param_name[j]);
	}
	// printf("\nEND\n");
	//j = i;
	while (t->value[i].isTemp)
	{
		i++;
	}
	param_name[j] = t->key[i];
	param_loc[j] = -16;
	i++;
	j++;

	// printf("\nt->ctr:%d\n",i);
	while (i < t->ctr)
	{
		// printf("\nI can't be here!!\n");
		if (!t->value[i].isTemp)
		{
			param_name[j] = t->key[i];
			param_loc[j] = param_loc[j-1] - 4;
			j++;
			
		}
		i++;
	}
	locals = j - t->paramCount-1;
	// for (i=0; i<j; i++)
	// {
	// 	printf("\nVar:%s\n", param_name[i]);
	// 	printf("\nLoc:%d\n", param_loc[i]);
	// }

}

void x86_append(int i,char* s)									//append an x86 instr
{
	instr* temp = x86_create_node(i,s);

	//check for first insertion
    if(head == NULL){
        head = malloc(sizeof(instr));
        head = temp;
    }

    instr *ptr = head;

	while(ptr->next != NULL)
	{
		ptr = ptr->next;
	}
		ptr->next = temp;
		ptr = temp;
		ptr->next = NULL;
}

instr* x86_search(int i)										//search for an instr given its quad
{
	instr* ptr = head;
	while(ptr != NULL)
	{
		if (ptr->id == i)
			return ptr;
		ptr = ptr->next;
	}
}

void x86_prepend(char* s, char* t)								//prepend the code of an instr to print the label
{
    int len = strlen(t);
    int i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}


int extract_label(char* s)										//find the label froma string
{
	int l = strlen(s);
	char s1[3];
	int i;
	int j = 0;
	for (i=l-3; i<l; i++)
	{
		s1[j] = s[i];
		j++;
	}
	// printf("\n%s\n", s1);
	int a = atoi(s1);
	// printf("\n%d\n", a);
	return a;
}

void assign_label(int i, tac* head)								//Assign a label to an instr.
{
	tac* ptr = head;
	while(ptr != NULL)
	{
		if (ptr->quad == i)
		{
			ptr->assignLabel = 1;
			// printf("\nLabel assigned to %d\n", ptr->quad);
			break;
		}
		ptr = ptr->next;
	}
}

void do_print()
{
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n\nprnt_int:\n");
	x86_append(label_ctr, str);
	// free(str);

	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n pushl %%ebp");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl %%esp, %%ebp");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n pushl %%esi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl 8(%%ebp), %%eax");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl %%esp, %%esi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n cmpl $0, %%eax \n jge prnt1");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n imull $(-1), %%eax");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl %%eax, 8(%%ebp)");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl $45, %%edx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl %%edx, group+400");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n movl $4, %%eax \n movl $1, %%ebx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl $group+400, %%ecx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n movl $1, %%edx\n int $0x80");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl 8(%%ebp), %%eax");
	x86_append(label_ctr, str);
	
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n\nprnt1:\n\n cdq");
	x86_append(label_ctr, str);
	// free(str);

	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl $10, %%ebx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n idivl %%ebx\n pushl %%edx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n cmpl $0, %%eax\n jne prnt1");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n jmp prnt2");
	x86_append(label_ctr, str);

	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n\nprnt2:\n\n popl %%edx");
	x86_append(label_ctr, str);

	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n addl $48, %%edx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl %%edx, group+400");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n movl $4, %%eax \n movl $1, %%ebx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl $group+400, %%ecx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n movl $1, %%edx\n int $0x80");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n cmp %%esp, %%esi\n jne prnt2");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n\n movl $10, group+400");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n movl $4, %%eax \n movl $1, %%ebx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl $group+400, %%ecx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n movl $1, %%edx\n int $0x80");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str,"\n popl %%esi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*200);
	sprintf(str,"\n movl %%ebp, %%esp");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*200);
	sprintf(str,"\n popl %%ebp");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*200);
	sprintf(str,"\n ret\n");
	x86_append(label_ctr, str);
	// label_ctr++;
	
}

void do_scan()
{
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n\nscan:\n");
	x86_append(label_ctr, str);
	// free(str);

	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n pushl %%ebp");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl %%esp, %%ebp");
	x86_append(label_ctr, str);	
	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n movl $0, %%edi");
	x86_append(label_ctr, str);
	
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n\nscan1:\n");
	x86_append(label_ctr, str);
	// free(str);

	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl $3, %%eax");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl $0, %%ebx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl $numb, %%ecx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n movl $1, %%edx\n int $0x80");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n cmpl $10, numb\n je scan2");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n cmpl $45, numb\n je scan11");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n imull $10, %%edi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl numb, %%esi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n subl $48, %%esi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n addl %%esi, %%edi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n jmp scan1");
	x86_append(label_ctr, str);

	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n\nscan11:\n");
	x86_append(label_ctr, str);
	// free(str);

	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl $3, %%eax");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl $0, %%ebx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl $numb, %%ecx");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n movl $1, %%edx\n int $0x80");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*30);
	sprintf(str, "\n cmpl $10, numb\n je scan22");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n imull $10, %%edi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n movl numb, %%esi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n subl $48, %%esi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n addl %%esi, %%edi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str, "\n jmp scan11");
	x86_append(label_ctr, str);

	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n\nscan2:\n");
	x86_append(label_ctr, str);

	str = (char*) malloc (sizeof(char)*20);
	sprintf(str,"\n movl %%edi, %%eax");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*200);
	sprintf(str,"\n movl %%ebp, %%esp");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*200);
	sprintf(str,"\n popl %%ebp");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*200);
	sprintf(str,"\n ret\n");
	x86_append(label_ctr, str);

	str = (char*) malloc (sizeof(char)*25);
	sprintf(str, "\n\nscan22:\n");
	x86_append(label_ctr, str);

	str = (char*) malloc (sizeof(char)*20);
	sprintf(str,"\n imull $(-1),%%edi");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*20);
	sprintf(str,"\n movl %%edi, %%eax");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*200);
	sprintf(str,"\n movl %%ebp, %%esp");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*200);
	sprintf(str,"\n popl %%ebp");
	x86_append(label_ctr, str);
	str = (char*) malloc (sizeof(char)*200);
	sprintf(str,"\n ret\n");
	x86_append(label_ctr, str);
	// label_ctr++;
}

void tac_to_x86(sym_tab* t, tac* ptr, tac* head1)							//translator
{
	int p,q,r;
	int d,e;
	// print_st(t);
	if (ptr->type == ASSIGN)		
	{
		// printf("\n%s\n", ptr->dest);
		p = lookup(t, ptr->dest);
		// printf("\nHere\n");
		q = lookup(t, ptr->opnd1);
		r = lookup(t, ptr->opnd2);

		if (strcmp(ptr->opnd2, "") != 0)							//2 operators on RHS
		{
			if (q == -1)											//first operand in an int
			{
				// fprintf(wfile,"\n movl $%s, %%eax", ptr->opnd1);
				str = (char*) malloc (sizeof(char)*20);
				sprintf(str,"\n movl $%s, %%eax", ptr->opnd1);
				x86_append(ptr->quad, str);
			}
			else
			{
				if (t->value[q].isTemp) 
				{
					str = (char*) malloc (sizeof(char)*20);
					sprintf(str,"\n movl %%ecx, %%eax");
					x86_append(ptr->quad, str);
				}
				else
				{
					// printf("\nasjjhdga\n");
					str = (char*) malloc (sizeof(char)*20);
					sprintf(str,"\n movl %s, %%eax", ptr->opnd1);
					x86_append(ptr->quad, str);
				}
			}

			if (r == -1)
			{
				if (strcmp(ptr->op, "+") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n addl $%s, %%eax", ptr->opnd2);
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "-") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n subl $%s, %%eax", ptr->opnd2);
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "*") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n imull $%s, %%eax", ptr->opnd2);
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "/") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str, "\n cdq");
					x86_append(ptr->quad, str);
					sprintf(str,"\n movl $%s, %%ebx", ptr->opnd2);
					x86_append(ptr->quad, str);
					sprintf(str, "\n idivl %%ebx");
					x86_append(ptr->quad, str);
					// fprintf(wfile, "\npushl %%eax");

				}

				if (strcmp(ptr->op, "\%") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n movl $0, %%edx");
					x86_append(ptr->quad, str);
					sprintf(str, "\n cdq");
					x86_append(ptr->quad, str);
					sprintf(str,"\n movl $%s, %%ebx", ptr->opnd2);
					x86_append(ptr->quad, str);
					sprintf(str, "\n idivl %%ebx");
					x86_append(ptr->quad, str);
					sprintf(str, "\n movl %%edx, %%eax");
					x86_append(ptr->quad, str);
				}
			}
			else
			{
				if (strcmp(ptr->op, "+") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n addl %s, %%eax", ptr->opnd2);
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "-") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n subl %s, %%eax", ptr->opnd2);
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "*") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n imull %s, %%eax", ptr->opnd2);
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "/") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str, "\n cdq");
					x86_append(ptr->quad, str);
					sprintf(str,"\n movl %s, %%ebx", ptr->opnd2);
					x86_append(ptr->quad, str);
					sprintf(str, "\n idivl %%ebx");
					x86_append(ptr->quad, str);
					// fprintf(wfile, "\npushl %%eax");

				}

				if (strcmp(ptr->op, "\%") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n movl $0, %%edx");
					x86_append(ptr->quad, str);
					sprintf(str, "\n cdq");
					x86_append(ptr->quad, str);
					sprintf(str,"\n movl %s, %%ebx", ptr->opnd2);
					x86_append(ptr->quad, str);
					sprintf(str, "\n idivl %%ebx");
					x86_append(ptr->quad, str);
					sprintf(str, "\n movl %%edx, %%eax");
					x86_append(ptr->quad, str);
				}	
			}
			sprintf(str,"\n movl %%eax, %%ecx");
			x86_append(ptr->quad, str);
		}

		else
		{
			if (!t->value[p].isDone)
			{
				fprintf(wfile1, "\n%s:\n.long -1", ptr->dest);
				t->value[p].isDone = 1;
			}

			if (q == -1)
			{
				str = (char*) malloc (sizeof(char)*200);
				sprintf(str,"\n movl $%s, %s", ptr->opnd1, ptr->dest);
				x86_append(ptr->quad, str);
			}

			else
			{
				// printf("\ntemp = %d\n", t->value[q].isTemp);
				if(t->value[q].isTemp)
				{

					str = (char*) malloc (sizeof(char)*20);
					sprintf(str,"\n movl %%ecx, %s", ptr->dest);
					x86_append(ptr->quad, str);					
					
				}
				
				else
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n movl %s, %%edx", ptr->opnd1);
					x86_append(ptr->quad, str);

					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n movl %%edx, %s", ptr->dest);
					x86_append(ptr->quad, str);
					

				}
			}
		}
	}

	else if (ptr->type == INC)
	{
		str = (char*) malloc (sizeof(char)*200);
		sprintf(str,"\n incl %s", ptr->opnd1);
		x86_append(ptr->quad, str);
	}

	else if (ptr->type == DEC)
	{
		str = (char*) malloc (sizeof(char)*200);
		sprintf(str,"\n decl %s", ptr->opnd1);
		x86_append(ptr->quad, str);
	}

	else if (ptr->type == ARRAY)							//a[i] = t
	{
		int p = lookup(t, ptr->dest);
		int q = lookup(t, ptr->opnd1);
		// printf("\np = %d\n", p);
		if (!t->value[p].isDone)
		{
			fprintf(wfile1, "\n%s:\n.space %d", ptr->dest, t->value[p].no_elements*4);
			t->value[p].isDone = 1;
		}
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl $%d, %%eax", ptr->label);
		x86_append(ptr->quad, str);
		if (q == -1)
			sprintf(str,"\n movl $%s, %s(,%%eax,4)", ptr->opnd1, ptr->dest);
		else
			sprintf(str,"\n movl %s, %s(,%%eax,4)", ptr->opnd1, ptr->dest);
		x86_append(ptr->quad, str);
	}

	else if (ptr->type == ARRAY1)							//t = a[1]
	{
		int p = lookup(t, ptr->dest);
		if (!t->value[p].isDone)
		{
			fprintf(wfile1, "\n%s:\n.long -1", ptr->dest);
			t->value[p].isDone = 1;
		}
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl $%d, %%eax", ptr->label);
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %s(,%%eax,4), %%ebx", ptr->opnd1);
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %%ebx, %s", ptr->dest);
		x86_append(ptr->quad, str);
	}

	else if (ptr->type == ARRAY2)							//t = a[i]
	{
		int p = lookup(t, ptr->dest);
		if (!t->value[p].isDone)
		{
			fprintf(wfile1, "\n%s:\n.long -1", ptr->dest);
			t->value[p].isDone = 1;
		}
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl %s, %%eax", ptr->opnd2);
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %s(,%%eax,4), %%ebx", ptr->opnd1);
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %%ebx, %s", ptr->dest);
		x86_append(ptr->quad, str);
	}

	else if (ptr->type == PRINT)
	{
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n pushl %s", ptr->opnd1);
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n call prnt_int");
		x86_append(ptr->quad, str);

		printDone = 1;
	}

	else if (ptr->type == SCAN)
	{
		int p = lookup(t, ptr->opnd1);
		if (!t->value[p].isDone)
		{
			fprintf(wfile1, "\n%s:\n.long -1", ptr->opnd1);
			t->value[p].isDone = 1;
		}

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n call scan");
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl %%eax, %s", ptr->opnd1);
		x86_append(ptr->quad, str);

		scanDone = 1;
	}

	else if (ptr->type == PRINT1)								//print a[i]
	{
		int q = lookup(t, ptr->opnd2);

		str = (char*) malloc (sizeof(char)*20);
		if (q == -1)
			sprintf(str, "\n movl $%s, %%eax", ptr->opnd2);
		else
			sprintf(str, "\n movl %s, %%eax", ptr->opnd2);
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n pushl %s(,%%eax, 4)", ptr->opnd1);
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n call prnt_int");
		x86_append(ptr->quad, str);

		printDone = 1;
	}

	else if (ptr->type == SCAN1)								//scan a[i]
	{
		int q = lookup(t, ptr->opnd2);

		int p = lookup(t, ptr->opnd1);
		if (!t->value[p].isDone)
		{
			fprintf(wfile1, "\n%s:\n.long -1", ptr->opnd1);
			t->value[p].isDone = 1;
		}

		
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n call scan");
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl %%eax, %%ebx");
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		if (q == -1)
			sprintf(str, "\n movl $%s, %%eax", ptr->opnd2);
		else
			sprintf(str, "\n movl %s, %%eax", ptr->opnd2);
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl %%ebx, %s(,%%eax,4)", ptr->opnd1);
		x86_append(ptr->quad, str);


		scanDone = 1;
	}

	else if (ptr->type == GOTO_L)	
	{
		str = (char*) malloc (sizeof(char)*200);
		sprintf(str,"\n jmp L%d", ptr->label);
		x86_append(ptr->quad, str);
		if (ptr->quad > ptr->label)
		{
			temp1 = (instr*) malloc(sizeof(instr));
			temp1 = x86_search(ptr->label);
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n\nL%d:\n", ptr->label);
			x86_prepend(temp1->code, str);
		}
		else
		{
			assign_label(ptr->label, head1);
		}
		labels_array[labarrcnt] = ptr->label;
		labarrcnt++;
	}

	else if (ptr->type == GOTO)
	{
		int label = extract_label(ptr->code);
		// printf("\nLabel: %d\n", label);
		str = (char*) malloc (sizeof(char)*15);
		sprintf(str,"\n jmp L%d", label);
		x86_append(ptr->quad, str);
		if (ptr->quad > label)
		{
			temp1 = (instr*) malloc(sizeof(instr));
			temp1 = x86_search(label);
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n\nL%d:\n", label);
			x86_prepend(temp1->code, str);
		}
		else
		{
			// printf("\nAssign Label\n");
			assign_label(label, head1);
		}
		labels_array[labarrcnt] = label;
		labarrcnt++;
	}

	else if (ptr->type == IF_GOTOL)
	{
		q = lookup(t, ptr->opnd1);
		r = lookup(t, ptr->opnd2);

		if (q == -1 && r == -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl $%s, $%s", ptr->opnd2, ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else if (q != -1 && r == -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl $%s, %s", ptr->opnd2, ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else if (q == -1 && r != -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl %s, $%s", ptr->opnd2, ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else 
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n movl %s, %%edx", ptr->opnd2);
			x86_append(ptr->quad, str);

			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl %%edx, %s", ptr->opnd1);
			x86_append(ptr->quad, str);
		}

		if (strcmp(ptr->op, ">") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jg L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "<") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jl L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, ">=") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jge L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "<=") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jle L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "==") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n je L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else 											//op:!=
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jne L%d", ptr->label);
			x86_append(ptr->quad, str);
		}

		if (ptr->quad > ptr->label)
		{
			temp1 = (instr*) malloc(sizeof(instr));
			temp1 = x86_search(ptr->label);
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n\nL%d:\n", ptr->label);
			x86_prepend(temp1->code, str);
		}
		else
		{
			assign_label(ptr->label, head1);
		}

		labels_array[labarrcnt] = ptr->label;
		labarrcnt++;
		
	}

	else if (ptr->type == IF_GOTO)
	{
		q = lookup(t, ptr->opnd1);
		r = lookup(t, ptr->opnd2);

		int label = extract_label(ptr->code);

		if (q == -1 && r == -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl $%s, $%s", ptr->opnd2, ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else if (q != -1 && r == -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl $%s, %s", ptr->opnd2, ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else if (q == -1 && r != -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl %s, $%s", ptr->opnd2, ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else 
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n movl %s, %%edx", ptr->opnd2);
			x86_append(ptr->quad, str);

			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl %%edx, %s", ptr->opnd1);
			x86_append(ptr->quad, str);
		}

		if (strcmp(ptr->op, ">") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jg L%d", label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "<") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jl L%d", label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, ">=") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jge L%d", label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "<=") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jle L%d", label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "==") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n je L%d", label);
			x86_append(ptr->quad, str);
		}
		else 											//op:!=
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jne L%d", label);
			x86_append(ptr->quad, str);
		}

		if (ptr->quad > label)
		{
			temp1 = (instr*) malloc(sizeof(instr));
			temp1 = x86_search(label);
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n\nL%d:\n", label);
			x86_prepend(temp1->code, str);
		}
		else
		{
			// printf("\nAssign Label\n");
			assign_label(label, head1);
		}
		labels_array[labarrcnt] = label;
		labarrcnt++;
	}
	
	else if (ptr->type == PARAM)
	{
		int q = lookup(t, ptr->opnd1);
		str = (char*) malloc (sizeof(char)*200);
		if (q == -1)
			sprintf(str,"\n pushl $%s", ptr->opnd1);
		else
			sprintf(str,"\n pushl %s", ptr->opnd1);
		x86_append(ptr->quad, str);
		// fprintf(wfile,"\n pushl $%s", ptr->opnd1);
	}
	else if (ptr->type == FCALL)
	{
		str = (char*) malloc (sizeof(char)*200);
		sprintf(str,"\n call %s", ptr->opnd1);
		x86_append(ptr->quad, str);

		// if (!t->value[p].isDone)
		// {
		// 	fprintf(wfile1, "\n%s:\n.long -1", ptr->dest);
		// 	t->value[p].isDone = 1;
		// }

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %%eax, %%ecx");
		x86_append(ptr->quad, str);
		// fprintf(wfile,"\n call %s",ptr->opnd1);
	}
}

void tac_to_x86f(sym_tab* t, tac* ptr, tac* head1)				//translator for a func.
{
	int p,q,r;
	int d,e;
	// print_st(t);
	if (ptr->type == ASSIGN)		
	{
		// printf("\n%s\n", ptr->dest);
		p = lookup(t, ptr->dest);
		// printf("\nHere\n");
		q = lookup(t, ptr->opnd1);
		r = lookup(t, ptr->opnd2);

		if (strcmp(ptr->opnd2, "") != 0)							//2 operators on RHS
		{
			if (q == -1)											//first operand in an int
			{
				// fprintf(wfile,"\n movl $%s, %%eax", ptr->opnd1);
				str = (char*) malloc (sizeof(char)*200);
				sprintf(str,"\n movl $%s, %%eax", ptr->opnd1);
				x86_append(ptr->quad, str);
			}
			else
			{
				if (t->value[q].isTemp) 
				{
					str = (char*) malloc (sizeof(char)*20);
					sprintf(str,"\n movl %%ecx, %%eax");
					x86_append(ptr->quad, str);
				}
				else
				{
					// printf("\nasjjhdga\n");
					str = (char*) malloc (sizeof(char)*20);
					sprintf(str,"\n movl %d(%%ebp), %%eax", param_search(t,ptr->opnd1));
					x86_append(ptr->quad, str);
				}
				
			}

			if (r == -1)
			{
				if (strcmp(ptr->op, "+") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n addl $%s, %%eax", ptr->opnd2);
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "-") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n subl $%s, %%eax", ptr->opnd2);
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "*") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n imull $%s, %%eax", ptr->opnd2);
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "/") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str, "\n cdq");
					x86_append(ptr->quad, str);
					sprintf(str,"\n movl $%s, %%ebx", ptr->opnd2);
					x86_append(ptr->quad, str);
					sprintf(str, "\n idivl %%ebx");
					x86_append(ptr->quad, str);
					// fprintf(wfile, "\npushl %%eax");

				}

				if (strcmp(ptr->op, "\%") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n movl $0, %%edx");
					x86_append(ptr->quad, str);
					sprintf(str, "\n cdq");
					x86_append(ptr->quad, str);
					sprintf(str,"\n movl $%s, %%ebx", ptr->opnd2);
					x86_append(ptr->quad, str);
					sprintf(str, "\n idivl %%ebx");
					x86_append(ptr->quad, str);
					sprintf(str, "\n movl %%edx, %%eax");
					x86_append(ptr->quad, str);
				}
			}
			else
			{
				if (strcmp(ptr->op, "+") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n addl %d(%%ebp), %%eax", param_search(t,ptr->opnd2));
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "-") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n subl %d(%%ebp), %%eax", param_search(t,ptr->opnd2));
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "*") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n imull %d(%%ebp), %%eax", param_search(t,ptr->opnd2));
					x86_append(ptr->quad, str);
				}

				if (strcmp(ptr->op, "/") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str, "\n cdq");
					x86_append(ptr->quad, str);
					sprintf(str,"\n movl %d(%%ebp), %%ebx", param_search(t,ptr->opnd2));
					x86_append(ptr->quad, str);
					sprintf(str, "\n idivl %%ebx");
					x86_append(ptr->quad, str);
					// fprintf(wfile, "\npushl %%eax");

				}

				if (strcmp(ptr->op, "\%") == 0)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n movl $0, %%edx");
					x86_append(ptr->quad, str);
					sprintf(str, "\n cdq");
					x86_append(ptr->quad, str);
					sprintf(str,"\n movl %d(%%ebp), %%ebx", param_search(t,ptr->opnd2));
					x86_append(ptr->quad, str);
					sprintf(str, "\n idivl %%ebx");
					x86_append(ptr->quad, str);
					sprintf(str, "\n movl %%edx, %%eax");
					x86_append(ptr->quad, str);
				}	
			}
			sprintf(str,"\n movl %%eax, %%ecx");
			x86_append(ptr->quad, str);
		}

		else
		{	
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n subl $4, %%esp");
			x86_append(ptr->quad, str);

			if (q == -1)
			{
				str = (char*) malloc (sizeof(char)*200);
				sprintf(str,"\n movl $%s, %d(%%ebp)", ptr->opnd1, param_search(t,ptr->dest));
				x86_append(ptr->quad, str);
			}

			else
			{
				// printf("\ntemp = %d\n", t->value[q].isTemp);
				if(t->value[q].isTemp)
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n movl %%ecx, %d(%%ebp)", param_search(t,ptr->dest));
					x86_append(ptr->quad, str);
				}
				
				else
				{
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n movl %d(%%ebp), %d(%%ebp)", param_search(t,ptr->opnd1), param_search(t,ptr->dest));
					x86_append(ptr->quad, str);

				}
			}
		}
	}

	else if (ptr->type == INC)
	{
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n incl %d(%%ebp)", param_search(t,ptr->opnd1));
		x86_append(ptr->quad, str);
	}

	else if (ptr->type == DEC)
	{
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n decl %d(%%ebp)", param_search(t,ptr->opnd1));
		x86_append(ptr->quad, str);
	}

	else if (ptr->type == ARRAY)
	{
		int p = lookup(t, ptr->dest);
		int q = lookup(t, ptr->opnd1);
		// printf("\np = %d\n", p);
		
		str = (char*) malloc (sizeof(char)*200);
		sprintf(str, "\n movl $%d, %%eax", ptr->label);
		x86_append(ptr->quad, str);
		if (q == -1)
			sprintf(str,"\n movl $%s, %d(%%ebp,%%eax,4)", ptr->opnd1, param_search(t,ptr->dest));	//
		else
			sprintf(str,"\n movl %s, %d(%%ebp,%%eax,4)", ptr->opnd1, param_search(t,ptr->dest));	//
		x86_append(ptr->quad, str);
	}


	else if (ptr->type == ARRAY1)
	{
		int p = lookup(t, ptr->dest);
		
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl $%d, %%eax", ptr->label);
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %d(%%ebp,%%eax,4), %%ebx", param_search(t,ptr->opnd1));
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %%ebx, %d(%%ebp)", param_search(t,ptr->dest));
		x86_append(ptr->quad, str);
	}

	else if (ptr->type == ARRAY2)
	{
		int p = lookup(t, ptr->dest);
		
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl %d(%%ebp), %%eax", param_search(t,ptr->opnd2));
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %d(%%ebp,%%eax,4), %%ebx", param_search(t,ptr->opnd1));
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %%ebx, %d(%%ebp)", param_search(t,ptr->dest));
		x86_append(ptr->quad, str);
	}
	else if (ptr->type == PRINT)
	{
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl %d(%%ebp), %%esi", param_search(t,ptr->opnd1));
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n pushl %%esi");
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n call prnt_int");
		x86_append(ptr->quad, str);

		printDone = 1;
	}

	else if (ptr->type == SCAN)
	{
		int p = lookup(t, ptr->opnd1);
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n call scan");
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl %%eax, %d(%%ebp)", param_search(t,ptr->opnd1));
		x86_append(ptr->quad, str);

		scanDone = 1;
	}

	else if (ptr->type == PRINT1)
	{
		int q = lookup(t, ptr->opnd2);

		str = (char*) malloc (sizeof(char)*20);
		if (q == -1)
			sprintf(str, "\n movl $%s, %%eax", ptr->opnd2);
		else
			sprintf(str, "\n movl %d(%%ebp), %%eax", param_search(t,ptr->opnd2));
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*25);
		sprintf(str, "\n pushl %d(%%ebp,%%eax, 4)", param_search(t,ptr->opnd1));
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n call prnt_int");
		x86_append(ptr->quad, str);

		printDone = 1;
	}
/*
	else if (ptr->type == SCAN1)
	{
		int q = lookup(t, ptr->opnd2);

		int p = lookup(t, ptr->opnd1);
				
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n call scan");
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str, "\n movl %%eax, %%ebx");
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*30);
		if (q == -1)
			sprintf(str, "\n movl $%s, %%eax", ptr->opnd2);
		else
			sprintf(str, "\n movl %d(%%ebp), %%eax", param_search(t,ptr->opnd2));
		x86_append(ptr->quad, str);

		str = (char*) malloc (sizeof(char)*30);
		sprintf(str, "\n movl %%ebx, %d(%%ebp,%%eax,4)", param_search(t,ptr->opnd1));
		x86_append(ptr->quad, str);


		scanDone = 1;
	}*/
	else if (ptr->type == RETURN)
	{
		int q = lookup(t, ptr->opnd1);
		str = (char*) malloc (sizeof(char)*20);
		if (q != -1)
			sprintf(str,"\n movl %d(%%ebp), %%eax", param_search(t,ptr->opnd1));
		else
			sprintf(str,"\n movl $%s, %%eax", ptr->opnd1);
		x86_append(ptr->quad, str);
	}

	else if (ptr->type == GOTO_L)	
	{
		str = (char*) malloc (sizeof(char)*200);
		sprintf(str,"\n jmp L%d", ptr->label);
		x86_append(ptr->quad, str);
		if (ptr->quad > ptr->label)
		{
			temp1 = (instr*) malloc(sizeof(instr));
			temp1 = x86_search(ptr->label);
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n\nL%d:\n", ptr->label);
			x86_prepend(temp1->code, str);
		}
		else
		{
			assign_label(ptr->label, head1);
		}
		labels_array[labarrcnt] = ptr->label;
		labarrcnt++;
	}

	else if (ptr->type == GOTO)
	{
		int label = extract_label(ptr->code);
		// printf("\nLabel: %d\n", label);
		str = (char*) malloc (sizeof(char)*15);
		sprintf(str,"\n jmp L%d", label);
		x86_append(ptr->quad, str);
		if (ptr->quad > label)
		{
			temp1 = (instr*) malloc(sizeof(instr));
			temp1 = x86_search(label);
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n\nL%d:\n", label);
			x86_prepend(temp1->code, str);
		}
		else
		{
			// printf("\nAssign Label\n");
			assign_label(label, head1);
		}
		labels_array[labarrcnt] = label;
		labarrcnt++;
	}

	else if (ptr->type == IF_GOTOL)
	{
		int q = lookup(t, ptr->opnd1);
		int r = lookup(t, ptr->opnd2);

		if (q == -1 && r == -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl $%s, $%s", ptr->opnd2, ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else if (q != -1 && r == -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl $%s, %d(%%ebp)", ptr->opnd2, param_search(t,ptr->opnd1));
			x86_append(ptr->quad, str);
		}
		else if (q == -1 && r != -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl %d(%%ebp), $%s", param_search(t,ptr->opnd2), ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else 
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl %d(%%ebp), %d(%%ebp)", param_search(t,ptr->opnd2), param_search(t,ptr->opnd1));
			x86_append(ptr->quad, str);
		}

		if (strcmp(ptr->op, ">") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jg L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "<") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jl L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, ">=") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jge L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "<=") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jle L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "==") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n je L%d", ptr->label);
			x86_append(ptr->quad, str);
		}
		else 											//op:!=
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jne L%d", ptr->label);
			x86_append(ptr->quad, str);
		}

		if (ptr->quad > ptr->label)
		{
			temp1 = (instr*) malloc(sizeof(instr));
			temp1 = x86_search(ptr->label);
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n\nL%d:\n", ptr->label);
			x86_prepend(temp1->code, str);
		}
		else
		{
			assign_label(ptr->label, head1);
		}
		labels_array[labarrcnt] = ptr->label;
		labarrcnt++;
		
	}

	else if (ptr->type == IF_GOTO)
	{
		int q = lookup(t, ptr->opnd1);
		int r = lookup(t, ptr->opnd2);

		int label = extract_label(ptr->code);

		if (q == -1 && r == -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl $%s, $%s", ptr->opnd2, ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else if (q != -1 && r == -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl $%s, %d(%%ebp)", ptr->opnd2, param_search(t,ptr->opnd1));
			x86_append(ptr->quad, str);
		}
		else if (q == -1 && r != -1)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl %d(%%ebp), $%s", param_search(t,ptr->opnd2), ptr->opnd1);
			x86_append(ptr->quad, str);
		}
		else 
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n cmpl %d(%%ebp), %d(%%ebp)", param_search(t,ptr->opnd2), param_search(t,ptr->opnd1));
			x86_append(ptr->quad, str);
		}

		if (strcmp(ptr->op, ">") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jg L%d", label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "<") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jl L%d", label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, ">=") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jge L%d", label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "<=") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jle L%d", label);
			x86_append(ptr->quad, str);
		}
		else if (strcmp(ptr->op, "==") == 0)
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n je L%d", label);
			x86_append(ptr->quad, str);
		}
		else 											//op:!=
		{
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n jne L%d", label);
			x86_append(ptr->quad, str);
		}

		if (ptr->quad > label)
		{
			// printf("\nAM I HERE\n");
			temp1 = (instr*) malloc(sizeof(instr));
			temp1 = x86_search(label);
			str = (char*) malloc (sizeof(char)*10);
			sprintf(str, "\n\nL%d:\n", label);
			x86_prepend(temp1->code, str);
		}
		else
		{
			// printf("\nAssign Label\n");
			assign_label(label, head1);
		}
		labels_array[labarrcnt] = ptr->label;
		labarrcnt++;
	}

	else if (ptr->type == PARAM)
	{
		int q = lookup(t, ptr->opnd1);
		str = (char*) malloc (sizeof(char)*20);
		if (q == -1)
			sprintf(str,"\n pushl $%s", ptr->opnd1);
		else
			sprintf(str,"\n pushl %d(%%ebp)", param_search(t,ptr->opnd1));
		x86_append(ptr->quad, str);
		// fprintf(wfile,"\n pushl $%s", ptr->opnd1);
	}
	else if (ptr->type == FCALL)
	{
		str = (char*) malloc (sizeof(char)*200);
		sprintf(str,"\n call %s", ptr->opnd1);
		x86_append(ptr->quad, str);

		// if (!t->value[p].isDone)
		// {
		// 	fprintf(wfile1, "\n%s:\n.long -1", ptr->dest);
		// 	t->value[p].isDone = 1;
		// }

		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n movl %%eax, %%ecx");
		x86_append(ptr->quad, str);
		// fprintf(wfile,"\n call %s",ptr->opnd1);
	}
}

void code_gen(sym_tab* t, struct tac* head)						//takes in tac list and generates x86 code
{
	if (strcmp(t->name, "_start") == 0)
	{
		str = (char*) malloc (sizeof(char)*10);
		sprintf(str,"_start:\n");
		x86_append(label_ctr, str);

		if (head == NULL)
		{
			fprintf(wfile,"\nNo Assembly Code");
		}

		else
		{
			tac* ptr = head->next;
	
			while(ptr != NULL)
			{	
				// printf("\nLabel status: %d for %d\n", ptr->assignLabel, ptr->quad);
				if (ptr->assignLabel)
				{
					// printf("\n%d has label\n", ptr->quad);
					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\n\nL%d:\n", ptr->quad);
					x86_append(label_ctr, str);
					label_ctr++;
				}
				tac_to_x86(t, ptr, head);

				ptr = ptr -> next;
			}
			
		}
		str = (char*) malloc (sizeof(char)*20);
		sprintf(str,"\n jmp exit");
		x86_append(label_ctr, str);

		tac* ptr = head->next;
		while(ptr->next != NULL)
			ptr = ptr->next;
		if (lab_search(ptr->quad+1))
		{
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n\nL%d:\n\n jmp exit", ptr->quad+1);
			x86_append(label_ctr, str);
		}
		fprintf(wfile,"\n");

	}
	else
	{
		str = (char*) malloc (sizeof(char)*10);
		sprintf(str,"\n\n%s:\n", t->name);
		x86_append(label_ctr, str);

		if (head == NULL)
		{
			fprintf(wfile,"\nNo Assembly Code");
		}

		else
		{	//printf("\nHERE\n");
			initialize(t);
			int p;
			// printf("\nHERE\n");
			tac* ptr = head->next;
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n pushl %%ebp");
			x86_append(ptr->quad, str);
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n movl %%esp, %%ebp");
			x86_append(ptr->quad, str);
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n pushl %%esi");
			x86_append(ptr->quad, str);
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n pushl %%edi");
			x86_append(ptr->quad, str);
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n pushl %%ebx");
			x86_append(ptr->quad, str);

			while(ptr != NULL)
			{	
				// printf("\nLabel status: %d for %d\n", ptr->assignLabel, ptr->quad);
				if (ptr->assignLabel)
				{
					// printf("\n%d has label\n", ptr->quad);

					str = (char*) malloc (sizeof(char)*200);
					sprintf(str,"\nL%d:\n", label_ctr);
					x86_append(ptr->quad, str);
					label_ctr++;
				}
				// printf("\nHERE\n");
				tac_to_x86f(t, ptr,head);
				ptr = ptr -> next;
			}

			for (p=0; p<locals; p++)
			{
				str = (char*) malloc (sizeof(char)*20);
				sprintf(str,"\n addl $4, %%esp");
				x86_append(label_ctr, str);
			}
			
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n popl %%esi");
			x86_append(label_ctr, str);
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n popl %%edi");
			x86_append(label_ctr, str);
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n popl %%ebx");
			x86_append(label_ctr, str);

			str = (char*) malloc (sizeof(char)*200);
			sprintf(str,"\n movl %%ebp, %%esp");
			x86_append(label_ctr, str);
			str = (char*) malloc (sizeof(char)*200);
			sprintf(str,"\n popl %%ebp");
			x86_append(label_ctr, str);
			str = (char*) malloc (sizeof(char)*200);
			sprintf(str,"\n ret\n");
			x86_append(label_ctr, str);
			label_ctr++;

		}
		tac* ptr = head->next;
		while(ptr->next != NULL)
			ptr = ptr->next;
		if (lab_search(ptr->quad+1))
		{
			str = (char*) malloc (sizeof(char)*20);
			sprintf(str,"\n\nL%d:\n\n jmp exit", ptr->quad+1);
			x86_append(label_ctr, str);
		}
		fprintf(wfile,"\n");
		// x86_append(ptr->quad, str);
	}

	if (dpc == 0 && printDone)
	{
		do_print();
		dpc ++;
	}

	if (dsc == 0 && scanDone)
	{
		do_scan();
		dsc++;
	}

}

void print_x86()												//print x86 instr. list
{
	if (head == NULL)
	{
		fprintf(wfile, "\nNo Assembly Code");
	}

	else
	{
		instr* ptr = head;
		while(ptr != NULL)
		{	
			fprintf(wfile, "%s", ptr->code);
			ptr = ptr -> next;
		}
	}
	fprintf(wfile, "\n\nexit: \n");
	fprintf(wfile, "\n movl $1, %%eax\n movl $0, %%ebx");
	fprintf(wfile, "\n int $0x80");
	fprintf(wfile, "\n");
}