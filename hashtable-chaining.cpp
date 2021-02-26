#include<stdio.h>
#include<string.h>
#include<stdlib.h>

const int MAX_ELEMENT = 5; // jumlah index di hashtable
int COLLISION_COUNT = 0;

struct Node
{
    char name[255];
    Node *next; // pointer ke node selanjutnya
}*head[MAX_ELEMENT], *tail[MAX_ELEMENT]; // head dan tail global sebanyak MAX_ELEMENT

Node *createNode(const char *str)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, str);
    newNode->next = NULL;
    return newNode;
}

int hash(const char *str) 
{
    int sum = 0;

    for(int i = 0; str[i] != '\0'; i++)
    {
        sum = sum + str[i] - '0';
    }

    return sum % MAX_ELEMENT;
}

void insert(const char *str)
{
    int index = hash(str); // dapat index
    Node *temp = createNode(str); // node baru

    if(!head[index]) // jika indexnya masih kosong
    {
        head[index] = tail[index] = temp; // temp akan menjadi head dan tail
    }else{
        COLLISION_COUNT++;
        tail[index]->next = temp;
        tail[index] = temp;
    }
}

void view()
{
    for(int i = 0;i< MAX_ELEMENT; i++)
    {
        printf("Index %d: ", i);

        //print linked listnya
        if(head[i])
        {
            Node *curr = head[i];
            while(curr)
            {
                printf("%s -> ", curr->name);
                curr = curr->next;
            }
        }

        puts("NULL");
    }
}

int main()
{
    insert("MEOW");
    insert("novia");
    insert("lololololol");
    insert("hihi");
    insert("momomo");
    insert("a");
    insert("b");
    insert("c");
    insert("d");
    insert("e");
    insert("f");
    view();
    printf("ASCII COUNT : %d\n", COLLISION_COUNT);
    //DJB2? 
    //Cari sendiri algoritma hash yang cocok dengan data yang di atas ^
    return 0;
}