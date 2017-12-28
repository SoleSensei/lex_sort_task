#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define size 8

char** form_str (char* str)
{
    char* save = str; //save pointer to string
    char** res = NULL;
    char* wd = NULL; //word
    int wdsize = 1; //current word size
    int next = 1; //to the next word
    int i,k;  //res[i] wd[k]
    /*char allow[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01234567890._$/";
    for () //allow symbols check*/
    i = k = 0;
    res = (char** ) malloc (strlen(str)*size);//res->block (size == 1)
    wd = (char*) malloc (1);//fake malloc for the first iteration, sadly without memory freed
    while (*str==' '||*str=='\t'||*str=='\n') ++str; //skip all spaces
    while (*str)
    {
        switch (*str){//|, ||, &, &&, ; , >, >>, <, (, ) - spec
        case ' ':case '\t':case '\n': next = 1; wd[k] = '\0'; //replace 'space' by 'eol'
         while (*str==' '||*str=='\t'||*str=='\n') ++str;   //skip all spaces
                continue;
        case ';': next = 1; wd[k] = '\0'; res[i++]=";"; str++; //macros
                continue;
        case '<': next = 1; wd[k] = '\0'; res[i++]="<"; str++;
                continue;
        case '(': next = 1; wd[k]= '\0'; res[i++]="("; str++;
                continue;
        case ')': next = 1; wd[k] = '\0'; res[i++]=")"; str++;
                continue;
        case '|': next = 1; wd[k] = '\0';
                if ( *++str=='|' )
                {  res[i++]="||"; str++; }
                else res[i++]="|";
                continue;
        case '>': next = 1; wd[k] = '\0';
                if ( *++str=='>')
                {  res[i++]=">>"; str++; }
                else res[i++]=">";
                continue;
        case '&': next = 1; wd[k]= '\0';
                if ( *++str=='&' )
                {  res[i++]="&&"; str++; }
                else res[i++]="&";
                continue;
        }

        if (next){
           res[i++] = wd = (char *) malloc (sizeof(char));
           wdsize = 1;
           k = next = 0;
        }

        wdsize++;
        wd = (char*) realloc (wd,wdsize);
        if (wd == NULL) {printf("wd realloc err\n");exit(1);}
        wd[k++] = *str++;
    }
  res[i] = NULL; // after last word pointer = NULL
  str = save; //return pointer to the start
  return res;

}

char* read_str (void)
{
    printf("stdin:  ");

    char* buf = NULL; // buffer
    char* str = NULL; // string left
    char* check = NULL; // check realloc on error
    char* el = NULL; //check fgets on EOF
    int count = 1;
    buf = (char *) malloc (size);
    if (buf)
    do
    {
       //if (feof(stdin)){ printf("eof"); exit(1);}
       el = fgets(buf,size,stdin);
       if (ferror(stdin)){ printf(" fgets err\n"); exit(1); }
       check = (char *) realloc(str,count*size);
       if (check == NULL) { printf(" relloc err\n"); free(str); exit(1); }
       str = check; //check -> cur string
       if (el) strncat(str,buf,size);
       count++;
    }while (el);
    else { printf(" malloc err\n"); exit(1); }
    free(buf);
  return str;
}

void  merge_str(char **strA, int first, int last, const int buf_size)
{
    int middle, left, right, i;
    char** strB = (char**) malloc (buf_size*size); //buff for strA
    middle=(first+last)/2;
    left=first;
    right=middle+1;
    for(i=first; i<=last; i++)
    if ((left<=middle) && ( (right>last) || strcmp(strA[left],strA[right])<0 ) )
    {
        strB[i]=strA[left];
        left++;
    }else{
        strB[i]=strA[right];
        right++;
    }
    for (i=first; i<=last; i++) strA[i]=strB[i]; //think here 
    free(strB);
}

void sort_str (char **strA, int first, int last, const int buf_size) //merge
{
    if (first<last)
    {
        sort_str(strA, first, (first+last)/2, buf_size); //sort left
        sort_str(strA, (first+last)/2+1, last, buf_size); //sort right
        merge_str(strA, first, last, buf_size); //merge two parts
    }

}

int out_str (char** s, char type)
{
    int i;
    if (type == 's') type = '\0';
    for(i = 0; s[i]; ++i){
        fputs( s[i], stdout );
        type ? printf(" ") : printf("\n");
    }
    printf("\n");

    return i; //words number
}

void freed(char **s)
{
    int i;
    for (i = 0; s[i]; ++i)
        free(s[i]);
    free(s);   
}
