#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

    int i = 0;
    char linhas[250];

typedef struct{
    int DH;
    char sensor[16];
    char dc[16];
    int di;
    bool db;
    float dds;
}DADOS;

DADOS dd[100];

int abrirarquivo(DADOS dados[]){
    FILE *arc = fopen("dados.txt", "r");
    if(arc == NULL){
        perror("Erro ao abrir o arquivo: ");
        return 1;
    }

    while(fgets(linhas, sizeof(linhas), arc) != NULL){

        char *tk;
        // Data e hora
        tk = strtok(linhas, " ");
        dados[i].DH = atoi(tk);

        // Sensores
        tk = strtok(NULL, " ");
        if(strlen(tk) >= sizeof(dados[i].sensor)){
            printf("\nEstouro de memoria em Sensores!\n");
        }
        strcpy(dados[i].sensor, tk);

        //troca de formto de dados para cada sensor
        if(strcmp(dados[i].sensor, "TEM")  == 0){
            tk=strtok(NULL, " ");
            if(strlen(tk) >= sizeof(dados[i].sensor)){
            printf("Estouro de memoria em dados dos sensores!");
            }
            strcpy(dados[i].dc, tk);
        }else if(strcmp(dados[i].sensor, "VIB") == 0){
            tk = strtok(NULL, " ");
            dados[i].dds = atof(tk);
            
        }else if(strcmp(dados[i].sensor, "PRE") == 0){
            tk = strtok(NULL, " ");
            dados[i].db = atoi(tk);
            
        }else if(strcmp(dados[i].sensor, "SON") == 0){
            tk = strtok(NULL, " ");
            dados[i].di = atoi(tk);    
        }else printf("Erro na leitura dos dados do sensor %s\n", dados[i].sensor);
        i++;
        }

        fclose(arc);
        return 0;
    }

//ordenar por data e hora
void orddh(DADOS dados[]){
    
    int aux;
    for(int p = 0; p < i; p++){

        for(int j = 0; j < i; j++){
            if(dados[j].DH < dados[j+1].DH){

                aux = dados[j].DH;
                dados[j].DH = dados[j+1].DH;
                dados[j+1].DH = aux;
            }else {
                continue;
            }
        }
    }
        for (int j = 0; j < i; j++){
                if(strcmp(dados[j].sensor, "PRE") == 0){
                    printf(" %-12d | %-5s | %s\n", dados[j].DH, dados[j].sensor, (dados[j].db == 1 ? "True" : "False"));
                }else if(strcmp(dados[j].sensor, "TEM") == 0){
                    printf(" %-12d | %-5s | %s", dados[j].DH, dados[j].sensor, dados[j].dc);
                }else if(strcmp(dados[j].sensor, "VIB") == 0){
                    printf(" %-12d | %-5s | %-10.2f\n", dados[j].DH, dados[j].sensor, dados[j].dds);
                }else if(strcmp(dados[j].sensor, "SON") == 0){
                    printf(" %-12d | %-5s | %-10.d\n", dados[j].DH, dados[j].sensor, dados[j].di);
                }else printf("Erro ao ler!\n");
            }
}

//Criar novo arquivo
int narc(DADOS dados[]){

    FILE *narc = fopen("Dados_por_Data_e_Hora.txt", "w");
    if(narc == NULL){
        perror("Erro ao criar novo arquivo: ");
    }

    for (int j = 0; j < i; j++){
        if(strcmp(dados[j].sensor, "PRE") == 0){
            fprintf(narc, " %-12d | %-5s | %s\n", dados[j].DH, dados[j].sensor, (dados[j].db == 1 ? "True" : "False"));
        }else if(strcmp(dados[j].sensor, "TEM") == 0){
            fprintf(narc, " %-12d | %-5s | %s", dados[j].DH, dados[j].sensor, dados[j].dc);
        }else if(strcmp(dados[j].sensor, "VIB") == 0){
            fprintf(narc, " %-12d | %-5s | %-10.2f\n", dados[j].DH, dados[j].sensor, dados[j].dds);
        }else if(strcmp(dados[j].sensor, "SON") == 0){
            fprintf(narc, " %-12d | %-5s | %-10.d\n", dados[j].DH, dados[j].sensor, dados[j].di);
        }else printf("Erro ao ler!\n");
    }

    fclose(narc);
    printf("\nDados salvos com sucesso!\n");
    return 0;
}

int cascii(char *c){
    return (int)c[0];
}

