#define MAX_SIZE 1000
#define AR_TAM 30

void drawLine(int x0,int y0,int x1,int y1,int quadro[MAX_SIZE][MAX_SIZE],int cor);
//Desenha uma linha do vetor x0,y0 até o x1,y1 na matriz com a cor selecionada.

void floodFill(int x,int y,int quadro[MAX_SIZE][MAX_SIZE],int maxX,int maxY,int cor);
//De forma recursiva, preenche a matriz a partir do x,y até encontrar uma cor diferente da variável cor

void fill(int x,int y,int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int widthM,int heightM,int cor);
//Recebe as variáveis necessárias para a recursividade floodFill

void line(int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int cor);
//Recebe variáveis para usar o drawLine

void polygon(int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int cor);
//Recebe variáveis para usar o drawLine de forma a loopar desenhando um polígono

void drawCircle(int xc, int yc, int x, int y,int quadro[MAX_SIZE][MAX_SIZE],int cor);
//Desenha um círculo com centro xc,yc onde x e y são os atuais de onde o círculo está usando a cor selecionada.

void circleBres(int quadro[MAX_SIZE][MAX_SIZE],int *comN,char (*str)[AR_TAM],int cor);
//Recebe variáveis para usar a função drawCircle.

