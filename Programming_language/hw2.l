%{
#include <stdio.h>
int preprocessorcount = 0;
int octalnumbercount = 0;
int negativedecimalnumbercount = 0;
int positivedecimalnumbercount = 0;
int operatorcount = 0;
int commentcount = 0;
int equalcount = 0;
int openbracecount = 0;
int closebracecount = 0;
int wordcase1count = 0;
int wordcase2count = 0;
int wordcount = 0;
int markcount = 0;
%}

%%
#(include|define){1}.*\n        {preprocessorcount++;}
0{1}[0-7]+      {octalnumbercount++;}
\-[0-9]+        {negativedecimalnumbercount++;}
[0-9]+  {positivedecimalnumbercount++;}
[\+\-\*\/\%\,]  {operatorcount++;}
(\&\&)|(\|\|)|\!        {operatorcount++;}
((\<)|(\>)|(\=\=)|(\!\=)|(\>\=)|(\<\=))(^(\<.*\>)) {operatorcount++;}
([a-z]+\+\+)|(\+\+[a-z]+)|(\-\-[a-z]+)|([a-z]+\-\-)     {wordcount++; operatorco                                                                                                             unt++;}
([a-z]+\*)|(\&[a-z]+)   {wordcount++; operatorcount++;}
\/\/.*\n        {commentcount++;}
\/\*(.|\n)*\*\/ {commentcount++;}
={1}    {equalcount++;}
\{{1}   {openbracecount++;}
\}{1}   {closebracecount++;}
p{2}    {wordcase1count++;}
e[a-zA-Z]*m     {wordcase2count++;}
[a-zA-Z]+       {wordcount++;}
.|\n    {markcount++;}
%%

int main() {
        yylex();
        printf("B911139 ¿Ã¡§¡¯\n");
        printf("preprocessor = %d\n", preprocessorcount);
        printf("octal number = %d\n", octalnumbercount);
        printf("negative decimal number = %d\n", negativedecimalnumbercount);
        printf("positive decimal number = %d\n", positivedecimalnumbercount);
        printf("operator = %d\n", operatorcount);
        printf("comment = %d\n", commentcount);
        printf("\'=\' = %d\n", equalcount);
        printf("\'{\' = %d\n", openbracecount);
        printf("\'}\' = %d\n", closebracecount);
        printf("wordcase1 = %d\n", wordcase1count);
        printf("wordcase2 = %d\n", wordcase2count);
        printf("word = %d\n", wordcount);
        printf("mark = %d\n", markcount);
        return 0;
}

int yywrap() {
        return 1;
}
