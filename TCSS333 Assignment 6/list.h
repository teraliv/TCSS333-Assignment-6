/*
 *  list.h
 *  TCSS 333 - Autumn 2015
 *
 *  Assignment 6 - Using Linked List
 *  Alex Terikov (teraliv@uw.edu)
 *  11/18/15.
 */

// Linked List Header file
#ifndef STDIO
#define STDIO 1
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>

// Data type definitions
typedef struct node {
    char name[30];
    int f1Counter;
    int f2Counter;
    struct node *next;
} Node, List;

// LinkedList prototypes
Node *createList(void);
void insert(List **, char *, int);
void insertAtBeginning(List **, Node *);
void printList(List *);
void freeList(List *);

