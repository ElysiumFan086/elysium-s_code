/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

ListNode* reverseList(ListNode* head) {
    if(head == NULL || head->next == NULL)    return head;
    
    ListNode *p, *q, *r;
    p = head;
    q = head->next;
    head->next = NULL;
    
    while(q != NULL) {
        r = q->next;
        q->next = p;
        p = q;
        q = r;
    }
    
    head = p;      // Finally q is NULL, so head is p
    return head;
}

/**
   q = p->next:
   +---+    +---+    +---+    +---+    +---+    +---+
   | 1 |    | 2 |    | 3 |    | 4 |    | 5 |    | 6 |
   +---+    +---+    +---+    +---+    +---+    +---+
   | n |--->| n |--->| n |--->| n |--->| n |--->| X |
   +---+    +---+    +---+    +---+    +---+    +---+
     ^        ^        ^
     h        p        q

   p->next = q->next:
              +------------+
   +---+    +-|-+    +---+ |  +---+    +---+    +---+
   | 1 |    | 2 |    | 3 | +->| 4 |    | 5 |    | 6 |
   +---+    +---+    +---+    +---+    +---+    +---+
   | n |--->| n |    | n |--->| n |--->| n |--->| X |
   +---+    +---+    +---+    +---+    +---+    +---+
     ^        ^        ^
     h        p        q

   q->next = head->next:
              +------------+
   +---+    +-|-+    +---+ |  +---+    +---+    +---+
   | 1 |    | 2 |    | 3 | +->| 4 |    | 5 |    | 6 |
   +---+    +---+    +---+    +---+    +---+    +---+
   | n |--->| n |<---| n |    | n |--->| n |--->| X |
   +---+    +---+    +-+-+    +---+    +---+    +---+
     ^        ^        ^
     h        p        q

   head->next = q:
              +------------+
     h        |        q   |
   +---+    +-|-+    +---+ |  +---+    +---+    +---+
   | 1 |    | 2 |    | 3 | +->| 4 |    | 5 |    | 6 |
   +---+    +---+    +---+    +---+    +---+    +---+
   | n |    | n |<---| n |    | n |--->| n |--->| X |
   +-+-+    +---+    +-+-+    +---+    +---+    +---+
     |        ^        ^
     |        p        |
     +-----------------+
  
  What is done in the while loop is insert very node after the second node
  behind the original head node one by one. After the processing of while,
  the nodes become "1, 6, 5, 4, 3, 2".

 */
ListNode* reverseList_v2(ListNode* head) {
    if(head == NULL || head->next == NULL)    return head;
    
    ListNode *p, *q;
    p = head->next;

    while(p->next != NULL) {
    	q = p->next;
    	p->next = q->next;
    	q->next = head->next;
    	head->next = q;
    }

    p->next = head;   // Form a circle
    head = p->next->next;
    p->next->next = NULL;

    return head;
}