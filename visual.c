#include "visual.h"
#include "logic.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void new_game(int mode);
int deck_size();
void menu(){
  return;
}

void name_choice(){
  int choice;
  while(1){
    printf("1 -> vybrat nove jmena\n");
    printf("2 -> pouzit jmena z minule hry\n");
    printf("3 -> hall of fame\n");
    printf("4 -> exit\n");
    scanf("zvolte cislem: %i\n", &choice);
    switch (choice) {
      case 1:
        new_game(0);
        break;
      case 2:
        new_game(1);
        break;
      case 3:
        top_players();
        break;
      case 4:
        exit(1);
      default:
        printf("invalid vyber\n");
        clear_screen();
        break;
    }
  }
}

void new_game(int mode){
  char names[2][64];
  int name_len[2];
  int first;
  int size;
  if(mode == 0){
    printf("jmeno prvniho hrace: ");
    scanf("%63s\n", names[0]);
    printf("jmeno druheho hrace: ");
    scanf("%63s\n", names[1]);
    for(int n = 0; n<2; n++){
      for(int k = 0; k<64; k++){
        if((names[n][k] < 126) && (names[n][k] > 31)){
          name_len[n]++;
        }else{
          break;
        }
      }
    }
    save_data(names, name_len, "./data/players");
  }else{
    //fixnout
    get_names(names);
  }
  first = player_choice();
  size = deck_size();
  play_screen(first, size, names);
}


int player_choice(){
  srand(time(0));
  if(rand()%2==1){
    return 1;
  }else{
    return 0;
  }
}

int deck_size(){
  int size;
  printf("zvolte velikost hraci desky: ");
  scanf("%i\n",&size);
  while(size < 0 && size > 15){
    printf("zvolte validni velikost hraci desky: ");
    scanf("%i\n",&size);
  }
  return size;
}

void top_players(){
  clear_screen();
  printf("hall of fame: \n");
  FILE *fd;
  char s;
  fd = fopen("./data/top_ten", "r");
  while((s=fgetc(fd))!=EOF){
    printf("%c", s);
  }
  fclose(fd);
  return;
}
