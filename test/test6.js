function abc(var a @ int)
{
	var b @ int = 2;
	print(b);
	a++;
	return a;
}

var a @ int = 5;
var b @ int = 7;
var c @ int;

c = abc(b);
print(b);
print(c);
