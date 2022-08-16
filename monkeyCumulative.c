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
    int i,j;
    for(i=0; i<tSize-1; i++)
        curSentence[i] = possibleChars[rand()%27];
    curSentence[tSize-1] = '\0';

    //Verifichiamo se un discendente è uguale alla frase obiettivo
    printf("Frase obiettivo: \t%s\nFrase iniziale: \t%s\n\nFrasi figlie:\n",target,curSentence);
    int gens=0;
    int cpg = 100; //childs per generation
    char** childSentences = malloc(sizeof(char*)*cpg);
    for(i=0; i<cpg; i++){
        childSentences[i] = malloc(sizeof(char)*tSize);
        childSentences[i][tSize-1] = '\0';
    }
    Sleep(3000);

    while(1){
        //I discendenti sono una copia del padre... ...ma possono subire delle variazioni
        for(i=0; i<cpg; i++){
            for(j=0; j<tSize-1; j++){
                if(rand()%100 < 5) //mutazione di un carattere, 5% di possibilità
                    childSentences[i][j] = possibleChars[rand()%27];
                else
                    childSentences[i][j] = curSentence[j];
            }
        }

        //Verifichiamo quale figlio è più simile all'obiettivo
        int maxPoints = 0;
        int maxIdx = 0;
        int points;
        for(i=0; i<cpg; i++){
            points=0;
            for(j=0; j<tSize-1; j++){   //verifichiamo quanto è simile
                if(childSentences[i][j] == target[j])
                    points++;
            }
            if(points > maxPoints){     //per ora è il figlio più simile
                maxPoints = points;
                maxIdx = i;
            }
        }

        printf("figlio piu\' simile, della gen %d: \t%s\n", ++gens, childSentences[maxIdx]);

        //Trovato il figlio più simile, verifichiamo se è identico all'obiettivo
        //altrimenti eseguiamo di nuovo il ciclo partendo da lui come padre
        for(i=0; i<tSize-1; i++){
            if(target[i]!=childSentences[maxIdx][i])
                    break;
        }

        if(i==tSize-1){
            break; //trovata, usciamo dal while
        }
        else{   //non trovata, il figlio diventerà il nuovo genitore
            for(i=0; i<tSize-1; i++)
                curSentence[i] = childSentences[maxIdx][i];
        }

    }

    printf("\n\nLa frase obiettivo e\' stata trovata dopo %d generazioni.\n", gens);
    
    free(curSentence);
    for(i=0; i<cpg; i++)
        free(childSentences[i]);
    free(childSentences);
    return 0;
}