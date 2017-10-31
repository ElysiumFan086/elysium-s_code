/**
 * Given an integer 'n', counting the BST number, whose nodes record the numbers from 1 to 'n'.
 * 
 * Calculating with dynamic origramming:
 * We defines the solution of this question is f(n), which means numbers from 1 to 'n' can
 * build f(n) unique BST.
 * It is clear that f(0) = f(1) = 1;
 * For the cases more than one node, such as 'n' nodes, we can devided the question into
 * several sub-questions:
 *     we can choose the i-th node as the root node of the BST, so numbers from 1 to 'i-1'
 *     must be placed in left sub-tree, there are totally f(i-1) cases;
 *     And numbers from 'i+1' to 'n' must be placed into right sub-tree, there is f(n-1-i)
 *     cases.
 *  So the final solution of original question can be regarded as:
 *
 *         f(n) = f(0)*f(n-1) + f(1)*f(n-2) + ... + f(i)*f(n-i-1) + ... + f(n-1)*f(0);
 *  The solutions of sub-questions is gragually calculated, and do calculated only once.
 */

int getTreeNum(int n_node_nb) {
	if(n_node_nb == 1 || n_node_nb == 0)  return 1;
	if(n_node_nb < 0)  return 0;

	int* p_res = new int[n_node_nb + 1];
	memset(p_res, 0, (n_node_nb + 1) * sizeof(int));

	p_res[0] = 1;  p_res[1] = 1;
	for(int i = 2; i <= n; ++i) {
		for(int j = 0; j < i; ++j) {
			p_res[i] += (p_res[j] * p_res[n_node_nb - 1 - j]);
		}
	}

	int n_tree_nb = p_res[n];
	delete[] p_res;
	return n_tree_nb;
}