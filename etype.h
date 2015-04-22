//For defining the attributes
struct etype
{
	char *type;
	int width;
	int* truelist;
	int* falselist;
	int* nextlist;
	int* breaklist;
	int* continuelist;
	int* switchlist;
	int quad;
	char *place; 
	char* val;
	int checkFunc;
};
