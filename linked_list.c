#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node * next;
} node_t;


void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

node_t * push(node_t * head, int val) {
    if (head == NULL) {
        node_t * new_node = (node_t *) malloc(sizeof(node_t));
        new_node->val = val;
        new_node->next = NULL;
        
        return new_node;
    }


    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (node_t *) malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;

    return head;
}


node_t remove_last(node_t * head) {

    int retval = 0;
    
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->val;
        head = NULL;
        free(head);
        return (node_t) { .val = retval, .next = NULL };
    }

    /* get to the second to last node in the list */
    node_t * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->val;
    current->next = NULL;
    free(current->next);
    return (node_t) { .val = retval, .next = head };
}


// void push(node_t ** head, int val) { //Adding an item to the end of the list
//     node_t * new_node;
//     new_node = (node_t *) malloc(sizeof(node_t));

//     new_node->val = val;
//     new_node->next = *head;
//     *head = new_node;
// }

// void push(node_t ** head, int val) { // Adding an item to the beginning of the list (pushing to the list)
//     node_t * new_node;
//     new_node = (node_t *) malloc(sizeof(node_t));

//     new_node->val = val;
//     new_node->next = *head;
//     *head = new_node;
// }

// int pop(node_t ** head) {
//     int retval = -1;
//     node_t * next_node = NULL;

//     if (*head == NULL) {
//         return -1;
//     }

//     next_node = (*head)->next;
//     retval = (*head)->val;
//     free(*head);
//     *head = next_node;

//     return retval;
// }


// int remove_by_index(node_t ** head, int n) {
//     int i = 0;
//     int retval = -1;
//     node_t * current = *head;
//     node_t * temp_node = NULL;

//     if (n == 0) {
//         return pop(head);
//     }

//     for (i = 0; i < n-1; i++) {
//         if (current->next == NULL) {
//             return -1;
//         }
//         current = current->next;
//     }

//     temp_node = current->next;
//     retval = temp_node->val;
//     current->next = temp_node->next;
//     free(temp_node);

//     return retval;

// }