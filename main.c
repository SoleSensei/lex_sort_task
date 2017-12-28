#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "./include/func.h"

int main(void)
{
    char* str = NULL;  // string stdin
    char** sstr = NULL; //string of string
    str = read_str();
    sstr = form_str(str);
    free(str);
    printf("\nformed: ");
    int length = out_str (sstr,'n'); //n - non-sorted | s - sorted
    sort_str(sstr,0,length-1,length);
    printf("sorted:\n");
    printf ("length = %d\n",length);
    out_str (sstr,'s');
    free(sstr);

    return 0;
}

