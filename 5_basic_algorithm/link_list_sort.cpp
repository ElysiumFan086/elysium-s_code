ListNode* merge(ListNode* head1, ListNode* head2) {
        if(head1 == NULL)    return head2;
        if(head2 == NULL)    return head1;
        
        ListNode *res, *p;
        if(head1->val < head2->val) {
            res = head1;
            head1 = head1->next;
        }
        else {
            res = head2;
            head2 = head2->next;
        }
        p = res;
        
        while(head1 != NULL && head2 != NULL) {
            if(head1->val < head2->val) {
                p->next = head1;
                head1 = head1->next;
            }
            else {
                p->next = head2;
                head2 = head2->next;
            }
            
            p = p->next;
        }
        
        if(head1 != NULL)    p->next = head1;
        else if(head2 != NULL)    p->next = head2;
        
        return res;
    }
    
    ListNode* sortList(ListNode* head) {
        if(head == NULL || head->next == NULL)    return head;
        
        ListNode* fast = head, *slow = head;
        while(fast->next != NULL && fast->next->next != NULL) {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        fast = slow;    slow = slow->next;
        fast->next = NULL;
        fast = sortList(head);
        slow = sortList(slow);
        
        return merge(fast, slow);
    }
