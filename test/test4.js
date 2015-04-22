var a @ int = 354;
var b @ int = 21;
var c @ int;
var x @ int;
scan(x);

switch(x)
{
	case 1: c = a + b;
			break;

	case 2: c = a - b;
			break;

	case 3: c = a * b;
			break;

	case 4: c = a / b;
			break;

	case 5: c = a % b;
			break;

	default:c = 0;
			break;
}

print(c);