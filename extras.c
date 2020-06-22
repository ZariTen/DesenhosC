#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#define AR_TAM 30

int color(int corAtual,int *comN,char (*str)[AR_TAM]){
   corAtual = atoi(str[*comN+1]);
   return corAtual;

}

void clear(int quadro[MAX_SIZE][MAX_SIZE],int width,int height,int cor){
	for(int i = 0;i<height;i++){
		for(int j = 0;j<width;j++){
			quadro[i][j] = cor;
		}
	}
}

void filter(int *comN,char (*str)[AR_TAM],int * filtro){
    if(strcmp(str[*comN+1],"dark")==0){
      *filtro = 1;
    }
    if(strcmp(str[*comN+1],"retro")==0){
      *filtro = 2;
    }
    if(strcmp(str[*comN+1],"blackwhite")==0){
    	*filtro = 3;

    }


}

void merge(int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int w,int h){
  char* strFile = str[*comN+1];
  FILE *image =  fopen(strcat(strFile,".ppm"),"r");//Abre arquivo com nome
  
  int x,y;
  x = atoi(str[*comN+2]);
  y = atoi(str[*comN+3]);

  if(image == NULL){
    printf("\nErro ao abrir arquivo\n");
    return;
  }
  
  for(int i = 0;i < h;i++){
    for(int j = 0; j < w;j++){
      char c[15];
      fgets(c,15,image);
      if(strcmp(c,"255 255 255\n")==0){//Verificar qual cor é e passar para a matriz
        quadro[i+x][j+y]= quadro[i+x][j+y];
      }
      else if(strcmp(c,"0 0 0\n")==0){
        quadro[i+x][j+y]= 1;
      }
      else if(strcmp(c,"0 0 255\n")){
        quadro[i+x][j+y] = 2;
      }
      else if(strcmp(c,"255 0 0\n")){
        quadro[i+x][j+y] = 3;
      }
      else if(strcmp(c,"0 255 0\n")){
        quadro[i+x][j+y] = 4;
      }
      else if(strcmp(c,"255 165 0\n")){
        quadro[i+x][j+y] = 5;
      }
    }
  }
    fclose(image);

}
