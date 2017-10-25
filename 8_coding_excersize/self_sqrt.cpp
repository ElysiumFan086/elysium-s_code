#include <cmath>

static bool is_sqrt_correct = true;

/**
 * Calculating square root for a double value with Newton method.
 * Regard this problem as solving a equation:
 *      f(x) = x^2 - a = 0
 * And the itration formulor is:
 *      x[n+1] = x[n] - f(x[n])/f'(x[n]) = (x[n]^2 + a) / (2 * x[n])
 */
double sqrt(double a){ 
	if(a < 0){
		is_sqrt_correct = false;
		return a;
	}

	double eps = 1e-10; 
	if(a - 0 <= eps){
		return 0.0;
	}

	int n_itr_nb = 1;
	double x = a; 
	while (fabs(x - a / x) > eps * x) { 
		std::cout << "itration round " << n_itr_nb++ << std::endl;
		x = (x + a / x) / 2.0; 
	} 
	return x; 
}

/**
 * Calculating square root value approximatly with the thought of binary search.
 */
int my_sqrt(int a){
	if(a < 2)  return a;

	int n_low = 0;
	int n_high = a;

	int n_itr_nb = 1;

	while(n_low + 1 < n_high){
		std::cout << "itration round " << n_itr_nb++ << std::endl;
		const int n_mid = n_low + (n_high - n_low) / 2;
		if(n_mid * n_mid == a)	return n_mid;
		else if(n_mid * n_mid < a)	n_low = n_mid;
		else	n_high = n_mid;
	}

	return n_low;
}