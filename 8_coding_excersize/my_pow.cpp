/**
 * Implement pow() function in a novle way, in which we think this problem in the 
 * aspect of binary bits. Firstly, we calculated how much value is contributed for 
 * every binary bit; and then, parsing which bit for 'n' is 1 and 'add'(in fact, it
 * is multiply) corresponding contribute into the finnaly result.
 */

double my_pow(double x, int n) {
	if(fabs(x - 0.0) < 1e-10 && n != 0){
		return 0;
	}
	if(n == 1){
		return x;
	}
	if(fabs(x - 0.0) > 1e-10 && n == 0){
		return 1.0;
	}

	if (n < 0) {
		x = 1.0 / x;
		n = -n;
	}
	int unsigned m = n;
	double tbl[32] = { 0 };
	double result = 1;
	tbl[0] = x;
	for (int i = 1; i < 32; i++){
		tbl[i] = tbl[i - 1] * tbl[i - 1];
	}
	for (int i = 0; i < 32; i++){
		if (m & (0x1 << i))
			result *= tbl[i];
	}
	return result;
}