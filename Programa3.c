#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_SENSORES 4
#define LEITURAS_POR_SENSOR 2000

char *sensores[NUM_SENSORES] = {"TEM", "PRE", "VIB", "SON"};
char *clima[6] = {"Muito_Frio", "Frio", "Fresco", "Quente", "Muito_Quente"};

float criar_val(int sensor){
    switch (sensor) {
        case 0:
            return (rand() % 1000) / 10.0 + 20.0;
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

    time_t time_aleatorio = inic + rand() % (fin - inic + 1);
    
    return time_aleatorio;
}

int main() {
    int di, mi, ai, df, mf, af;
    char sens[4];

    printf("//========================================\\\\");
    printf("\n||\n");
    printf("\r||\tDigite o dia de inicio (1-31): ");
    scanf("%d", &di);
    if(di < 1 || di > 31){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    printf("||\n");
    printf("||\tDigite o mes de incio(1-12): ");
    scanf("%d", &mi);
    if(mi < 1 || mi > 12){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    printf("||\n");
    printf("\r||\tDigite o ano de inicio: ");
    scanf("%d", &ai);
    if(ai < 1){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    printf("||\n");
    printf("\\\\=======================================//\n");
    printf("\n//========================================\\\\");
    printf("\n||\n");
    printf("\r||\tDigite o dia final (1-31): ");
    scanf("%d", &df);
    if(df < 1 || df > 31){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    printf("||\n");
    printf("||\tDigite o mes final(1-12): ");
    scanf("%d", &mf);
    if(mf < 1 || mf > 12){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    printf("||\n");
    printf("\r||\tDigite o ano final inicio: ");
    scanf("%d", &af);
    if(af < 1){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    printf("||\n");
    printf("\\\\=======================================//\n");
    printf("//==================================================================================\\\\\n");
    printf("||\n");
    printf("||\t\tTEMP - Temperatura, PRE - Pressao, VIB - Vibracao, SON - Sonoro\n");
    printf("||\n");
    printf("||\tDigite o tipo de sensor: ");
    scanf(" %s", sens);
    printf("\n\\\\==================================================================================//\n");
    srand(time(NULL));

    int ver = 0;
    ver = strcmp(sens, "TEMP");
    ver = strcmp(sens, "PRE");
    ver = strcmp(sens, "VIB");
    ver = strcmp(sens, "SON");
    if(ver != 0){
    printf("\n//========================================\\\\");
    printf("\n||\n");
    printf("||\tSensor invalido!\n");
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
            if(strcmp(sens, "TEMP") == 0){
                char valor[16];
                strcpy(valor, clima[(rand() % 5)]);
                fprintf(fp, "%ld %s %s\n", timtamp, sensores[0], valor);
            }else if(strcmp(sens, "PRE") == 0){
                int valor = criar_val(1);
                fprintf(fp, "%ld %s %s\n", timtamp, sensores[1], (valor == 1 ? "True" : "False"));
            }else if(strcmp(sens, "VIB") == 0){
                float valor = criar_val(2);
                fprintf(fp, "%ld %s %.2f\n", timtamp, sensores[2], valor);
            }else if(strcmp(sens, "SON") == 0){
                int valor = criar_val(3);
                fprintf(fp, "%ld %s %d\n", timtamp, sensores[3], valor);
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