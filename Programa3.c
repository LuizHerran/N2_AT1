#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LEITURAS_POR_SENSOR 2000

char *sensores;

float criar_val(int sensor){
    switch (sensor) {
        case 1:
            return (rand() % 2);
        case 2:
            return (rand() % 1000) / 1000.0; 
        case 3: 
            return rand() % 101; 
        default:
            return 0.0;
    }
}

time_t gerar_timtamp(int d, int m, int a) {
    struct tm t = {0};

    t.tm_year = a - 1900; 
    t.tm_mon = m - 1; 
    t.tm_mday = d;
    t.tm_hour = rand() % 24; 
    t.tm_min = rand() % 60;  
    t.tm_sec = rand() % 60;

    return mktime(&t);
}

time_t gerar_time(int inic, int fin){

    int aux = fin - inic;
    time_t time_aleatorio = (inic + (fin - (rand() % aux)));
    if(time_aleatorio < 0){
        time_aleatorio = abs(time_aleatorio);
    }
    return time_aleatorio;
}

char* string(int se, char *va){

    switch(se){
        case 0:
            return strcpy(va, "Cabelo");
        case 1:
            return strcpy(va, "Banana");
        case 2:
            return strcpy(va, "Manco");
        case 3:
            return strcpy(va, "Cobra");
        case 4:
            return strcpy(va, "Macaco");
        case 5:
            return strcpy(va, "Helicoptero");
        case 6:
            return strcpy(va, "Bolo");
        case 7:
            return strcpy(va, "Cenoura");
        case 8:
            return strcpy(va, "Dipirona");
        case 9:
            return strcpy(va, "Ponte");
        default:
            return strcpy(va, "Teto");
    }
}

int main(int argc, char *argv[]){

    if(argc > 9){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tMais informcoes do que o necessario... %d\n", argc);
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }

    int di, mi, ai, df, mf, af;
    di = atoi(argv[1]);
    mi = atoi(argv[2]);
    ai = atoi(argv[3]);
    df = atoi(argv[4]);
    mf = atoi(argv[5]);
    af = atoi(argv[6]);

    if(di < 1 || di > 31){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }else if(mi < 1 || mi > 12){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }else if(ai < 0){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }else if(af < 0 || af < ai){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }else if(mf < 1 || mf > 12 || (af < ai && mf < mi)){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }else if(df < 1 || df > 31 || (af < ai && df < di)){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    
    if(strlen(argv[7]) > 20){
        printf("\n//========================================\\\\");
        printf("\n||\n");
        printf("||\tNome do sensor muito grande\n||\tuse apenas 20 caracteres!\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
    }
    
    char sens[strlen(argv[7])];
    strcpy(sens, argv[7]);

    /*if(strcmp(sens, " ")){
    printf("\n//========================================\\\\");
    printf("\n||\n");
    printf("||\tSensor invalido! - %s\n", sens);
    printf("||\n");
    printf("\\\\=======================================//\n");
    return(1);
    }*/

    char tip[sizeof(argv[8])];
    strcpy(tip, argv[8]);

    int ver = 0;
    ver = strcmp(tip, "CONJ_Z");
    ver = strcmp(tip, "CONJ_Q");
    ver = strcmp(tip, "TEXTO");
    ver = strcmp(tip, "BINARIO");

    if(ver != 0){
    printf("\n//========================================\\\\");
    printf("\n||\n");
    printf("||\tTipo de dado invalido!\n");
    printf("||\n");
    printf("\\\\=======================================//\n");
    return(1);
    }

    FILE *fp = fopen("novos_dados.txt", "w");
    if (!fp) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Leituras aleatorias
        for (int j = 0; j < LEITURAS_POR_SENSOR; j++) {
            time_t timtampi = gerar_timtamp(di, mi, ai);
            time_t timtampf = gerar_timtamp(df, mf, af);
            time_t timtamp = gerar_time(timtampi, timtampf);
            if(strcmp(tip, "TEXTO") == 0){
                char valor[16];
                string(rand() % 10, valor);
                fprintf(fp, "%ld %s %s\n", timtamp, sens, valor);
            }else if(strcmp(tip, "BINARIO") == 0){
                int valor = criar_val(1);
                fprintf(fp, "%ld %s %s\n", timtamp, sens, (valor == 1 ? "True" : "False"));
            }else if(strcmp(tip, "CONJ_Q") == 0){
                float valor = criar_val(2);
                fprintf(fp, "%ld %s %.2f\n", timtamp, sens, valor);
            }else if(strcmp(tip, "CONJ_Z") == 0){
                int valor = criar_val(3);
                fprintf(fp, "%ld %s %d\n", timtamp, sens, valor);
            }
        }
    fclose(fp);
    printf("\n//======================================\\\\\n");
    printf("||\n");
    printf("||\tArquivo com novos dados criados!\n");
    printf("||\n");
    printf("\\\\======================================//");
    return 0;
}