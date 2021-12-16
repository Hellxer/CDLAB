#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isNum( char buffer[])
{        int f =0;
 	for(int i=0; buffer[i]!='\0';i++)
        {
              if(isdigit(buffer[i]))
			f=1;
              else{ f=0;break;}
        }
return f;
}
                   
int isKeyword(char buffer[]){
char keywords[32][10] = {"auto","break","case","char","const","continue","default",
"do","double","else","include","stdio.h","float","for","goto",
"if","int","long","register","return","short","signed",
"sizeof","printf","struct","switch","typedef","union",
"unsigned","void","scanf","while"};
int i, flag = 0;
for(i = 0; i < 32; ++i){
if(strcmp(keywords[i], buffer) == 0){
flag = 1;
break;
}
}
return flag;
}
 
int main(){
char ch, buffer[15], operators[] = "+-*/%=";
char dummy;
FILE *fp;
int i,j=0;
fp = fopen("program.txt","r");
if(fp == NULL){
printf("error while opening the file\n");
exit(0);
}
int lno=3;
printf("\nLine No: 1..............\n");
while((ch = fgetc(fp)) != '\n')
{

	if (ch == '#') printf("%c is special charachter\n",ch);

	if(isalnum(ch) || ch == '.'){
   		buffer[j++] = ch;
  	}
   	else if((ch == '>' || ch == '<') && (j != 0)){

   		buffer[j] = '\0';
   		j = 0;
     
   	if(isKeyword(buffer) == 1)
   printf("%s is keyword\n", buffer);
   else
   {
      printf("%s not a  keyword\n", buffer);
   }
   }
}

printf("\nLine No: 2..............\n");
 

while((ch = fgetc(fp)) != EOF){
  
   if(ch == '\n')
      {printf("\nLine No: %i..............\n",lno);lno++;}

   if(ch == '{' || ch == '}')
      printf("%c is special charachter\n",ch);
   for(i = 0; i < 6; ++i){
   if(ch == operators[i]){
    if(ch == '=')
    {
        
	
	dummy = fgetc(fp);
        printf("%c\n",dummy);
	
	if(dummy == '=')printf("%c%c is relational operator\n",ch,dummy);
        else {printf("%c is  arithemetic operator\n", ch);fseek(fp,-1,SEEK_CUR);}
    }
    else{ printf("%c is arithemetic operator\n", ch); }
   }}
    
   if(ch == '>' || ch == '<' || ch == '!')
   {       
	dummy = fgetc(fp);
	if(dummy == '=')
	  printf("%c%c is relational operator\n",ch,dummy);
        else
	  {printf("%c is arithemetic operator\n", ch);fseek(fp,-1,SEEK_CUR);}
   }

   if(isalnum(ch)){
   buffer[j++] = ch;
   }
   else if((ch == ',' || ch == '\n' || ch == ' '|| ch == ';'|| ch == '(' || ch == ')') && (j != 0)){
   if(ch == ',' || ch == ';')printf("%c is separator\n", ch);
   buffer[j] = '\0';
   j = 0;
     
   if(isKeyword(buffer) == 1)
   printf("%s is keyword\n", buffer);
   else
   {
      if(isalpha(buffer[0]) || buffer[0] == '_') 
     	 printf("%s is indentifier\n", buffer);
      else if(isNum(buffer))  printf("%s is constant\n", buffer);
      else
	   printf("%s is not an indentifier\n", buffer);
   }
   }

	
  
}
fclose(fp);
return 0;
}
