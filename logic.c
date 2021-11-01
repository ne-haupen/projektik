#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //???


void save_data(char data[2][64], char* filename){
  FILE *fptr;

  fptr = fopen(filename, "w");

  if(fptr == NULL){
    printf("error while opening file");
    exit(1);
  }

  for(int n=0; n<2; n++){
    for(int a=0; a!='\n'; a++){
      fprintf(fptr, "%c", data[n][a]);
    }
    fprintf(fptr, "\n");
  }
  fclose(fptr);
  return;
}

void get_names(char names[2][64]){
  FILE *fp;
  char ch;
  fp = fopen("./data/last_players", "r");
  if(fp == NULL){
    printf("error while opening file");
    exit(1);
  }
  for(int n=0; n<2; n++){
    for(int a=0; (ch = fgetc(fp))!='\0'; a++){
      names[n][a] = ch;
    }
  }
  fclose(fp);
  return;
}
// O X
int check_win(char gamee[15][15], int size){
  for(int n=0; n<size; n++){
    for(int k=0; k<size; k++){
      if(gamee[n][k] != '*'){
        if(check_surrounding(n, k, gamee[n][k], gamee) == 1){
          return 1;
        }
      }
    }
  }
  return 0;
}

int check_surrounding(int a, int b, char xo, char game[4][4]){
  int hm[] = {-1, 0, 1};
  int current = 1;
  int c,d;
  c = a;
  d = b;
  const int win_value = 3; //pocet znaku za sebou pro win fixxxxxxx
  for(int n = 0; n<3; n++){
    for(int k = 0; k<3; k++){
      current=1;
      if((game[a+hm[k]][b+hm[n]] == xo)){
        if((hm[k] == 0 && hm[n]==0)){
          break;
        }
        //printf("dd cur %i k %i n %i\n", current, k, n);
        while(game[a+hm[k]][b+hm[n]] == xo){
          if((0 <= a+hm[k] < 4) && (0 <= b+hm[n] < 4)){
            current++;
          }else{
            break;
          }
          a = a+hm[k];
          b = b+hm[n];
        }
        a = c;
        b = d;
        while(game[a-hm[k]][b-hm[n]] == xo){
          if((0 <= a-hm[k] < 4) && (0 <= b-hm[n] < 4)){
            current++;
          }else{
            break;
          }
          a = a-hm[k];
          b = b-hm[n]; //eeeeeeeee
        }
          //printf("dd %i \n", current);
        if(current == win_value){
          return 1;
          }
        }
      }
    }
  return 0;
}
