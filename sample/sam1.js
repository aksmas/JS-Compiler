var a @ int_array;
var i @ int;
var max @ int = 0;
var t @ int;
var n @ int;
scan(n);

for (i=0; i<n; i++)
{
	scan(a[i]);
}

i=0;
do{
	t = a[i];
	if (max < t)
	{
		max = t;
	}
	i++;
}while (i<n);

print (max);