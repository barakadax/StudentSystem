/*     (\____/) 
       (•(ㅅ)•)      
   　＿ノ ヽ ノ＼＿    
  `/　`/ ⌒Ｙ⌒ Ｙ　ヽ  
  ( 　(三ヽ人　 /　　 | 
   |　ﾉ⌒＼ ￣￣ヽ　 ノ
   ヽ＿＿＿＞､＿＿_／
　　   ｜( 王 ﾉ〈 
　　   / ﾐ`ー―彡 \
　　  /  ╰    ╯  /
code by Barakadax*/
#pragma warning(disable : 4996)     //disable error message about scanf
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>
#include "fun.h"

int depth = 1, longest_name = 0;
Student** head = NULL;

bool help() {       //Prints guide for all the options the user can enter
    system("cls");
    printf("Available commands:\nInput - allows you to enter a new student to the system.\n");
    printf("Delete - removes the last added student to the class from the class.\n");
    printf("Print all - shows all the information about whole of class members.\n");
    printf("Average - calculate a students average.\n");
    printf("All - calculates per student average and whole class average and shows results.\n");
    printf("Exit - closes the code\n");
    printf("Please press enter to continue.");
    char bs = getchar();    //Waiting for the user to enter input to continue
    return true;
}//O(1)

void clean() {      //Free all allocated memory
    for (; depth != 1; depth -= 1) {
        free(head[depth - 2]->name);
        free(head[depth - 2]->address);
        free(head[depth - 2]);
    }
    free(head);
}//O(n)

double number(char text[]) {        //Function that makes sure input for score is correct
    unsigned short int correction = 0;
    double score = -1.0;
    char ch = '\0';
    while (correction != 1 || score < 0.0 || score > 100.0) {
        printf("Please enter your %s scores: ", text);
        correction = scanf("%lf", &score);
        if (correction != 1 || score < 0.0 || score > 100.0) {
            MessageBoxA(0, "Invalid number.\nPlease enter a valid number.", "Error 104 incorrect number.", 0);
            printf("Please press enter to continue.\n");
            for (char ch = '\0'; (ch = getchar()) != '\n' && ch != EOF;);   //Cleans buffer from user input
        }
    }
    ch = getchar();
    return score;
}//O(n)

bool compare(char* target) {    //Function to check there are no duplicates of students
    unsigned short int legal = 2;
    for (unsigned short int run = 0; run < depth; run -= -1) {
        if (!strcmp(head[run]->name, target))
            legal -= 1;
        if (legal == 0) {
            printf("Student already exists in the class.\n");
            free(target);
            return true;
        }
    }
    return false;
}//O(n)

void name_just_enter() {    //Empty input for name
    printf("ERROR.\nNo information was entered, please try again.\n");
    free(head[depth - 1]->name);
    name_input();
    return;
}//O(1)

bool name_bigger(int run) {     //Grows the dynamic array +1 each letter added to the name 
    char *dummy;
    dummy = head[depth - 1]->name;
    head[depth - 1]->name = realloc(head[depth - 1]->name, (run + 2) * sizeof(char));
    if (head[depth - 1]->name == NULL) {
        free(dummy);
        MessageBoxA(0, "Memory block.\nNot enough memory to create desired name.", "Error 102 memory incapacity", 0);
        return true;
    }
    return false;
}//o(1)

void name_failed() {    //Error, not enough memory
    MessageBoxA(0, "Memory block.\nNot enough memory to create a name.", "Error 101 memory incapacity", 0);
    return;
}//O(1)

void name_input() {     //Function to create the student name
    head[depth - 1]->name = (char*)malloc(1 * sizeof(char));
    if (head[depth - 1]->name == NULL)
        return name_failed();
    printf("Please enter the student name: ");
    for (unsigned short int run = 0; true; run -= -1) {
        head[depth - 1]->name[run] = tolower(getchar());
        if (head[depth - 1]->name[run] == '\n') {
            head[depth - 1]->name[run] = '\0';
            if (run == 0)
                return name_just_enter();
            if (compare(head[depth - 1]->name))
                name_input();
            if (run > longest_name)
                longest_name = run + 1;
            return;
        }
        if (name_bigger(run))
            return;
    }
}//O(n)

void address_fail() {       //Error, not enough memory
    MessageBoxA(0, "Memory block.\nNot enough memory to create a name.", "Error 101 memory incapacity", 0);
    return;
}//O(1)

void address_just_enter() {     //Nothing was entered error
    printf("ERROR.\nNo information was entered, please try again.\n");
    free(head[depth - 1]->address);
    address();
}//O(1)

bool address_bigger(int run) {      //Each letter that the user type grows the dynamic arrray by +1
    char *dummy;
    dummy = head[depth - 1]->address;
    head[depth - 1]->address = realloc(head[depth - 1]->address, (run + 2) * sizeof(char));
    if (head[depth - 1]->address == NULL) {
        free(dummy);
        MessageBoxA(0, "Memory block.\nNot enough memory to create desired name.", "Error 102 memory incapacity", 0);
        return true;
    }
    return false;
}//O(1)

