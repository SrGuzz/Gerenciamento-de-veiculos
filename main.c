#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const char *nomes_arquivos[] = {
    "historico_vendas.csv",
    "marcas.csv",
    "relatorio.txt",
    "veiculos_estoque.csv",
    "veiculos_ofertas.csv",
    "historico_compras.csv"}; // Lista de nomes dos arquivos a serem processados

typedef struct {
  char nomeMarca[21];
  char modelo[50];
  char cor[21];
} Marca;

typedef struct {
  float preco;
  char ano[5];
  Marca marca;
  char condicao[21];
  char combustivel[21];
  char km[21];
  char status[21];
  char cambio[21];
  char tamanho[21];
  char tipo[21];
} Carro;

void remover_nova_linha(char *str) {
  char *pos;
  if ((pos = strchr(str, '\n')) != NULL)
    *pos = '\0';
  if ((pos = strchr(str, '\r')) != NULL)
    *pos = '\0';
} // REMOVE O \n

void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
} // LIMPA O BUFFER

float temMarca(char *nomeMarca) {
  FILE *marcas = fopen("marcas.csv", "a+");
  float taxa;
  bool temMarca = false;
  char linha[1000];

  while (fgets(linha, sizeof(linha), marcas) != NULL) {
    char *pedaco = strtok(linha, ",");
    int cont = 0;
    while (pedaco != NULL) {
      switch (cont) {
      case 0:
        if (strcmp(nomeMarca, pedaco) == 0) {
          temMarca = true;
        }
        break;
      case 1:
        taxa = atof(pedaco);
        break;
      }
      pedaco = strtok(NULL, ","); // OBTEM O PROXIMO PEDAÇO
      cont++;
    }
  }
  fclose(marcas);

  FILE *marcas2 = fopen("marcas.csv", "a");
  if (temMarca == false) {
    system("clear");
    printf("TAXA PARA %s NAO ENCONTRADA, DIGITE UMA TAXA: ", nomeMarca);
    limparBuffer();
    scanf("%f", &taxa);
    fprintf(marcas2, "%s,%.2f\n", nomeMarca, taxa);
  }
  fclose(marcas2);
  return taxa;
} // Procedimento responsavel por realizar a leitura da taxa.

float operacoesTaxa(float preco, char *marca) {
  float taxa = temMarca(marca);
  preco = preco + (taxa / 100 * preco);
  return preco;
} // Procedimento responsavél pela taxa aplicado.

