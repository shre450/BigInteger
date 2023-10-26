#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BigInteger.h"
// struct node{
//     int data;
//     struct node *next;
// };
// typedef struct BigInteger {
//     int length;
//     struct node *L;
// }SBI;



// Define your struct node here

//function to convert the given string to int
SBI initialise(char* str) {
    SBI temp ;
    temp.L=NULL;

    int l;
    int i;
    int num;
    l = strlen(str); //finding length of string
   for(i=0;i<l;i++){
    if(str[i]>='0' && str[i]<='9' || str[i]=='-' || str[i]=='+')
    {
        int digit=str[i]-'0';
        insertAtEnd(&temp.L, digit);

    }
   }
   temp.length=0;
   struct node*current=temp.L;
   while(current!=NULL){
    temp.length++;
    current=current->next;
   }
   return temp;
}
//function to create the node for final sum linked list
struct node* create(int sum) {
    
    struct node* newNode = (struct node*)malloc(sizeof(struct node ));
    if(newNode==NULL){
        printf("Memory allocation failed\n");
    }
    newNode->data = sum;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(struct node**head,int data)
{
    struct node*newnode=create(data);
    if(*head==NULL){
        *head=newnode;
    } else{
        struct node*current=*head;
        while(current->next!=NULL){
            current=current->next;
        }
        current->next=newnode;
    }
}
//function to reverse the linked list
SBI reverseLinkedList(SBI num) {
    SBI prev;
    SBI current=num;
    SBI next;
    prev.L=NULL;
    next.L=NULL;
    
    while (current.L != NULL) {
        next.L = current.L->next;
        current.L->next = prev.L;
        prev.L = current.L;
        current.L = next.L;
    }
    return prev;
}

//function to do the addition of bigInteger
SBI add(SBI num1, SBI num2) {
    //convert(num1);
    //convert(num2);
    struct node*result=NULL;
    
    SBI temp1 = reverseLinkedList(num1);
    SBI temp2 = reverseLinkedList(num2);
    struct node*ptr1=temp1.L;
    struct node*ptr2=temp2.L;
    int carry = 0;
    int sum;
    while (ptr1!=NULL || ptr2!=NULL) {
       int v1=(ptr1 !=NULL)?ptr1->data:0;
       int v2=(ptr2 !=NULL)?ptr2->data:0;
       sum=v1+v2+carry;
       carry=sum/10;
       insertAtEnd(&result,sum%10);
       if(ptr1 !=NULL){
        ptr1=ptr1->next;
       }
       if(ptr2 !=NULL){
        ptr2=ptr2->next;
       }
    }
    
    if (carry > 0) {
        insertAtEnd(&result,carry);
    }
    SBI resultSBI;
    resultSBI.length=num1.length+num2.length;
    resultSBI.L=result;
    
    return reverseLinkedList(resultSBI);
}

//function to perform subtraction of linked list
SBI sub(SBI num1, SBI num2) {
    SBI result;
    result.L=NULL;
    result.length=0;
    //convert(num1);
    //convert(num2);
   SBI temp1 = reverseLinkedList(num1); //reversing the num1 linked list
    SBI temp2 = reverseLinkedList(num2); //reversing the num2 linked list
    struct node* ptr1 = temp1.L;
    struct node* ptr2 = temp2.L;
    int borrow = 0;
    while (ptr1 != NULL || ptr2 != NULL) {
        int val1 = (ptr1 != NULL) ? ptr1->data : 0;
        int val2 = (ptr2 != NULL) ? ptr2->data : 0;
        int diff = val1 - val2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        struct node* newNode = create(diff);
        
        if (result.L == NULL) {
            result.L = newNode;
        } else {
           struct node*current=result.L;
           while(current->next!=NULL){
            current=current->next;
           }
           current->next=newNode;
        }
        if(ptr1 !=NULL){
            ptr1=ptr1->next;
        }
        if(ptr2 !=NULL){
            ptr2=ptr2->next;
        }
       
}
struct node* current=result.L;
while(current!=NULL && current->data==0){
    struct node*temp=current;
    current=current->next;
    free(temp);
}
result.L=current;
result.length=0;
current=result.L;
while(current!=NULL){
    result.length++;
    current=current->next;
}
return reverseLinkedList(result);
}
SBI mul(SBI num1,SBI num2)
{
    SBI result;
    result.L = create(0);  // Initialize with a single node containing 0
    result.length = 1;
    SBI temp1=reverseLinkedList(num1);
    SBI temp2=reverseLinkedList(num2);
    struct node* ptr2 = temp2.L;
    while (ptr2 != NULL) 
    {
        int val2 = ptr2->data;
        SBI tempResult;
        tempResult.L = NULL;
        tempResult.length = 0;
        struct node* current = temp1.L;
        int carry = 0;
        // Multiply num1 with a single digit of num2
        while (current != NULL || carry != 0) 
        {
            int val1 = (current != NULL) ? current->data : 0;
            int product = val1 * val2 + carry;
            carry = product / 10;
            int digit = product % 10;
            struct node* newNode = create(digit);
            if (tempResult.L == NULL) 
            {
                tempResult.L = newNode;
            } 
            else 
            {
                struct node* tempCurrent = tempResult.L;
                while (tempCurrent->next != NULL) 
                {
                    tempCurrent = tempCurrent->next;
                }
                tempCurrent->next = newNode;
            }
            if (current != NULL) 
            {
               current = current->next;
            }
        }
        // Add the temporary result to the final result with appropriate shifts
        for (int i = 0; i < result.length - 1; i++) 
        {
            struct node* newNode = create(0);
            struct node* tempCurrent = tempResult.L;
            while (tempCurrent->next != NULL) 
            {
                tempCurrent = tempCurrent->next;
            }
            tempCurrent->next = newNode;
            tempResult.length++;
        }
        result = add(result, tempResult);
        ptr2 = ptr2->next;
    }
    return reverseLinkedList(result);
}

SBI div1(SBI num1,SBI num2)
{
    SBI quotient;
    SBI temp1=reverseLinkedList(num1);
    SBI temp2=reverseLinkedList(num2);
    quotient.L = NULL;
    quotient.length = 0;
    SBI remainder = temp1;
    while (compare(remainder, temp2) >= 0) 
    {
        SBI temp;
        temp.L = NULL;  
        temp.length = 0;
        int count = 0;
        while (compare(remainder, temp2) >= 0) 
        {
            remainder = sub(remainder, temp2);
            count++;
        }
        insertAtEnd(&(temp.L), count);
        temp.length = 1;
        quotient = add(quotient, temp);
    }
    return reverseLinkedList(quotient);
}
int compare(SBI num1,SBI num2)
{
    if(num1.length<num2.length)
    return -1;
    if(num1.length>num2.length)
    return 1;
    struct node *p1=num1.L;
    struct node *p2=num2.L;
    while(p1!=NULL && p2!=NULL)
    {
        if(p1->data<p2->data)
        return -1;
        if(p1->data>p2->data)
        return 1;
        p1=p1->next;
        p2=p2->next;
    }
    return 0;
}

//function to display the linked list
void display(SBI num) {
    struct node*current=num.L;
    while (current!=NULL) {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}