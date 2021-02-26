#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node 
{
    char name[255];
    int score;
    Node *next; //menunjuk ke node selanjutnya
} *head, *tail; //*head, *tail itu utk nampung address dari node pertama
//dan node terakhir dari linked list
/*Kenapa head dan tail gak di dlm struct? karena itu artinya
setiap node memiliki head dan tail. Padahal satu linked list hanya boleh
punya 1 head dan 1 tail.*/


//const char *name == char name[]
Node *createNode(const char *name, int score)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name,name);
    newNode->score=score;
    newNode->next = NULL; //supaya bs tahu mana yg tail, kalo gk ada yg nextnya NULL gk ketemu
    return newNode;
}

void pushHead(const char *name, int score)
{
   
    
    //1. buat node
    //2. cek kondisi
    //jika tidak ada head, maka nodenya akan menjadi head and tail
    //jika ada head, maka node akan menjadi head baru dan node->next = head lama

    Node *temp = createNode(name, score);

    if(!head)//artinya linked listnya kosong, belum ada isi
    {
        head = tail = temp;
    } else
    {
        temp->next = head;
        head = temp;
        //why not head->next = NULL? karena belom tentu node yg ada itu cuma 1
        //bisa aja dibelakang head ada 2,3, atau lebih node.
    }
    
}


void pushTail(const char *name, int score)
{

    
    //1. buat node
    //2. cek kondisi
    //jika tidak ada head, maka nodenya akan menjadi head and tail
    //jika ada head, maka node akan menjadi head baru dan node->next = head lama

    Node *temp = createNode(name, score);

    if(!head)//artinya linked listnya kosong, belum ada isi
    {
        head = tail = temp;
    } else
    {
        tail->next = temp;
        // temp->next = NULL;
        //^ this is not needed, karena setiap createNode by default sudah NULL. 
        tail = temp;
    }
    
}

void popHead()
{
    if(!head)// jika tidak ada head
    {
        return;
    }else if(head == tail) // kalau node cuma 1
    {
        free(head);
        head = tail = NULL; // head = NULL jg boleh
    }else // 53(head) -> 70 -> 40 -> 25
    {
        Node *temp = head->next; //53(head) -> 70(temp) -> 40 -> 25
        head->next = NULL; // 53(head) -> NULL || 70(temp) -> 40 -> 25
        free(head);
        head = temp; // 70(head, temp) -> 40 -> 25
    }// kalau gak ada condition head == tail, nanti NULL yg jd temp dan itu bs
    //jd undefined behaviour

}


void popTail()
{
    if(!head)
    {
        return;
    }else if(head == tail)
    {
        free(tail);
        head = tail = NULL;
    }else
    {
        Node *temp = head;
        
        while(temp->next != tail)
        {
            temp = temp->next;
        }
        temp->next = NULL; // pisahin jd 2 linked list
        //53(head)-> 70 -> 40(temp) -> NULL || 25(tail) -> NULL
        free(tail);
        tail = temp; // 53(head) -> 70 -> 40(temp, tail) -> NULL
    }
}

void printList()
{
    Node *curr = head;

    while(curr)
    {
        if(curr == head && curr == tail)
        {
            printf(" (head, tail) ");
        }else if(curr == head)
        {
            printf(" (head) ");
        }
        else if(curr == tail)
        {
            printf(" (tail) ");
        }
        printf("%s %d -> ", curr->name, curr->score);
        curr = curr->next;
    }printf("NULL\n");
}


// if x = NULL, dan kita mau printf x->value, bisa segmentation fault
// ini karena kita mau mengakses sesuatu yg gak ada nilainya
/*makanya utk ngecek biasanya gini :
if(x != NULL && x -> next != NULL)
{
    blabla...
}

or

if(x && x->next)
{
    blablabla..
}
*/




int main()
{
    Node *lol = createNode("Novia", 99);
    pushHead(lol->name, lol->score);
    // pushHead("Lol", 100);
    printList();
    return 0;
}