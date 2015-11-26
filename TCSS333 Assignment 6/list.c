/*
 *  list.c
 *  TCSS 333 - Autumn 2015
 *
 *  Assignment 6 - Using Linked List
 *  Alex Terikov (teraliv@uw.edu)
 *  11/18/15.
 */

// Linked List ADT

Node *createList(void) {
    return NULL;
}

// Inserts alphabetically on name
void insert(List **list, char *name, int fileNum) {
    Node *scan, *back = NULL;
    Node *newNode = malloc(sizeof(Node));
    strcpy(newNode->name, name);
    if (fileNum == 1) {
        (*newNode).f1Counter = 1;
        (*newNode).f2Counter = 0;
    }
    if (fileNum == 2) {
        (*newNode).f1Counter = 0;
        (*newNode).f2Counter = 1;
    }
    newNode->next = NULL;
    
    if (*list == NULL) // Insert the very first node to the list:
        *list = newNode;
    else {
        scan = *list;
        while (scan != NULL && (strcmp(scan->name, name) < 0 || strcmp(scan->name, name) == 0)) {
            back = scan;
            scan = scan->next;
        }
        if (scan == *list)
            insertAtBeginning(list, newNode);
        else if (strcmp(back->name, name) == 0) {
            if (fileNum == 1)
                back->f1Counter++;
            if (fileNum == 2)
                back->f2Counter++;
        } else if (scan == NULL) {       // insert at the end:
            newNode->next = back->next;  //yeah, I know, its already NULLL
            back->next = newNode;
        } else {                         // insert in the middle:
            newNode->next = scan;
            back->next = newNode;
        }
    }
}

void insertAtBeginning(List **list, Node *n) {
    n->next = *list;
    *list = n;
}


void printList(List *list) {
    if (list) {
        printf("%30s %10d %10d\n", (*list).name, (*list).f1Counter, (*list).f2Counter);
        printList((*list).next);
    }
}


void freeList(List *list) {
    if (list) {
        freeList(list->next);
        free(list);
    }
}


