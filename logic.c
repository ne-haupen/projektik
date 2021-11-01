#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //???


void save_data(char data[2][64], int name_len[2], char* filename){
  FILE *fptr;

  fptr = fopen(filename, "w");

  if(fptr == NULL){
    printf("error while opening file");
    exit(1);
  }

  for(int n=0; n<2; n++){
    for(int k=0; k<name_len[n], k++){
      fprintf(fptr, "%c", data[n][k]);
    }
    fprintf(fptr, "\n");
  }
  fclose(fptr);
  return;
}

void get_names(char names[2][64]){
  FILE *fp;
  fp = fopen("./data/last_players", "r");
  if(fp == NULL){
    printf("error while opening file");
    exit(1);
  }
  fgets(names[0], 64, fp);
  int len = strlen(names[0]);
  fseek(fp, 3, SEEK_CUR);
  fgets(names[1], 64, fp);
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

int check_surrounding(int a, int b, char xo, char game[15][15]){
  int hm[] = {-1, 0, 1};
  int current = 1;
  const int win_value = 5; //pocet znaku za sebou pro win fixxxxxxx
  for(int n = 0; n<3; n++){
    for(int k = 0; k<3; k++){
      current = 1;
      if((game[a+hm[k]][b+hm[n]] == xo)){
        current++;
        if((hm[k] == 0 && hm[n]==0)){
          break;
        }
        while(game[a+hm[k]][b+hm[n]] == xo){
          if((0 <= a+hm[k] < 15) && (0 <= b+hm[n] < 15)){
            current++;
          }else{
            break;
          }
          a = a+hm[k];
          b = b+hm[n];
        }
        while(game[a-hm[k]][b-hm[n]] == xo){
          if((0 <= a+hm[k] < 15) && (0 <= b+hm[n] < 15)){
            current++;
          }else{
            break;
          }
        if(current == win_value){
          return 1;
          }
          a = a+hm[k];
          b = b+hm[n];
        }
      }
    }
  }
  return 0;
}
