/*Agenda de Contatos*/
// Arquivos necess�rios
#include "sll.h"
#include <reg52.h>
#include <stdio.h>
#include <string.h>

// estruturas
struct nasc {
  char dia;
  char mes;
  unsigned int ano;
};

struct registro {
  char nome[32]; // no final tem o 0 - 31 caracteres
  char tel[14];  // 13 caracteres
  struct nasc datan;
  char relacionamento;
};

struct registro code contatosold[10] = {
  "Lindomar Mir",     "71974859614", 12, 6, 2007, 0,
  "Clea Santos",      "71987412345", 20, 6, 2003, 1,
  "Franklin Savaget", "72999121620", 18, 6, 2008, 2,
  "Mariana Barros",   "74974859613", 12, 6, 2002, 3,
  "Jos� Eduardo",     "71974859613", 30, 6, 1989, 4,
  "Tatiana Oliveira", "71974859610", 12, 6, 1999, 5,
  "Camila de Jesus",  "71974859615", 1,  6, 1957, 6,
  "Louise Poliana",   "79987514952", 30, 6, 1962, 7,
  "Heitor Dias",      "71984125247", 12, 6, 1975, 8,
  "Reinaldo Goes",    "71974859618", 27, 8, 1978, 9};

struct registro xdata contatos[500];

// funcao principal
void main(void) {
  // declaracoes de variaveis
  char c;
  int n;
  int selecionado;
  char string[32];
  TMOD = 0x20;
  SCON = 0X52;
  TH1 = (256 - 13);
  PCON |= 0X80;
  TR1 = 1;
  // limpeza
  memset(&contatos, 0, sizeof(contatos));
  // copia struc old para contatos
  memcpy(&contatos, &contatosold, sizeof(contatosold));

  while (1) {
    printf("\f+-----------------------------------+\n"
      "|                                   |\n"
      "|     AGENDA DE CONTATOS            |\n"
      "|                                   |\n");

    printf("| Menu - Digite a op��o desejada    |\n");
    printf("| [L] - Lista de Contatos           |\n");
    printf("| [N] - Pesquisa por nome           |\n");
    printf("| [I] - Pesquisa por idade          |\n");
    printf("| [R] - Pesquisa por Relacionamento | \n");
    printf("| [A] - Adcionar contato            |\n");
    printf("| [D] - Deletar contato             |\n");
    printf("| [E] - Renomear contato            | \n");
    printf("+-----------------------------------+\n\n");

    c = getchar();

    if (c == 'l' || c == 'L') {
      // L�gica para listar os contatos
      printf("/f");
      printf("Lista de Contatos selecionada.\n");
      for (n = 0; n < 500; n++) {
        // exibe todos contatos da lista
        if (contatos[n].nome[0] != 0) {       
          printf("%s %s %bd\n", contatos[n].nome, contatos[n].tel,
          contatos[n].relacionamento);
        }
      }
      printf("\n Pressione espa�o para continuar");
      while (getchar() != ' ')
        ;

    } 
    else if (c == 'n' || c == 'N') {
      // L�gica para pesquisar por nome
      printf("Pesquisa por nome selecionada.\n");
      gets(string, 32);
      printf("Digite o nome\n");
      for (n = 0; n < 500; n++) {
        if (strstr(contatos[n].nome, string) != NULL) {
          printf("%s %s %bd\n", contatos[n].nome, contatos[n].tel,
          contatos[n].relacionamento);
        }
      }
      printf("\n Pressione espa�o para continuar");
      while (getchar() != ' ');
    } 
    else if (c == 'i' || c == 'I') {

      // L�gica para pesquisar por idade
      printf("Pesquisa por idade selecionada.\n");
    } 
    else if (c == 'r' || c == 'R') {

      // L�gica para pesquisar por relacionamento
      printf("Pesquisa por relacionamento selecionada.\n");

    } 
    else if (c == 'a' || c == 'A') {
      // L�gica para adicionar contato
      printf("Adicionar contato selecionado.\n");

      for (n = 0; n < 500; n++) {
        if (contatos[n].nome[0] == 0) {

          printf("Insira o nome\n");
          scanf("%s", contatos[n].nome);

          printf("Digite o telefone do contato: ");
          scanf("%s", contatos[n].tel);

          printf("Digite a data de nascimento do contato (dia m�s ano): ");
          scanf("%d %d %d", contatos[n].datan.dia, contatos[n].datan.mes,
          contatos[n].datan.ano);

          printf("Digite o relacionamento do contato: ");
          scanf(" %c", contatos[n].relacionamento);

          printf("\n Pressione espa�o para voltar");
          while (getchar() != ' ');
          break;

        } 
      }
    } 
    else if (c == 'd' || c == 'D') {
      // L�gica para deletar contato
      printf("Deletar contato selecionado.\n");

    } 
    else if (c == 'e' || c == 'E') {
      // L�gica para renomear contato
      gets(string, 32);
      printf("Digite o nome\n");
      gets(string, 32);
      for (n = 0; n < 500; n++) {
        if (strstr(contatos[n].nome, string) != NULL) {
          printf("%d""� " "%s %s %bd\n",n, contatos[n].nome, contatos[n].tel,
          contatos[n].relacionamento);
        }
      }
      printf("Informe o numero do contato a selecionar");
      selecionado = getchar();
      printf("Nome do contato novo");
 //     contatos[selecionado].nome = contatos[string]
      printf("\n Pressione espa�o para continuar");
      while (getchar() != ' ');
     

    } // else if E 
    else {
      printf("\nOp��o inv�lida. Tente novamente.\n");
      while (getchar() != ' ');
    }
  } // while primario
} // main