#include <stdio.h> // input output
#include <string.h> // strcpy
#include <stdlib.h> // dynamic memory allocation

struct Course // kenapa Course dipisah dari Student? Karena 
             // dosen & aslab kan juga punya Course gak hanya student
{
    char ID[10];
    int score;
};


struct Student
{
    char name[255];
    double GPA;
    Course c; // object Course

};

// Student * artinya akan mereturn pointer yang mengarah ke Student
// or in other words to change the value of Student :>
// const char* name == char name[], difference is char name[] will get warning in vscode
// const is used to indicate that there will be no change in the *char variable (would be same all the way around)
//createStudent(struct) langsung jg boleh, malah lebih bagus
Student *createStudent(const char *name, double gpa, const char *ID, int score)
{
    Student *newStudent = (Student*)malloc(sizeof(Student));
    //malloc(200) -> alokasi memori 200 bytes
    strcpy(newStudent->name,name); // sama dengan strcpy(newStudent.name,name);
    newStudent->GPA = gpa;
    strcpy(newStudent->c.ID,ID);
    newStudent->c.score = score;

    return newStudent;
}


void removeStudent(Student *s)
{
    free(s); //buang memory yg sudah dialokasikan
    s = NULL; // kosongkan nilainya
}

void printStudent(Student *s)
{
    printf("Name: %s\n", s->name);
    printf("GPA: %lf\n", s->GPA);
    printf("Course ID: %s\n", s->c.ID);
    //why can't s->c->ID? because it equals to (s*).(c*).ID, which c here isn't a c*
    printf("Score: %d\n", s->c.score);
}

int main()
{
    // s1 mengarah ke student yang direturn createStudent
    // in other words, yang direturn adalah penambahan file di Student

    //why do we need Student*? Because we need to return a pointer to the struct Student
    // not only returning a struct
   Student *s1 = createStudent("Nana", 4.00,"COMP123", 90);
   printStudent(s1);
   removeStudent(s1);
   printStudent(s1);

    /*disini setelah removed bs dilihat hasil print-annya jadi kacau
    (name jadi aneh), ini karena kita mencoba utk mengakses file ilegal, yaitu
    file yang sudah dihapus. Kasus ini disebut undefined behaviour.*/

    return 0;
}