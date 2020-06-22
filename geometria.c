#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#define AR_TAM 30

void drawLine(int x0,int y0,int x1,int y1,int quadro[MAX_SIZE][MAX_SIZE],int cor){ //Função principal para desenhar linhas
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;//Algoritmo de Bresenham
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;//https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    quadro[x0][y0] = cor;
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void floodFill(int x,int y,int quadro[MAX_SIZE][MAX_SIZE],int maxX,int maxY,int cor){//Algorítmo para fill
                                                                             //https://www.geeksforgeeks.org/flood-fill-algorithm-using-c-graphics/
	if(quadro[x][y]==cor)
		return;

	if (x >= 0 && y >= 0 && x <= maxX  && y <= maxY) { //Recursividade para preencher
        quadro[x][y] = cor;
        
        floodFill(x + 1, y, quadro,maxX,maxY,cor); 
        
        floodFill(x - 1, y, quadro,maxX,maxY,cor); 

        floodFill(x, y + 1, quadro,maxX,maxY,cor); 
        
        floodFill(x, y - 1, quadro,maxX,maxY,cor);
    } 
}

void fill(int x,int y,int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int widthM,int heightM,int cor){

	if(x ==0&&y==0){
	x = atoi(str[*comN+1]);
	y = atoi(str[*comN+2]);
	}
	floodFill(x,y,quadro,widthM,heightM,cor);//Chamar fill para recursividade


}

void line(int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int cor){
	int x1,y1,x2,y2;
	char *ptr;
	x1 = atoi(str[*comN+1]);
	y1= atoi(str[*comN+2]);
	x2 = atoi(str[*comN+3]);
	y2 = atoi(str[*comN+4]);
	*comN=*comN+5;

	drawLine(x1,y1,x2,y2,quadro,cor);
}

void polygon(int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int cor){
    int V,Vo;
    int i = 0;
    int p_atual[] = {0,0};
    int p_ant[] = {0,0};
    int p_primeiro[] = {0,0};
	V=atoi(str[*comN+1]);
	Vo=V;
	while(V>0){
		int x,y;
		x=atoi(str[*comN+2+i]);
		i++;
		y=atoi(str[*comN+2+i]);
		i++;
		if(p_primeiro[0] == 0 && p_primeiro[1] ==0){
			p_primeiro[0] = x;
		    p_primeiro[1] = y;
		}
		if(V%2!=0){
		   p_atual[0] = x;
		   p_atual[1] = y;
		}
		else{
		   p_ant[0] = x;
		   p_ant[1] = y;
		}
		
		if(p_ant[0]!=0&&p_ant[1]!=0&&p_atual[0]!=0&&p_atual[1]!=0){
		drawLine(p_ant[0],p_ant[1],p_atual[0],p_atual[1],quadro,cor);
	    }
		V--;
	}
	drawLine(p_atual[0],p_atual[1],p_primeiro[0],p_primeiro[1],quadro,cor);
	*comN=*comN+Vo+i-1;
}



void drawCircle(int xc, int yc, int x, int y,int quadro[MAX_SIZE][MAX_SIZE],int cor) 
{ 
    quadro[xc+x][yc+y] = cor; 
    quadro[xc-x][yc+y] = cor; 
    quadro[xc+x][yc-y] = cor; 
    quadro[xc-x][yc-y] = cor; 
    quadro[xc+y][yc+x] = cor; 
    quadro[xc-y][yc+x] = cor; 
    quadro[xc+y][yc-x] = cor; 
    quadro[xc-y][yc-x] = cor; 
} 

void circleBres(int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int cor) 
{ 
	int xc = atoi(str[*comN+1]); //Algorítmo de Bresenham para desenho de círculo
	int yc = atoi(str[*comN+2]); //https://www.geeksforgeeks.org/bresenhams-circle-drawing-algorithm/
	int r = atoi(str[*comN+3]);
    int x = 0, y = r; 
    int d = 3 - 2 * r; 
    drawCircle(xc, yc, x, y,quadro,cor); 
    while (y >= x) 
    {         
        x++; 
  
        if (d > 0) 
        { 
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 
        drawCircle(xc, yc, x, y,quadro,cor); 
    } 
} 
