#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>
#include <dos.h>
#include <time.h>

#define COLUNAS 11
#define LINHAS  7


typedef struct jogador JOGADOR;
struct jogador {
    char nome [20];
    int pontosjogador;
    int nivelatual;
};

JOGADOR jogadores;

typedef struct score SCOREBOARD;
struct score {
    char nome [20];
    int pontosjogador;
};

SCOREBOARD rank[10] = {0};
SCOREBOARD aux_rank[100];

FILE *mapacontinuar;
FILE *dadosjogador;

int pontos = 0; // DECLARA PONTOS COMO GLOBAL
int pontosnivel = 0;
int pontosmax = 350;
char mapa[LINHAS][COLUNAS]; // DECLARA  OS MAPAS COMO GLOBAL
char mapamaior[22][44];
int njogadores = -1;
int combinacoes = 0;
int n_combinacoes1 = 0, n_combinacoes2=0, n_combinacoes3=0;
int continua = 0, auxcontinua = 0;
int x=0, y=0;
int x2=0, y2=0;


void tabuleiro(int selecao);

void tabuleiro_escalonado(int selecao);

void mexe_peca(int *x, int *y, int selecao, int *x2, int *y2);

void troca_peca(int x, int y, int x2, int y2);

int menu (void);

void comojogar(void);

void descepecas(void);

void conferepontos(int *continua);

void peca_aleatoria(void);

void ranking(void);

void escrever_arquivo(SCOREBOARD rank[]);

int ler_arquivo(SCOREBOARD aux_rank[100]);

int continuar(int selecao);

void jogo(int selecao);

void reticencias(int linha, int coluna);

//FUNCAO PRINCIPAL
int main(){
    system("mode 100, 40");
    textbackground(BLACK);
    textcolor(WHITE);

    int op;
    int i = 0, j = 0;
    for (i = 0; i<22; i++){ //INICIALIZA O TABULEIRO COM ESPACOS EM TODAS AS POSICOES
        for (j = 0; j<44; j++){
            mapamaior[i][j] = ' ';
        }
    }

    do{
        op = menu();

        switch(op){
            case 3:
                    jogo(1);
                    escrever_arquivo(rank);
            break;
            case 5:
                    if(continuar(2) != 1){
                        jogo(2);
                        escrever_arquivo(rank);
                    } else {
                        gotoxy(35, 10);
                        printf("Nao existe partida em andamento!");
                        Sleep(4000);
                        clrscr();
                    }
            break;
            case 7:
                    ranking();
            break;
            case 9: comojogar();
            break;
            default:
                    gotoxy(40, 10);
                    printf("Ate logo!!\n\n");
                     Sleep(2000);
            break;
        }
    }while (op != 11);


    textbackground(BLACK);
    textcolor(WHITE);

    return 0;
}

int menu (void){

    int enter = 0;
    int cordx;
    int cordy;

    cputsxy(36, 1, "C O M B I N A  3");

    cputsxy(38, 3, "[NOVO JOGO]");
    cputsxy(38, 5, "[CONTINUAR]");
    cputsxy(38, 7, "[RANKING]");
    cputsxy(38, 9, "[COMO JOGAR]");
    cputsxy(38, 11, "[SAIR DO JOGO]");

    cordx = 36;
    cordy = 3;

    while(enter != 13){
        if (GetKeyState (VK_UP) & 0x80){
            if (cordy-1 >= 3){
                cordy-=2;
                cputsxy(cordx, cordy+2, "  ");
            }
        } else if (GetKeyState (VK_DOWN) & 0x80){
            if (cordy+1 <= 11){
                cordy+=2;
                cputsxy(cordx, cordy-2, "  ");
            }
        }
            cputsxy(cordx, cordy, "=>");
            enter = getch();
            Sleep(70);
    }

    system("CLS");

    return cordy;
}

