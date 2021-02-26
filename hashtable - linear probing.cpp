#include<stdio.h>
#include<string.h>

// # -> preprocessor directive = dijalankan sebelum program dicompile.
// that's why include pakai #

// Linear Probing

/*no need to use const actually, tapi ditulis gitu karena
 kita udah tau gak bakal diubah2 lg valuenya. Supaya lebih rapi aja */
const int MAX_ELEMENT = 5; // panjang array
const int MAX_LENGTH = 255; //panjang string
char HASHTABLES[MAX_ELEMENT][MAX_LENGTH];

// ^ udah jadi hash tablenya

int hash(const char *str) // ascii sum hash function
{
    //Use : menghasilkan index array yang akan diisi
    int sum = 0;

    for(int i = 0; str[i] != '\0'; i++)
    {
        sum = sum + str[i] - '0';
    }

    /*
    OR 

    sum = sum + str[i] - 'a';
    dengan anggapan bahwa a = 0, b = 1, c = 2, dst..)
    */

    return sum % MAX_ELEMENT; // menghindari index di luar batas array
}

void linearProbing(const char *str, int index)
{
    for(int i = (index+1) % MAX_ELEMENT;i != index; i = (i+1) % MAX_ELEMENT ) // utk menghindari out of bound
    {
        //^ INGET % MAX_ELEMENT NYA AJA 
        if(!HASHTABLES[i][0])
        {
            strcpy(HASHTABLES[i], str);
            return;
        }
    }
    puts("THE TABLE IS FULL!"); // tidak berhasil masuk ke hash table(semua index sudah terisi)
}
void insert (const char *str)
{
    int index = hash(str); // dapetin idx array lewat hash function
    if(!HASHTABLES[index][0]) // jika index masih kosong, mau liat apakah dia '\0' atau gak
    {
        strcpy(HASHTABLES[index], str);
        //HASHTABLES[index] = str; => isn't allowed bcs array of char can't be initialized that way
    }else // jika sudah terisi
    {
        linearProbing(str, index);
    }
    
}

void view()
{
    puts("HASHTABLE");
    for(int i = 0; i < MAX_ELEMENT; i++)
    {
        printf("Index %d: %s\n", i, HASHTABLES[i]);
    }
}



int main()
{
    insert("Novia");
    insert("Novia Sari");
    insert("Meow");
    insert("Woof");
    insert("GRAWR");
    view();

    insert("SATAN");


    return 0;
}