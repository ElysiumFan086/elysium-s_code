/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

ListNode* merge_sort_list(ListNode* l1, ListNode* l2) {
	if(l1 == NULL || l2 == NULL)    return l1 == NULL ? l2 : l1;

	ListNode* p_head = NULL;
	if(l1->val < l2->val) {
		p_head = l1;
		l1 = l1->next;
	}
	else {
		p_head = l2;
		l2 = l2->next;
	}

	ListNode* p_cur = p_head;

	while(l1 != NULL && l2 != NULL) {
		if(l1->val < l2->val) {
			p_cur->next = l1;
			l1 = l1->next;
		}
		else {
			p_cur->next = l2;
			l2 = l2->next;
		}
		p_cur = p_cur->next;
	}

	p_cur->next = (l1 == NULL ? l2 : l1);

	return p_head;
}

ListNode* merge_sort_list(std::vector<ListNode*> vec_list) {
	if(vec_list.empty())    return NULL;

	ListNode *p_head = NULL, *p_cur = NULL;
	int n_npn_empty = 0;
	while(true) {
		int n_min_idx = -1, n_min_val = INT_MAX;
		n_npn_empty = 0;
		for(int i = 0; i < vec_list.size(); ++i) {
			if(vec_list[i] != NULL) {
				n_npn_empty++;
				if(vec_list[i]->val < n_min_val){
					n_min_val = vec_list[i]->val;
					n_min_idx = i;
				}
			}
		}

		if(n_npn_empty <= 1)    break;

		if(p_head == NULL) {
			p_head = vec_list[n_min_idx];
			p_cur = p_head;
		}
		else {
			p_cur->next = vec_list[n_min_idx];
			p_cur = p_cur->next;
		}

		vec_list[n_min_idx] = vec_list[n_min_idx]->next;
	}

	if(n_npn_empty == 0)  return p_head;

	for(int i = 0; i < vec_list.size(); ++i) {
		if(vec_list[i] != NULL) {
			if(p_head == NULL)    return vec_list[i];
			p_cur->next = vec_list[i];
			break;
		}
	}

	return p_head;
}