void tabuleiro_escalonado(int selecao){

    int i=0, j=0, k=0, l=0;
    int x=0, y=0;

    if (selecao == 1){
        for (i=0; i<LINHAS; i++) // pra botar os caracteres do tabuleiro no escalonado
        {
            k += 2;
            for (j=0; j<COLUNAS; j++)
            {
                mapamaior[k][l] = mapa[i][j];
                l += 4;
            }

        }
    }

    for (i=0; i<22; i++) // ESCALONA AS BORDAS
    {
        for (j=0; j<42; j++)
        {
            switch(mapamaior[i][j])
            {
            case 'x' :
                if(i>=2 && i<=19 && j>=0 && j<=2 || i>=2 && i<=19 && j>=39 && j<=41){
                    mapamaior[i+1][j] = 'x';
                    mapamaior[i+2][j] = 'x';
                }
                if (i>=2 && i<=3 && j>=0 && j<=39 || i>=20 && i<=21 && j>=0 && j<=39){
                    mapamaior[i][j+1] = 'x';
                    mapamaior[i][j+2] = 'x';
                }
            break;
            }
        }
    }


    for (i=2; i<22; i+=3) //ESCALONA OS CARACTERES
    {
        for (j=0; j<42; j+=2)
        {
            switch(mapamaior[i][j]){
            case 'R' :
                mapamaior[i][j+1] = 'R';
                mapamaior[i+1][j] = 'R';
                mapamaior[i+1][j+1] = 'R';
                break;
            case 'G' :
                mapamaior[i][j+1] = 'G';
                mapamaior[i+1][j] = 'G';
                mapamaior[i+1][j+1] = 'G';
                break;
            case 'B' :
                mapamaior[i][j+1] = 'B';
                mapamaior[i+1][j] = 'B';
                mapamaior[i+1][j+1] = 'B';
                break;
            case 'C' :
                mapamaior[i][j+1] = 'C';
                mapamaior[i+1][j] = 'C';
                mapamaior[i+1][j+1] = 'C';
                break;
            case 'P' :
                mapamaior[i][j+1] = 'P';
                mapamaior[i+1][j] = 'P';
                mapamaior[i+1][j+1] = 'P';
                break;
            }
        }
    }

    x = 24;
    y=7;

    gotoxy(x, y);

    for (i=2; i<22; i++) // PRINTA O MAPA ESCALONADO
    {
        for (j=0; j<42; j++)
        {
            switch(mapamaior[i][j]){
            case 'x' :
                textcolor(YELLOW);
                textbackground(YELLOW);
                break;
            case 'R' :
                textcolor(RED);
                textbackground(RED);
                break;
            case 'G' :
                textcolor(GREEN);
                textbackground(GREEN);
                break;
            case 'B' :
                textcolor(BLUE);
                textbackground(BLUE);
                break;
            case 'C' :
                textcolor(CYAN);
                textbackground(CYAN);
                break;
            case 'P' :
                textcolor(BLACK);
                textbackground(BLACK);
                Sleep(0.97);
                break;
            default:
                textcolor(WHITE);
                textbackground(BLACK);
            }

            printf("%c", mapamaior[i][j]);
        }
        y++;
        gotoxy(x,y);
    }

    textcolor(WHITE);
    textbackground(BLACK);

    gotoxy(69,3);
    printf("%d", pontos);

    gotoxy(30,5);
    if(jogadores.nivelatual == 1){
        if((n_combinacoes1-combinacoes) < 0)
            printf("Combinacoes necessarias: 0");
        else {
            printf("Combinacoes necessarias: %d", n_combinacoes1-combinacoes);
            printf(" ");
        }
    }else if (jogadores.nivelatual == 2){
        if((n_combinacoes2-combinacoes) < 0)
            printf("Combinacoes necessarias: 0");
        else {
            printf("Combinacoes necessarias: %d", n_combinacoes2-combinacoes);
            printf(" ");
        }
    }else if (jogadores.nivelatual == 3){
        if((n_combinacoes3-combinacoes) < 0)
            printf("Combinacoes necessarias: 0");
        else {
            printf("Combinacoes necessarias: %d", n_combinacoes3-combinacoes);
            printf(" ");
        }
    }
}

