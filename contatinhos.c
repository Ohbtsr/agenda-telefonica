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
  unsigned int relacionamento; 
 
};

struct registro code contatosold[10] = {
    "Lindomar Mir",     "71974859614", 12, 6, 2007, 0,
    "Clea Santos",      "71987412345", 20, 6, 2003, 1,
    "Franklin Savaget", "72999121620", 18, 6, 2008, 1,
    "Mariana Barros",   "74974859613", 12, 6, 2002, 1,
    "Jose Eduardo",     "71974859613", 30, 6, 1989, 4,
    "Tatiana Oliveira", "71974859610", 12, 6, 1999, 5,
    "Camila de Jesus",  "71974859615", 1,  6, 1957, 6,
    "Louise Poliana",   "79987514952", 30, 6, 1962, 7,
    "Heitor Dias",      "71984125247", 12, 6, 1975, 8,
    "Reinaldo Goes",    "71974859618", 27, 8, 1978, 9};

struct registro xdata contatos[500];

// declaracoes de funcoes
void voltarMenu(); // voltar ao menu
void exibirContatos(); // exibe lista ordenada

// Variaveis globais
char string[32];
int n;
int selecionado;
char afinidade_pesquisada[20];

// funcao principal
void main(void) {
   
  // declaracoes de variaveis
  char c;
  int relacionamento_numero;
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
    printf("+-----------------------------------+\n"
           "|                                   |\n"
           "|     AGENDA DE CONTATOS            |\n"
           "|                                   |\n");

    printf("| Menu - Digite a opcao desejada    |\n");
    printf("| [L] - Lista de Contatos    OK     |\n");
    printf("| [N] - Pesquisa por nome    OK     |\n");
    printf("| [I] - Pesquisa por idade          |\n");
    printf("| [R] - Pesquisa por Relacionamento | \n");
    printf("| [A] - Adcionar contato     OK     |\n");
    printf("| [D] - Deletar contato             |\n");
    printf("| [E] - EDITAR contato              | \n");
    printf("+-----------------------------------+\n\n");

    c = getchar();
    // logica para listar os contatos
    if (c == 'l' || c == 'L') {
      //      printf("/f");  // Limpar Chat
      printf("Lista de Contatos selecionada.\n");
      for (n = 0; n < 500; n++) {
        // Verifica se o primeiro caractere da string 'nome' do contato na
        // posi??o 'n' n?o ? igual a zero. Isso significa que o nome do contato
        // na posi??o 'n' n?o est? vazio, ou seja, cont?m pelo menos um
        // caractere
        if (contatos[n].nome[0] != 0) {
          printf("%s %s %u \n", contatos[n].nome, contatos[n].tel,
                 contatos[n].relacionamento);
        }
      }
voltarMenu();
      // logica Pesquisar Nome
    } else if (c == 'n' || c == 'N') {
      printf("\nPesquisa por nome selecionada.\n");
      printf("Digite o nome: ");
      gets(string, 32);
      for (n = 0; n < 500; n++) {
        if (strstr(contatos[n].nome, string) !=
            NULL) { // Verifica se 'string' esta contida
          printf("%s %s %bd\n", contatos[n].nome, contatos[n].tel,
                 contatos[n].relacionamento);
        }
      }
      voltarMenu();


      // logica Pesquisar Idade
    } else if (c == 'i' || c == 'I') {
      printf("Pesquisa por idade selecionada.\n");
      voltarMenu();


      // logica Pesquisa Relacionamento
    } else if (c == 'r' || c == 'R') {
	  printf("\nDigite o relacionamento: ");
	  gets (string, 32); // ler string
      if (strcmp(string, "Amigo") == 0) {
        relacionamento_numero = 1;
		printf("Lista da categoria Amigo");
      } else if (strcmp(string, "Amizade") == 0) {
          relacionamento_numero = 2;
		printf("Lista da categoria Amizade");
          } else if (strcmp(string, "Namorado") == 0) {
		printf("Lista da categoria Namorado");
            relacionamento_numero = 3;
		    }
	for (n = 0; n < 500; n++) {
        if (contatos[n].relacionamento == relacionamento_numero) {
            printf("%s %u\n", contatos[n].nome, contatos[n].relacionamento);
        }
    }
		  


 
//        scanf("%s", &afinidade_pesquisada);// se voce quer armazenar nessa variavel ? necessario o uso do & - para representar o endereco
//		getchar(); // Limpa o buffer de caractere indesejado ocasionado pelo scanf
//	    printf("Contatos com afinidade %s:\n", afinidade_pesquisada);
//	  for (n = 0; n < 500; n++) {
	  // utiliza strstr para procurar primeiro 
	  // Pq vai que o usuario coloque algo que nao exista
	  // tem que lembrar q o professor quer os numeros tambem 
//	  	if (strstr(contatos[n].relacionamento, string) !=
  //          NULL) { // Verifica se 'string' esta contida
    //      printf("%s %s %bd\n", contatos[n].nome, contatos[n].tel,
      //           contatos[n].relacionamento);
       // }
	    //if (strcmp([contatos[n].relacionamento], afinidade_pesquisada) == 0) {
       // printf("%s %s %d/%d/%d\n", contatos[n].nome, contatos[n].tel);

	//	}
     //   }

      voltarMenu();
	  
	  

      // Adcionar Contato
    } else if (c == 'a' || c == 'A') {
      printf("Adicionar novo contato.\n");

      for (n = 0; n < 500; n++) {
        if (contatos[n].nome[0] == 0) {

          printf("Insira o nome: ");
          scanf(" %s", contatos[n].nome);

          printf("\nTelefone do contato: ");
          scanf(" %s", contatos[n].tel);

          printf("\nData de nascimento do contato (DD/MM/AAAA):  ");
          scanf(" %d/%d/%d", &contatos[n].datan.dia, &contatos[n].datan.mes,
                &contatos[n].datan.ano);
          getchar();

          printf("\nData de Nascimento: %d / %d / %d", contatos[n].datan.dia,
                 contatos[n].datan.mes, contatos[n].datan.ano);

          printf("\nDigite o relacionamento do contato: ");
          scanf(" %u",contatos[n].relacionamento);

          voltarMenu();
        }
      }


      // logica deletar contato
    } else if (c == 'd' || c == 'D') {
      printf("\nDeletar contato\n");
	  exibirContatos();
	  printf("O contato %s ser? exclu?do. \n Tem certeza ? [S]im X [N]?o :",contatos[selecionado].nome);
	  c = getchar();
	  if (c == 'S' || c == 's') {
	  contatos[selecionado].nome[0] = 0;
	  contatos[selecionado].tel[0] = 0;
	  contatos[selecionado].relacionamento = 0;
	  printf("im.  \n -> Contato Deletado\n");
	  }	else {
	  printf("?o \n -> Opera??o cancelada");}
	  voltarMenu();

      // L?gica para EDITAR contato
    } else if (c == 'e' || c == 'E') {
	  exibirContatos();

	  // Menu - EDITAR contato
      printf("Informe o dado que deseja editar\n");
      printf("[A] - Nome do contato\n");
      printf("[B] - Telefone\n");
      printf("[C] - Relacionamento\n");
      printf("[D] - Data de Nascimento\n");

      // Recebe e atualiza a op??o escolhida
      c = getchar();

      switch (c) {
      case 'A':
      case 'a':
        // Atualiza nome
        printf("Informe o novo nome do contato:\n");
        gets(string, 32);
        strcpy(contatos[selecionado].nome, string);
        break;

      case 'B':
      case 'b':
        // Atualiza telefone
        printf("Informe o novo telefone do contato:\n");
        gets(string, 14);
        strcpy(contatos[selecionado].tel, string);
        break;

      case 'C':
      case 'c':
        // Atualiza relacionamento
        printf("Novo relacionamento:\n");
        scanf(" %u", &contatos[selecionado].relacionamento);
		getchar();
		printf("Atualizado para: %u", contatos[selecionado].relacionamento);
        break;

      case 'D':
      case 'd':
        printf("\nData de nascimento do contato (DD/MM/AAAA):  ");
        scanf("%d/%d/%d", &contatos[n].datan.dia, &contatos[n].datan.mes,
              &contatos[n].datan.ano);
        getchar();
        break;

      default:
        printf("Op??o inv?lida.\n");
      }
      voltarMenu();

    } else { // Sem correspond?ncia das alternativas
      printf("\nOp??o inv?lida. Press Space e Tente novamente.\n");
      while (getchar() != ' ')
        ;
    }

  } // while primario
} // main

void voltarMenu() {
  printf("\nPressione espa?o para continuar\n");
  while (getchar() != ' ')
    ;
}
      // Exibir contatos
void exibirContatos() { 
      printf("\nDigite o nome para pesquisar os contatos existentes\n");
      gets(string, 32);
      for (n = 0; n < 500; n++) {
        // verifica se 'string' contida diferente de null
        if (strstr(contatos[n].nome, string) != NULL) {
          printf("%d? - %s %s %u\n", n, contatos[n].nome, contatos[n].tel,
                 contatos[n].relacionamento);
        }
      }
	        printf("\nInforme o n?mero ? correspondente ao contato.\n");
			scanf("%d", &selecionado);
			getchar();
}