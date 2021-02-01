#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define X 10
#define Y 43

void loadFile(char template[][Y],FILE* file);
void displayFrame(char frame[][Y], int x, int y);
void displayMessage(char* message, int x, int y);

int main(int argc, char *argv[]) {
  // Const var coordinates
  const int x = 10, y = 5;

  if(argc < 2){
    errno = EINVAL;
    perror("Usage: leperssay [MESSAGE]");
    exit(EXIT_FAILURE);
  }

  // Open files
  FILE* lepers_pos1 = fopen("/usr/share/leperssay/templates/lepers/lepers_pos1.txt","r");
  FILE* lepers_pos2 = fopen("/usr/share/leperssay/templates/lepers/lepers_pos2.txt","r");

  if(lepers_pos1 == NULL || lepers_pos2 == NULL){
    perror("Error with templates");
    exit(EXIT_FAILURE);
  }

  // Save content
  char c_pos1[X][Y];
  loadFile(c_pos1,lepers_pos1);
  char c_pos2[X][Y];
  loadFile(c_pos2,lepers_pos2);

  // Close files
  fclose(lepers_pos1);
  fclose(lepers_pos2);

  // Init ncurses values
  initscr();
  start_color();
  noecho();
  curs_set(FALSE);

  // Init color values
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

  while(1) {
    // Clear display
    clear();

    // Display first frame
    displayFrame(c_pos1,x,y);

    // Refresh display
    refresh();

    // Wait a second
    sleep(1);

    // Clear display
    clear();

    // Display second frame
    displayFrame(c_pos2,x,y);

    // Display text
    displayMessage(argv[1],x,y);

    // Refresh display
    refresh();

    // Wait a second
    sleep(1);
  }

  // End
  endwin();

  exit(EXIT_SUCCESS);
}

/**
* Load a text file into a double table
*/
void loadFile(char template[][Y], FILE* file){
	int i;
	for(i=0;i<X;i++){
		if(fgets(template[i],Y,file)==NULL){
			break;
		}
	}
}

/**
* Display a double table
*/
void displayFrame(char frame[][Y], int x, int y){
  int i,j;

  // Display frame
  for (i=0;i<X;i++){
    for(j=0;j<Y;j++){
      if (frame[i][j]=='#'){
        attron(COLOR_PAIR(2));
      }
      if (frame[i][j]=='*'){
        attron(COLOR_PAIR(3));
      }
      char c[2];
      strncpy(c,(frame[i]+j),1);
      mvprintw(y+i,x+j,c);
      attron(COLOR_PAIR(1));
    }
  }
}

/**
* Display the entry message
*/
void displayMessage(char* message, int x, int y){
  int j;
  mvprintw(1,25+x,"  ");
  for(j=0;j<strlen(message)+2;j++){
    char c[2];
    strncpy(c,"-",2);
    mvprintw(1,27+x+j,c);
  }
  mvprintw(2,25+x,"< ");
  mvprintw(2,27+x,message);
  mvprintw(2,27+x+strlen(message)," ! >");
  mvprintw(3,25+x,"/ ");
  for(j=0;j<strlen(message)+2;j++){
    char c[2];
    strncpy(c,"-",2);
    mvprintw(3,27+x+j,c);
  }
  mvprintw(4,24+x,"/");
}