void tabuleiro(int selecao){

    char mapaaux[COLUNAS];
    FILE *file;
    int i=0, j=0;
    int aux=0;
    int nivel = 0;

    if(selecao == 1)
        nivel = 0;
    else
        nivel = jogadores.nivelatual;

    file = fopen("nivel-0.txt", "r"); //LE O NUMERO DE COMBINACOES NECESSARIAS PARA CADA NIVEL
    fscanf(file,"%d", &n_combinacoes1);
    fclose(file);
    file = fopen("nivel-1.txt", "r");
    fscanf(file,"%d", &n_combinacoes2);
    fclose(file);
    file = fopen("nivel-2.txt", "r");
    fscanf(file,"%d", &n_combinacoes3);
    fclose(file);

    if(selecao == 1){
        if(combinacoes < n_combinacoes1){
            nivel = 1;
            pontosnivel = n_combinacoes1*10;
            file = fopen("nivel-0.txt", "r");

            njogadores++;
            cputsxy(36, 1, "C O M B I N A  3");
            cputsxy(28, 5, "NOME DO JOGADOR: ");
            gets(jogadores.nome);
            jogadores.pontosjogador = 0;
            clrscr();
        } else if (combinacoes < n_combinacoes2){
            nivel = 2;
            pontosnivel = n_combinacoes2*10;
            file = fopen("nivel-1.txt", "r");
            pontos = 0;
            combinacoes = 0;
        } else if (combinacoes < n_combinacoes3){
            nivel = 3;
            file = fopen("nivel-2.txt", "r");
            pontosnivel = n_combinacoes3*10;
            pontos = 0;
            combinacoes = 0;
        }
    } else {
        if(nivel == 1){
            pontosnivel = n_combinacoes1*10;
        } else if (nivel == 2){
            pontosnivel = n_combinacoes2*10;
        } else if (nivel == 3){
            pontosnivel = n_combinacoes3*10;
        }
    }

    pontosmax = n_combinacoes3*10;

    if (selecao == 1){
        jogadores.nivelatual = nivel;

        while(fgets(mapaaux, COLUNAS+1, file) != NULL){
            for (j=0; j<COLUNAS; j++){
                if (mapaaux[j] == '\n' || aux > 0){
                    aux++;
                    if(mapaaux[j] == '\n' && aux > 1){
                        i++;
                    }
                    mapa[i][j] = mapaaux[j];
                }
            }
        }
        fclose(file);
    }
    //CABECALHO//

    if(selecao == 1){
        if(jogadores.nivelatual == 1){
            gotoxy(35, 14);
            printf("INICIANDO O JOGO!");
            Sleep(3000);
            clrscr();
        } else {
            gotoxy(30, 14);
            printf("AVANCANDO PARA O PROXIMO NIVEL");
            reticencias(60, 14);
            clrscr();
        }
    } else {
            gotoxy(34, 14);
            printf("VOLTANDO AO JOGO");
            reticencias(50, 14);
            clrscr();
    }
    for (i=0; i<10; i++){
        gotoxy(40, 11);
        Sleep(200);
        printf("NIVEL : %d", jogadores.nivelatual);
        Sleep(200);
        clrscr();
    }
    cputsxy(36, 1, "C O M B I N A  3");
    cputsxy(16,3,"JOGADOR: ");
    cputsxy(25,3, jogadores.nome);
    gotoxy(40,3);
    printf("NIVEL : %d", jogadores.nivelatual);
    cputsxy(58,3,"PONTUACAO: ");
}

