#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;

void abertura() {
    printf("/****************/\n");
    printf("/ Jogo de Forca */\n");
    printf("/****************/\n\n");
}
void chuta() {
    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    (chutesdados)++;
}
int jachutou(char letra) {
    int achou = 0;
    for(int j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}
void desenhaforca() {


    printf("Você já deu %d chutes\n", chutesdados);

    for(int i = 0; i < strlen(palavrasecreta); i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}

void adcionarpalavra() {   
    char resposta;

    printf("Gostaria de adcionar uma nova palavra no Jogo? (S/N)");
    scanf(" %c", &resposta);

    if(resposta == 'S'){

        char nova[20];

        printf("Digite a nova palavra: ");
        scanf("%s", nova);

        FILE* f;

        f = fopen("palavras.txt", "r+");

        if(f == 0){
            printf("Perdão, Banco de dados indisponível\n\n");
            exit(1);
        }
        
        int quantidadelinha;
        fscanf(f, "%d", &quantidadelinha);
        quantidadelinha++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", quantidadelinha);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", nova);

        fclose(f);

    }
}
void escolhepalavra() {
    FILE* f;
    
    f = fopen("palavras.txt", "r");
    if (f == 0)
    {
        printf("Perdão, Banco de dados indisponível");
        exit(1);
    }
    
    int quantidadespalavra;
    fscanf(f, "%d", &quantidadespalavra);

    srand(time(0));
    int randomico = rand() % quantidadespalavra;

    for (int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavrasecreta);
    }
    fclose(f);
}
int enforcou(){
    int erros = 0;

    for(int i = 0; i < chutesdados; i++){

        int existe = 0;
        for (int j = 0; j < strlen(palavrasecreta); j++){
            if(chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            } 
        }

        if (!existe) erros++;
        
    }
    return erros >= 5;
}
int acertou(){
    for (int i = 0; i < strlen(palavrasecreta); i++){
        if (!jachutou(palavrasecreta[i])){
            return 0; 
        }
    } 
      
    return 1;
}
int main() {

    abertura();
    escolhepalavra();

    do {

        desenhaforca();
        chuta();
        
    } while (!acertou() && !enforcou());

    if(acertou()){
        printf("Parabens, você acertou a palavra secreta\n");
    }else{
        printf("Que pena, você perdeu a palavra secreta era **%s\n\n**", palavrasecreta);
    }

    adcionarpalavra();

}