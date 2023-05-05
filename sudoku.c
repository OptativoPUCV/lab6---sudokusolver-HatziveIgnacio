#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    // Verificar filas
    for(int i=0; i<9; i++){
        int used[10] = {0}; // Inicializar arreglo de números usados
        for(int j=0; j<9; j++){
            int num = n->sudo[i][j];
            if(num != 0){
                if(used[num] == 1){ // Número ya fue usado en la fila
                    return 0; // Estado inválido
                }
                used[num] = 1; // Marcar número como usado
            }
        }
    }
    
    // Verificar columnas
    for(int j=0; j<9; j++){
        int used[10] = {0}; // Inicializar arreglo de números usados
        for(int i=0; i<9; i++){
            int num = n->sudo[i][j];
            if(num != 0){
                if(used[num] == 1){ // Número ya fue usado en la columna
                    return 0; // Estado inválido
                }
                used[num] = 1; // Marcar número como usado
            }
        }
    }
    
    // Verificar submatrices de 3x3
    for(int k=0; k<9; k++){ // Recorrer todas las submatrices
        int used[10] = {0}; // Inicializar arreglo de números usados
        for(int i=k/3*3; i<k/3*3+3; i++){ // Recorrer filas de la submatriz
            for(int j=k%3*3; j<k%3*3+3; j++){ // Recorrer columnas de la submatriz
                int num = n->sudo[i][j];
                if(num != 0){
                    if(used[num] == 1){ // Número ya fue usado en la submatriz
                        return 0; // Estado inválido
                    }
                    used[num] = 1; // Marcar número como usado
                }
            }
        }
    }
    
    return 1; // Estado válido
}



List* get_adj_nodes(Node* n){
    List* list=createList();
    Node* new_node;
    for(int i=0; i<9; i++)
    { // recorrer 
      for(int j=0; j<9; j++)
      {  
        if(n->sudo[i][j]==0)
        { // remplazar 0 por 1,2,3...,9
          for(int k=1; k<=9; k++)
          {
            new_node = copy(n);
            new_node->sudo[i][j] = k;
            if(is_valid(new_node))
            {
              pushBack(list, new_node);
            } else {
              free(new_node);
            }
          }
        }
        return list;
      }
    }
  return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/