void mexe_peca(int *x, int *y, int selecao, int *x2, int *y2){

    int i=0, j=0;
    int aux = 0, aux2 = 0;
    int enter = 0;

    if (selecao == 2){
        *x = *x2;
        *y = *y2;
    } else {
        *x = 42;
        *y = 14;
    }

    while(enter != 13){
        if (GetKeyState (VK_RIGHT) & 0x80){
            aux++;
            if (*x+4 < 62){
                *x+=4;
               for(i=1;i<=4;i++) {
                    for(j=1;j<=4;j++) {
                    if(!( (*x+2) == *x+i && (*y+2)== *y+j || (*x+3) == *x+i && (*y+2)== *y+j || (*x+2) == *x+i && (*y+3)== *y+j || (*x+3) == *x+i && (*y+3)== *y+j) ){
                        textbackground(BLACK);
                        textcolor(BLACK);
                        putchxy(*x+i-4, *y+j, ' ');
                    }
                    }
                }
            }
        } else if (GetKeyState (VK_LEFT) & 0x80){
            aux++;
           if (*x-1 > 27){
                *x-=4;
               for(i=1;i<=4;i++) {
                    for(j=1;j<=4;j++) {
                    if(!( (*x+2) == *x+i && (*y+2)== *y+j || (*x+3) == *x+i && (*y+2)== *y+j || (*x+2) == *x+i && (*y+3)== *y+j || (*x+3) == *x+i && (*y+3)== *y+j) ){
                        textbackground(BLACK);
                        textcolor(BLACK);
                        putchxy(*x+i+4, *y+j, ' ');
                    }
                }
                }
           }
        } else if (GetKeyState (VK_UP) & 0x80){
            aux++;
           if (*y-1 > 9){
                *y-=3;
               for(i=1;i<=4;i++) {
                    for(j=1;j<=4;j++) {
                    if(!( (*x+2) == *x+i && (*y+2)== *y+j || (*x+3) == *x+i && (*y+2)== *y+j || (*x+2) == *x+i && (*y+3)== *y+j || (*x+3) == *x+i && (*y+3)== *y+j) ){
                        textbackground(BLACK);
                        textcolor(BLACK);
                        putchxy(*x+i, *y+j+3, ' ');
                    }
                }
                }
            }
        } else if (GetKeyState (VK_DOWN) & 0x80){
            aux++;
            if (*y+4 < 24){
                *y+=3;
                for(i=1;i<=4;i++) {
                    for(j=1;j<=4;j++) {
                    if(!( (*x+2) == *x+i && (*y+2)== *y+j || (*x+3) == *x+i && (*y+2)== *y+j || (*x+2) == *x+i && (*y+3)== *y+j || (*x+3) == *x+i && (*y+3)== *y+j) ){
                        textbackground(BLACK);
                        textcolor(BLACK);
                        putchxy(*x+i, *y+j-3, ' ');
                    }
                }
                }
            }
        }

    if (selecao == 2){
        for(i=1;i<=4;i++) {
            for(j=1;j<=4;j++) {
                if(!( (*x+2) == *x+i && (*y+2)== *y+j || (*x+3) == *x+i && (*y+2)== *y+j || (*x+2) == *x+i && (*y+3)== *y+j || (*x+3) == *x+i && (*y+3)== *y+j) ){
                    textcolor(WHITE);
                    textbackground(WHITE);
                    putchxy(*x2+i, *y2+j, ' ');
                }
            }
        }
    }

    if(aux == aux2){
        aux2++;
        for(i=1;i<=4;i++) {
            for(j=1;j<=4;j++) {
                if(!( (*x+2) == *x+i && (*y+2)== *y+j || (*x+3) == *x+i && (*y+2)== *y+j || (*x+2) == *x+i && (*y+3)== *y+j || (*x+3) == *x+i && (*y+3)== *y+j) ){
                    textcolor(WHITE);
                    textbackground(WHITE);
                    putchxy(*x+i, *y+j, ' ');
                }
            }
        }
    }

    enter = getch();
    Sleep(70);
    }


    if(selecao == 2){
        for(i=1;i<=4;i++) {
            for(j=1;j<=4;j++) {
                if(!( (*x+2) == *x+i && (*y+2)== *y+j || (*x+3) == *x+i && (*y+2)== *y+j || (*x+2) == *x+i && (*y+3)== *y+j || (*x+3) == *x+i && (*y+3)== *y+j) ){
                    textbackground(BLACK);
                    textcolor(BLACK);
                    putchxy(*x+i, *y+j, ' ');
                    putchxy(*x2+i, *y2+j, ' ');
                }
            }
        }
    }

    textcolor(WHITE);
    textbackground(BLACK);
}

