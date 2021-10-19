#include "visual.h"
#include "logic.h"
#include <time.h>
#include <stdio>

void new_game(int mode);

void menu(){
  return;
}

void name_choice(){
  int choice;
  while(1){
    printf("1 -> vybrat nove jmena\n");
    printf("2 -> pouzit jmena z minule hry\n");
    printf("3 -> hall of fame\n", );
    printf("4 -> exit\n", );
    scanf_s("%i\n", &choice);
    switch (choice) {
      case 1:
        new_game(0);
        break;
      case 2:
        new_game(1);
        break;
      case 3:
        best_players();
        break;
      case 4:
        end_game();
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
    save_data(names[0]);
    save_data(names[1]);
  }else{
    names[0] = get_data();
    names[1] = get_data();
  }
  for(int n = 0; n<2; n++){
    for(int k = 0; k<64; k++){
      if(names[n][k] < 126 and names[n][k] > 31){
        name_len[n]++;
      }else{
        break;
      }
    }
  }
  first = player_choice();
  size = deck_size();
  play_screen(first, size, names, name_len);
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
  return size;
}
