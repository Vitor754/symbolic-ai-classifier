//#################### CABECALHO ##############################
// NOME>: VITOR MANOEL ALVES DE SOUSA
// DISICIPLINA>: CES-11
// TURMA>: 4
// ID DO LAB>: LAB 7

//#################### BIBLIOTECAS E IMPORTS ##################
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#################### CONSTANTES E VARIAVEIS GLOBAIS ##########
# define MAX_RULES 1000 // Numero maximo de regras no heap
# define MAX_DESC 100 // Tamanho maximo da descricao da regra
# define MAX_CLASS 50

//########## ESTRUTURA E OPERACOES ESSENCIAIS DA TAD ############
//STRUCT PARA UMA REGRA
struct leis{
  int id;
  char descricao[MAX_DESC];
  char classe[MAX_CLASS];
  float peso;
};

typedef struct leis tipoLeis;

int size = 0;

//HEAPFY BASEADA NO PESO
void heapify_down(int i, tipoLeis v[]){
  int esq, dir;
  int maior;
  esq = 2*i + 1;
  dir = 2*i + 2;
  maior = i;
  if(esq < size && v[esq].peso > v[i].peso){
     maior = esq;
  }
  if(dir <  size && v[dir].peso > v[maior].peso){
     maior = dir;
  }
  if(maior != i) {
     tipoLeis aux;
     aux = v[i];
     v[i] = v[maior];
     v[maior] = aux;
     heapify_down(maior, v);
   }
}

//INSERE REGRA
void insert(tipoLeis x, tipoLeis heap[]){
  if (size >= MAX_RULES) {
        return;
  }
  heap[size] = x;
  int k = size;
  size++;
  //ORGANIZA FILA COM A ORDEM DE PRIORIDADE
  while(k > 0 && heap[(k-1)/2].peso < heap[k].peso){
        tipoLeis temp_aux;
  temp_aux = heap[k];
  heap[k] = heap[(k-1)/2];
  heap[(k-1)/2] = temp_aux;
  k = (k-1)/2;
  }
}


//################# OUTRAS FUNCOES E PROCEDIMENTOS ############
//CLASSIFICADOR
void classify(int id_aux, int atributo_x, int atributo_y, char classe_aux[], tipoLeis fila[]){
    char letra;
    char operador;
    float valor;
    float valor_atributo_amostra;
    char classe_lida[MAX_CLASS];
    tipoLeis max_atual;
    int testes;
    testes = 0;
    int i = 0;

    //FLAG PARA SABER SE ENCONTROU PELO MENOS UMA REGRA
    int flag = 0;
    //LAÇO PARA VERIFICAR REGRA POR ORDEM DO VETOR
    while(flag == 0 && i < size){
    max_atual = fila[i];
    sscanf(max_atual.descricao, "Atributo%c%c%f", &letra, &operador, &valor);
       if (letra == 'X') {
           valor_atributo_amostra = atributo_x;
       }
       else if (letra == 'Y') {
           valor_atributo_amostra = atributo_y;
      }
      if(operador == '>') {
         if(valor_atributo_amostra > valor){
            strcpy(classe_lida, max_atual.classe);
            flag = 1;
        }
    }
    else if (operador == '<') {
         if(valor_atributo_amostra < valor){
                strcpy(classe_lida, max_atual.classe);
            flag = 1;
        }
    }
    testes++;
    i++;
    }

    if(flag == 1){
       i = 0;
       //COMPARA CLASSE
       if(strcmp(classe_aux, max_atual.classe) == 0){
       //ACHA ID NA FILA ORIGINAL CORRESPONDENTE À REGRA ENCONTRADA
       while(max_atual.id != fila[i].id){
            i++;
       }
       printf("CLASS %s OK %d\n", fila[i].classe, testes);
       fila[i].peso = fila[i].peso + 0.5;
       int k = i; // Começa do índice que mudou
       while(k > 0 && fila[(k-1)/2].peso < fila[k].peso){
            tipoLeis temp_aux;
       temp_aux = fila[k];
       fila[k] = fila[(k-1)/2];
       fila[(k-1)/2] = temp_aux;
        k = (k-1)/2;
        }
       //CORRIGE FILA
       }
       else{
          i = 0;
        while(max_atual.id != fila[i].id){
            i++;
        }
       printf("CLASS %s ERR %d\n", fila[i].classe, testes);
       fila[i].peso = fila[i].peso - 0.3;
       heapify_down(i, fila);
       }
    }
    else if(flag == 0){
        printf("SEM REGRA %d\n", testes);
    }
}

//LISTA A HEAP PELA ORDEM DO VETOR
void listheap(tipoLeis v[]){
  int i;
  for(i = 0; i < size; i++){
      printf("%d \"%s\" %s %.1f\n", v[i].id, v[i].descricao, v[i].classe, v[i].peso);
  }
}

//DELETA REGRA
void deleta(int id_aux, tipoLeis v[]){
  int k = -1;
  for(int i = 0; i < size; i++) {
      if(v[i].id == id_aux) {
         k = i;
         break;
      }
  }
  if(k == -1) {
     printf("REGRA INEXISTENTE\n");
     return;
  }
  if(k == size - 1) {
     size--;
  }
  else{
     v[k] = v[size - 1];
     size--;
     heapify_down(k, v);
  }
  printf("REGRA REMOVIDA\n");
}

//################# MAIN ######################################
int main(void) {
  // VARIAVEIS DE APOIO
  int i;
  char comando[9];
  tipoLeis fila[MAX_RULES];
  tipoLeis infos;
  tipoLeis *lei_aux;
  lei_aux = &infos;
  int id_aux;
  char classe_aux[MAX_CLASS];


  //LEITURA DOS INPUTS

  while(strcmp(comando, "EXIT")!= 0){
     scanf("%s", comando );
     if(strcmp(comando, "ADDREGRA")== 0){
        scanf ("%d", &infos.id);
        scanf (" \"%[^\"]\"", infos.descricao);
        scanf ("%s", infos.classe);
        scanf ("%f", &infos.peso);
        int duplicada = 0;
        for(i = 0; i < size; i++){
            if(fila[i].id == infos.id){
               printf("REGRA DUPLICADA\n");
               duplicada = 1;
               break;
            }
        }
        if(!duplicada && size < MAX_RULES) {
           insert(infos, fila);
           printf("OK\n");
        }
     }
     else if(strcmp(comando, "DELREGRA")== 0){
        scanf("%d", &id_aux);
        deleta(id_aux, fila);
     }
    else if(strcmp(comando, "CLASSIFY")== 0){
        int atributo_x;
        int atributo_y;
        scanf("%d %d %d %s", &id_aux, &atributo_x, &atributo_y, &classe_aux);
        int salva_size = size;
        classify(id_aux, atributo_x, atributo_y, classe_aux, fila);
        size = salva_size;
    }
    else if(strcmp(comando, "LISTHEAP")== 0){
        listheap(fila);
    }
  }
  printf("Total de regras no heap: %d", size);
  return 0;
}
