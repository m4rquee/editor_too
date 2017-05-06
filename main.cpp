#include "Acao.h"
#include "Pilha.h"
#include "Lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio2.h>

unsigned char POSX;
const unsigned char LARGURA = 80;
const unsigned char NUM_ACOES = 15;
const unsigned char NUM_LINHAS_PAGE = 25;

using namespace std;

void colocaNoComeco(Lista& _lista) {
    while (true)
        if (!_lista.estaNoPrimeiro()) {
            gotoxy(wherex(), wherey() - 1);
            _lista.retroceda();
        } else
            break;
}

void abrir(char* src, Lista& lista) {
    FILE* arquivo = fopen(src , "r");
    char linha[LARGURA + 1];

    clrscr();

    if(arquivo == NULL)
       cout << "Arquivo nao existe";
    else {
        while(fgets(linha, sizeof(linha), arquivo) != NULL) {
            String novaLinha(linha);

            char aux = fgetc(arquivo);

            if (aux != '\n')
                ungetc(aux, arquivo);

            if (novaLinha[novaLinha.length() - 1] == '\n')
                novaLinha.deleteCharAt(novaLinha.length() - 1);

            while (novaLinha.length() < LARGURA)
                novaLinha.append(' ');

            lista.insiraDepois(novaLinha);
        }

        fclose(arquivo);

        cout << "Arquivo aberto";
    }

    cout << " (Digite qualquer tecla)";
    getch();
    clrscr();
}

void salvarComo(char* _texto) {
    clrscr();
    cout << "Voce deseja salvar? [s/S-Sim / Outro-Nao] ";

    char op;
    cin >> op;
    if (op == 's' || op == 'S') {
        clrscr();
        cout << "Digite o caminho do arquivo: ";

        char caminho[1000];
        cin >> caminho;

        FILE* arq = fopen(caminho, "r");
        if (arq) {
            fclose(arq);

            clrscr();

            cout << "O arquivo ja existe! Deseja sobrescrever? [s/S-Sim / Outro-Nao] ";
            cin >> op;
        }

        if (op != 's' && op != 'S')
            return;

        arq = fopen(caminho, "w");
        fputs(_texto, arq);

        cout << "Arquivo salvo (Digite qualquer tecla)";

        getch();

        fclose(arq);
    }

    system("cls");
}

void cima(Lista& _lista) {
    if (!_lista.estaNoPrimeiro()) {
        gotoxy(wherex(), wherey() - 1);
        _lista.retroceda();
    }
}

void baixo(Lista& _lista) {
    gotoxy(POSX, wherey() + 1);

    if (_lista.estaNoUltimo())
        _lista.insiraDepois(String(LARGURA));
    else
        _lista.avance();
}

int main() {
    //Inicializa as variaveis:
    Lista texto;

    Pilha<Acao> ida(NUM_ACOES);
    Pilha<Acao> volta(NUM_ACOES);

    POSX = 1;

    char caminhoA[1000];

    unsigned int cod = 0;

    //Abre ou cria o arquivo solicitado pelo usuário
    printf("Digite o diretorio de um arquivo: ");
    cin >> caminhoA;

    abrir(caminhoA, texto);

    if (texto.qntos() == 0)
        texto.insiraDepois(String(LARGURA));

    texto.paraPrimeiro();
    cputsxy(1, 1, texto.toStringSemPula().toString());
    gotoxy(1, 1);

    //Ciclo principal:
    while (true) {
        cod += getch();

        if (cod == 27) {
            break;
        } else if (cod == 224) { //codigos de comandos
            continue;
        } else if ((cod >= 32 && cod <= 126) || (cod >= 128 && cod <= 255)) { //digitaveis
            if (POSX == LARGURA + 1) {
                POSX = 1;

                if (texto.estaNoUltimo())
                    texto.insiraDepois(String(LARGURA));
                else
                    texto.avance();

                gotoxy(1, wherey() + 1);
            }

            texto.infoAtual()->insertInto(POSX - 1, cod);
            texto.infoAtual()->deleteCharAt(LARGURA);

            cputsxy(1, wherey(), texto.infoAtual()->toString());

            gotoxy(POSX, wherey() - 1);

            POSX++;
        } else if (cod == 8) { //backspace
            if (wherex() == 1 && !texto.estaNoPrimeiro()) {
                putchxy(LARGURA, wherey() - 1, ' ');
                gotoxy(LARGURA, wherey() - 1);

                texto.retroceda();

                (*texto.infoAtual()) [POSX = LARGURA - 1] = ' ';
            } else if (wherex() != 1) {
                POSX = wherex() - 1;
                texto.infoAtual()->deletePos(wherex() - 2);

                cputsxy(1, wherey(), texto.infoAtual()->toString());

                gotoxy(POSX, wherey() - 1);
            }
        } else if (cod == 295) { //home
            cout << '\r';
            POSX = 1;
        } else if (cod == 303) { //end
            POSX = LARGURA;
            gotoxy(POSX, wherey());
        } else if (cod == 307) { //del
            POSX = wherex();

            texto.infoAtual()->deletePos(POSX - 1);

            cputsxy(1, wherey(), texto.infoAtual()->toString());
            gotoxy(POSX, wherey() - 1);
        } else if (cod == 296) { //cima
            cima(texto);
        } else if (cod == 304) { //baixo
            baixo(texto);
        } else if (cod == 301) { //direita
            if (POSX < LARGURA)
                gotoxy(++POSX, wherey());
            else {
                gotoxy(POSX = 1, wherey() + 1);

                if (texto.estaNoUltimo())
                    texto.insiraDepois(String(LARGURA));
                else
                    texto.avance();
            }
        } else if (cod == 299) { //esquerda
            if (POSX > 1)
                gotoxy(--POSX, wherey());
            else if (!texto.estaNoPrimeiro()) {
                POSX = LARGURA;
                gotoxy(POSX, wherey() - 1);
                texto.retroceda();
            }
        } else if (cod == 19) { //salvar ctrl + s
            salvarComo(texto.toString().toString());

            String textoArq = texto.toStringSemPula();

            cputsxy(1, 1, textoArq.toString());

            POSX = 1;

            colocaNoComeco(texto);
        } else if (cod == 297) { //page up
            unsigned char i;

            for (i = 0; i < NUM_LINHAS_PAGE; i++)
                cima(texto);
        } else if (cod == 305) { //page down
            unsigned char i;

            for (i = 0; i < NUM_LINHAS_PAGE; i++)
                baixo(texto);
        }

        cod = 0;
    }

    salvarComo(texto.toString().toString());

    return 0;
}
