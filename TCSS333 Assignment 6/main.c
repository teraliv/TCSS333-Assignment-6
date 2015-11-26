/*
 *  main.c
 *  TCSS 333 - Autumn 2015
 *
 *  Assignment 6 - Using Linked List
 *  Alex Terikov (teraliv@uw.edu)
 *  11/18/15.
 */

#ifndef STDIO
#define STDIO 1
#include <stdio.h>
#endif

//#include "list.h"
//#include "list.c"

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int removeGarbage(char *clean, char *orig);
void clearStringData(char *str);
List *addWordsToList(FILE *in1, FILE *in2, List *list, int *p);
void printFirsTwentyFive(List *list, char fName1[], char fName2[]);
List *sortList(List *list, int length);
int calculateWordCounts(int counter1, int counter2);
void printLastFive(List *list, char fName1[], char fName2[], int length);


int main(int argc, const char * argv[]) {
    
    int length = 0;
    
    char fName1[] = "ShortBadge.txt";
    char fName2[] = "ShortReg.txt";

//    char fName1[] = "RedBadge.txt";
//    char fName2[] = "LittleRegiment.txt";
    
//    char fName1[] = "sample.txt";
//    char fName2[] = "sample2.txt";
    

    FILE *in1 = fopen(fName1, "r");
    FILE *in2 = fopen(fName2, "r");
    
    if (!in1 || !in2) {
        perror("Error opening a file ");
    }
    
    
    List *list = createList();
    
    list = addWordsToList(in1, in2, list, &length);
    
    printf("There are %d unique words!\n", length);
    
    printf("Sorted by word:\n");
    printFirsTwentyFive(list, fName1, fName2);
    
    list = sortList(list, length);
    
    printf("Sorted by difference (descending):\n");
    printFirsTwentyFive(list, fName1, fName2);
    
    printf("Now printing the last 5 elements of the list:\n");
    printLastFive(list, fName1, fName2, length);

//    printf("Original LIST: \n");
//    printList(list);
    
    freeList(list);
    
    fclose(in1);
    fclose(in2);
    
    return 0;
}


List *addWordsToList(FILE *in1, FILE *in2, List *list, int *length) {

    char cleanWord[30] = {'\0'};
    char origWord[30] = {'\0'};
    
    int count = 0;
    
    while (fscanf(in1, "%s", origWord) != EOF) {
        
        if (removeGarbage(cleanWord, origWord)) {
            if (strlen(cleanWord) != 0) {
                insert(&list, cleanWord, 1);
            }
        }
        
        clearStringData(cleanWord);
        count++;
    }
    
    while (fscanf(in2, "%s", origWord) != EOF) {
        
        if (removeGarbage(cleanWord, origWord)) {
            if (strlen(cleanWord) != 0) {
                insert(&list, cleanWord, 2);
            }
        }
        clearStringData(cleanWord);
    }
    
    *length = count;
    
    return list;
}


List *sortList(List *list, int length) {
    
    int i;
    int p1Counter;
    int p2Counter;
    int swapped = 1;
    
    char tempName[30];
    
    int tempCounter1;
    int tempCounter2;
    
    List *p1;
    List *p2;    
    
    while (swapped) {
        
        swapped = 0;
        
        p1 = list;
        p2 = list->next;
        
        for (i = 0; i < length - 1; i++) {
            
            
            p1Counter = calculateWordCounts(p1->f1Counter, p1->f2Counter);
            p2Counter = calculateWordCounts(p2->f1Counter, p2->f2Counter);
            
            // swap nodes by value
            if (p1Counter < p2Counter) {
                
                strcpy(tempName, p1->name);
                tempCounter1 = p1->f1Counter;
                tempCounter2 = p1->f2Counter;
                
                strcpy(p1->name, p2->name);
                p1->f1Counter = p2->f1Counter;
                p1->f2Counter = p2->f2Counter;
                
                strcpy(p2->name, tempName);
                p2->f1Counter = tempCounter1;
                p2->f2Counter = tempCounter2;
                
                swapped = 1;
            }
            
            if (p2->next != NULL) {
                p1 = p1->next;
                p2 = p2->next;
            }
                
        }
    }
    
    return list;
}


int calculateWordCounts(int counter1, int counter2) {
    
    int result = 0;
    
    if (counter1 >= counter2)
        result = counter1 - counter2;
    else
        result = counter2 - counter1;
    
    
    return result;
}



void printFirsTwentyFive(List *list, char fName1[], char fName2[]) {
    int i;
    
    for (i = 0; i < 25; i++) {
        printf("%5d. %20s   %-s: %5d, %s: %5d,  Difference: %-5d\n", i+1, list->name, fName1, list->f1Counter,
               fName2, list->f2Counter, calculateWordCounts(list->f1Counter, list->f2Counter));
        list = list->next;
    }
    printf("\n");
}



void printLastFive(List *list, char fName1[], char fName2[], int length) {
    int i;
    
    for (i = 0; i < length - 1; i++, list = list->next) {
        if (i > length - 7) {
            printf("%5d. %20s   %-s: %5d, %s: %5d,  Difference: %-5d\n", i+2, list->name, fName1, list->f1Counter,
                   fName2, list->f2Counter, calculateWordCounts(list->f1Counter, list->f2Counter));
        }
        
//        if (list->next != NULL)
//            list = list->next;
    }
    printf("\n");
}


int removeGarbage(char *clean, char *orig) {

    int i;
    int result = 1;
    char *p;
    int length = (int) strlen(orig) + 1;
    
    for (i = 0, p = orig; i < length; i++, p++) {
        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || *p == '\'' || *p == '-') {
            
            
            if (*p >= 'A' && *p <= 'Z') {
                *p = *p + 32;
            }
            
            *clean++ = *p;
        }
        if (*p >= '0' && *p <= '9') {
            result = 0;
        }
    }
    
    return result;
}

void clearStringData(char *str) {
    int i;
    
    for (i = 0; i < 30; i++, str++) {
        *str = '\0';
    }
}
