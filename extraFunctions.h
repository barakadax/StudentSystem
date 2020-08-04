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
typedef struct {
    char *name, *address;
    double first, second, third, fourth, fifth, avg;
} Student;
extern int depth, longest_name;
extern Student **head;
bool help();
void clean();
double number(char text[]);
bool compare(char *target);
void name_input();
void address();
bool add();
bool del();
bool print_all();
bool avg();
bool all();