/*Agenda de Contatos*/
// Arquivos necessários
#include "sll.h"
#include <reg52.h>
#include <stdio.h>
#include <string.h>

// estruturas
struct nasc {
  unsigned int dia;
  unsigned int mes;
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
  "José Eduardo",     "71974859613", 30, 6, 1989, 4,
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

    printf("| Menu - Digite a opção desejada    |\n");
    printf("| [L] - Lista de Contatos ok          |\n");
    printf("| [N] - Pesquisa por nome  ok!!         |\n");
    printf("| [I] - Pesquisa por idade          |\n");
    printf("| [R] - Pesquisa por Relacionamento | \n");
    printf("| [A] - Adcionar contato    ok!!        |\n");
    printf("| [D] - Deletar contato             |\n");
    printf("| [E] - Renomear contato    ok!!        | \n");
    printf("+-----------------------------------+\n\n");

    c = getchar();

    if (c == 'l' || c == 'L') {
      // Lógica para listar os contatos
      printf("/f");
      printf("Lista de Contatos selecionada.\n");
      for (n = 0; n < 500; n++) {
        // exibe todos contatos da lista
        if (contatos[n].nome[0] != 0) {       
          printf("%s %s %bd\n", contatos[n].nome, contatos[n].tel,
          contatos[n].relacionamento);
        }
      }
      printf("\n Pressione espaço para continuar");
      while (getchar() != ' ')
        ;

    } 
    else if (c == 'n' || c == 'N') {
      // Lógica para pesquisar por nome
      printf("Pesquisa por nome selecionada.\n");
      gets(string, 32);
      printf("Digite o nome\n");
      for (n = 0; n < 500; n++) {
        if (strstr(contatos[n].nome, string) != NULL) {
          printf("%s %s %bd\n", contatos[n].nome, contatos[n].tel,
          contatos[n].relacionamento);
        }
      }
      printf("\n Pressione espaço para continuar");
      while (getchar() != ' ');
    } 
    else if (c == 'i' || c == 'I') {

      // Lógica para pesquisar por idade
      printf("Pesquisa por idade selecionada.\n");
    } 
    else if (c == 'r' || c == 'R') {

      // Lógica para pesquisar por relacionamento
      printf("Pesquisa por relacionamento selecionada.\n");

    } 
    else if (c == 'a' || c == 'A') {
      // Lógica para adicionar contato
      printf("Adicionar contato selecionado.\n");

      for (n = 0; n < 500; n++) {
        if (contatos[n].nome[0] == 0) {

          printf("Insira o nome\n");
          scanf("%s", contatos[n].nome);

          printf("Digite o telefone do contato: ");
          scanf("%s", contatos[n].tel);

			printf("Digite a data de nascimento do contato (dia mês ano):\n ");
			scanf("%d %d %d", &contatos[n].datan.dia, &contatos[n].datan.mes, &contatos[n].datan.ano);
			printf("Data de Nascimento: %d / %d / %d", contatos[n].datan.dia, contatos[n].datan.mes, contatos[n].datan.ano);


          printf("\nDigite o relacionamento do contato: ");
          scanf(" %c", contatos[n].relacionamento);

          printf("\n Pressione espaço para voltar");
          while (getchar() != ' ');
          break;
        } 
      }
    } 
    else if (c == 'd' || c == 'D') {
      // Lógica para deletar contato
      printf("Deletar contato selecionado.\n");

    } 
    else if (c == 'e' || c == 'E') {

      // Lógica para renomear contato
      printf("\nDigite o nome do contato que deseja renomear\n");
      gets(string, 32); // Le e armazena na var string

	  // Varre TODO o array independente se ha ou nao valores
      for (n = 0; n < 500; n++) {

	  	// verifica se 'string' contida é diferente de null
        if (strstr(contatos[n].nome, string) != NULL) {	
          printf("%d""º " "%s %s %bd\n",n, contatos[n].nome, contatos[n].tel,
          contatos[n].relacionamento); //lista contatos com numerador
        }
      }
      printf("\nInforme o numero correspondente ao contato. \n");

	  // Lógica verifica entrada 
	  while (1) {
		if (scanf("%d", &selecionado) != 1) {
        printf("Digite apenas números!\n");
        } else {
		  if (selecionado < 0 || selecionado > 500){
			printf("Número fora de intervalo, digite novamente");
	      }	else {
		    getchar(); // Limpa resíduos de scanf
		  	break;
		  }
		}   
	  }
	  // Recebe e atualiza nome
      printf("Informe o novo nome do contato:\n");
	  gets(string, 32);
	  strcpy(contatos[selecionado].nome, string);
	  // Fim da lógica para renomear

      printf("\n --> Pressione espaço para continuar <--");
      while (getchar() != ' ');

    } else { // Sem correspondência das alternativas
      printf("\nOpção inválida. Tente novamente.\n");
      while (getchar() != ' ');
    }
  } // while primario
} // main