void troca_peca(int x, int y, int x2, int y2){
    char aux[2][2];
    int i=0, j=0;
    int flag = 0;

    x = x - 22;
    y = y - 3;
    x2= x2 - 22;
    y2 = y2 - 3;

    for(i=0;i<2;i++) {
        for(j=0;j<2;j++) {
            aux[i][j] = mapamaior[y+i][x+j];

            mapamaior[y+i][x+j] = mapamaior[y2+i][x2+j];
            mapamaior[y2+i][x2+j] = aux[i][j];
        }
    }
}

void comojogar(void){
    int esc = 0;

    while(esc != 27) {
        cputsxy(32,3,"O JOGO CONSISTE ");
        cputsxy(25,4,"EM JUNTAR 3 PEÇAS DA MESMA COR");
        cputsxy(25,5,"NA HORIZONTAL OU NA VERTICAL");
        cputsxy(25,6,"ASSSIM QUE COMPLETAR O OBJETIVO");
        cputsxy(29,7,"IRA PARA O PROXIMO NIVEL");
        cputsxy(29,8,"LEMBRE-SE : DIVIRTA-SE");
        cputsxy(50,9,"ESC P/ RETORNAR");

        esc=getch();
   }
    clrscr();
    main();
}

void descepecas(void){
    char aux[2][2];
    int i=0, j=0, k=0, l=0;


    for(k=0;k<2;k++) {
        for(l=0;l<2;l++) {
            for(i=8;i<20;i++) {
                for(j=4;j<37;j++) {
                    if(mapamaior[i][j] == 'P'){
                        aux[k][l] = mapamaior[i][j];

                        mapamaior[i][j] = mapamaior[i-3][j];
                        mapamaior[i-3][j] = aux[k][l];

                    }
                }
            }
        }
    }
    Sleep(100);
    tabuleiro_escalonado(2);
}

void conferepontos(int *continua){
    int i=0, j=0;
    int flag = 0;

    for(i=5;i<19;i++) {
        for(j=4;j<38;j++) {
                if(mapamaior[i][j]==mapamaior[i][j+4] && mapamaior[i][j+4]==mapamaior[i][j+8] && mapamaior[i][j] != ' ' && mapamaior[i][j] != 'P'){ //testando linhas
                        mapamaior[i][j] = 'P';
                        mapamaior[i][j+4] = 'P';
                        mapamaior[i][j+8] = 'P';

                        flag ++;
                } else if(mapamaior[i][j]==mapamaior[i+3][j] && mapamaior[i+3][j]==mapamaior[i+6][j] && mapamaior[i][j] != ' ' && mapamaior[i][j] != 'P'){ //testando colunas
                        mapamaior[i][j] = 'P';
                        mapamaior[i+3][j] = 'P';
                        mapamaior[i+6][j] = 'P';

                        flag ++;
                }
        }
    }

    flag /= 4;

    pontos += flag*10;
    combinacoes = pontos/10;
    jogadores.pontosjogador += flag*10;
    gotoxy(1, 26);

    if(flag > 0){
        *continua = 1;
    } else {
        *continua = 0;
    }
    Sleep(100);
}