int filtroDeBusca(char carros[][1000]) {
  int op, qtdOP = 0, qtdCarros = 0;
  char linhaDoArquivo[1000];
  char preco[21], ano[5], marca[21], modelo[21], cond[21], comb[21], km[21],
      stts[21], cambio[21], tam[21], cat[21], cor[21], cor2[21];
  int pc = 0, an = 0, mc = 0, md = 0, co = 0, cmb = 0, kt = 0, st = 0, cb = 0,
      tm = 0, ct = 0, cr = 0;

  FILE *ofertas = fopen("veiculos_ofertas.csv", "r"); // ABRE O ARQUIVO
  if (ofertas == NULL) { // TERMINA O PROGRAMA SE O ARQUIVO NAO ABRIR
    printf("NAO FOI POSSIVEL ABRIR O ARQUIVO!");
    exit(EXIT_FAILURE);
  }

  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="
         "-\n");
  printf("OPCOES DE FILTRAGEM: [1] PRECO\t [2] ANO\t [3] MARCA\t [4] MODELO\t "
         "[5] CONDICAO\t [6] COMBUSTIVEL\t [7] KILOMETRAGEM\t [8] STATUS\t [9] "
         "CAMBIO\t [10] TAMANHO [11] TIPO\t [12] COR\n");
  printf("DIGITE A QUANTIDADE DE OPCOES DE FILTRAGEM: ");
  do { // ENQUNARO NÂO DIGITA UMA QUANTIDADE DE OPÇOES VALIDA N SAI DO LAÇO.
    scanf("%d", &qtdOP);
    if (qtdOP < 0 || qtdOP > 12) {
      printf("QUANTIDADE INVALIDA!\n");
    }
  } while (qtdOP < 0 || qtdOP > 12);

  int opcoesEscolhidas[qtdOP]; // GUARDA QUAL FORAM AS OPÇOES DE FILTRO
                               // ESCOLHIADAS

  for (int i = 0; i < qtdOP; i++) { // LE AS OPCOES DE FILTRO
    int c = 0;
    printf("DIGITE A %d OPCAO DE FILTRAGEM: ", i + 1);
    scanf("%d", &op);
    if (op < 1 || op > 12) {
      i--;
      printf("OPCAO INVALIDA!\n");
      continue;
    }
    for (int j = 0; j <= i; j++) { // VERIFICA SE A OPÇÂO JA FOI ESCOLHIDA
      if (op == opcoesEscolhidas[j]) {
        c++;
      }
    }
    if (c == 0) { // SE NÂO TIVER SIDO ATRIBUI NO VETOR
      opcoesEscolhidas[i] = op;
    } else { // SE TIVER CIDO PEDE PARA DIGITAR DNV
      printf("OPCAO JA DIGITADA, DIGITE NOVAMENTE\n");
      i--;
    }
  }
  for (int j = 0, i = 0; i < qtdOP; i++) { // VERIFICA A OPCAO DESEJADA
    if (opcoesEscolhidas[i] == 1) {
      printf("DIGITE O PRECO: ");
      limparBuffer();
      scanf("%[^\n]", preco);
      pc++;
    }
    if (opcoesEscolhidas[i] == 2) {
      printf("DIGITE O ANO: ");
      limparBuffer();
      scanf("%[^\n]", ano);
      an++;
    };
    if (opcoesEscolhidas[i] == 3) {
      printf("DIGITE O MARCA: ");
      limparBuffer();
      scanf("%[^\n]", marca);
      mc++;
    }
    if (opcoesEscolhidas[i] == 4) {
      printf("DIGITE O MODELO: ");
      limparBuffer();
      scanf("%[^\n]", modelo);
      md++;
    }
    if (opcoesEscolhidas[i] == 5) {
      printf("DIGITE A CONDICAO: ");
      limparBuffer();
      scanf("%[^\n]", cond);
      co++;
    }
    if (opcoesEscolhidas[i] == 6) {
      printf("DIGITE O COMBUSTIVEL: ");
      limparBuffer();
      scanf("%[^\n]", comb);
      cmb++;
    }
    if (opcoesEscolhidas[i] == 7) {
      printf("DIGITE O KM: ");
      limparBuffer();
      scanf("%[^\n]", km);
      kt++;
    }
    if (opcoesEscolhidas[i] == 8) {
      printf("DIGITE O STATUS: ");
      limparBuffer();
      scanf("%[^\n]", stts);
      st++;
    }
    if (opcoesEscolhidas[i] == 9) {
      printf("DIGITE O CAMBIO: ");
      limparBuffer();
      scanf("%[^\n]", cambio);
      cb++;
    }
    if (opcoesEscolhidas[i] == 10) {
      printf("DIGITE O TAMANHO: ");
      limparBuffer();
      scanf("%[^\n]", tam);
      tm++;
    }
    if (opcoesEscolhidas[i] == 11) {
      printf("DIGITE O TIPO: ");
      limparBuffer();
      scanf("%[^\n]", cat);
      ct++;
    }
    if (opcoesEscolhidas[i] == 12) {
      printf("DIGITE A COR: ");
      limparBuffer();
      scanf("%s", cor);
      cr++;
    }
  }

  int vseachou = 0;
  while (fgets(linhaDoArquivo, sizeof(linhaDoArquivo), ofertas) !=
         NULL) {              // LE TODAS AS LINHAS DO ARQUIVO UMA DE CADA VEZ
    char linhaDividida[1000]; // VAI RECEBER A LINHA DO ARQUIVO
    strcpy(linhaDividida,
           linhaDoArquivo); // COPIA A LINHA DO ARQUIVO PARA UMA OUTRA STRING
    char *pedaco = strtok(
        linhaDividida,
        ","); // DIVIDE A LINHA DO ARQUIVO EM PEDAÇOS SEPARANDO PELA VIRGULA

    int count = 0; // CONTADOR DE PEDAÇOS
    int ci = 0; // CONTA A QUANTIDADE DE PEDACOS QUE TA IGUAL AO QUE O USUARIO
                // DIGITOU

    while (pedaco !=
           NULL) { // PASSA POR CADA PEDACO(PALAVRA) DA FRASE DE UMA VEZ
      int p = 0;
      switch (count) { // DESCOBRE QUAL PARTE DO FILTRO E
      case 0:
        if (strcmp(preco, pedaco) == 0 && pc == 1)
          ci++;
        break;
      case 1:
        if (strcmp(ano, pedaco) == 0 && an == 1)
          ci++;
        break;
      case 2:
        if (strcmp(marca, pedaco) == 0 && mc == 1)
          ci++;
        break;
      case 3:
        if (strcmp(modelo, pedaco) == 0 && md == 1)
          ci++;
        break;
      case 4:
        if (strcmp(cond, pedaco) == 0 && co == 1)
          ci++;
        break;
      case 5:
        if (strcmp(comb, pedaco) == 0 && cmb == 1)
          ci++;
        break;
      case 6:
        if (strcmp(km, pedaco) == 0 && kt == 1)
          ci++;
        break;
      case 7:
        if (strcmp(stts, pedaco) == 0 && st == 1)
          ci++;
        break;
      case 8:
        if (strcmp(cambio, pedaco) == 0 && cb == 1)
          ci++;
        break;
      case 9:
        if (strcmp(tam, pedaco) == 0 && tm == 1)
          ci++;
        break;
      case 10:
        if (strcmp(cat, pedaco) == 0 && ct == 1)
          ci++;
        break;
      case 11:
        remover_nova_linha(cor);
        remover_nova_linha(pedaco);
        if (strcmp(cor, pedaco) == 0 && cr == 1)
          ci++;
        break;
      }

      pedaco = strtok(NULL, ","); // OBTEM O PROXIMO PEDAÇO
      count++;
    }

    if (qtdOP ==
        ci) { // SE A QUANTIDADE DE OPCOES DE FILTRAGEM ESCOLHIDAS FOR IGUAL A
              // QUANTIDADE DE PEDACOS IGUAIS ACHADA EM UMA LINHA IMPRIME ELA.
      if (qtdCarros < 8000) {
        strcpy(carros[qtdCarros],linhaDoArquivo); // COPIA LINHA DO ARQUIVO PARA O VETOR
        qtdCarros++;
        ci = 0;
        if (qtdCarros == 8000) {
          printf("\e[1;1H\e[2J");
          printf("MILHARES DE CARROS ENCONTRADOS, SEJA MAIS ESPECIFICO!\n");
          sleep(3);
          printf("\e[1;1H\e[2J");
          return qtdCarros;
        }
      }
    }
  }

  fclose(ofertas); // Fecha o arquivo

  if (qtdCarros == 0) {
    printf("\e[1;1H\e[2J");
    printf("NENHUM CARRO ENCONTRADO!\n");
    if (remove("cpy_ofertas.csv") != 0) {
      printf("ERRO AO EXCLUIR O ARQUIVO!");
      exit(EXIT_FAILURE);
    }
    sleep(3);
    printf("\e[1;1H\e[2J");
  }

  return qtdCarros;
}