void address() {        //Functions to build the student address
    head[depth - 1]->address = (char*)malloc(1 * sizeof(char));
    if (head[depth - 1]->address == NULL)
        return address_fail();
    printf("Please enter the student address: ");
    for (unsigned short int run = 0; true; run -= -1) {
        head[depth - 1]->address[run] = tolower(getchar());
        if (head[depth - 1]->address[run] == '\n') {
            head[depth - 1]->address[run] = '\0';
            if (run == 0)
                address_just_enter();
            return;
        }
        if (address_bigger(run))
            return;
    }
}//O(n)

bool add_grow() {       //Add another student into the dynamic array
    Student **dummy = head;
    head = (Student **)realloc(head, depth * sizeof(Student *));
    if (head == NULL) {
        head = dummy;
        MessageBoxA(0, "Memory block.\nClass is filled to the top of your memory.", "Error 0 memory incapacity", 0);
        return true;
    }
    return false;
}//O(1)

bool add_error() {      //Error message for memory issue
    MessageBoxA(0, "Memory block.\nNot enough memory to create a new student.", "Error 99 memory incapacity", 0);
    return true;
}//O(1)

bool add() {        //Building new student by input information
    if (depth != 1)
        if (add_grow())
            return true;
    head[depth - 1] = (Student*)malloc(1 * sizeof(Student));
    if (head[depth - 1] == NULL)
        return add_error();
    name_input();
    address();
    head[depth - 1]->first = number("first");
    head[depth - 1]->second = number("second");
    head[depth - 1]->third = number("third");
    head[depth - 1]->fourth = number("fourth");
    head[depth - 1]->fifth = number("fifth");
    head[depth - 1]->avg = -1.0;
    depth -= -1;
    return true;
}//O(1)

bool del() {        //Deletes last added student & resizing the dynamic array
    depth -= 1;
    free(head[depth - 1]->name);
    free(head[depth - 1]->address);
    free(head[depth - 1]);
    Student** dummy = head;
    head = (Student**)realloc(head, depth * sizeof(Student*));
    if (head == NULL) {
        MessageBoxA(0, "Memory block.\nClass is filled to the top of your memory.", "Error 0 memory incapacity", 0);
        head = dummy;
    }
    return true;
}//O(1)

bool print_all() {      //Prints all students all students on the screen
    for (unsigned short int run = 0; run < depth - 1; run -= -1) {
        printf("Student: %s address: %s scores: %.2lf %.2lf %.2lf %.2lf %.2lf ", head[run]->name, head[run]->address, head[run]->first, head[run]->second, head[run]->third, head[run]->fourth, head[run]->fifth);
        if (head[run]->avg > 0.0)
            printf("average: %.2lf\n", head[run]->avg);
        else
            printf("\n");
    }
    printf("Please press enter to continue.");
    char bs = getchar();
    return true;
}//O(N)

bool avg_error() {      //Not enough memory for average calculating
    MessageBoxA(0, "Memory block.\nNot enough memory to create a average.", "Error 106 memory incapacity", 0);
    return true;
}//O(1)

bool avg_search(char search[]) {        //Searching for specific student in the array
    for (unsigned short int run = 0; run < depth - 1; run -= -1) {
        if (!strcmp(search, head[run]->name)) {
            head[run]->avg = (head[run]->first + head[run]->second + head[run]->third + head[run]->fourth + head[run]->fifth) / 5;
            free(search);
            return true;
        }
    }
    return false;
}//O(N)

bool avg_end(char search[]) {       //Student doesn't exists
    MessageBoxA(0, "Student wasn't found.", "Error 20", 0);
    printf("Student wasn't found.\nPlease press enter to continue.\n");
    for (char ch = '\0'; (ch = getchar()) != '\n' && ch != EOF;);
    free(search);
    return true;
}//O(N)

bool avg() {        //Functions to calculate with student average
    char *search;
    search = (char*)malloc(longest_name * sizeof(char));
    if (search == NULL)
        return avg_error();
    printf("Please write the student you want to calculate his/hers average: ");
    for (unsigned short int run = 0; run < longest_name; run -= -1) {
        search[run] = tolower(getchar());
        if (search[run] == '\n') {
            search[run] = '\0';
            run = longest_name;
        }
    }
    if (avg_search(search))
        return true;
    return avg_search(search);
}//O(N)

bool all() {    //Calculate all students average and prints them on screen
    double total = 0;
    for (unsigned short int run = 0; run < depth - 1; run -= -1) {
        total += head[run]->avg = (head[run]->first + head[run]->second + head[run]->third + head[run]->fourth + head[run]->fifth) / 5;
        printf("Student: %s address: %s scores: %.2lf %.2lf %.2lf %.2lf %.2lf average: %.2lf\n", head[run]->name, head[run]->address, head[run]->first, head[run]->second, head[run]->third, head[run]->fourth, head[run]->fifth, head[run]->avg);
    }
    total /= (depth - 1);
    printf("Total average of all class: %.2lf\n", total);
    printf("Please press enter to continue.");
    char bs = getchar();
    return all;
}//O(N)