var a1 @ int = 10;
var b1 @ int;
b1 = (a1 == 10)? a1 : 2;
print(b1); 

var i @ int;
for (i=0; i<10; i++)
{
	if (i == 7)
		continue;
	print(i);
}