void compraCarro() {
  FILE *ofertas =
      fopen("veiculos_ofertas.csv", "r"); // ARQUIVO DE OFERTAS ORIGINAL
  FILE *cpyOfertas =
      fopen("cpy_ofertas.csv", "a"); // COPIA DO ARQUIVO DE OFERTAS
  FILE *estoque = fopen("veiculos_estoque.csv",
                        "a"); // ARQUIVO QUE ARMAZENA OS VEICULOS EM ESTOQUE
  FILE *historico = fopen("historico_compras.csv",
                          "a"); // ARQUIVO QUE ARMAZENA O HISTORICO DE COMPRAS

  struct tm *data_hora; // VARIAVEL PARA USAR A DATA E HORA DE COMPRA DO VEICULO
  time_t segundos;
  time(&segundos);
  data_hora = localtime(&segundos);

  Carro carro; // STRUCT PARA ALOCAR OS DADOS DO CARRO
  char carrosEncontrado[8000][1000];
  int qtdCarros = filtroDeBusca(
      carrosEncontrado); // CHAMA O FILTRO RETORNA A QUANTIDADE DE CARROS
                         // ENCONTRADOS E PREENCHE O VETOR COM OS CARROS

  if (qtdCarros > 0 && qtdCarros < 8000) {
    printf("\nCARROS ENCONTRADOS:\n");
    for (int i = 0; i < qtdCarros; i++) { // IMPRIME OS CARROS ENCONTRADOS
      printf("%d - %s\n", i, carrosEncontrado[i]);
    }

    char querComprar;
    do {
      printf("DESEJA COMPRAR ALGUM CARRO? [S] SIM / [N] NÃO: ");
      limparBuffer();
      scanf("%c", &querComprar);
      querComprar = toupper(querComprar); // TRANSFORMA A LETRA EM MAIUSCULO
      if (querComprar != 'S' && querComprar != 'N') {
        printf("OPCAO INVALIDA!\n");
      }
    } while (querComprar != 'S' &&
             querComprar !=
                 'N'); // REPETE O LAÇO ATE SER INFORMADA UMA OPÇÃO VALIDA

    if (querComprar == 'S') { // SE O USUARIO QUISER COMPRAR O CARRO
      int qualCompra;
      printf("DIGITE O NUMERO DA LINHA DO CARRO QUE DESEJA COMPRAR: ");
      limparBuffer();
      do {
        scanf("%d", &qualCompra);
        if (qualCompra >= qtdCarros || qualCompra < 0)
          printf("OPCAO INVALIDA!\n");
      } while (qualCompra >= qtdCarros ||
               qualCompra < 0); // REPETE ATE DIGITAR UMA LINHA DE CARRO VALIDA

      char linha[1000]; // VARIAVEL PARA PEGAR A LINHA DO ARQUIVO
      for (int i = 0; i < qtdCarros;
           i++) { // VERIFICA QUAL DOS CARROS QUE O FILTRO ACHOU E O ESCOLHIDO
                  // PARA COMPRA
        if (i == qualCompra) { // SE O CONTADOR FOR IGUAL AO CARRO DESEJADO
          int c = 0;

          while (fgets(linha, sizeof(linha), ofertas) !=
                 NULL) { // LE TODAS AS LINHAS DO ARQUIVO
            if (strcmp(linha, carrosEncontrado[i]) != 0) {
              fputs(linha, cpyOfertas); // COLOCA A LINHA NO ARQUIVO NOVO
            } else if (strcmp(linha, carrosEncontrado[i]) == 0) {
              if (c != qualCompra)
                c++;
            }
          } // REMOVE O CARRO DAS OFERTAS

          char *pedaco = strtok(carrosEncontrado[i], ",");
          c = 0;
          while (pedaco != NULL) {
            switch (c) {
            case 0:
              carro.preco = atof(pedaco);
              break;

            case 1:
              strcpy(carro.ano, pedaco);
              break;

            case 2:
              strcpy(carro.marca.nomeMarca, pedaco);
              break;

            case 3:
              strcpy(carro.marca.modelo, pedaco);
              break;

            case 4:
              strcpy(carro.condicao, pedaco);
              break;

            case 5:
              strcpy(carro.combustivel, pedaco);
              break;

            case 6:
              strcpy(carro.km, pedaco);
              break;

            case 7:
              strcpy(carro.status, pedaco);
              break;

            case 8:
              strcpy(carro.cambio, pedaco);
              break;

            case 9:
              strcpy(carro.tamanho, pedaco);
              break;

            case 10:
              strcpy(carro.tipo, pedaco);
              break;

            case 11:
              strcpy(carro.marca.cor, pedaco);
              break;
            }
            pedaco = strtok(NULL, ","); // OBTEM O PROXIMO PEDAÇO
            c++;
          } // ALOCA OS DADOS DO CARRO NA STRUCT

          carro.preco = operacoesTaxa(carro.preco, carro.marca.nomeMarca);

          fprintf(estoque, "%.2f,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", carro.preco,
                  carro.ano, carro.marca.nomeMarca, carro.marca.modelo,
                  carro.condicao, carro.combustivel, carro.km, carro.status,
                  carro.cambio, carro.tamanho, carro.tipo,
                  carro.marca.cor); // GRAVA O CARRO NO ESTOQUE

          fprintf(historico,
                  "%d/%d/%d,%d:%d:%d,%.2f, %s, %s, %s, %s, %s, %s, %s, %s, %s, "
                  "%s, %s",
                  data_hora->tm_mday, data_hora->tm_mon + 1,
                  data_hora->tm_year + 1900, data_hora->tm_hour,
                  data_hora->tm_min, data_hora->tm_sec, carro.preco, carro.ano,
                  carro.marca.nomeMarca, carro.marca.modelo, carro.condicao,
                  carro.combustivel, carro.km, carro.status, carro.cambio,
                  carro.tamanho, carro.tipo,
                  carro.marca.cor); // GRAVA O CARRO NO HISTORICO
        }
      } // ENCONTRA O CARRO DESEJADO

      fclose(historico);
      fclose(estoque);
      fclose(ofertas);
      fclose(cpyOfertas);

      if (remove("veiculos_ofertas.csv") != 0) {
        printf("ERRO AO EXCLUIR O ARQUIVO!");
        exit(EXIT_FAILURE);
      } // EXCLUI O ARQUIVO ANTIGO

      if (rename("cpy_ofertas.csv", "veiculos_ofertas.csv") != 0) {
        printf("ERRO AO RENOMEAR O ARQUIVO!");
        exit(EXIT_FAILURE);
      } // RENOMEIA O TEMPORARIO COM NOME DO ANTIGO

      printf("\e[1;1H\e[2J");
      printf("VEICULO ADICIONADO AO ESTOQUE\n");
      sleep(3);
    }

    else if (querComprar == 'N') {
      printf("\e[1;1H\e[2J");
      printf("NENHUM VEICULO ADICIONADO AO ESTOQUE!\n");
      sleep(3);
    }
  }
}

