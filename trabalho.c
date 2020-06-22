#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "geometria.h"
#include "extras.h"
#define MAX_SIZE 1000
#define AR_TAM 30

int filtro;

typedef struct desenho_t{//Struct de um "desenho" com largura 
	int width;           //e altura junto com sua matriz para desenho
	int height;
	int corSel;
} desenho;

enum cores{Branco=0,Preto,Vermelho,Verde,Azul};//Enum para saber a cor selecionada

//Abre o arquivo selecionado e a passa para a matriz quadro
void open(desenho *imgd,int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM]){
	char* strFile = str[*comN+1];
	FILE *image =  fopen(strcat(strFile,".ppm"),"r");//Abre arquivo com nome
	*comN=*comN+2;

	if(image == NULL){
		printf("\nErro ao abrir arquivo\n");
		return;
	}
    

        int widthM = imgd->width;
	int heightM = imgd->height;

	if(widthM == 0 || heightM == 0){
		printf("Use o comando image para definir o tamanho primeiro\n");
		return;
	}	
	
	for(int i = 0;i < heightM;i++){
		for(int j = 0; j < widthM;j++){
		   char c[15];
           fgets(c,15,image);

           if(strcmp(c,"0 0 0\n")==0){//Verificar qual cor é e passar para a matriz
        	    quadro[i][j]= 1;
           }
           if(strcmp(c,"255 255 255\n")==0){
        	    quadro[i][j] = 0;
           }
           if(strcmp(c,"0 0 255\n")){
				quadro[i][j] = 2;
			}
			if(strcmp(c,"255 0 0\n")){
				quadro[i][j] = 3;
			}
			if(strcmp(c,"0 255 0\n")){
				quadro[i][j] = 4;
			}
			if(strcmp(c,"255 165 0\n")){
				quadro[i][j] = 5;
			}
		}
	}
    fclose(image);
}

//Passa a matriz para o arquivo, e o salva como .ppm
void save(desenho *imgd,int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM]){
    char* strFile = str[*comN+1];
    FILE *img;
	img = fopen(strcat(strFile,".ppm"),"w");//Cria/Sobescreve arquivo com nome desejado
	*comN+=2;

	if(img == NULL){//Caso não consiga abrir, retorne erro
		printf("Erro ao criar a imagem\n");
		return; 
	}

	int widthM = imgd->width;//Apenas para diminuir leitura
	int heightM = imgd->height;

	fprintf(img,"P3\n%d %d\n255\n",widthM,heightM);//Header ppm
	float r=1,g=1,b=1;
	int filtR=255,filtG=255,filtB=255,filtTotal=0;
	printf("%d",filtro);

	if(filtro==1){//Detecta qual filtro será usado
		filtR=80;
		filtG=80;
		filtB=80;
		filtTotal=0;
	}
	if(filtro==2){
		filtR=100;
		filtG=255;
		filtB=255;
		filtTotal=100;
	}
	if(filtro==3){
		filtR=0;
		filtB=0;
		filtG=0;
		filtTotal = 0;
	}

	for(int i = 0;i < heightM;i++){//Passagem da matriz para o arquivo
		for(int j = 0; j < widthM;j++){
			if(quadro[i][j] == 1){//Preto
				fprintf(img,"%d %d %d\n",(int)r*0,(int)g*0,(int)b*0);
			}
			if(quadro[i][j]==0){//Branco
				fprintf(img,"%d %d %d\n",(int)r*255,(int)g*255,(int)b*255);
			}
			if(quadro[i][j]==2){//Azul
				fprintf(img,"%d %d %d\n",(int)r*filtTotal,(int)g*0,(int)b*filtB);
			}
			if(quadro[i][j]==3){//Vermelho
				fprintf(img,"%d %d %d\n",(int)r*filtR,(int)g*0,(int)b*filtTotal);
			}
			if(quadro[i][j]==4){//Verde
				fprintf(img,"%d %d %d\n",(int)r*filtTotal,(int)g*filtG,(int)b*filtTotal);
			}
			if(quadro[i][j]==5){//Laranja
				fprintf(img,"%d %d %d\n",(int)r*filtR,(int)g*165,(int)b*filtTotal);
			}
			
		}
    }


	fclose(img);
}

//Seta a largura e altura máxima a ser utilizadas pela imagem.
void criarImagem(desenho * mainD,int quadro[MAX_SIZE][MAX_SIZE],char (*str)[AR_TAM],int *comN){//Cria uma imagem vazia com altura e largura definida
	int v1,v2;
	v1 = atoi(str[*comN+1]);
	v2 = atoi(str[*comN+2]);//Armazenar altura e largura da imagem
	*comN=*comN+3;
	mainD->width = v1;
	mainD->height = v2;
}

//Lê os comandos passados para ele
void receiveCommand(desenho *mainD,int quadro[MAX_SIZE][MAX_SIZE],char (*str)[AR_TAM],int *comN){
    if(strcmp(str[*comN],"image")==0){
    	criarImagem(mainD,quadro,str,comN);
    }

    if(strcmp(str[*comN],"save")==0){
    	save(mainD,quadro,comN,str);
    }

    if(strcmp(str[*comN],"open")==0){
       open(mainD,quadro,comN,str);
    }

    if(strcmp(str[*comN],"line")==0){
       line(quadro,comN,str,mainD->corSel);
    }

    if(strcmp(str[*comN],"polygon")==0){
       polygon(quadro,comN,str,mainD->corSel);
    }

    if(strcmp(str[*comN],"fill")==0){
       fill(0,0,quadro,comN,str,mainD->width,mainD->height,mainD->corSel);
       *comN+=3;
    }

    if(strcmp(str[*comN],"circle")==0){
       circleBres(quadro,comN,str,mainD->corSel);
       *comN+=4;
    }

    if(strcmp(str[*comN],"color")==0){
       mainD->corSel = color(mainD->corSel,comN,str);
       *comN+=2;
    }

    if(strcmp(str[*comN],"clear")==0){
       clear(quadro,mainD->width,mainD->height,mainD->corSel);
       *comN+=1;
    }

    if(strcmp(str[*comN],"filter")==0){
       filter(comN,str,&filtro);
       *comN+=2;
    }

    if(strcmp(str[*comN],"merge")==0){
       merge(quadro,comN,str,mainD->width,mainD->height);
       *comN+=4;
    }



}

int main(){
	desenho mainD;
	mainD.corSel=1;

	int quadro[MAX_SIZE][MAX_SIZE];

	printf("Nome do arquivo de comandos: ");
	char path[20];
	scanf(" %[^\n]",path);

    FILE *cmd;
	cmd = fopen(path,"r");//Abre o arquivo com os comandos

	if(cmd== NULL){//Caso não consiga abrir, retorne erro
		printf("Erro ao abrir arquivo\n");
	}
	

	char comandos[AR_TAM][AR_TAM];
    
    char c[30];
    int j=0;
	while(fgets(c,30,cmd)){
		c[strcspn(c,"\n")]=0;//Salva todos os comandos em uma matriz de comandos
        strcpy(comandos[j],c);
        j++;
    }
    fclose(cmd);

    int comN = 0;//Variável usada para saber qual linha estou lendo

    for(int i = 0;i<AR_TAM;i++){
    	receiveCommand(&mainD,quadro,comandos,&comN);//Loopar usando receiveCommand para ler os comandos
    }

    




	return 0;
}
