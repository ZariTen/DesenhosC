# Desenho Gráfico

Criação de imagens com desenhos por comandos.

# Como compilar
- gcc geometria.c extras.c -c
- gcc trabalho.c geometria.o extras.o -o nome
- ./nome

# Funcionamento do programa:
 - Abre arquivo contendo os comandos
 
 - Executa comandos

# Recebimento de comandos:
image\
200\
200

# Cores disponíveis:
Branco   - 0

Preto    - 1

Azul     - 2

Vermelho - 3

Verde    - 4

# Lista de comandos:
**image(x,y) - Cria uma nova “imagem”, com a largura x e altura y.**\
image\
200\
200

**color - Muda a cor atual para uma cor especificada.**\
color\
1

**clear(cor) - Limpa a imagem, setando todos os pixels para a cor especificada.**\
clear\
3

**circle(x,y,r) - Desenha um círculo com centro x,y e raio r.**\
circle\
200\
200\
3

**polygon(linhas,[LOOP]x,y) - Desenha um polígono delimitado por uma lista de pontos.**\
polygon\
2\
20\
20\
40\
40

**fill(x,y) - Preenche um espaço a partir de x,y.**\
fill\
500\
300

**save(nome .ppm) - Salva a imagem atual em um arquivo usando o formato ppm.**\
save\
salvamento

**open(nome .ppm) - Abre uma imagem no formato ppm e carrega essa imagem no programa.**\
open\
salvamento

# Extras:
**filter(filtro) - Coloca um filtro na imagem, mudando as cores.**\
filtro\
dark

**merge(.ppm,x,y) - Merge a imagem na matriz na posição x,y.**\
merge\
salvamento\
0\
0

# Filtros:
-dark: deixa as cores mais escuras

-retro: cores azuls ficam roxas, vermelhas azuladas.

-blackwhite: cores escuras viram pretas, cores claras brancas.