void venderCarro() {
  bool filtroPreco = false, filtroAno = false, filtroMarca = false,
       filtroModelo = false, filtroCond = false;
  bool filtroComb = false, filtroKm = false, filtroStts = false,
       filtroCambio = false, filtroTamanho = false, filtroTipo = false,
       filtroCor = false;

  int qntdFiltros, opcaoFiltroUsuario;
  char preco[20], ano[20], marca[20], modelo[20], cond[20], comb[20], km[20],
      stts[20], cambio[20], tam[20], tipo[20], cor[20];
  printf("\e[1;1H\e[2J");
  printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="
         "-\n");
  printf("OPCOES DE FILTRAGEM: [1] PRECO\t [2] ANO\t [3] MARCA\t [4] MODELO\t "
         "[5] CONDICAO\t [6] COMBUSTIVEL\t [7] KILOMETRAGEM\t [8] STATUS\t [9] "
         "CAMBIO\t [10] TAMANHO [11] TIPO\t [12] COR\n");
  printf("DIGITE A QUANTIDADE DE OPCOES DE FILTRAGEM: ");
  do { // ENQUNARO NÂO DIGITA UMA QUANTIDADE DE OPÇOES VALIDA N SAI DO LAÇO.
    scanf("%d", &qntdFiltros);
    limparBuffer();
    if (qntdFiltros < 1 || qntdFiltros > 12) {
      printf("QUANTIDADE INVALIDA!\n");
    }
  } while (qntdFiltros < 1 || qntdFiltros > 12);

  int opcoesEscolhidas[qntdFiltros]; // GUARDA QUAL FORAM AS OPÇOES DE FILTRO
                                     // ESCOLHIADAS

  for (int i = 0; i < qntdFiltros; i++) { // LE AS OPCOES DE FILTRO
    int c = 0;
    printf("DIGITE A %d OPCAO DE FILTRAGEM: ", i + 1);
    scanf("%d", &opcaoFiltroUsuario);
    limparBuffer();
    for (int j = 0; j <= i; j++) { // VERIFICA SE A OPÇÂO JA FOI ESCOLHIDA
      if (opcaoFiltroUsuario == opcoesEscolhidas[j]) {
        c++;
      }
    }
    if (c == 0) { // SE NÂO TIVER SIDO ATRIBUI NO VETOR
      opcoesEscolhidas[i] = opcaoFiltroUsuario;
    } else { // SE TIVER CIDO PEDE PARA DIGITAR DNV
      printf("OPCAO JA DIGITADA, DIGITE NOVAMENTE\n");
      i--;
    }
  }

  for (int i = 0; i < qntdFiltros;
       i++) // Loop que terá varios if(s), verificando o valor da posição i do
            // vetor opcoesEscolhidas.
  { // Para cada valor (De 1 a 12), o programa irá alterar variaveis booleanas
    // relacionadas a cada caso respectivamente.
    if (opcoesEscolhidas[i] ==
        1) // Ex= Caso o valor de qntdFiltros[i] seja 1, a variavel booleana de
           // FiltroPreco será true.
    { // Em seguida o programa receberá do usuario a string relativa a busca
      // (Dentro daquele atributo);
      filtroPreco = true;
      printf("Informe o preco: ");
      fflush(stdin);
      fgets(preco, 20, stdin);
    }
    if (opcoesEscolhidas[i] == 2) {
      filtroAno = true;
      printf("Informe o ano: ");
      fflush(stdin);
      fgets(ano, 20, stdin);
    };
    if (opcoesEscolhidas[i] == 3) {
      filtroMarca = true;
      printf("Informe a marca: ");
      fflush(stdin);
      fgets(marca, 20, stdin);
    }
    if (opcoesEscolhidas[i] == 4) {
      filtroModelo = true;
      printf("Informe o modelo: ");
      fflush(stdin);
      fgets(modelo, 20, stdin);
    }
    if (opcoesEscolhidas[i] == 5) {
      filtroCond = true;
      printf("Informe a condicao: ");
      fflush(stdin);
      fgets(cond, 20, stdin);
    }
    if (opcoesEscolhidas[i] == 6) {
      filtroComb = true;
      printf("Informe o combustivel: ");
      fflush(stdin);
      fgets(comb, 20, stdin);
    }
    if (opcoesEscolhidas[i] == 7) {
      filtroKm = true;
      printf("Informe a kilometragem: ");
      fflush(stdin);
      scanf("%[^\n]", km);
    }
    if (opcoesEscolhidas[i] == 8) {
      filtroStts = true;
      printf("Informe o status: ");
      fflush(stdin);
      fgets(stts, 20, stdin);
    }
    if (opcoesEscolhidas[i] == 9) {
      filtroCambio = true;
      printf("Informe o cambio: ");
      fflush(stdin);
      fgets(cambio, 20, stdin);
    }
    if (opcoesEscolhidas[i] == 10) {
      filtroTamanho = true;
      printf("Informe o tamanho: ");
      fflush(stdin);
      fgets(tam, 20, stdin);
    }
    if (opcoesEscolhidas[i] == 11) {
      filtroTipo = true;
      printf("Informe o tipo: ");
      fflush(stdin);
      fgets(tipo, 20, stdin);
    }
    if (opcoesEscolhidas[i] == 12) {
      filtroCor = true;
      printf("Informe a cor: ");
      fflush(stdin);
      fgets(cor, 20, stdin);
    }
  }
  printf("\e[1;1H\e[2J");

  FILE *veiculos_estoque = fopen(
      "veiculos_estoque.csv",
      "r"); // O programa irá abir o arquivo .csv, onde é armazenado o estoque
            // de veiculos. Modo leitura e escrita (O Arquivo deve existir)
  if (veiculos_estoque ==
      NULL) // Exibe uma mensagem de erro e encerra o programa caso o arquivo
            // não tenha sido aberto corretamente.
  {
    printf("Erro ao consultar o estoque!\n");
    exit(0);
  }
  int countLinha =
      0; // Variavel responsável por contar o numero total de linhas do arquivo.
  char vetorLinha[200]; // Vetor de caracteres que irá receber cada linha do
                        // arquivo de estoque.
  while (fgets(vetorLinha, 200, veiculos_estoque) !=
         NULL) // Inicia um loop que só se encerrará quando o valor da função
               // retornar NULL, ou seja, quando o cursor do arquivo chegar ao
               // final do mesmo.
  {
    char varTeste[200]; // Cria-se um vetor temporario que irá receber uma seção
                        // especifica do vetorLinha (Que será equivalente a uma
                        // das caracteristicas do carro)
    int passaNoFiltro = 0,
        numeroVirgula =
            0;    // Variavel inteira responsavel pela filtragem // Variavel
                  // inteira responsavel pela contagem de virgulas do vetorLinha
    countLinha++; // A cada iteração, o numero de linhas é acrescido em 1
                  // unidade (Já que cada leitura do fgets representa a leitura
                  // de 1 linha)
    for (int i = 0; i < strlen(vetorLinha);
         i++) // Nesse for é realizada uma quantidade de iterações que é igual
              // ao tamanho do vetorLinha (Numero de caracteres da linha)
    {
      if (numeroVirgula == 0 && filtroPreco == true &&
          vetorLinha[i] !=
              ',') // Verifica se é a primeira seção de atributos, verifica se o
                   // filtro preço está sendo utilizado,
      { // e se a posição atual não é um caracter que divide atributos (',')
        int j = 0;
        for (int x = 0; x <= 19; x++) // Limpa todos os caracteres da variavel,
                                      // para evitar lixo de memoria
        {
          varTeste[x] = 0;
        }
        do // inicio do loop
        {
          varTeste[j] = vetorLinha[i]; // iguala o caracter de varTeste[j] ao
                                       // caracter de vetorLinha[i]
          j++;
          i++;
        } while (vetorLinha[i] != ','); // Processo se repete até o caracter
                                        // vetorLinha[i] for igual a ','
        varTeste[j] = '\n'; // Adiciono o caracter \n ao final, para tornar a
                            // comparação abaixo possivel.
        if (strcmp(varTeste, preco) !=
            0) // Comparo se a variavel varTeste e a variavel preco (Com valor
               // recebido do usuario) são iguais. Caso não sejam, o codigo
               // abaixo será executado.
        {
          passaNoFiltro =
              1; // A variavel passaNoFiltro tem seu valor definido como 1
                 // (Tornando a linha invalida para ser exibida na tela)
        }
      } else if (numeroVirgula == 1 && filtroAno == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\n';
        if (strcmp(varTeste, ano) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 2 && filtroMarca == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\n';
        if (strcmp(varTeste, marca) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 3 && filtroModelo == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\n';
        if (strcmp(varTeste, modelo) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 4 && filtroCond == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\n';
        if (strcmp(varTeste, cond) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 5 && filtroComb == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\n';
        if (strcmp(varTeste, comb) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 6 && filtroKm == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\0';
        if (strcmp(varTeste, km) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 7 && filtroStts == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\n';
        if (strcmp(varTeste, stts) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 8 && filtroCambio == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\n';
        if (strcmp(varTeste, cambio) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 9 && filtroTamanho == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\n';
        if (strcmp(varTeste, tam) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 10 && filtroTipo == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != ',');
        varTeste[j] = '\n';
        if (strcmp(varTeste, tipo) != 0) {
          passaNoFiltro = 1;
        }
      } else if (numeroVirgula == 11 && filtroCor == true &&
                 vetorLinha[i] != ',') {
        int j = 0;
        for (int x = 0; x <= 19; x++) {
          varTeste[x] = 0;
        }
        do {
          varTeste[j] = vetorLinha[i];
          j++;
          i++;
        } while (vetorLinha[i] != '\n');
        varTeste[j] = '\n';
        if (strcmp(varTeste, cor) != 0) {
          passaNoFiltro = 1;
        }
      }

      if (vetorLinha[i] == ',') {
        numeroVirgula++;
      }

      if(passaNoFiltro != 0){
          break;
      }
    }

    if (passaNoFiltro ==
        0) // Verifica, após toda a execução do for, se a variavel passaNoFiltro
           // continua com seu valor inalterado (Sinalizando que a linha é
           // relevante com base nos filtros selecionados)
    {
      printf("%d - %s", countLinha,
             vetorLinha); // Exibe efetivamente a linha relevante, e o respetivo
                          // numero da linha.
    }
  }
  int escolhaVenda; // variavel que irá receber a escolha de venda do usuario
                    // (Numero da linha do veiculo que será vendido)
  do {
    printf("\nEscolha qual sera vendido:\n");
    scanf("%d", &escolhaVenda);
  } while (escolhaVenda > countLinha || escolhaVenda < 0);
  limparBuffer(); // repete a requisição do valor de escolhaVenda até que seja
                  // menor que a quantidade de linhas do arquivo e maior que 0
  printf("\e[1;1H\e[2J");
  rewind(veiculos_estoque); // Reseta o cursor de leitura/escrita do arquivo
                            // (Volta ele para o inicio)
  FILE *veiculos_estoque2 =
      fopen("veiculos_estoque2.csv", "w+"); // Abre o arquivo temporário
  FILE *historicoVendas =
      fopen("historico_vendas.csv",
            "a+"); // Abre ou cria o arquivo de historico de vendas
  if (historicoVendas == NULL) {
    printf("Erro ao abrir o arquivo de historico de vendas!\n");
  } else if (veiculos_estoque2 == NULL) {
  }
  char copiarLinha[200]; // Variavel que receberá cada linha do arquivo
                         // veiculos_estoque.csv
  char buffer[20];       // Tamanho suficiente para armazenar a data formatada
  for (int i = 1; i <= countLinha; i++) // Cada iteração representará 1 linha do
                                        // arquivo veiculos_estoque.csv
  {
    if (escolhaVenda == i) // Caso o numero da linha atual seja igual ao
                           // informado pelo usuario anteriormente/ Numero da
                           // linha seja do carro escolhido para ser vendido
    {
      fgets(copiarLinha, 200,
            veiculos_estoque); // Copia a linha atual para a string copiarLinha
      char temp[200];
      for (int i = 0; i < 100; i++) {
        temp[i] = 0;
      }
      for (int i = 0; i < 20; i++) {
        buffer[i] = 0;
      }

      time_t t;
      struct tm *info;

      time(&t);
      info = localtime(&t);

      // Formata a data e hora e armazena em buffer
      strftime(buffer, sizeof(buffer), "%d/%m/%Y,%H:%M:%S", info);
      buffer[(strlen(buffer))] = 0;
      strcat(temp,
             buffer); // Concatena a string de data/horario e a da linha atual
      strcat(temp, ",");
      strcat(temp, copiarLinha);
      printf("O Veiculo escolhido foi vendido, removido do estoque e "
             "adicionado ao historico de vendas.\n");

      fputs(temp, historicoVendas); // Coloca a string atual no arquivo
                                    // historico_vendas.csv
      fflush(historicoVendas);      // Limpa o Buffer do arquivo
      continue; // Continua para a proxima iteração do for, ignorando o codigo
                // abaixo
    }
    fgets(copiarLinha, 200,
          veiculos_estoque); // Copia a linha atual do arquivo veiculos_estoque
                             // para o vetor copiarLinha
    fputs(copiarLinha, veiculos_estoque2); // Copia a string copiarLinha para o
                                           // arquivo_estoque2
    fflush(veiculos_estoque2); // Limpa o Buffer do arquivo veiculos_estoque2
  }
  // Fecha os arquivos, exclui o arquivo veiculos_estoque.cs e renomeira o
  // arquivo veiculos_estoque2.csv para veiculos_estoque.csv
  fclose(veiculos_estoque2);
  fclose(veiculos_estoque);
  fclose(historicoVendas);
  remove("veiculos_estoque.csv");
  rename("veiculos_estoque2.csv", "veiculos_estoque.csv");
}

void alteraTaxa(){
  Carro carro;
  char Marcas[500][100];
  char linhaArquivo[100];
  int contaLinha = 0, linhaMarca;
  float taxa;

  FILE *marcas = fopen("marcas.csv", "r");
  if(marcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }
  FILE *cpymarcas = fopen("copia_marcas.csv", "a");
  if(cpymarcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }

  printf("MARCAS E SUAS TAXAS\n");
  while(fgets(linhaArquivo, sizeof(linhaArquivo), marcas) != NULL){
    printf("%d - %s",contaLinha, linhaArquivo);
    strcpy(Marcas[contaLinha], linhaArquivo);
    contaLinha++;
  }

  printf("\nDIGITE A LINHA DA MARCA QUE DESEJA A ALTERACAO: ");
  scanf("%d", &linhaMarca);

  sscanf(Marcas[linhaMarca], "%20[^,],%f[^\n]",carro.marca.nomeMarca, &taxa);
  for(int i = 0; i < contaLinha; i++){
    if(i != linhaMarca){
      fprintf(cpymarcas, "%s", Marcas[i]);
    }
  }

  printf("DIGITE A NOVA TAXA PARA A MARCA %s: ", carro.marca.nomeMarca);
  scanf("%f",&taxa);

  fprintf(cpymarcas, "%s,%.2f\n",carro.marca.nomeMarca, taxa);

  fclose(marcas);
  fclose(cpymarcas);

  if (remove("marcas.csv") != 0) {
    printf("ERRO AO EXCLUIR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // EXCLUI O ARQUIVO ANTIGO

  if (rename("copia_marcas.csv", "marcas.csv") != 0) {
    printf("ERRO AO RENOMEAR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // RENOMEIA O TEMPORARIO COM NOME DO ANTIGO
  
  system("clear");
  printf("TAXA MODIFICADA!\n");
  sleep(3);
}//ALTERA A TAXA DE UMA MARCA
void alteraPreco(){//ALTERA O PRECO DE UM CARRO DO ESTOQUE
  Carro carro;
  char Carros[500][1000];
  char linhaArquivo[1000];
  int contaLinha = 0, linhaMarca;

  FILE *marcas = fopen("veiculos_estoque.csv", "r");
  if(marcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }
  FILE *cpymarcas = fopen("copia_estoque.csv", "a");
  if(cpymarcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }

  printf("VEICULOS DO ESTOQUE\n");
  while(fgets(linhaArquivo, sizeof(linhaArquivo), marcas) != NULL){
    printf("%d - %s",contaLinha, linhaArquivo);
    strcpy(Carros[contaLinha], linhaArquivo);
    contaLinha++;
  }

  printf("\nDIGITE A LINHA DO CARRO QUE DESEJA A ALTERACAO: ");
  scanf("%d", &linhaMarca);

  sscanf(Carros[linhaMarca],"%f,%4[^,],%20[^,],%49[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^\n]",&carro.preco,carro.ano,carro.marca.nomeMarca,carro.marca.modelo,carro.condicao,carro.combustivel,carro.km,carro.status,carro.cambio,carro.tamanho,carro.tipo,carro.marca.cor);
  for(int i = 0; i < contaLinha; i++){
    if(i != linhaMarca){
      fprintf(cpymarcas, "%s", Carros[i]);
    }
  }

  printf("DIGITE O NOVO PRECO PARA O CARRO: ");
  scanf("%f",&carro.preco);

  fprintf(cpymarcas,"%.2f,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",carro.preco,carro.ano,carro.marca.nomeMarca,carro.marca.modelo,carro.condicao,carro.combustivel,carro.km,carro.status,carro.cambio,carro.tamanho,carro.tipo,carro.marca.cor);

  fclose(marcas);
  fclose(cpymarcas);

  if (remove("veiculos_estoque.csv") != 0) {
    printf("ERRO AO EXCLUIR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // EXCLUI O ARQUIVO ANTIGO

  if (rename("copia_estoque.csv", "veiculos_estoque.csv") != 0) {
    printf("ERRO AO RENOMEAR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // RENOMEIA O TEMPORARIO COM NOME DO ANTIGO

  system("clear");
  printf("PRECO MODIFICADO!\n");
  sleep(3);
}//ALTERA O PRECO DE UM CARRO
void alteraCor(){//ALTERA O PRECO DE UM CARRO DO ESTOQUE
  Carro carro;
  char Carros[500][1000];
  char linhaArquivo[1000];
  int contaLinha = 0, linhaMarca;

  FILE *marcas = fopen("veiculos_estoque.csv", "r");
  if(marcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }
  FILE *cpymarcas = fopen("copia_estoque.csv", "a");
  if(cpymarcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }

  printf("VEICULOS DO ESTOQUE\n");
  while(fgets(linhaArquivo, sizeof(linhaArquivo), marcas) != NULL){
    printf("%d - %s",contaLinha, linhaArquivo);
    strcpy(Carros[contaLinha], linhaArquivo);
    contaLinha++;
  }

  printf("\nDIGITE A LINHA DO CARRO QUE DESEJA A ALTERACAO: ");
  scanf("%d", &linhaMarca);

  sscanf(Carros[linhaMarca],"%f,%4[^,],%20[^,],%49[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^\n]",&carro.preco,carro.ano,carro.marca.nomeMarca,carro.marca.modelo,carro.condicao,carro.combustivel,carro.km,carro.status,carro.cambio,carro.tamanho,carro.tipo,carro.marca.cor);
  for(int i = 0; i < contaLinha; i++){
    if(i != linhaMarca){
      fprintf(cpymarcas, "%s", Carros[i]);
    }
  }

  limparBuffer();
  printf("DIGITE A NOVA COR PARA O CARRO: ");
  scanf("%20[^\n]",carro.marca.cor);

  fprintf(cpymarcas,"%.2f,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",carro.preco,carro.ano,carro.marca.nomeMarca,carro.marca.modelo,carro.condicao,carro.combustivel,carro.km,carro.status,carro.cambio,carro.tamanho,carro.tipo,carro.marca.cor);

  fclose(marcas);
  fclose(cpymarcas);

  if (remove("veiculos_estoque.csv") != 0) {
    printf("ERRO AO EXCLUIR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // EXCLUI O ARQUIVO ANTIGO

  if (rename("copia_estoque.csv", "veiculos_estoque.csv") != 0) {
    printf("ERRO AO RENOMEAR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // RENOMEIA O TEMPORARIO COM NOME DO ANTIGO

  system("clear");
  printf("COR MODIFICADA!\n");
  sleep(3);
}//ALTERA A COR DE UM CARRO
void alteraCondicao(){//ALTERA O PRECO DE UM CARRO DO ESTOQUE
  Carro carro;
  char Carros[500][1000];
  char linhaArquivo[1000];
  int contaLinha = 0, linhaMarca;

  FILE *marcas = fopen("veiculos_estoque.csv", "r");
  if(marcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }
  FILE *cpymarcas = fopen("copia_estoque.csv", "a");
  if(cpymarcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }

  printf("VEICULOS DO ESTOQUE\n");
  while(fgets(linhaArquivo, sizeof(linhaArquivo), marcas) != NULL){
    printf("%d - %s",contaLinha, linhaArquivo);
    strcpy(Carros[contaLinha], linhaArquivo);
    contaLinha++;
  }

  printf("\nDIGITE A LINHA DO CARRO QUE DESEJA A ALTERACAO: ");
  scanf("%d", &linhaMarca);

  sscanf(Carros[linhaMarca],"%f,%4[^,],%20[^,],%49[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^\n]",&carro.preco,carro.ano,carro.marca.nomeMarca,carro.marca.modelo,carro.condicao,carro.combustivel,carro.km,carro.status,carro.cambio,carro.tamanho,carro.tipo,carro.marca.cor);
  for(int i = 0; i < contaLinha; i++){
    if(i != linhaMarca){
      fprintf(cpymarcas, "%s", Carros[i]);
    }
  }

  limparBuffer();
  printf("DIGITE A NOVA CONDICAO PARA O CARRO: ");
  scanf("%20[^\n]",carro.condicao);

  fprintf(cpymarcas,"%.2f,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",carro.preco,carro.ano,carro.marca.nomeMarca,carro.marca.modelo,carro.condicao,carro.combustivel,carro.km,carro.status,carro.cambio,carro.tamanho,carro.tipo,carro.marca.cor);

  fclose(marcas);
  fclose(cpymarcas);

  if (remove("veiculos_estoque.csv") != 0) {
    printf("ERRO AO EXCLUIR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // EXCLUI O ARQUIVO ANTIGO

  if (rename("copia_estoque.csv", "veiculos_estoque.csv") != 0) {
    printf("ERRO AO RENOMEAR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // RENOMEIA O TEMPORARIO COM NOME DO ANTIGO

  system("clear");
  printf("CONDICAO MODIFICADA!\n");
  sleep(3);
}//ALTERA A CONDICAO DE UM CARRO
void alteraStts(){//ALTERA O PRECO DE UM CARRO DO ESTOQUE
  Carro carro;
  char Carros[500][1000];
  char linhaArquivo[1000];
  int contaLinha = 0, linhaMarca;

  FILE *marcas = fopen("veiculos_estoque.csv", "r");
  if(marcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }
  FILE *cpymarcas = fopen("copia_estoque.csv", "a");
  if(cpymarcas == NULL){
    printf("ERRO AO ARBIR O ARQUIVO MARCAS!");
    exit(EXIT_FAILURE);
  }

  printf("VEICULOS DO ESTOQUE\n");
  while(fgets(linhaArquivo, sizeof(linhaArquivo), marcas) != NULL){
    printf("%d - %s",contaLinha, linhaArquivo);
    strcpy(Carros[contaLinha], linhaArquivo);
    contaLinha++;
  }

  printf("\nDIGITE A LINHA DO CARRO QUE DESEJA A ALTERACAO: ");
  scanf("%d", &linhaMarca);

  sscanf(Carros[linhaMarca],"%f,%4[^,],%20[^,],%49[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^,],%20[^\n]",&carro.preco,carro.ano,carro.marca.nomeMarca,carro.marca.modelo,carro.condicao,carro.combustivel,carro.km,carro.status,carro.cambio,carro.tamanho,carro.tipo,carro.marca.cor);
  for(int i = 0; i < contaLinha; i++){
    if(i != linhaMarca){
      fprintf(cpymarcas, "%s", Carros[i]);
    }
  }

  limparBuffer();
  printf("DIGITE O NOVO STATUS PARA O CARRO: ");
  scanf("%20[^\n]",carro.status);

  fprintf(cpymarcas,"%.2f,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",carro.preco,carro.ano,carro.marca.nomeMarca,carro.marca.modelo,carro.condicao,carro.combustivel,carro.km,carro.status,carro.cambio,carro.tamanho,carro.tipo,carro.marca.cor);

  fclose(marcas);
  fclose(cpymarcas);

  if (remove("veiculos_estoque.csv") != 0) {
    printf("ERRO AO EXCLUIR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // EXCLUI O ARQUIVO ANTIGO

  if (rename("copia_estoque.csv", "veiculos_estoque.csv") != 0) {
    printf("ERRO AO RENOMEAR O ARQUIVO!");
    exit(EXIT_FAILURE);
  } // RENOMEIA O TEMPORARIO COM NOME DO ANTIGO

  system("clear");
  printf("COR MODIFICADA!\n");
  sleep(3);
}//ALTERA O STATUS DE UM CARRO
void alteraDados(){
  int op = 0;
  do{
    system("clear");
    printf("OPCOES DE ALTERACAO \n[1] TAXA \n[2] PRECO DE VENDA \n[3] COR \n[4] CONDICAO \n[5] STATUS \n[6] VOLTAR\n");
    scanf("%d",&op);
  
    if(op == 1){
      system("clear");
      alteraTaxa();
    }
  
    else if(op == 2){
      system("clear");
      alteraPreco();
    }
  
    else if(op == 3){
      system("clear");
      alteraCor();
    }
  
    else if(op == 4){
      system("clear");
      alteraCondicao();
    }
  
    else if(op == 5){
      system("clear");
      alteraStts();
    }
      
    else{
      printf("OPCAO INVALIDA!");
    }
    
  }while(op != 6);



}

void geraRelatorios() {
  // Abrir o arquivo historico_vendas.csv para leitura
  FILE *arquivoVendas = fopen("historico_vendas.csv", "r");
  if (arquivoVendas == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  // Abrir o arquivo historico_compras.csv para leitura
  FILE *arquivoCompras = fopen("historico_compras.csv", "r");
  if (arquivoCompras == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  char vendido[1000][1000];
  char comprado[1000][1000];
  int contCompra = 0, contVenda = 0;

  char dataInicial[11];
  char dataFinal[11];

  printf("Digite a data inicial (formato DD/MM/AAAA): ");
  limparBuffer();
  scanf("%[^\n]", dataInicial);

  printf("Digite a data final (formato DD/MM/AAAA): ");
  limparBuffer();
  scanf("%[^\n]", dataFinal);

  double saldoVendas = 0.0;
  double saldoCompras = 0.0;
  char valorVenda[15];
  char horaVenda[8];
  float preco;

  // Ler as vendas dentro do período especificado
  char dataVenda[11];
  char linha[1000]; // Linha tendo no máximo 100 caracteres
  while (fgets(linha, sizeof(linha), arquivoVendas) != NULL) {
    sscanf(linha, "%[^,],%[^,],%[^,]", dataVenda, horaVenda, valorVenda);
    preco = atof(valorVenda);
    // Comparar a data da venda com as datas inicial e final
    if (strcmp(dataVenda, dataInicial) >= 0 &&
        strcmp(dataVenda, dataFinal) <= 0) {
      // A venda ocorreu dentro do período especificado
      saldoVendas += preco;
      strcpy(vendido[contVenda], linha);
      contVenda++;
    }
  }

  char dataCompra[11];
  char valorCompra[15];
  char horaCompra[8];
  // Ler as compras dentro do período especificado
  while (fgets(linha, sizeof(linha), arquivoCompras) != NULL) {
    sscanf(linha, "%[^,],%[^,],%[^,]", dataCompra, horaCompra, valorCompra);
    preco = atof(valorCompra);
    // Comparar a data da compra com as datas inicial e final
    if (strcmp(dataCompra, dataInicial) >= 0 &&
        strcmp(dataCompra, dataFinal) <= 0) {
      // A compra ocorreu dentro do período especificado
      saldoCompras += preco;
      strcpy(comprado[contCompra], linha);
      contCompra++;
    }
  }

  // Calculo do saldo final
  double saldoFinal = saldoVendas - saldoCompras;

  int opcao;

  printf("OPCOES DE RELATORIO: [1] TELA   [2] ARQUIVO TXT: ");
  scanf("%d", &opcao);
  limparBuffer();

  if (opcao == 1) {
    // Escreve na tela
    printf("\nExtrato de Compras e Vendas - Período de %s a %s\n\n",
           dataInicial, dataFinal);
    printf("Vendas:\n");
    for (int i = 0; i < contVenda; i++) {
      printf("%s", vendido[i]);
    }
    printf("\nCompras:\n");
    for (int i = 0; i < contCompra; i++) {
      printf("%s", comprado[i]);
    }
    printf("\nSaldo Final: %.2lf\n", saldoFinal);
    char sair;
    printf("\nPRECIONE ENTER PARA SAIR\n");
    scanf("%c", &sair);

  } // MOSTRA O RELATORIO NA TELA
  else if (opcao == 2) {
    FILE *arquivoRelatorio = fopen(
        "relatorio.txt", "w"); // Abrir o arquivo de relatório para escrita
    if (arquivoRelatorio == NULL) {
      printf("Erro ao abrir o arquivo de relatório\n");
      exit(EXIT_FAILURE);
    }
    // Escreve no arquivo
    fprintf(arquivoRelatorio,
            "\nExtrato de Compras e Vendas - Período de %s a %s\n\n",
            dataInicial, dataFinal);
    fprintf(arquivoRelatorio, "Vendas:\n");
    for (int i = 0; i < contVenda; i++) {
      fprintf(arquivoRelatorio, "%s", vendido[i]);
    }
    fprintf(arquivoRelatorio, "\nCompras:\n");
    for (int i = 0; i < contCompra; i++) {
      fprintf(arquivoRelatorio, "%s", comprado[i]);
    }
    fprintf(arquivoRelatorio, "\nSaldo Final: %.2lf\n", saldoFinal);

    fclose(arquivoRelatorio);
    printf("RELATORIO EFETUADO COM SUCESSO!\n");
    sleep(3);
  } // GRAVA O RELATORIO EM UM ARQUIVO TXT

  fclose(arquivoVendas);
  fclose(arquivoCompras);
}

void Realizar_Backup(const char *nome_original) {
  // Abre o arquivo original em modo leitura de texto
  FILE *arquivo_original = fopen(nome_original, "r");
  if (arquivo_original == NULL) {
    printf("ERRO AO ABRIR O ARQUIVO %s", nome_original);
    perror("\n");
    return;
  }

  // Cria a subpasta "Backup" se ela não existir
  system("mkdir -p Backup");

  // Monta o nome do arquivo de backup na subpasta
  char nome_backup[1000];
  sprintf(nome_backup, "Backup/Backup_%s.bin", nome_original);

  // Abre o arquivo de backup em modo escrita binária
  FILE *arquivo_backup = fopen(nome_backup, "wb");
  if (arquivo_backup == NULL) {
    perror("ERRO AO RALIZAR O BACKUP!");
    fclose(arquivo_original);
    return;
  }

  char caractere;
  // Copia os dados completos do arquivo original para o arquivo de backup em
  // formato binário
  while ((caractere = fgetc(arquivo_original)) != EOF) {
    fwrite(&caractere, sizeof(char), 1, arquivo_backup);
  }

  // Fecha os arquivos
  fclose(arquivo_original);
  fclose(arquivo_backup);

  // Informa que o backup foi realizado com sucesso
  printf("O BACKUP DE DADOS FOI REALIZADO COM SUCESSO PARA %s\n", nome_backup);
} // Função para realizar o backup de um arquivo de texto para um arquivo
  // binário na subpasta "Backup"
void Deletar_Backup(const char *nome_original) {
  // Monta o nome do arquivo de backup na subpasta
  char nome_backup[1000];
  sprintf(nome_backup, "Backup/Backup_%s.bin", nome_original);

  // Tenta deletar o arquivo de backup
  if (remove(nome_backup) == 0) {
    printf("O BACKUP %s FOI EXCLUIDO COM SUCESSO!\n", nome_backup);
  } else {
    perror("ERRO AO EXCLUIR O BACKUP!");
  }

} // Função para deletar o backup de um arquivo
void Fazer_Backup_Todos() {
  for (int i = 0; i < sizeof(nomes_arquivos) / sizeof(nomes_arquivos[0]); ++i) {
    Realizar_Backup(nomes_arquivos[i]);
  }
  char sair;
  printf("\n\nPRECIONE ENTER PARA VOLTAR AO MENU\n");
  limparBuffer();
  scanf("%c", &sair);
  printf("\e[1;1H\e[2J");
} // Função para fazer backup de todos os arquivos
void opBackup() {
  int op = -1;
  do {
    printf("MENU BACKUP:\n");
    printf("[1] FAZER BACKUP DE TODOS OS ARQUIVOS\n");
    printf("[2] DELETAR BACKUPS EXISTENTES\n");
    printf("[3] VOLTAR AO MENU PRINCIPAL\n");
    scanf("%d", &op);

    switch (op) {
    case 1:
      Fazer_Backup_Todos(); // Realiza backup para todos os arquivos da lista
      break;
    case 2:
      for (int i = 0; i < sizeof(nomes_arquivos) / sizeof(nomes_arquivos[0]);
           ++i) { // Deleta backups para todos os arquivos da lista
        Deletar_Backup(nomes_arquivos[i]);
      }
      char sair;
      printf("\n\nPRECIONE ENTER PARA VOLTAR AO MENU\n");
      limparBuffer();
      scanf("%c", &sair);
      printf("\e[1;1H\e[2J");
      break;
    case 3:
      // Volta ao Menu Principal
      break;
    default:
      printf(
          "Opcao invalida. Tente novamente.\n"); // Mensagem para opção inválida
    }
  } while (op != 3);
} // ESCOLHE A OPCAO DE BACKUP

int main() {
  int op = 0;
  while (op != 6) {
    system("clear");
    printf("[1] COMPRA DE VEICULOS \n[2] VENDA DE VEICULOS \n[3] GERAR "
           "RELATORIO \n[4] BACKUP \n[5] ALTERAR DADOS \n[6] SAIR\n");
    scanf("%d", &op);

    switch (op) {
    case 1:
      printf("\e[1;1H\e[2J");
      compraCarro();
      break;
    case 2:
      printf("\e[1;1H\e[2J");
      venderCarro();
      break;
    case 3:
      printf("\e[1;1H\e[2J");
      geraRelatorios();
      break;
    case 4:
      printf("\e[1;1H\e[2J");
      opBackup();
      break;
    case 5:
      printf("\e[1;1H\e[2J");
      alteraDados();
    default:
      if (op > 6 || op < 1) {
        printf("OPCAO INVALIDA!\n");
        sleep(2);
      }
    }
  }
  return 0;
}
// printf("\e[1;1H\e[2J");
