#include <stdlib.h>

int compara(char* str, char* str2){
    int i;
    for (i=0;str[i]!='\0' && str2!='\0';i++){
        if (str[i]>str2[i])
            return -1;
        else
            return 1;
    }
    if(str[i]<str2[i])
        return -1;
    else if (str[i]>str2[i])
        return 1;
    else
        return 0;
}

void strcat(char *str, char *str2)
{
    int i,tam=strlen(str),tam2=strlen(str2),j=0;
    for (i=tam;i<tam+tam2;i++)
    {
        str[i]=str2[j];
        j++;
    }
    str[i]='\0';
}

int strlen(char *str)
{
    int i;
    for (i=0;str[i]!='\0';i++)
    {

    }
    return i;
}