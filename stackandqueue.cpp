#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int value;
    Node *prev, *next;
};

Node *top; // untuk stack
Node *first, *last;// untuk queue

/*
STACK
10(TOP)
8
3
BAWAH = NEXT, ATAS = PREV
*/

/*
QUEUE
5(FIRST) 3 2 10 (LAST)
KIRI = PREV, KANAN = NEXT
*/

Node * createNode(int value) // yang diterima hanya attribut nodenya
{

    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->prev = newNode->next = NULL;
    return newNode;

}

// Stack : pushStack(), removeStack() => pushHead(), popHead()
// Queue : pushQueue(), removeQueue() + pushTail(), popHead()

void pushStack(int value)
{
    Node *temp = createNode(value);
    
    if(!top) // empty stack
    {
        top = temp;
    }else // >= 1 node
    {
        top->prev = temp; // lietnya dari top ke dalam makanya temp jadi prevnya top
        temp->next = top;
        top = temp;
    }
}

void removeStack()
{

    /*Condition
    1. Gak ada top
    2. Hanya ada 1 node, yaitu top
    3. ada lebih dari 1 node
    */

    if(!top) // empty stack
    {
        return;
    }else if(!top->next) // 1 node
    {
        free(top); //remove memorinya
        top = NULL; //remove valuenya
    }
    else //> 1 node
    {
        Node *temp = top->next;
        top->next->prev = NULL; // atau temp->prev langsung jg boleh
        top->next = NULL;
        free(top);
        top = temp;
        
    }
}

/*Kenapa setiap pointernya harus di NULL kan?
Karena gini misal ada 10 -> <- 8
kalau hanya pointer 8->prev = NULL : 10 -> 8
free(10) : -> 8 (pointer menuju ke 8 nya masih ada)
Kejadian ini disebut dangling pointer. Kalau gak di NULL,
entar ada banyak pointer menuju 8.

 */


void pushQueue(int value)
{
  Node *newNode = createNode(value);

  if(!first)
  {
      first = last = newNode;
  }else
  {
     last->next = newNode;
     newNode->prev = last;
     last = newNode;
  }
}


void removeQueue()
{
    if(!first)
    {
        return;
    }else if(first == last) // 1 node
    {
        free(first);
        first = last = NULL;
    }else // > 1 node
    {
        Node *temp = first->next;
        first->next = temp->prev = NULL;
        free(first);
        first = temp;
    }
}

void printStack()
{
    Node *curr = top;
    puts("Stack :");
    while(curr)
    {
        printf("%d\n", curr->value);
        curr = curr->next;
    }
    puts("NULL");
}

void printQueue()
{
    Node *curr = first;
    puts("Queue :");
    while(curr)
    {
        printf("%d\n", curr->value);
        curr = curr->next;
    }
    puts("NULL");


}

int main()
{
    pushStack(10);
    pushStack(9);
    pushStack(13);
    printStack();

    removeStack();
    printStack();

    pushQueue(12);
    pushQueue(5);
    pushQueue(11);
    printQueue();
    
    return 0;
}