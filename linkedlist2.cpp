#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//TUGAS ASG 1


/*Mau buet 2 linked list? Mudahh
struct Node
{
    int value;
    Node *next;
}head, head2, tail, tail2;  <- jadi deh 2 linked list
    
    terus utk function popHead, popTailnya gk masalah klo mau buet 
    utk masing-masing

kalo mau gabung gini :

void pushHead(Node *index, int value)
{
    ...
}
pushHead(head, value);
pushHead(head2, value);
    */

/*
struct Equipment 
{
    char name[255];
    char desc[255];
};


struct Hero
{
    int health;
    Equipment *e; //Heronya memiliki PENUNJUK ke Equipmentnya
                // bukan langsung object Equipmentnya
                //sekalian ngisi valuenya.
    Equipment e; //Heronya copas isi dari e, ke dalam isi
                // == int health, char name[255], char desc[255];
};


*/


struct Node 
{
    int value;
    Node *prev, *next;
}*head, *tail;

Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// 30 -> <- 50 -> <- 80
void pushHead(int value)
{
    Node *temp = createNode(value);

    if(!head)
    {
        head = tail = temp;
        // head->next = head->prev = NULL; this is only necessary if u
        // put head = tail = value.
    }else if(head == tail)
    {
        head->prev = temp; // 20(temp)<- 30(head,tail)
        temp->next = head; // 20(temp)-> <- 30(head,tail)
        head = temp; // 20(temp,head)-><- 30(tail)
    }else
    {
        // 30(head) -> <- 50 -> <- 80
        head->prev = temp; // 20(temp) <- 30(head) -> <- 50 -> <- 80
        temp->next = head; // 20(temp)-> <- 30(head) -> <- 50 -> <- 80
        head = temp;// 20(head,temp)-> <- 30 -> <- 50 -> <- 80

    }
    // apparently for condition (head == tail ) && node > 1
    // has the same statement! :o so we don't have to write for head==tail
}

void pushTail(int value)
{
    Node *temp = createNode(value);

    if(!head) // 0 node
    {
        head = tail = temp;

    }else if(head == tail) // 1 node
    {
        head->next = temp; //  30(head,tail)-> 20(temp)
        temp->prev = head; //  30(head,tail)-> <- 20(temp)
        tail = temp; //  30(head)-> <- 20(temp, tail)
    }else
    {
        // 30(head) -> <- 50 -> <- 80
        tail->next = temp; // 30(head) -> <- 50 -> <- 80(tail) -> 20 (temp)
        temp->prev = tail; // 30(head) -> <- 50 -> <- 80(tail) -> <-20 (temp)
        tail = temp;// 30(head) -> <- 50 -> <- 80 -> <-20 (temp, tail)

    }
}


void pushMid(int value) // mau brapapun value yg dimasukin, listnya pasti akan selalu sorted
{
    /*Possible condition :
    1. Linked list kosong
    2. Insert dari depan
    3. Insert dari belakang
    4. Insert di tengah
    */
    // 9-> <- 10 -> <- 12 -> <- 15

   if(!head) // linked list kosong
   {
        Node *newNode = createNode(value);
        head = tail = newNode;

   }else if(value < head->value) // insert dari depan
   {
      pushHead(value);
   }else if(value > tail->value) // insert dari belakang
   {
       pushTail(value);

   }else // insert di tengah (mau insert 12)
   {
       //9(head) -> <- 10 -> <- 13 -> <- 15(tail)
       Node *curr = head;
       Node *temp = createNode(value);

       while (curr->value < value)
       {
          curr = curr->next;
       }

       temp->prev = curr->prev;
       /*                   12(temp)
                     /(prev)
       9(head) -> <- 10 ->          <- 13(curr)-> <- 15(tail)
       */
       temp->next = curr;
       /*                   12(temp)
                    /(prev)             \ (next)
       9(head) -> <- 10 ->              <- 13(curr) -> <- 15(tail)
       */
       curr->prev = temp;
      /*                   12(temp)
                    /(prev)             \\ (prev, next)
       9(head) -> <- 10 ->              <- 13(curr) -> <- 15(tail)
       */
       temp->prev->next = temp;
      /*                   12(temp)
                    /(next, prev)             \\ (prev, next)
       9(head) -> <- 10 ->              <- 13(curr) -> <- 15(tail)
       */

       //^ dia harus nunjuk ke node ya, bukan ke angkanya
       //jadi yg gini kurang tepat :
       //    curr->prev->next = value;
       //    curr->prev = value; 

       //pilihan curr itu mending jaraknya hanya 1 node dari temp kalo
       //lebih ribet

   }

   //Step by step:
   // 1. Cari posisi curr yg tepat
   //       Butuh curr karena linked list tidak punya index/label
   //       Jika 1 curr tidak memungkinkan, gunakan > 1 curr
   // 2. Hubungkan curr dengan temp
   // 3. Hubungkan temp dengan kanan kirinya



}
// kalo pushMid gak mau sorted bs pakai 
// void pushMid(int index, int value)

void popHead()
{
    if(!head)
    {
        return;
    }else if(head == tail)
    {
        free(head);
        head = NULL;
    }else
    {
        Node *temp = head->next;   // 30(head) -> <- 50(temp) -> <- 80 
        head->next = temp->prev = NULL; // 30(head) -> NULL || NULL <- 50(temp) -> <- 80 
        free(head);
        head = temp; // 50(temp,head) -> <- 80 
    }
}

void popTail()
{
    if(!head)
    {
        return;
    }else if(head == tail)
    {
        free(tail);
        tail = NULL;
    }else
    {
        Node *temp = tail->prev;   // 30 -> <- 50(temp) -> <- 80 (tail)
        tail->prev = temp->next = NULL;  // 30 -> <- 50(temp) -> NULL || NULL <- 80 (tail)
        //^ artinya bukan prev & next valuenya dihapus, tapi prev dan next skrg menunjuk/point ke value NULL
        free(tail);
        tail = temp; // 30 -> <- 50(temp, tail)
    }
}

void popMid(int value)
{
    if(!head)
    {
        return;
    }else if(value == head->value)
    {
        popHead();
    }else if(value == tail->value)
    {
        popTail();
    }else
    {
        Node *curr = head;
        while(curr && curr->value != value) //curr utk siapa tau valuenya gk ada di linked list
        {
            curr = curr->next;
        }

        if(!curr)
        {
            puts("There is no target in the linked list");
            return;
        }

        //9(head) -> <- 10 -> <- 13(curr) -> <- 15(tail)
        curr->prev->next = curr->next; //10 -> 15
        curr->next->prev = curr->prev; //10-> <-15
        curr->next = curr->prev = NULL; //9(head) -> <- 10 -> <- 15(tail) (hapusin pointer curr)
        free(curr);
        curr = NULL;

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


/*Untuk tugas di BINUS:
Buatnya gini aja,

Insert nilai yang mau dihapus,
search(nilai) dulu

kalo return 0 /  FALSE -> printf "nilai tidak ditemukan";
kalo return 1 / TRUE -> popMid(nilai)

*/

int main()
{
    return 0;
}