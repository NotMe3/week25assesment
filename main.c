#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 50
#define WIDTH 125
#define HOUSES 6
#define MAX_MISSILES 10
#define CROSSHAIR_SPEED 3





typedef struct Bullet {
    int xPos;
    int xOrigin;
    int yPos;
    int changesAfter;
    int direction;
    int target;
} Bullet;

typedef struct Cursor {
    int xPos;
    int yPos;
    int speed;
} Cursor;


/*Cursor createCursor() {
    Cursor myCursor;
    myCursor.xPos = 10;
    myCursor.yPos = 20;
    myCursor.speed = CROSSHAIR_SPEED;
}*/


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
   int temp = -1;

    if(myBullet.direction == 1) {
        move(1,1);
        if(myBullet.changesAfter == 0){
            myBullet.target = housePos[(rand() % HOUSES)];
            myBullet.xPos = myBullet.target;
            myBullet.xOrigin = myBullet.xPos;
            myBullet.yPos = 1;
        }
        else if(myBullet.changesAfter == 1) {
            while(temp < 2) {
                temp = (rand() % HOUSES);
                myBullet.target = housePos[temp];
                myBullet.xPos = myBullet.target -((HEIGHT-3)/myBullet.changesAfter);
                myBullet.xOrigin = myBullet.xPos;
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 2) {
            while(temp < 1) {
                temp = (rand() % HOUSES);
                myBullet.target = housePos[temp];
                myBullet.xPos = myBullet.target -((HEIGHT-3)/myBullet.changesAfter);
                myBullet.xOrigin = myBullet.xPos;
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 3) {
            while(temp < 1) {
                temp = (rand() % HOUSES);
                myBullet.target = housePos[temp];
                myBullet.xPos = myBullet.target -((HEIGHT-3)/myBullet.changesAfter);
                myBullet.xOrigin = myBullet.xPos;
                myBullet.yPos = 1;
            }
        }
        else {
            temp = (rand() % HOUSES);
            myBullet.target = housePos[temp];
            myBullet.xPos = myBullet.target -((HEIGHT-3)/myBullet.changesAfter);
            myBullet.xOrigin = myBullet.xPos;
            myBullet.yPos = 1;
        }
        
    }
    else {
        if(myBullet.changesAfter == 0){
            myBullet.target = housePos[(rand() % HOUSES)];
            myBullet.xPos = myBullet.target;
            myBullet.xOrigin = myBullet.xPos;
            myBullet.yPos = 1;
        }
        else if(myBullet.changesAfter == 1) {
            while(temp < 0 || temp > 3) {
                temp = (rand() % HOUSES);
                myBullet.target = housePos[temp];
                myBullet.xPos = myBullet.target +((HEIGHT-3)/myBullet.changesAfter);
                myBullet.xOrigin = myBullet.xPos;
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 2) {
            while(temp < 0 || temp > 4) {
                temp = (rand() % HOUSES);
                myBullet.target = housePos[temp];
                myBullet.xPos = myBullet.target +((HEIGHT-3)/myBullet.changesAfter);
                myBullet.xOrigin = myBullet.xPos;
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 3) {
            while(temp < 0 || temp > 4) {
                temp = (rand() % HOUSES);
                myBullet.target = housePos[temp];
                myBullet.xPos = myBullet.target +((HEIGHT-3)/myBullet.changesAfter);
                myBullet.xOrigin = myBullet.xPos;
                myBullet.yPos = 1;
            }
        }
        else if(myBullet.changesAfter == 4) {
            temp = (rand() % HOUSES);
            myBullet.target = housePos[temp];
            myBullet.xPos = myBullet.target +((HEIGHT-3)/myBullet.changesAfter);
            myBullet.xOrigin = myBullet.xPos;
            myBullet.yPos = 1;
            
        }
    }
    return myBullet;
}



Bullet createBullet(int housePos[HOUSES]) {
    Bullet myBullet;
    myBullet.target = -1;
    myBullet.changesAfter = (rand() % 5);
    if((rand() % 2) == 0) {
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
        move(15+i,15);
    }
    drawMissile(48, ((WIDTH/HOUSES*temp)/2+(WIDTH/HOUSES/2)));
}



int isValidToMoveTo(int x, int y) {
    if(x > 44 || x < 1) {
        return -1;
    }
    if(y > 123 || y < 1) {
        return -1;
    }
    return 1;
}




int main() {
    int housePos[HOUSES];
    Bullet bullet[MAX_MISSILES];
    int input, tempx, tempy;
    srand(time(NULL));

    //mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    //EMERGENCY USE ONLY!!! printf("\033[?1003h\n");

    createWindow();
    refresh();
    WINDOW *game;
    game = newwin(HEIGHT, WIDTH, 0,0);
    box(game,0,0);
    keypad(stdscr, TRUE);
    keypad(game, TRUE);
    wrefresh(game);
    createBase(housePos);
    
    for(int i = 0; i < MAX_MISSILES; i++) {
        bullet[i] = createBullet(housePos);
    }

    move(50,1);
    for(int i = 0; i < MAX_MISSILES; i++) {
        printw("x:%d,change:%d,direction:%d,target:%d\n", bullet[i].xPos, bullet[i].changesAfter, bullet[i].direction, bullet[i].target);
    }


    for(int h = 1; h < HEIGHT-1; h++) {
        for(int i = 0; i < MAX_MISSILES;i++) {
            mvaddch(bullet[i].yPos, bullet[i].xPos, '*');
        }
        for(int i = 0; i < MAX_MISSILES; i++) {
            if(bullet[i].changesAfter != 0) {
                if(bullet[i].direction == 1) {
                    bullet[i].xPos = bullet[i].xOrigin + (int)(h/bullet[i].changesAfter);
                }
                else {
                    bullet[i].xPos = bullet[i].xOrigin - (int)(h/bullet[i].changesAfter);
                }
            }
            bullet[i].yPos += 1;
        }
        refresh();
        usleep(10000);
    }

    wrefresh(game);

    Cursor cursor;
    cursor.xPos = 44;
    cursor.yPos = 62;
    cursor.speed = CROSSHAIR_SPEED;
    
    while(1) {
        

        mvprintw(1,1,"%d %d",cursor.xPos, cursor.yPos);
        mvaddch(cursor.xPos,cursor.yPos,'X');
        mvaddch(tempx,tempy,' ');
        mvaddch(51,126, 'L');
        mvaddch(51,126, 'L');
        refresh();

        input = getch();

        if(input == KEY_UP) {
            tempx = cursor.xPos;
            tempy = cursor.yPos;
            if(isValidToMoveTo(cursor.xPos -= CROSSHAIR_SPEED, cursor.yPos)) {
                cursor.xPos -= CROSSHAIR_SPEED;
            }
        }else if(input == KEY_DOWN) {
            tempx = cursor.xPos;
            tempy = cursor.yPos;
            if(isValidToMoveTo(cursor.xPos  += CROSSHAIR_SPEED, cursor.yPos)) {
                cursor.xPos += CROSSHAIR_SPEED;
            }
        }else if(input == KEY_LEFT) {
            tempx = cursor.xPos;
            tempy = cursor.yPos;
            if(isValidToMoveTo(cursor.xPos, cursor.yPos  -= CROSSHAIR_SPEED)) {
                cursor.yPos -= CROSSHAIR_SPEED;
            }
        }else if(input == KEY_RIGHT) {
            tempx = cursor.xPos;
            tempy = cursor.yPos;
            if(isValidToMoveTo(cursor.xPos, cursor.yPos += CROSSHAIR_SPEED)) {
                cursor.yPos += CROSSHAIR_SPEED;
            }
        }
    }
    printf("\033[?1003l\n");
    wrefresh(game);
    refresh();
    delwin(game);
    endwin();
}