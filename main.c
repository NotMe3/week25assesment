#include <curses.h>
#include <time.h>
#include <stdlib.h>

#define HEIGHT 50
#define WIDTH 125
#define HOUSES 6
#define MAX_MISSILES 10





typedef struct Bullet {
    int xPos;
    int yPos;
    int changesAfter;
    int direction;
    int target;
} Bullet;

void createWindow() {
    initscr();
    clear();
    cbreak();
    noecho();
}

void drawHouse(int x, int y){
    mvprintw(x,y, "#####");
    mvprintw(x-1,y, " ## |");
    mvprintw(x-2,y, " #| |");
    move(x-3, y+2);
    printw("%d, %d", x, y+2);
}


void drawMissile(int x, int y) {
    mvprintw(x,y-1, "/#####\\");
    mvprintw(x-1,y, "|###|");
    mvprintw(x-2,y, " ( ) ");
    mvprintw(x-3,y, "  @  ");
}




Bullet choosetarget(Bullet myBullet, int housePos[HOUSES]) {
   
    if(myBullet.direction == 1) {
        if(myBullet.changesAfter == 0){
            myBullet.target = housePos[rand() % HOUSES];
            myBullet.xPos = myBullet.target;
            myBullet.yPos = 1;
        }
        else if(myBullet.changesAfter == 1) {
            while((myBullet.target < 0) && (myBullet.target < 2)) {
                myBullet.target = rand() % HOUSES;
                myBullet.xPos = myBullet.target -((HEIGHT-3)/myBullet.changesAfter);
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 2) {
            while(myBullet.target < 1) {
                myBullet.target = rand() % HOUSES;
                myBullet.xPos = myBullet.target -((HEIGHT-3)/myBullet.changesAfter);
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 3) {
            while(myBullet.target < 1) {
                myBullet.target = rand() % HOUSES;
                myBullet.xPos = myBullet.target -((HEIGHT-3)/myBullet.changesAfter);
                myBullet.yPos = 1;
            }
        }
        else {
            myBullet.target = rand() % HOUSES;
            myBullet.xPos = myBullet.target -((HEIGHT-3)/myBullet.changesAfter);
            myBullet.yPos = 1;
        }
        
    }
    else {
        if(myBullet.changesAfter == 0){
            myBullet.target = housePos[rand() % HOUSES];
            myBullet.xPos = myBullet.target;
            myBullet.yPos = 1;
        }
        else if(myBullet.changesAfter == 1) {
            while((myBullet.target < 0 || myBullet.target > 3) && (myBullet.target < 2)) {
                myBullet.target = rand() % HOUSES;
                myBullet.xPos = myBullet.target +((HEIGHT+3)/myBullet.changesAfter);
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 2) {
            while(myBullet.target < 1 || myBullet.target > 5) {
                myBullet.target = rand() % HOUSES;
                myBullet.xPos = myBullet.target +((HEIGHT+3)/myBullet.changesAfter);
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 3) {
            while(myBullet.target < 1 || myBullet.target > 5) {
                myBullet.target = rand() % HOUSES;
                myBullet.xPos = myBullet.target +((HEIGHT+3)/myBullet.changesAfter);
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 4) {
            myBullet.target = rand() % HOUSES;
            myBullet.xPos = myBullet.target +((HEIGHT+3)/myBullet.changesAfter);
            myBullet.yPos = 1;
            
        }
    }
    return myBullet;
}



Bullet createBullet(int housePos[HOUSES]) {
    Bullet myBullet;
    myBullet.target = -1;
    srand(time(NULL));
    myBullet.changesAfter = rand() % 5;
    if(rand() % 2 == 0) {
        myBullet.direction = 1;
    
    }
    else {
        myBullet.direction = -1;
    }
    myBullet = choosetarget(myBullet, housePos);
    return myBullet;
}


void createBase(int housePos[HOUSES]) {
    int temp;
    for(int i = 0; i < HOUSES; i++) {
        drawHouse(48, (WIDTH/HOUSES*i)+(WIDTH/HOUSES/2));
        housePos[i] = (WIDTH/HOUSES*i)+(WIDTH/HOUSES/2)+2;
        temp = i;
    }
    mvaddch(0,0,'1');
    mvaddch(49,0,'2');
    mvaddch(0,124,'3');
    mvaddch(49,124,'4');
    drawMissile(48, ((WIDTH/HOUSES*temp)/2+(WIDTH/HOUSES/2)));
}




int main() {
    int housePos[HOUSES];
    Bullet bullet[MAX_MISSILES];

    /*for(int i = 0; i < MAX_MISSILES; i++) {
        bullet[i] = createBullet();
    }*/
    createWindow();
    refresh();
    WINDOW *game;
    game = newwin(HEIGHT, WIDTH, 0,0);
    box(game,0,0);
    wrefresh(game);
    createBase(housePos);
    for(int i = 0; i < MAX_MISSILES; i++) {
        bullet[i] = createBullet(housePos);
    }
    /*for(int i = 1; i < 49; i++) {
        mvaddch(i,i,'X');
    }
    for(int i = 1; i < 49; i++) {
        mvaddch(i,i,'X');
    }
    for(int i = 1; i < 49; i++) {
        mvaddch(i,i,'X');
    }
    for(int i = 1; i < 49; i++) {
        mvaddch(i,i/2,'X');
    }
    for(int i = 1; i < 49; i++) {
        mvaddch(i,i/3,'X');
    }
    for(int i = 1; i < 49; i++) {
        mvaddch(i,i/4,'X');
    }*/
    while(1) {
        for(int i = 0; i < MAX_MISSILES; i++) {

        }
        refresh();
    }

    getch();
    delwin(game);
    endwin();
}