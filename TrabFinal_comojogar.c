#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>
#include <dos.h>

#define COLUNAS 11
#define LINHAS  7
// #define ESC 27

void tabuleiro();

void tabuleiro_escalonado(char mapa[][COLUNAS], char mapamaior[][44], int selecao);

void mexe_peca(char mapa[][COLUNAS], int *x, int *y, int selecao, int *x2, int *y2);

void troca_peca(char mapamaior[][44],int x, int y, int x2, int y2);

int menu (void);

void comojogar(void);


int main(){
    system("mode 115, 40");

    int x=0, y=0;
    char personagem = 'M';
    char mapa[LINHAS][COLUNAS];
    char mapamaior[22][44] = {{' '}};
    int x2=0, y2=0;

    y = menu();

    switch(y){
        case 3:

            tabuleiro(mapa);
            tabuleiro_escalonado(mapa, mapamaior, 1);
            while(1){ //APENAS PARA TESTAR
            mexe_peca(mapa, &x, &y, 1, &x2, &y2);
            x2 = x;
            y2 = y;
            mexe_peca(mapa, &x, &y, 2, &x2, &y2);
            troca_peca(mapamaior, x, y, x2, y2);
            tabuleiro_escalonado(mapa, mapamaior, 2);
            }
        break;
        case 5: printf("OPCAO 2\n");
        break;
        case 7: printf("OPCAO 3\n");
        break;
        case 9: comojogar();
        break;
        default:  ;
        break;
    }

    textbackground(BLACK);
    textcolor(WHITE);
    return 0;
}

int menu (void){
    int enter = 0;
    int x;
    int y;

    cputsxy(36, 1, "C O M B I N A  3");

    cputsxy(38, 3, "[NOVO JOGO]");
    cputsxy(38, 5, "[CONTINUAR]");
    cputsxy(38, 7, "[RANKING]");
    cputsxy(38, 9, "[COMO JOGAR]");
    cputsxy(38, 11, "[SAIR DO JOGO]");

    x = 36;
    y = 3;

    while(enter != 13){
        if (GetKeyState (VK_UP) & 0x80){
            if (y-1 >= 3){
                y-=2;
                cputsxy(x, y+2, "  ");
            }
        } else if (GetKeyState (VK_DOWN) & 0x80){
            if (y+1 <= 11){
                y+=2;
                cputsxy(x, y-2, "  ");
            }
        }
            cputsxy(x, y, "=>");
            enter = getch();
            Sleep(70);
    }

    system("CLS");

    return y;
}

void tabuleiro_escalonado(char mapa[][COLUNAS], char mapamaior[][44], int selecao){

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
        for (j=2; j<42; j+=2)
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
            }
        }
    }

    x = 24;
    y=5;

    gotoxy(x, y);

    for (i=0; i<22; i++) // PRINTA O MAPA ESCALONADO
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
}

void tabuleiro(char mapa[][COLUNAS]){
   // char mapa[LINHAS][COLUNAS]; //= { "xxxxxxxxxxx", "xRGRBCCBGRx", "xRBBCGRGBGx", "xGGRCBCCRBx", "xBCGBRBGCGx", "xCBBRRGCBBx", "xxxxxxxxxxx"};
    char nome[20];
    char mapaaux[COLUNAS];
    FILE *file;
    int i=0, j=0;
    int aux=0;

    file = fopen("nivel-0.txt", "r");

    while(fgets(mapaaux, COLUNAS, file) != NULL)
    {
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

    cputsxy(36, 1, "C O M B I N A  3");
    cputsxy(28, 5, "NOME DO JOGADOR: ");
    gets(nome);
    clrscr();
    cputsxy(36, 1, "C O M B I N A  3");
    gotoxy(2, 4);
   cputsxy(16,3,"JOGADOR: ");
   cputsxy(24,3, nome);
   cputsxy(40,3,"NIVEL :01");
   cputsxy(58,3,"PONTUACAO: ");
}

void mexe_peca(char mapa[][COLUNAS], int *x, int *y, int selecao, int *x2, int *y2){

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

void troca_peca(char mapamaior[][44], int x, int y, int x2, int y2){
    char aux[2][2];
    int i=0, j=0;

    gotoxy(1, 20);
    x = x - 22;
    y = y - 3;
    x2= x2 - 22;
    y2 = y2 - 3;

    for(i=0;i<2;i++) {
        for(j=0;j<2;j++) {
            aux[i][j] = mapamaior[y+i][x+j];
         //   printf("%c", aux[i][j]);
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




