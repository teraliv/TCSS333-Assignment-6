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

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void removeGarbage(char *, char *);
void clearStringData(char *);
List *addWordsToList(FILE *, FILE *, List *);
void printFirsTwentyFive(List *, char [], char []);
List *sortList(List *, int);
int calculateWordCounts(int, int);
int calculateAllWords(List *);
void printLastFive(List *, char [], char [], int);

void printAllWords(List *list, char fName1[], char fName2[]);


int main() {
    
    int length; // the number of total words in the list

//    char fName1[] = "ShortBadge.txt";
//    char fName2[] = "ShortReg.txt";

    char fName1[] = "RedBadge.txt";
    char fName2[] = "LittleRegiment.txt";

    FILE *in1 = fopen(fName1, "r");
    FILE *in2 = fopen(fName2, "r");
    
    if (!in1 || !in2) {
        perror("Error opening a file ");
    }
    
    List *list = createList();
    list = addWordsToList(in1, in2, list);
    length = calculateAllWords(list);
    
    printf("There are %d unique words!\n", length);
    
    printf("Sorted by word:\n");
    printFirsTwentyFive(list, fName1, fName2);
    
    list = sortList(list, length);
    
    printf("Sorted by difference (descending):\n");
    printFirsTwentyFive(list, fName1, fName2);
    
    printf("Now printing the last 5 elements of the list:\n");
    printLastFive(list, fName1, fName2, length);
    
    freeList(list);
    
    fclose(in1);
    fclose(in2);
    
    return 0;
}


/*
 * A function to read words from two files and 
 * add unique words to to linked list.
 *
 * @param *in1 - text file to read words.
 * @param *in2 - text file to read words.
 * @param *list - pointer to a linked list to add words.
 * @param *length - total number of words.
 * @return - linked list with added words.
 */
List *addWordsToList(FILE *in1, FILE *in2, List *list) {

    char cleanWord[30] = {'\0'};
    char origWord[30] = {'\0'};
    
    // get words from first text file
    while (fscanf(in1, "%s", origWord) != EOF) {
        
        removeGarbage(cleanWord, origWord);
        if (strlen(cleanWord) != 0) {
            insert(&list, cleanWord, 1);
        }
        clearStringData(cleanWord);
    }
    
    // get words from second text file
    while (fscanf(in2, "%s", origWord) != EOF) {
        
        removeGarbage(cleanWord, origWord);
        if (strlen(cleanWord) != 0) {
            insert(&list, cleanWord, 2);
        }
        clearStringData(cleanWord);
    }
    return list;
}


/*
 * A function to buuble sort linked list.
 *
 * @param *list - pointer to a linked list with unique words.
 * @param *length - total number of words.
 * @return - linked list of sorted words.
 */
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
    
    // loop untill elements are not swapped
    while (swapped) {
        
        swapped = 0;
        
        p1 = list;
        p2 = list->next;
        
        for (i = 0; i < length - 1; i++) {
            
            // calculate word counts differences
            p1Counter = calculateWordCounts(p1->f1Counter, p1->f2Counter);
            p2Counter = calculateWordCounts(p2->f1Counter, p2->f2Counter);
            
            // swap nodes by value
            if (p1Counter < p2Counter) {
                // make temp of fires node
                strcpy(tempName, p1->name);
                tempCounter1 = p1->f1Counter;
                tempCounter2 = p1->f2Counter;
                
                // first node gets data from second node
                strcpy(p1->name, p2->name);
                p1->f1Counter = p2->f1Counter;
                p1->f2Counter = p2->f2Counter;
                
                // second node gets data from first node
                strcpy(p2->name, tempName);
                p2->f1Counter = tempCounter1;
                p2->f2Counter = tempCounter2;
                
                swapped = 1; // swap is made
            }
            
            // move nodes to the next position
            if (p2->next != NULL) {
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }
    
    return list;
}


/*
 * A function to calcute the difference of words appearance.
 *
 * @param counter1 - word's occurences in 1st file.
 * @param counter2 - word's occurences in 2nd file
 * @return - returns the difference of occurences.
 */
int calculateWordCounts(int counter1, int counter2) {
    
    int result = 0;
    
    if (counter1 >= counter2)
        result = counter1 - counter2;
    else
        result = counter2 - counter1;
    
    
    return result;
}


/*
 * A function to calcute total number of words.
 *
 * @param counter1 - word's occurences in 1st file.
 * @param counter2 - word's occurences in 2nd file
 * @return - returns the difference of occurences.
 */
int calculateAllWords(List *list) {
    
    int result = 1;
    
    while (list->next != NULL) {
        result++;
        list = list->next;
    }
    
    return result;
}


/*
 * A function to display first 25 words from the linked list.
 *
 * @param *list - pointer to a linked list with unique words.
 * @param fName1 - the name of 1st file
 * @param fName2 - the name of 2nd file
 */
void printFirsTwentyFive(List *list, char fName1[], char fName2[]) {
    int i;
    
    for (i = 1; i <= 25; i++) {
        printf("%5d. %20s   %-s: %5d, %s: %5d,  Difference: %-5d\n", i, list->name, fName1, list->f1Counter,
               fName2, list->f2Counter, calculateWordCounts(list->f1Counter, list->f2Counter));
        list = list->next;
    }
    printf("\n");
}


/*
 * A function to display the last 5 words from the linked list.
 *
 * @param *list - pointer to a linked list with unique words.
 * @param fName1 - the name of 1st file
 * @param fName2 - the name of 2nd file
 * @param length - total number of all words in the list.
 */
void printLastFive(List *list, char fName1[], char fName2[], int length) {
    int i;

    for (i = 1; i <= length; i++, list = list->next) {
        if (i > length - 5) {
            printf("%5d. %20s   %-s: %5d, %s: %5d,  Difference: %-5d\n", i, list->name, fName1, list->f1Counter,
                   fName2, list->f2Counter, calculateWordCounts(list->f1Counter, list->f2Counter));
        }
    }
    printf("\n");
}


/*
 * A function to remove all unnecessary characters from a word.
 *
 * @param *clean - a pointer to a cleaned word.
 * @param *orig - a pointer to a original word.
 */
void removeGarbage(char *clean, char *orig) {

    int i;
    char *p;
    int length = (int) strlen(orig) + 1;
    
    // check if word consisto of the following characters
    for (i = 0, p = orig; i < length; i++, p++) {
        if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z') || *p == '\'' || *p == '-') {
            
            // make word lowercase
            if (*p >= 'A' && *p <= 'Z') {
                *p = *p + 32;
            }
            
            *clean++ = *p;
        }
    }
}

/*
 * A function to clear the string data.
 *
 * @param *clean - a pointer to a cleaned word.
 */
void clearStringData(char *str) {
    int i;
    
    for (i = 0; i < 30; i++, str++) {
        *str = '\0';
    }
}
