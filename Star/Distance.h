int ds(int a, int b, int c, int d) // calculates distance between any two positions on the board
{
	if (a < c) {
		int t;
		t = c;
		c = a;
		a = t;
		t = d;
		d = b;
		b = t;
	}
	int x, y = a - c;
	if (a % 2) {
		if (d>b) {
			x = b + y / 2;
			if (x>d) x = 0;
			else x = d - x;
		}
		else {
			x = b - (y + 1) / 2;
			if (x<d) x = 0;
			else x = x - d;
		}
	}
	else {
		if (d>b) {
			x = b + (y + 1) / 2;
			if (x>d) x = 0;
			else x = d - x;
		}
		else {
			x = b - y / 2;
			if (x<d) x = 0;
			else x = x - d;
		}
	}
	return x + y;
}

char* tostr(char s[], int n) // converts int to string
{
	int i;
	char str[100];
	if (!n) {
		s[0] = '0';
		s[1] = '\0';
		return s;
	}
	for (i = 0; n; i++, n/=10) str[i] = '0' + (n % 10);
	for (int j = 0; j < i; j++) s[i - j - 1] = str[j];
	s[i] = '\0';
	return s;
}