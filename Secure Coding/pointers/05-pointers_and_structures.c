#include<stdio.h>
#include<string.h>

struct tag{
    char lname[20];
    char fname[20];
    int age;
    float tag;
};

struct tag my_struct;

void show_name(struct tag *p){
    printf("%s ",p->fname); // p->fname == (*p).fname
    printf("%s ",p->lname);
    printf("%d\n",p->age);
}

int main(){
    struct tag *st_ptr;
    st_ptr=&my_struct;
    strcpy(my_struct.fname,"krishna");
    strcpy(my_struct.lname,"moorthi");
    my_struct.age=20;
    show_name(st_ptr);
}
