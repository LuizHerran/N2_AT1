#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINHAS 10000

typedef struct{
    time_t timestamp;
    float valor;
    char va[16];
} TIME;

// Compara duas TIMEs
int comparar(const void *a, const void *b)
{
    TIME *l1 = (TIME *)a;
    TIME *l2 = (TIME *)b;
    if (l1->timestamp < l2->timestamp)
        return -1;
    else if (l1->timestamp > l2->timestamp)
        return 1;
    else
        return 0;
}

int busca_binaria(TIME TIMEs[], int n, time_t alvo)
{
    int ini = 0, fim = n - 1;
    int melhor_indice = -1;
    long menor_diferenca = -1;

    while (ini <= fim)
    {
        int meio = (ini + fim) / 2;
        long diferenca = labs(difftime(TIMEs[meio].timestamp, alvo));

        if (menor_diferenca == -1 || diferenca < menor_diferenca){
            menor_diferenca = diferenca;
            melhor_indice = meio;
        }

        if (TIMEs[meio].timestamp < alvo){
            ini = meio + 1;
        }
        else if (TIMEs[meio].timestamp > alvo){
            fim = meio - 1;
        }
        else{
            return meio;
        }
    }
    return melhor_indice;
}

int main(int argc, char *argv[]){
    
    if(strlen(argv[1]) > 20){
        printf("\n//========================================\\\\");
        printf("\n||\n");
        printf("||\tNome do sensor muito grande\n||\tuse apenas 20 caracteres!\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    char sens[strlen(argv[1])];
    strcpy(sens, argv[1]);
    
    char dh[15];
    int ver = 0;
    if(strcmp(sens, "TEMP") != 0 && strcmp(sens, "PRE") != 0 && strcmp(sens, "VIB") != 0 && strcmp(sens, "SON") != 0){
    printf("\n//========================================\\\\");
    printf("\n||\n");
    printf("||\tSensor invalido! - %s\n", sens);
    printf("||\n");
    printf("\\\\=======================================//\n");
    return(1);
    }

    // Data e hora em timestamp
    struct tm t;
    memset(&t, 0, sizeof(struct tm));

    t.tm_mday = atoi(argv[2]);
    if(t.tm_mday < 1 || t.tm_mday > 31){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    t.tm_mon = atoi(argv[3]);
    if(t.tm_mon < 1 || t.tm_mon > 12){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    t.tm_year = atoi(argv[4]);
    if(t.tm_year < 1){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tData invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    t.tm_hour = atoi(argv[5]);
    if(t.tm_hour < 1 || t.tm_hour > 24){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tHora invalida...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    t.tm_min = atoi(argv[6]);
    if(t.tm_min < 1 || t.tm_min > 59){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tMin invalido...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }
    t.tm_sec = atoi(argv[7]);
    if(t.tm_sec < 1 || t.tm_sec > 59){
        printf("//========================================\\\\");
        printf("\n||\n");
        printf("||\tSegundo invalido...\n");
        printf("||\n");
        printf("\\\\=======================================//\n");
        return(1);
    }

    t.tm_year -= 1900;
    t.tm_mon -= 1;
    time_t momento = mktime(&t);

    // Arquivo completo
    FILE *fp = fopen("dados.txt", "r");
    if (!fp){
        perror("\nErro ao abrir o arquivo: ");
        return 1;
    }

    TIME TIMEs[MAX_LINHAS];
    int total = 0;

    char linha[100];
    while (fgets(linha, sizeof(linha), fp)){
        time_t ts;
        char sens_lido[10];
        float valor;
        char va[16];

        if(strcmp(sens, "TEMP") == 0){
            if (sscanf(linha, "%ld %s %s", &ts, sens_lido, va) == 3){
            if (strcmp(sens_lido, sens) == 0){
                if (total < MAX_LINHAS){
                    TIMEs[total].timestamp = ts;
                    for (int i = 0; i < 16; i++) {
                        if(sizeof(TIMEs[total].va[i] <= sizeof(TIMEs[total].va[i]))){
                            TIMEs[total].va[i] = va[i];
                        }
                    }
                    total++;
                }
                total++;
            }
            total++;
        }
        }
        else{
            if (sscanf(linha, "%ld %s %f", &ts, sens_lido, &valor) == 3){
            if (strcmp(sens_lido, sens) == 0){
                if (total < MAX_LINHAS){
                    TIMEs[total].timestamp = ts;
                    TIMEs[total].valor = valor;
                    total++;
                }
                total++;
            }
            total++;
        }
        }
    }
    fclose(fp);
    if (total == 0){
        printf("\n//==============================================\\\n");
        printf("|| Nenhuma TIME encontrada para o sensor %s.\n", sens);
        printf("\\\\==============================================//\n");
        return 1;
    }

    // TIMEs por timestamp
    qsort(TIMEs, total, sizeof(TIME), comparar);

    // TIME mais próxima
    int indice = busca_binaria(TIMEs, total, momento);

    struct tm *tm_info = localtime(&TIMEs[indice].timestamp);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);

    if (indice >= 0){
        if(strcmp(sens, "PRE") == 0){
            printf("\n//=======================================\\\\");
            printf("\n||\n");
            printf("||\tData e hora mais proxima:\n");
            printf("||\tTimestamp: %s\n", buffer);
            printf("||\tValor: %s\n", (TIMEs[indice].valor == 1 ? "True" : "False"));
            printf("\\\\======================================//");
        }else if(strcmp(sens, "TEMP") == 0){
            printf("\n//=======================================\\\\");
            printf("\n||\n");
            printf("||\tData e hora mais proxima:\n");
            printf("||\tTimestamp: %s\n", buffer);
            printf("||\tValor: %s\n", TIMEs[indice].va);
            printf("\\\\======================================//");  
        }else if(strcmp(sens, "VIB") == 0){
            printf("\n//=======================================\\\\");
            printf("\n||\n");
            printf("||\tData e hora mais proxima:\n");
            printf("||\tTimestamp: %s\n", buffer);
            printf("||\tValor: %.2f\n", TIMEs[indice].valor);
            printf("\\\\======================================//");  
        }else if(strcmp(sens, "SON") == 0){
            printf("\n//=======================================\\\\");
            printf("\n||\n");
            printf("||\tData e hora mais proxima:\n");
            printf("||\tTimestamp: %s\n", buffer);
            printf("||\tValor: %.2f\n", TIMEs[indice].valor);
            printf("\\\\======================================//"); 
        }else printf("Erro ao ler!\n");
    }
    else{
        printf("\nNenhuma TIME encontrado.\n");
    }
    return 0;
}