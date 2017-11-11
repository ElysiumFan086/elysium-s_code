/**
 * This function is used for selecting number is a an array with average O(n) time cost.
 * After invoking this function, the target element can be read from p_data[k - 1].
 *
 * Specially, it can be used for finding medium number or the k-th greatest element.
 */

typedef bool (*Comparable)(int, int);
bool less_than(int a, int b)    { return a < b; }
bool greater_than(int a, int b) { return a > b; }

void linear_select(int* p_data, int n_left, int n_right, int k, Comparable comp_func = greater_than) {
	if (p_data == NULL || n_left >= n_right)  return;
	int n_pivot = p_data[n_left];
	int i = n_left, j = n_right;
	while(i < j) {
		while (i < j && comp_func(n_pivot, p_data[j])) --j;
		p_data[i] = p_data[j];
		while (i < j && !comp_func(n_pivot, p_data[i])) ++i;
		p_data[j] = p_data[i];
	}
	p_data[i] = n_pivot;

	if (i + 1 == k)  return;
	else if (i + 1 < k) {
		linear_select(p_data, i + 1, n_right, k);
	}
	else {
		linear_select(p_data, n_left, i - 1, k);
	}
}
