#ifndef BigInteger_H
#define BigInteger_H
#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
typedef struct BigInteger {
    int length;
    struct node *L;
}SBI;
void insertAtEnd(struct node**, int);
SBI reverseLinkedList(SBI);
SBI add(SBI, SBI);
SBI sub(SBI, SBI);
struct node* create(int);
void display(SBI);
SBI initialise(char*);
#endif