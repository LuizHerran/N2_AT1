# N2_AT1
Prova final

Programa 1 - 
Possui uma interface intuitiva para o usuario poder, ler o arquivo como esta, ordenar por data e hora decrescente,
ordenar por sensor, e criar um novo arquivo.

O usuario acessa o programa que é estruturado em switch para garantir que ele só escolha opções que estão sendo apresentadas.

funções:
abrirarquivo - Ela abre o arquivo de dados e armazena dentro da struct
narc - cria um novo arquivo
orddh - Ordena por data e hora decrescente
cascci - converte char para ascci
senpres, senvib, senson - cria um arquivo só com dados referentes a suas iniciais.

programa 2 -
Os dados que serão separados por " " sendo apenas 7 dados a seren inseridos, primeiro o nome de um sensor, depois o dia,
mes, ano, hora, minutos e segundos, o programa compara os dados inseridos a base de dados e tras o dado mais proximo, como
temos uma base de dados solida nos limitamos ao sensores "SON", "PRE", "VIB" e "TEMP".

Programa 3 -
Os dados que serão separados por " " sendo apenas 8 em sequencia, dia incial, mes inicial, ano inicial seguidos por dia mes e ano
final para que o programa possa fazer a geração de tempo entre esses dois valores, em seguida o nome do sensor com no maxmimo 20
caracteres e por fim o tipo de dado que se limita a "CONJ_Z" para inteiros, "CONJ_Q" para flooat, "Binario" para booleano e 
"TEXTO" para palavras.
o programa gera 2000 linhas com dados e tempos aleatorios segindo o padrão dado pelo usuario no temrinal e nome do sensor.
