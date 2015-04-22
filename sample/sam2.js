function celtofar (var cel @ int)
{
	var far @ int;
	far = cel * 9 / 5 + 32;
	return far;
}

var cel @ int ;
scan(cel);
var ans @ int;

ans = celtofar(cel);
print (ans);