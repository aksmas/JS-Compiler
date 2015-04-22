%{
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "try1.h"
#include "etype.h"
#include "y.tab.h"

FILE *wfile;
FILE *wfile1;
FILE *ftemp;
char fch;
#include "codegn.h"

int yylex(void);
void yyerror(char *);


//To store different tac lists for different scopes
struct tac* tac_list[50];
sym_tab *func_list[50];
int fnum=0;
int j;

//For handling Switch Case
char* scases[20];
int saddr[20];
int k = 0;
int it;
int temp_quad;

				//stack for pointers of symbol tables 
sym_tab *t;					//pointer for symbol table	
char* u;					//int_to_real 
char ch[50];					//to store a line of the three address code
int p;						//for lookups						
int i;

int counter = 0;				//to count elements of arrays
char *s;						//for arrays
int array_elem[20];


char *try;
char* cnew;
int pcounter;					//for parameters

//For the stack 'tblptr', needed for symbol table
int stack_ctr = 0;
sym_tab *tblptr[50];

int search(sym_tab* t)					//to find the list in which the tac code should be appended
{
	int l;
	for (l = 0; l<50; l++)
	{
		if (func_list[l] == t)
		return l;
	} 
}
int check = 0;
void fadd(sym_tab *t)
{
	func_list[fnum]=t;
	fnum++;
}					
void push(sym_tab *t)					
{
	tblptr[stack_ctr] = t;
	stack_ctr++;
}
void pop()
{
	stack_ctr--;
}
sym_tab *stack_top()
{
	return tblptr[stack_ctr-1];
	
}

char* removeSubstring(char *s)
{
  char *new = (char*) malloc(sizeof(char)*8);
  int i = strlen(s) - 6;
  int j;
  for (j = 0; j<i; j++)
  {
  	new[j] = s[j];
  	
  }
  new[j] = '\0';
  return new;
}

char* extract_id(char* s)
{
	char *new = (char*) malloc(sizeof(char)*8);
	int i;
	for (i=0; s[i]!= '['; i++)
	{
		new[i] = s[i];
	}
	new[i] = '\0';
	return new;
}

int extract_loc(char* s)
{
	char *new = (char*) malloc(sizeof(char)*8);
	int i;
	int j=0;
	for (i=0; s[i]!= '['; i++)
	{
		
	}
	i++;
	while (s[i] != ']')
	{
		new[j] = s[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return atoi(new);
}

%}
%union 
{
        int num;
        char *str;
        double val;
        struct etype eval;
}
%token <str> IDENTIFIER STRING INT_CONST FLOAT
/*%token <str> STRING
%token <num> INT_CONST
%token <val> FLOAT*/
%token KEYWORD_BREAK KEYWORD_CONTINUE KEYWORD_RETURN
%token KEYWORD_VAR KEYWORD_FUNCTION KEYWORD_FLOAT KEYWORD_INT KEYWORD_CHAR KEYWORD_STRING KEYWORD_BOOL INT_ARRAY FLOAT_ARRAY CHAR_ARRAY STRING_ARRAY BOOL_ARRAY
%token KEYWORD_IF KEYWORD_ELSE KEYWORD_SWITCH KEYWORD_CASE KEYWORD_DEFAULT
%token KEYWORD_DO KEYWORD_WHILE KEYWORD_FOR KEYWORD_IN
%token BLOCK_BEGIN BLOCK_END REAL
%token OR_OPERATOR AND_OPERATOR NOT_OPERATOR BITWISE_OR BITWISE_AND BITWISE_XOR BITWISE_LSHIFT BITWISE_RSHIFT BITWISE_NOT
%token INCREMENT_BY DECREMENT_BY MULTIPLY_BY DIVIDE_BY MODULO_BY AND_ASSIGN OR_ASSIGN XOR_ASSIGN LSHIFT_ASSIGN RSHIFT_ASSIGN
%token EQUALS NOT_EQUALS LE GE INCREMENT DECREMENT
%token KEYWORD_THIS KEYWORD_NEW KEYWORD_DELETE KEYWORD_PRINT KEYWORD_SCAN
%token KEYWORD_TRUE KEYWORD_FALSE KEYWORD_NULL
%token error
%type <eval> Type Expression Assign ArrayList FunctionCall
%type <eval> M 
%type <eval> Statement Statements LoopStatement ConditionStatement CompoundStatement DeclarationStatement AssignmentStatement
%type <eval> JumpStatement Cases PrintStatement ScanStatement
%nonassoc NO_ELSE
//%nonassoc KEYWORD_ELSE

%left ':' '?'
%left OR_OPERATOR
%left AND_OPERATOR
%left EQUALS NOT_EQUALS
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right UMINUS NOT_OPERATOR

%start Start
%%

Start
	:{
	t = mktable(NULL,"_start");
	push(t);
	fadd(t);
	}
	Program
	{t = stack_top(); 
	pop();
	}
	;
	
Program
	:
	
	|Element Program
	;
	
Element
	:KEYWORD_FUNCTION IDENTIFIER
	{t = mktable(stack_top(),$2); push(t);fadd(t);
	enterproc(t, $2, t);
	pcounter = 0;
	}
	'(' ParametersOption ')' CompoundStatement
	{t = stack_top(); //printf("\nHERE\n");
	
	t->paramCount = pcounter;
	//printf("\nPrameters-%d\n", t->paramCount);
	pop(); 
	enterproc(stack_top(), $2, t);
	}
	
	|Statement
	;

ParametersOption
	:
	|Parameters
	;
	
Parameters
	:KEYWORD_VAR IDENTIFIER '@' Type
	{enter(stack_top(),$2,$4.type,$4.width,0);
	pcounter++;}
	
	|Parameters ',' KEYWORD_VAR IDENTIFIER '@' Type
	{enter(stack_top(),$4,$6.type,$6.width,0);
	pcounter++;}
	;
	
Type
	:KEYWORD_INT	
	{$$.type = "int"; $$.width = 4;}
	
	|KEYWORD_CHAR
	{$$.type = "char"; $$.width = 1;}
	 
	|KEYWORD_FLOAT
	{$$.type = "float"; $$.width = 8;}
	
	|KEYWORD_STRING
	{$$.type = "string"; $$.width = 100;}
	
	|KEYWORD_BOOL
	{$$.type = "bool"; $$.width = 4;}
	
	|INT_ARRAY
	{$$.type = "int_array"; $$.width = 4;}
	
	|CHAR_ARRAY
	{$$.type = "char_array"; $$.width = 1;}
	
	|FLOAT_ARRAY
	{$$.type = "float_array"; $$.width = 8;}
	
	|STRING_ARRAY
	{$$.type = "string_array"; $$.width = 100;}
	;
	
Statements
	:Statement M Statements
	{backpatch($1.nextlist, $2.quad, tac_list[check]);
	$$.nextlist = $3.nextlist;
	$$.breaklist = merge($1.breaklist, $3.breaklist);
	$$.continuelist = merge($1.continuelist,$3.continuelist);
	}
	
	|Statement
	{$$.nextlist = $1.nextlist;
	$$.breaklist = $1.breaklist;
	$$.continuelist = $1.continuelist;
	}
	;
	
Statement
	:CompoundStatement
	{$$.nextlist = $1.nextlist;
	$$.breaklist = $1.breaklist;
	$$.continuelist = $1.continuelist;
	}
	
	|DeclarationStatement
	{$$.nextlist = $1.nextlist;
	$$.breaklist = $1.breaklist;
	$$.continuelist = $1.continuelist;
	}
	
	|AssignmentStatement ';'
	{$$.nextlist = $1.nextlist;
	$$.breaklist = $1.breaklist;
	$$.continuelist = $1.continuelist;
	}
	
	|JumpStatement
	{$$.nextlist = $1.nextlist;
	$$.breaklist = $1.breaklist;
	$$.continuelist = $1.continuelist;
	}
	
	|ConditionStatement
	{backpatch($1.nextlist,nextquad, tac_list[check]);
	$$.breaklist = $1.breaklist;
	}
	
	|LoopStatement
	{backpatch($1.nextlist,nextquad, tac_list[check]);
	$$.breaklist = $1.breaklist;
	$$.continuelist = $1.continuelist;
	}
	
	|PrintStatement
	{$$.nextlist = $1.nextlist;
	$$.breaklist = $1.breaklist;
	$$.continuelist = $1.continuelist;
	}
	
	|ScanStatement
	{$$.nextlist = $1.nextlist;
	$$.breaklist = $1.breaklist;
	$$.continuelist = $1.continuelist;
	}
	;
	
	
CompoundStatement
	:BLOCK_BEGIN Statements M BLOCK_END
	{$$.nextlist = $2.nextlist;
	$$.breaklist = $2.breaklist;
	$$.continuelist = $2.continuelist;
	}
	;

DeclarationStatement
	:KEYWORD_VAR DecList IDENTIFIER '@' Type Assign';'
	{t = stack_top();
	p = lookup(stack_top(),$3);
	if (p!=-1) 
	{
		printf("\nVariable already exists.\n");
		return;	
	}
	else
	{
		if ($6.checkFunc != 1)
		{
			if ((strcmp($5.type,$6.type) != 0) && (strcmp($6.type,"NULL") != 0)) 
			{
				printf("\nType Error\n");
				return;
			}
		}
		enter(t,$3,$5.type,$5.width,0); 
		setValue(t,$6.place,$3);
		
		if(strstr($5.type, "_array") != NULL)
		{
			setElements(t, counter, $3);
			check = search(stack_top());
			for (i=0; i<counter; i++)
			{
				char* s = (char*) malloc(sizeof(char)*3);
				sprintf(s, "%d", array_elem[i]);
				append(ARRAY,$3,s,"","",i,nextquad,tac_list[check]);
				gen();
			}
			counter = 0;
		}
		
		if (strcmp($6.place,"NULL") != 0)
		{	
			check = search(stack_top());
			append(ASSIGN,$3,$6.place,"","",0,nextquad,tac_list[check]);
			gen();
		}
	}
	$$.nextlist = makelist(0);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(0);
	}
	;
	
DecList
	:
	
	|DecList IDENTIFIER '@' Type Assign ','
	{t = stack_top();
	p = lookup(stack_top(),$2);
	if (p!=-1) 
	{
		printf("\nVariable already exists.\n");
		return;	
	}
	else
	{
		if ($5.checkFunc != 1)
		{
			if ((strcmp($4.type,$5.type) != 0) && (strcmp($5.type,"NULL") != 0)) 
			{
				printf("\nType Error\n");
				return;
			}
		}

		enter(t,$2,$4.type,$4.width,0);
		setValue(t,$5.place,$2);
		if(strstr($4.type, "_array") != NULL)
		{
			
			setElements(t, counter, $2);
			check = search(stack_top());
			for (i=0; i<counter; i++)
			{
				char* s = (char*) malloc(sizeof(char)*3);
				sprintf(s, "%d", array_elem[i]);
				append(ARRAY,$2,s,"","",i,nextquad,tac_list[check]);
				gen();
			}
			counter = 0;
		}
		//print_st(t);
		if (strcmp($5.place,"NULL") != 0)
		{	
			check = search(stack_top());
			append(ASSIGN, $2, $5.place, "", "",0,nextquad,tac_list[check]);
			gen();
		}
	}
	}
	;

Assign
	:
	{$$.place = (char*)malloc(sizeof(char)*5);
	strcpy($$.place, "NULL");
	$$.type = "NULL";
	$$.width = 0;
	$$.checkFunc = 0;
	}
	
	|'=' Expression
	{$$.place = $2.place;
	$$.type = $2.type;
	$$.width = $2.width;
	$$.checkFunc = $2.checkFunc;
	}
	;
		
AssignmentStatement
	:IDENTIFIER '=' Expression 
	{p = lookup(stack_top(),$1);
	if (p!=-1) 
	{	
		if ((strcmp(stack_top()->value[p].type, $3.type) != 0) && ($3.checkFunc != 1))
		{
			printf("\nType Error\n");
			return;
		}
		setValue(t,$3.place, $1);//printf("\nHERE\n");
		check = search(stack_top());
		//int length = strlen($3.type);
		//if ($3.type[length-1] == ']')
		//	append(ARRAY1, $1, extract_id($3.place), "", "",extract_loc($3.place),nextquad,tac_list[check]);
		//else
			append(ASSIGN, $1, $3.place, "", "",0,nextquad,tac_list[check]);
		gen();
		$$.nextlist = makelist(0);
		$$.breaklist = makelist(0);
		$$.continuelist = makelist(0);
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", $1);
		return;
	}
	}
	
	|IDENTIFIER '=' IDENTIFIER '[' Expression ']'
	{p = lookup(stack_top(),$1);
	if (p!=-1) 
	{
		int q = lookup(stack_top(),$3);
		int r = lookup(stack_top(),$5.place);
		if (q != -1)
		{
			if(strstr(t->value[q].type, "_array") == NULL)
			{
				printf("\n%s is not an array.\n", $3);
				return;	
			}
			if (strcmp($5.type,"int") != 0)
			{
				printf("\nCan't access %s[%s]\n", $3, $5.place);
				return;	
			}
			check = search(stack_top());
			if (r == -1)
				append(ARRAY1, $1, $3, "", "",atoi($5.place),nextquad,tac_list[check]);
			else
				append(ARRAY2, $1, $3, "", $5.place,0,nextquad,tac_list[check]);
			gen();
		}
		else
		{
			printf("\nArray %s should be declared first.\n", $3);
			return;
		}
		$$.nextlist = makelist(0);
		$$.breaklist = makelist(0);
		$$.continuelist = makelist(0);
			
		
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", $1);
		return;
	}
		
	}
	
	| IDENTIFIER '[' Expression ']' '=' Expression
	{t = stack_top();
	p = lookup(t,$1);
	if (p!=-1) 
	{
		if(strstr(t->value[p].type, "_array") == NULL)
		{
			printf("\n%s is not an array.\n", $1);
			return;	
		}
		if (strcmp($3.type,"int") != 0)
		{
			printf("\nCan't access %s[%s]\n", $1, $3.place);
			return;	
		}
		if((strstr(t->value[p].type, "_array") != NULL) && (strcmp($3.type,"int") == 0))
		{
			if (atoi($3.place) > ((t->value[p].no_elements)-1))
			{
				printf("\nArray bound exceeded.\n");
				return;
			}
			
			s = removeSubstring(t->value[p].type);
			if ((strcmp(s, $6.type) != 0) && ($6.checkFunc != 1))
			{
				printf("\nType Error\n");
				return;
			}
			
			check = search(stack_top());
			append(ARRAY, $1, $6.place, "", "",atoi($3.place),nextquad,tac_list[check]);
			gen();
			
			/*char* u1;
			char* u2;
			char* u3;
			char* u4;
			int base = t->value[p].offset;
			int i = atoi($3.place);	
			int constant = base * $6.width;
			cnew = (char*) malloc(sizeof(char)*10);
			sprintf(cnew, "%d", $6.width);
			u1 = newtmp();

			check = search(stack_top());
			append(ARRAY, u1, $3.place, "*", cnew,0, nextquad,tac_list[check]);
			gen();
			u2 = newtmp();
			sprintf(cnew, "%d", constant);
			
			check = search(stack_top());
			append(ARRAY, u2, $1, "-", cnew,0,nextquad,tac_list[check]);
			gen();
			u3 = newtmp();
			
			check = search(stack_top());
			append(ARRAY, u3, u1, "+", u2,0,nextquad,tac_list[check]);
			gen();
			u4 = newtmp();
			
			check = search(stack_top());
			append(ARRAY, u4, u3, "", "",0,nextquad,tac_list[check]);
			gen();
			
			check = search(stack_top());
			append(ARRAY, u4, $6.place, "", "",0,nextquad,tac_list[check]);
			gen();
			return;	*/
		}
		
		$$.nextlist = makelist(0);
		$$.breaklist = makelist(0);
		$$.continuelist = makelist(0);
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", $1);
		return;
	}
	
	}
	
	|IDENTIFIER '=' Expression '?' Expression ':' Expression
	{t = stack_top();
	p = lookup(t,$1);
	if (p!= -1)
	{
		backpatch($3.truelist,nextquad, tac_list[check]);
		backpatch($3.falselist,nextquad+1, tac_list[check]);
		$$.place = newtmp();
		
		check = search(stack_top());
		append(ASSIGN, $1, $5.place, "", "",0,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(GOTO_L,"","","","",nextquad+3,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(GOTO_L,"","","","",nextquad+1,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(ASSIGN, $1, $7.place, "", "",0,nextquad,tac_list[check]);
		gen();
		$$.nextlist = makelist(0);
		$$.breaklist = makelist(0);
		$$.continuelist = makelist(0);
	
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", $1);
		return;
	}
	}
	
	|IDENTIFIER INCREMENT 
	{t = stack_top();
	p = lookup(t,$1);
	if (p!= -1)
	{
		/*$$.place = newtmp();
		check = search(stack_top());
		append(ASSIGN, $$.place, $1, "+", "1",0,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(ASSIGN, $1, $$.place, "", "",0,nextquad,tac_list[check]);
		gen();
		enter(t,$$.place,"int",4,1);*/
		check = search(stack_top());
		append(INC, "", $1, "", "",0,nextquad,tac_list[check]);
		gen();
		
		$$.nextlist = makelist(0);
		$$.breaklist = makelist(0);
		$$.continuelist = makelist(0);
		
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", $1);
		return;
	}
	}
	
	|IDENTIFIER DECREMENT 
	{t = stack_top();
	p = lookup(t,$1);
	if (p!= -1)
	{
		/*$$.place = newtmp();
		check = search(stack_top());
		append(ASSIGN, $$.place, $1, "-", "1",0,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(ASSIGN, $1, $$.place, "", "",0,nextquad,tac_list[check]);
		gen();
		enter(t,$$.place,"int",4,1);*/
		check = search(stack_top());
		append(DEC, "", $1, "", "",0,nextquad,tac_list[check]);
		gen();
		
		$$.nextlist = makelist(0);
		$$.breaklist = makelist(0);
		$$.continuelist = makelist(0);
		
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", $1);
		return;
	}
	}
	;
	
JumpStatement
	:KEYWORD_CONTINUE ';'
	{$$.nextlist = makelist(0);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(nextquad);
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
	
	|KEYWORD_BREAK ';'
	{$$.nextlist = makelist(0);
	$$.continuelist = makelist(0);
	$$.breaklist = makelist(nextquad);
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
	
	|KEYWORD_RETURN ';'
	{check = search(stack_top());
	append(RETURN,"", "", "", "",0,nextquad,tac_list[check]);
	gen();
	$$.nextlist = makelist(0);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(0);
	}
	
	|KEYWORD_RETURN Expression ';'
	{check = search(stack_top());
	append(RETURN,"", $2.place, "", "",0,nextquad,tac_list[check]);
	gen();
	$$.nextlist = makelist(0);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(0);
	}
	;
	
ConditionStatement
	:KEYWORD_IF Expression M Statement
	{
	if (strcmp($2.type,"bool")!= 0)
	{
		printf("\nIf condition must be a boolean\n");
		return;
	}
	backpatch($2.truelist, $3.quad, tac_list[check]);
	$$.nextlist = merge($2.falselist, $4.nextlist);
	$$.breaklist = $4.breaklist;
	$$.continuelist = $4.continuelist;
	}
	
	|KEYWORD_IF Expression M Statement KEYWORD_ELSE 
	{temp_quad = nextquad;
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	
	}
	M Statement
	{if (strcmp($2.type,"bool")!= 0)
	{
		printf("\nIf condition must be a boolean\n");
		return;
	}
	backpatch($2.truelist,$3.quad, tac_list[check]);
	backpatch($2.falselist,$7.quad, tac_list[check]);
	$$.switchlist = makelist(temp_quad);
	$$.nextlist = merge($4.nextlist,$8.nextlist);
	$$.nextlist = merge($$.nextlist, $$.switchlist);
	$$.breaklist = merge($4.breaklist, $8.breaklist);
	$$.continuelist = merge($4.continuelist, $8.continuelist);
	}
	
	|KEYWORD_SWITCH Expression BLOCK_BEGIN
	{temp_quad = nextquad;
	check = search(stack_top());
	append(GOTO,"", "", "", "",0,nextquad,tac_list[check]);
	gen();
	}
	Cases BLOCK_END
	{$$.switchlist = makelist(temp_quad);
	backpatch($$.switchlist,nextquad, tac_list[check]);
	for (it = 0; it<k-1; it++)
	{
		check = search(stack_top());
		append(IF_GOTOL,"", $2.place, "==", scases[it],saddr[it],nextquad,tac_list[check]);
		gen();
	}
	check = search(stack_top());
	append(GOTO_L,"","", "", "",saddr[it],nextquad,tac_list[check]);
	gen();
	$$.nextlist = makelist(0);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(0);
	backpatch($5.breaklist,nextquad, tac_list[check]);
	}
	;
	
Cases
	:Cases KEYWORD_CASE Expression ':'
	{strcpy(scases[k], $3.place);
	saddr[k] = nextquad;
	k++; 
	}
	Statements 
	{$$.breaklist = merge($1.breaklist, $6.breaklist);}
	
	|KEYWORD_CASE Expression ':' 
	{strcpy(scases[k], $2.place);
	saddr[k] = nextquad;
	k++; 
	}
	Statements
	{$$.breaklist = $5.breaklist;}
	
	|Cases KEYWORD_DEFAULT ':'
	{strcpy(scases[k], "");
	saddr[k] = nextquad;
	k++;
	}
	Statements
	{$$.breaklist = merge($1.breaklist, $5.breaklist);}
	;
	
LoopStatement
	:KEYWORD_WHILE M Expression M Statement
	{if (strcmp($3.type,"bool")!= 0)
	{
		printf("\nWhile condition must be a boolean\n");
		return;
	}
	backpatch($5.nextlist, $2.quad, tac_list[check]);
	backpatch($3.truelist, $4.quad, tac_list[check]);
	
	backpatch($5.continuelist, $4.quad, tac_list[check]);
	$$.nextlist = $3.falselist;
	check = search(stack_top());
	append(GOTO_L,"", "", "", "",$2.quad,nextquad,tac_list[check]);
	gen();
	backpatch($5.breaklist,nextquad, tac_list[check]);
	}
	
	|KEYWORD_DO M Statement KEYWORD_WHILE M Expression ';'
	{backpatch($6.truelist, $2.quad, tac_list[check]);
	backpatch($3.nextlist, $5.quad, tac_list[check]);
	backpatch($3.continuelist, $2.quad, tac_list[check]);
	backpatch($3.breaklist,nextquad, tac_list[check]);
	$$.nextlist = $6.falselist;
	}
	
	/*|KEYWORD_FOR '(' AssignmentStatement ';' M Expression ';' M AssignmentStatement ')'  Statement
	{backpatch($6.truelist, $8.quad, tac_list[check]);
	$$.nextlist = merge($6.falselist,$11.nextlist);
	print_list($$.nextlist);
	backpatch($11.continuelist, $8.quad, tac_list[check]);
	check = search(stack_top());
	append(GOTO_L,"", "", "", "",$5.quad,nextquad,tac_list[check]);
	gen();
	backpatch($11.breaklist,nextquad, tac_list[check]);
	}*/
	
	|KEYWORD_FOR '(' AssignmentStatement ';' M Expression ';' M IDENTIFIER INCREMENT ')'  Statement
	{backpatch($6.truelist, $8.quad, tac_list[check]);
	$$.nextlist = merge($6.falselist,$12.nextlist);
	//print_list($$.nextlist);
	backpatch($12.continuelist, nextquad, tac_list[check]);
	check = search(stack_top());
	append(INC, "", $9, "", "",0,nextquad,tac_list[check]);
	gen();
	append(GOTO_L,"", "", "", "",$5.quad,nextquad,tac_list[check]);
	gen();
	backpatch($12.breaklist,nextquad, tac_list[check]);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(0);
	}
	
	|KEYWORD_FOR '(' AssignmentStatement ';' M Expression ';' M IDENTIFIER DECREMENT ')'  Statement
	{backpatch($6.truelist, $8.quad, tac_list[check]);
	$$.nextlist = merge($6.falselist,$12.nextlist);
	//print_list($$.nextlist);
	backpatch($12.continuelist, $8.quad, tac_list[check]);
	check = search(stack_top());
	append(DEC, "", $9, "", "",0,nextquad,tac_list[check]);
	gen();
	append(GOTO_L,"", "", "", "",$5.quad,nextquad,tac_list[check]);
	gen();
	backpatch($12.breaklist,nextquad, tac_list[check]);
	}
	;
	
PrintStatement
	:KEYWORD_PRINT '(' Expression ')' ';'
	{check = search(stack_top());
	append(PRINT,"", $3.place, "", "",0,nextquad,tac_list[check]);
	gen();
	$$.nextlist = makelist(0);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(0);
	}
	
	|KEYWORD_PRINT '(' IDENTIFIER '[' Expression ']' ')' ';'
	{check = search(stack_top());
	append(PRINT1,"", $3, "", $5.place,0,nextquad,tac_list[check]);
	gen();
	$$.nextlist = makelist(0);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(0);
	}
	;
	
ScanStatement
	:KEYWORD_SCAN '(' Expression ')' ';'
	{check = search(stack_top());
	append(SCAN,"", $3.place, "", "",0,nextquad,tac_list[check]);
	gen();
	$$.nextlist = makelist(0);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(0);
	}
	
	|KEYWORD_SCAN '(' IDENTIFIER '[' Expression ']' ')' ';'
	{check = search(stack_top());
	append(SCAN1,"", $3, "", $5.place,0,nextquad,tac_list[check]);
	gen();
	$$.nextlist = makelist(0);
	$$.breaklist = makelist(0);
	$$.continuelist = makelist(0);
	}
	;
	
Expression
	:'(' Expression ')'
	{
	$$.type = $2.type;
	$$.place = $2.place;
	if (strcmp($2.type,"bool") == 0)
	{
		$$.truelist = $2.truelist;
		$$.falselist = $2.falselist;
	}
	}
	
	|Expression '+' Expression 
	{ t = stack_top();
	if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"int") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "+", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "int";
		enter(t,$$.place,$$.type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real+", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real+", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real+", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}

	|Expression '*' Expression 
	{t = stack_top();
	if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"int") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "*", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "int";
		enter(t,$$.place,$$.type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real*", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real*", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real*", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}

	|Expression  '-' Expression 
	{t = stack_top();
	if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"int") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "-", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "int";
		enter(t,$$.place,$$.type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real-", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real-", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real-", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}
	
	|Expression  '/' Expression 
	{t = stack_top();
	if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"int") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "/", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "int";
		enter(t,$$.place,$$.type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real/", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real/", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real/", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}
	
	|Expression  '%' Expression 
	{t = stack_top();
	if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"int") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "%", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "int";
		enter(t,$$.place,$$.type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real%", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real%", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real%", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}
	
	|Expression '>' Expression
	{$$.type = "bool";
	$$.truelist = makelist(nextquad);
	$$.falselist = makelist(nextquad+1);
	$$.place = (char*) malloc(sizeof(char)*5);
 	sprintf($$.place, "%s > %s", $1.place, $3.place);
	//sprintf(ch, "if %s > %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",$1.place,">",$3.place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
	
	|Expression '<' Expression
	{$$.type = "bool";
	$$.truelist = makelist(nextquad);
	$$.falselist = makelist(nextquad+1);
	$$.place = (char*) malloc(sizeof(char)*5);
 	sprintf($$.place, "%s < %s", $1.place, $3.place);
	//sprintf(ch, "if %s > %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",$1.place,"<",$3.place,0,nextquad,tac_list[check]);//printf("\nHere\n");
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
		
	|Expression LE Expression
	{$$.type = "bool";
	$$.truelist = makelist(nextquad);
	$$.falselist = makelist(nextquad+1);
	$$.place = (char*) malloc(sizeof(char)*5);
 	sprintf($$.place, "%s <= %s", $1.place, $3.place);
	//sprintf(ch, "if %s <= %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",$1.place,"<=",$3.place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
		
	|Expression GE Expression
	{$$.type = "bool";
	$$.truelist = makelist(nextquad);
	$$.falselist = makelist(nextquad+1);
	$$.place = (char*) malloc(sizeof(char)*5);
 	sprintf($$.place, "%s >= %s", $1.place, $3.place);
	//sprintf(ch, "if %s >= %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",$1.place,">=",$3.place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
		
	|Expression EQUALS Expression
	{$$.type = "bool";
	$$.truelist = makelist(nextquad);
	
	$$.falselist = makelist(nextquad+1);
	//print_list($$.falselist);
	$$.place = (char*) malloc(sizeof(char)*5);
 	sprintf($$.place, "%s == %s", $1.place, $3.place);
	//sprintf(ch, "if %s == %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",$1.place,"==",$3.place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
		
	|Expression NOT_EQUALS Expression
	{$$.type = "bool";
	$$.truelist = makelist(nextquad);
	$$.falselist = makelist(nextquad+1);
	$$.place = (char*) malloc(sizeof(char)*5);
 	sprintf($$.place, "%s != %s", $1.place, $3.place);
	//sprintf(ch, "if %s != %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",$1.place,"!=",$3.place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
		
	|Expression  AND_OPERATOR M Expression
	{$$.type = "bool";
	backpatch($1.truelist,$3.quad, tac_list[check]);
	$$.truelist = $4.truelist;
 	$$.falselist = merge($1.falselist,$4.falselist);
 	$$.place = (char*) malloc(sizeof(char)*5);
 	sprintf($$.place, "%s and %s", $1.place, $4.place);
	}
	 
	|Expression  OR_OPERATOR M Expression 
	{$$.type = "bool";//printf("\n%d\n",$3.quad);
	backpatch($1.falselist, $3.quad, tac_list[check]);
	$$.truelist = merge($1.truelist, $4.truelist);
	//print_list($$.truelist);
	$$.falselist = $4.falselist;
	$$.place = (char*) malloc(sizeof(char)*5);
	sprintf($$.place, "%s or %s", $1.place, $4.place);
	}

	|NOT_OPERATOR Expression
	{$$.type = "bool";
	$$.truelist = $2.falselist;
	$$.falselist = $2.truelist;
	$$.place = (char*) malloc(sizeof(char)*5);
	sprintf($$.place, "not %s", $2.place);
	}
	
	|'-' Expression %prec UMINUS
	{$$.type = $2.type;
	$$.place = (char*) malloc(sizeof(char)*5);
	sprintf($$.place,"-%s",$2.place);
	} 
	
	|IDENTIFIER
	{
	p = lookup(stack_top(),$1);

	if (p!=-1)
	{
		$$.place = (char*) malloc(sizeof(char)*5);
		strcpy($$.place,$1);
		strcpy($$.type,stack_top()->value[p].type);
	}
	else
	{
		printf("\nVariable not declared\n");
		return;
	}
	if (strcmp($$.type,"bool") == 0)
	{
		$$.truelist = makelist(0);
		$$.falselist = makelist(0);
	}
	}
	
	/*|IDENTIFIER '[' Expression ']'
	{
	p = lookup(stack_top(),$1);

	if (p!=-1)
	{
		$$.place = (char*) malloc(sizeof(char)*30);
		sprintf($$.place, "%s[%s]", $1, $3.place);
		//strcpy($$.place,$1);
		strcpy($$.type,$3.type);
	}
	else
	{
		printf("\nArray not declared\n");
		return;
	}
	if (strcmp($$.type,"bool") == 0)
	{
		$$.truelist = makelist(0);
		$$.falselist = makelist(0);
	}
	
	}*/
	
	|INT_CONST
	{
	$$.place = $1;$$.type = "int";
	$$.width = 4;
	}
	
	|FLOAT
	{
	$$.place = $1;$$.type = "float";
	$$.width = 8;}
	
	|STRING
	{
	$$.place = $1;
	if (strlen($1) == 3)
	{
		$$.type = "char";
		$$.width = 1;
	}
	else
	{
		$$.type = "string";
		$$.width = 100;
	}
	}
	
	|KEYWORD_TRUE
	{$$.place = "1";$$.type = "bool";
	$$.width = 4;
	$$.truelist = makelist(nextquad);
	$$.falselist = makelist(0);
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
	
	|KEYWORD_FALSE
	{$$.place = "0";$$.type = "bool";
	$$.width = 4;
	$$.truelist = makelist(0);
	$$.falselist = makelist(nextquad);
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
	
	|'[' ArrayList ']'
	{if (strcmp($2.type,"int") == 0)
	{
		$$.type = "int_array";
	}
	else if (strcmp($2.type,"char") == 0)
	{
		$$.type = "char_array";
	}
	else if (strcmp($2.type,"float") == 0)
	{
		$$.type = "float_array";
	}
	else if (strcmp($2.type,"string") == 0)
	{
		$$.type = "string_array";
	}
	$$.width = counter * $2.width;
	$$.place = "NULL";
	}
	
	|FunctionCall
	{$$.place = $1.place;
	$$.checkFunc = 1;
	}
	;
	
ArrayList
	: Expression
	{array_elem[counter] = atoi($1.place);
	counter++;
	$$.width = $1.width;
	$$.type = $1.type;
	}
	
	|ArrayList ',' Expression 
	{array_elem[counter] = atoi($3.place);
	counter++;
	if (strcmp($1.type,$3.type) != 0)
	{
		printf("\nArray elements should be of same type.\n");
		return;
	}
	}
	;

FunctionCall
	:IDENTIFIER '(' 
	{p = lookup(stack_top(), $1);
	if (p == -1)
	{
		printf("\nFunction not defined\n");
		return;
	}
	array_cnt = 0;}
	ArgList ')'
	{for (i=0; i<array_cnt; i++)
	{
		//printf("\nparam %s\n ", params[i]);
		check = search(stack_top());
		append(PARAM,"",params[i],"","",0,nextquad,tac_list[check]);
		gen();
	}
	$$.place = newtmp();
	//sprintf(ch, "%s = call %s ",$$.place, $1);
	check = search(stack_top());
	append(FCALL,$$.place,$1,"","",array_cnt,nextquad,tac_list[check]);
	gen();
	enter(stack_top(),$$.place, "int", 4,1);
	//enter(stack_top(), $$.place);
	}
	;
	
ArgList
	:
	|Arguments
	;
	
Arguments
	:Expression
	{//printf("\nInserting %s\n", $1.place);
	insert_param($1.place);
	}
	
	|Expression ',' ArgList
	{//printf("\nInserting %s\n", $1.place);
	insert_param($1.place);
	}
	;
	
M
	:
	{$$.quad = nextquad;
	}
	;
	
	
%%
extern FILE* yyin;
//int yydebug = 1;

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

void yyterminate() {
}


main(int argc, char **argv)

{           
	if (argc > 1)
	{
	    FILE *file;
	    file = fopen(argv[1], "r");
	    
	    if (!file)
	    {
	        fprintf(stderr, "Could not open %s\n", argv[1]);
	        //exit(1);
	    }
	    yyin = file;
	}
	
	wfile = fopen("code.s", "w");
	wfile1 = fopen("data.s", "w");
	for (j=0; j<20; j++)
	{
		tac_list[j] = (tac*)malloc(sizeof(tac));
		scases[j] = (char*)malloc(sizeof(char)*10);
	}
	
	
	yyparse();
	for (i =0; i<fnum; i++){
	printf("\n%s:\n",func_list[i]->name);
	print_tac(tac_list[i]);
	}
	
	fprintf(wfile, "\n.section .text\n");
	fprintf(wfile, "\n.globl _start\n");
	fprintf(wfile1, "\n.section .data\n");
	fprintf(wfile1, "\ngroup:\n.long 1\n");
	fprintf(wfile1, "\nnumb:\n.long 1\n");
	for (i =0; i<fnum; i++){
		//fprintf(wfile, "\n%s:",func_list[i]->name);
		code_gen(func_list[i], tac_list[i]);
	}
	//print_st(func_list[1]);
	print_x86();
	fclose(wfile);
	fclose(wfile1);
	
	wfile1 = fopen("data.s", "r");
	wfile = fopen("code.s", "r");
	
	ftemp = fopen("ans.s", "w");
	while ((fch = fgetc(wfile1)) != EOF)
		fputc(fch, ftemp);
	fprintf(ftemp, "\n");
	while ((fch = fgetc(wfile)) != EOF)
		fputc(fch, ftemp);
		
	fclose(wfile);
	fclose(wfile1);
	fclose(ftemp);
	
	
}
