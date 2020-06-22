#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#define AR_TAM 30

int color(int corAtual,int *comN,char (*str)[AR_TAM]);
//Altera a int corAtual que é usada para desenhar as cores das linhas.

void clear(int quadro[MAX_SIZE][MAX_SIZE],int width,int height,int cor);
//Loop pela matriz inteira setando seus valores para cor.

void filter(int *comN,char (*str)[AR_TAM],int * filtro);
//Altera o int filtro que serve para identificar qual filtro será usado.

void merge(int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int w,int h);
//Abre o arquivo selecionado e o passa para a matriz quadro de altura h e largura w.
