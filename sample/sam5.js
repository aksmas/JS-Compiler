

function abc(var a @ int)
{
	a++;
	return a;
}

var a @ int_array;
var i @ int;
for (i=0; i<4; i++)
{
	scan(a[i]);
}
for (i=0; i<4; i++)
{
	print(a[i]);
}
var x @ int;
x = a[1];
var y @ int = abc(x);
print(y);