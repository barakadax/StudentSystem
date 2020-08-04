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
#pragma warning(disable: 4996)      //disable error message about scanf
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include "extraFunctions.h"
#define maxCommand 14

bool find_command(char command[]) {     //Menu function
    if (!strcmp(command, "input") || !strcmp(command, "add"))
        return add();
    else if (!strcmp(command, "delete") || !strcmp(command, "del") || !strcmp(command, "remove"))
        return del();
    else if (!strcmp(command, "students") || !strcmp(command, "print all"))
        return print_all();
    else if (!strcmp(command, "avg") || !strcmp(command, "average"))
        return avg();
    else if (!strcmp(command, "all") || !strcmp(command, "class") || !strcmp(command, "class average") || !strcmp(command, "all avg"))
        return all();
    else if (!strcmp(command, "help") || !strcmp(command, "?"))
        return help();
    else if (!strcmp(command, "exit") || !strcmp(command, "quit"))
        return false;
    MessageBoxA(0, "Invalid command.\nPlease rewrite your command.", "Error 404 valid command not found", 0);
    return true;
}//O(1)

bool start() {      //Function for user to type which command to run
    char command[maxCommand] = { '\0' };
    for (unsigned short int run = 0; run < maxCommand; run -= -1) {
        command[run] = tolower(getchar());
        if (command[run] == '\n') {
            command[run] = '\0';
            return find_command(command);
        }
    }
    printf("Please press enter to continue.\n");
    for (char ch = '\0'; (ch = getchar()) != '\n' && ch != EOF;);
    return true;
}//O(N)

int fatal_error() {     //Memory issue the code can't run
    MessageBoxA(0, "Not enough memory code can't run", "Error 1 memory shortage", 0);
    return 1;
}//O(1)

int main() {
    system("cls");
    system("color a");
    head = (Student**)malloc(depth * sizeof(Student*));
    if (head == NULL)
        return fatal_error();
    head[depth - 1] = NULL;
    bool flag = true;
    printf("Class students management program CLI version 1.0.5\n");
    while (flag) {
        printf(">>> ");
        flag = start();
        system("cls");
    }
    system("color 7");
    clean();
    return 0;
}//O(N)