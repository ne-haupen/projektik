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
  //fseek(fp, 0, SEEK_END);
  fgets(names[0], 64, fp);
  int len = strlen(names[0]);
  fseek(fp, len, SEEK_SET);
  fgets(names[1], 64, fp);
  fclose(fp);
  return;
}