void peca_aleatoria(void){
    srand((unsigned)time(NULL));
    int i = 0, j = 0;
    int peca_aux = 0, aux = 0;
    char peca_asc;
    int valores[] = {66, 67, 71, 82};//Valores
    int num = sizeof valores / sizeof * valores;



    for(i=2;i<20;i++) {
        for(j=2;j<37;j++) {
            if(mapamaior[i][j] == 'P'){
            peca_asc = (char) valores[rand() % num];

            mapamaior[i][j] = peca_asc;
            mapamaior[i][j+1] = peca_asc;
            mapamaior[i+1][j] = peca_asc;
            mapamaior[i+1][j+1] = peca_asc;
            }
        }
    }
}

void ranking(){

    int len_vet = ler_arquivo(aux_rank);
	int i;

    clrscr();
    if(len_vet != 0){
        cputsxy(39, 2, "RANKING");
        for(i = 0; i < len_vet; i++) {
            gotoxy(25, 4+i*2);
            printf("[%d]", i+1);
            gotoxy(30, 4+i*2);
            printf("%s", aux_rank[i].nome);
            gotoxy(50, 4+i*2);
            printf("%d pts", aux_rank[i].pontosjogador);
        }

    gotoxy(30, 25);
    printf("Pressione qualquer tecla para sair");
	getch();
    } else {
        gotoxy(35, 15);
        printf("Nenhum jogador no ranking ainda!!");
        gotoxy(35, 16);
        printf("Voltando ao menu principal");
        reticencias(61, 16);
    }
	clrscr();
}

void escrever_arquivo(SCOREBOARD rank[]){
    int i = 0, j = 0, aux = 0;
    FILE *arq_ranking;
    SCOREBOARD maioratual;

    if ((arq_ranking = fopen("ranking.bin", "rb")) == NULL){
        rewind(arq_ranking);
        strcpy(rank[0].nome,jogadores.nome);
        rank[0].pontosjogador = jogadores.pontosjogador;
        maioratual = rank[0];
    } else {
        rewind(arq_ranking);
		SCOREBOARD p;
		while(!feof(arq_ranking)){
			if(fread(&p, sizeof(SCOREBOARD), 1, arq_ranking) == 1){
				rank[i] = p;
                i++;
			}
		}
    }

    if((i == 10 && rank[i-1].pontosjogador < jogadores.pontosjogador) || i<10){

        strcpy(rank[i-1].nome,jogadores.nome);
        rank[i-1].pontosjogador = jogadores.pontosjogador;

        for (i = 0; i < 10; i++){
            maioratual = rank[i];
            for (j=i; (j>0) && (maioratual.pontosjogador > rank[j-1].pontosjogador); j--){
                rank[j] = rank[j-1];
            }
                rank[j] = maioratual;
        }

        fclose(arq_ranking);

        arq_ranking = fopen("ranking.bin", "wb");

        if(arq_ranking != NULL){
            for(i = 0; i < 10; i++){ // escreve cada elemento do vetor no arquivo
                if(rank[i].pontosjogador != 0){
                    fwrite(&rank[i], sizeof(SCOREBOARD), 1, arq_ranking);
                }
            }
            fclose(arq_ranking); // aborta o programa
        } else{
            printf("\nErro ao abrir o arquivo para leitura!\n");
        }
    }

}

int ler_arquivo(SCOREBOARD aux_rank[100]){
	// abre o arquivo para leitura
	FILE *arq_ranking = fopen("ranking.bin", "rb");
    int i = 0;

	if(arq_ranking != NULL){
	    rewind(arq_ranking);

		SCOREBOARD p;
		while(!feof(arq_ranking)){
			if(fread(&p, sizeof(SCOREBOARD), 1, arq_ranking) == 1){
				aux_rank[i] = p;
                i++;
			}
		}
		fclose(arq_ranking); // fecha o arquivo
		return i;
	} else {
	    gotoxy(35, 15);
		printf("Nenhum jogador no ranking ainda!!");
		return 0;
	}
}

