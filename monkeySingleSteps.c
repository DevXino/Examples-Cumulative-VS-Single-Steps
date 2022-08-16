#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main(int argc, char argv[]){

    //Frase obiettivo
    char target[] = "SIAMO FATTI DELLA MATERIA DI CUI SON FATTI I SOGNI";
    int tSize = sizeof(target);

    //Frase generata a caso
    srand(time(NULL));
    char* curSentence = malloc(sizeof(char)*tSize);
    char possibleChars[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for(i=0; i<tSize-1; i++)
        curSentence[i] = possibleChars[rand()%27];
    curSentence[tSize-1] = '\0';

    //Verifichiamo se un discendente è uguale alla frase obiettivo
    printf("Frase obiettivo: \t%s\nFrase iniziale: \t%s\n\nFrasi figlie:\n",target,curSentence);
    int gens=0;
    Sleep(3000);
    while(1){
        for(i=0; i<tSize-1; i++){
            curSentence[i] = possibleChars[rand()%27];
        }
        printf("gen %d:\t", ++gens);
        for(i=0; i<tSize-1; i++){
            if(target[i]!=curSentence[i])
                break;
        }
        printf("%s\n",curSentence);

        if(i==tSize-1) break; //trovata
    }

    printf("\nLa frase obiettivo e\' stata trovata dopo %d generazioni.\n", gens);
    free(curSentence);
    return 0;
}