int senpres(DADOS dados[]){
    FILE *at = fopen("Dados_de_Pressao.txt", "w");
    if(at == NULL){
        perror("Erro ao gerar arquivo de Pressao: ");
        return 1;
    }

    for(int j = 0; j < i; j++){
        
        if(cascii(dados[j].sensor) == 80){
            fprintf(at, "%d, %s, %d\n", dados[j].DH, dados[j].sensor, dados[j].db);
            fflush(at);
        }
    }
    printf("\nArquivo de sensores de Pressao criado com sucessor!\n");
    fclose(at);
    return 0;
}

int sentemp(DADOS dados[]){
    FILE *at = fopen("Dados_de_Temperatura.txt", "w");
    if(at == NULL){
        perror("Erro ao gerar arquivo de temperatura: ");
        return 1;
    }

    for(int j = 0; j < i; j++){
        
        if(cascii(dados[j].sensor) == 84){
            fprintf(at, "%d, %s, %s\n", dados[j].DH, dados[j].sensor, dados[j].dc);
            fflush(at);
        }
    }
    printf("\nArquivo de sensores de Temperatura criado com sucessor!\n");
    fclose(at);
    return 0;
}

int senvib(DADOS dados[]){
    FILE *at = fopen("Dados_de_Vibracao.txt", "w");
    if(at == NULL){
        perror("Erro ao gerar arquivo de Vibracao: ");
        return 1;
    }

    for(int j = 0; j < i; j++){
        
        if(cascii(dados[j].sensor) == 86){
            fprintf(at, "%d, %s, %.2f\n", dados[j].DH, dados[j].sensor, dados[j].dds);
            fflush(at);
        }
    }
    printf("\nArquivo de sensores de Vibracao criado com sucessor!\n");
    fclose(at);
    return 0;
}

int senson(DADOS dados[]){
    FILE *at = fopen("Dados_Sonoros.txt", "w");
    if(at == NULL){
        perror("Erro ao gerar arquivo Sonoro: ");
        return 1;
    }

    for(int j = 0; j < i; j++){
        
        if(cascii(dados[j].sensor) == 86){
            fprintf(at, "%d, %s, %d\n", dados[j].DH, dados[j].sensor, dados[j].di);
            fflush(at);
        }
    }
    printf("\nArquivo de sensores sonoros criado com sucessor!\n");
    fclose(at);
    return 0;
}

int main(){
        abrirarquivo(dd);

        int opc, opc2;

        do{
        printf("\n//=====================================\\\\\n");
        printf("||\t1 - Ler arquivo bruto\n");
        printf("||\t2 - Ordenar por Data/Hora\n");
        printf("||\t3 - Orndenar por Sensor\n");
        printf("||\t4 - Criar novo arquivo\n");
        printf("||\t5 - Sair\n");
        printf("\\\\=====================================//");
        scanf("%d", &opc);

            switch(opc){
            case 1:
            for (int j = 0; j < i; j++){
                if(strcmp(dd[j].sensor, "PRE") == 0){
                    printf(" %-12d | %-5s | %s\n", dd[j].DH, dd[j].sensor, (dd[j].db == 1 ? "True" : "False"));
                }else if(strcmp(dd[j].sensor, "TEM") == 0){
                    printf(" %-12d | %-5s | %s", dd[j].DH, dd[j].sensor, dd[j].dc);
                }else if(strcmp(dd[j].sensor, "VIB") == 0){
                    printf(" %-12d | %-5s | %-10.2f\n", dd[j].DH, dd[j].sensor, dd[j].dds);
                }else if(strcmp(dd[j].sensor, "SON") == 0){
                    printf(" %-12d | %-5s | %-10.d\n", dd[j].DH, dd[j].sensor, dd[j].di);
                }else printf("Erro ao ler!\n");
            }

            break;

            case 2:
                orddh(dd);
            break;

            case 3:

                do{
                printf("\n//=====================================\\\\\n");
                printf("||\t1 - Sensor de Temperatura\n");
                printf("||\t2 - Sensor de Vibracao\n");
                printf("||\t3 - Sensor de Pressao\n");
                printf("||\t4 - Sensor Sonor\n");
                printf("||\t5 - Sair\n");
                printf("\\\\=====================================//");
                scanf("%d", &opc2);
                
                switch(opc2){

                    case 1:
                        sentemp(dd);
                    break;

                    case 2:
                        senvib(dd);
                    break;

                    case 3:
                        senpres(dd);
                    break;

                    case 4:
                        senson(dd);
                    break;

                    case 5:
                    break;
                }
            break;

            case 4:
                    narc(dd);
            break;
                }while(opc2 != 5);
            }
        }while(opc != 5);
}