int continuar(int selecao){

    int i=2, j=0;
    char mapaaux[44];
    int aux;
    int valido = 0;

    if(selecao == 1){
        if((mapacontinuar = fopen("mapacontinuar.txt", "w")) == NULL){
            printf("Erro na abertura do arquivo mapacontinuar.txt");
        } else {
            for (i=2; i<22; i++){
                for (j=0; j<42; j++){
                fprintf(mapacontinuar, "%c", mapamaior[i][j]);
                }
            fprintf(mapacontinuar, "\n");
            }
        }
        fclose(mapacontinuar);

        if((dadosjogador = fopen("dadosjogador.txt", "w")) == NULL){
            printf("Erro na abertura do arquivo dadosjogador.txt");
        } else {
            rewind(dadosjogador);
            fprintf(dadosjogador, "%s\n", jogadores.nome);
            fprintf(dadosjogador, "%d\n%d\n%d", jogadores.nivelatual, jogadores.pontosjogador, pontos);
        }
        fclose(dadosjogador);

    } else {
        if((dadosjogador = fopen("dadosjogador.txt", "r")) == NULL){
                valido = 1;
        } else {
            if((mapacontinuar = fopen("mapacontinuar.txt", "r")) == NULL){
                    valido = 1;
            printf("Erro na leitura do arquivo mapacontinuar.txt");
            } else {
                rewind(dadosjogador);
                fseek(dadosjogador, ftell(dadosjogador), SEEK_SET);
                fgets(jogadores.nome, 20, dadosjogador);
                jogadores.nome[(strlen(jogadores.nome)-1)] = '\0';

                fseek(dadosjogador, ftell(dadosjogador), SEEK_SET);
                fscanf(dadosjogador, "%d", &jogadores.nivelatual);

                fseek(dadosjogador, ftell(dadosjogador), SEEK_SET);
                fscanf(dadosjogador, "%d", &jogadores.pontosjogador);

                fseek(dadosjogador, ftell(dadosjogador), SEEK_SET);
                fscanf(dadosjogador, "%d", &pontos);

                combinacoes = pontos/10;

                fclose(dadosjogador);
            }

            while(fgets(mapaaux, 45, mapacontinuar) != NULL){
                for (j=0; j<44; j++){

                    if(mapaaux[j] == '\n'){
                        i++;
                    }

                    mapamaior[i][j] = mapaaux[j];
                }
            }
            fclose(mapacontinuar);
        }

    }
    return valido;
}

void jogo(int selecao){ //RODA O JOGO

    if(selecao == 1){
        pontos = 0;
        jogadores.nivelatual = 0;
        combinacoes = 0;
    }

    while(pontos < pontosmax){
        if(selecao == 1){
            tabuleiro(1);
            tabuleiro_escalonado(1);
        } else if(selecao == 2) {
            tabuleiro(2);
            tabuleiro_escalonado(2);
        }
        continuar(1);
        while(pontos < pontosnivel){
            mexe_peca(&x, &y, 1, &x2, &y2);
            x2 = x;
            y2 = y;
            mexe_peca(&x, &y, 2, &x2, &y2);
            troca_peca(x, y, x2, y2);
            continuar(1);
            do{
                continuar(1);
                tabuleiro_escalonado(2);
                conferepontos(&continua);
                descepecas();
                peca_aleatoria();
                Sleep(50);
            }while(continua == 1);
        }
        Sleep(3000);
        clrscr();
        selecao = 1;
    }
    clrscr();
    gotoxy(35, 10);
    printf("PARABENS, VOCE VENCEU!!");
    gotoxy(41, 11);
    printf("%d PONTOS", jogadores.pontosjogador);
    Sleep(5000);
    clrscr();
    remove("mapacontinuar.txt");
    remove("dadosjogador.txt");
}

void reticencias(int linha, int coluna){
    int i;

    for (i=0; i<3; i++){
        gotoxy(linha, coluna);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        printf(".");
        Sleep(500);
        cputsxy(linha, coluna, "   ");
        Sleep(500);
    }
}
