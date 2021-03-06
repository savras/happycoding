namespace mergeTwoLists{

struct ListNode { 
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
 
class SolutionMergeTwoLists {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(nullptr == l1)return l2;
        if(nullptr == l2)return l1;
        ListNode *head;
        if(l1->val <= l2->val)
        {
            head = l1;
            head->next = mergeTwoLists(l1->next, l2);
        }
        else
        {
            head = l2;
            head->next = mergeTwoLists(l1, l2->next);
        }
        return head;
    }
    ListNode* mergeTwoLists1(ListNode* l1, ListNode* l2) {
        if(nullptr == l1)return l2;
        if(nullptr == l2)return l1;
        ListNode *head = nullptr;
        if(l1->val <= l2->val)
        {
            head = l1;
            l1 = l1->next;
        }
        else
        {
            head = l2;
            l2 = l2->next;
        }
        ListNode *p = head;
        while(nullptr != l1 && nullptr != l2)
        {
            if(l1->val <= l2->val)
            {
                p->next = l1;
                l1 = l1->next;
            }
            else
            {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        if(nullptr != l1)
            p->next = l1;
        if(nullptr != l2)
            p->next = l2;
        return head;
    }
};
}
