#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    // Create a dummy head node to simplify the list construction
    struct ListNode dummy;
    dummy.val = 0;
    dummy.next = NULL;
    struct ListNode* current = &dummy;
    
    int carry = 0;
    
    // Loop through both lists as long as there are nodes left or a carry exists
    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        // Calculate the new carry and the digit value for the new node
        carry = sum / 10;
        
        // Allocate memory for the new node
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newNode->val = sum % 10;
        newNode->next = NULL;
        
        // Connect the new node to the list
        current->next = newNode;
        current = newNode;
    }
    
    return dummy.next;
}
