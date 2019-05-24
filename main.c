#include <curses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define HEIGHT 50
#define WIDTH 125
#define HOUSES 6
#define MAX_MISSILES 10
#define CROSSHAIR_SPEED 3
#define SHOTS 10





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



typedef struct Shot {
    int xPos;
    int yPos;
    int stage;
} Shot;




Cursor createCursor() {
    Cursor cursor;
    cursor.xPos = 40;
    cursor.yPos = 62;
    cursor.speed = CROSSHAIR_SPEED;

    return cursor;
}



Shot createShots() {
    Shot shots;
    shots.stage = 0;
    shots.xPos = 0;
    shots.yPos = 0;
    
    return shots;
}




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
    int temp = 1;

    if(x > 43 || x < 1) {
        mvprintw(20,20,"x boundaries broken");

        temp = -1;
    }
    else if(y > 120 || y < 5) {
        mvprintw(20,20,"y boundaries broken");

        temp = -1;
    }

    return temp;
}


void drawOrDeleteCursor(int flag, int x, int y) {
    if(flag) { //draw
        mvprintw(x-1,y,"-");
        mvprintw(x,y-2,"| + |");
        mvprintw(x+1,y,"-");
    }
    else { //delete
        mvprintw(x-1,y," ");
        mvprintw(x,y-2,"     ");
        mvprintw(x+1,y," ");
    }
}



void shoot(int x, int y, Shot shots[SHOTS]) {
    int temp = -1;

    for(int i = 0; i < SHOTS; i++) {
        if(shots[i].stage == 0) {
            temp = i;
            shots[i].stage = 1;
            shots[i].xPos = x;
            shots[i].yPos = y;
            break;
        }        
    }

    if(temp > 0) {
        mvprintw(x,y-1," + ");
        mvprintw(x,y-1,"+O+");
        mvprintw(x,y-1," + ");
    }
}




void manageShots(Shot shots[SHOTS]) {
    int temp;

    for(int i = 0; i < SHOTS; i++) {
        if(shots[i].stage == 1) {
            mvprintw(shots[i].xPos-2, shots[i].yPos,"+");
            mvprintw(shots[i].xPos-1, shots[i].yPos-1,"+#+");
            mvprintw(shots[i].xPos, shots[i].yPos-2,"+#O#+");
            mvprintw(shots[i].xPos+1, shots[i].yPos-1,"+#+");
            mvprintw(shots[i].xPos+2, shots[i].yPos,"+");
            shots[i].stage = 2;
        }
        else if(shots[i].stage == 2) {
            mvprintw(shots[i].xPos-2, shots[i].yPos-1,"###");
            mvprintw(shots[i].xPos-1, shots[i].yPos-2,"#####");
            mvprintw(shots[i].xPos, shots[i].yPos-2,"##@##");
            mvprintw(shots[i].xPos+1, shots[i].yPos-2,"#####");
            mvprintw(shots[i].xPos+2, shots[i].yPos-1,"###");
            shots[i].stage = 3;
        }
        else if(shots[i].stage == 3) {
            mvprintw(shots[i].xPos-2, shots[i].yPos-1,"   ");
            mvprintw(shots[i].xPos-1, shots[i].yPos-2,"     ");
            mvprintw(shots[i].xPos, shots[i].yPos-2,"     ");
            mvprintw(shots[i].xPos+1, shots[i].yPos-2,"     ");
            mvprintw(shots[i].xPos+2, shots[i].yPos-1,"   ");

            mvprintw(shots[i].xPos-2, shots[i].yPos,"+");
            mvprintw(shots[i].xPos-1, shots[i].yPos-1,"+#+");
            mvprintw(shots[i].xPos, shots[i].yPos-2,"+#O#+");
            mvprintw(shots[i].xPos+1, shots[i].yPos-1,"+#+");
            mvprintw(shots[i].xPos+2, shots[i].yPos,"+");
            shots[i].stage = 4;
        }
        else if(shots[i].stage == 4) {
            mvprintw(shots[i].xPos-2, shots[i].yPos," ");
            mvprintw(shots[i].xPos-1, shots[i].yPos-1,"   ");
            mvprintw(shots[i].xPos, shots[i].yPos-2,"     ");
            mvprintw(shots[i].xPos+1, shots[i].yPos-1,"   ");
            mvprintw(shots[i].xPos+2, shots[i].yPos," ");

            mvprintw(shots[i].xPos-1, shots[i].yPos,"+");
            mvprintw(shots[i].xPos, shots[i].yPos-1,"+O+");
            mvprintw(shots[i].xPos+1, shots[i].yPos,"+");
            shots[i].stage = 5;
        }
        else if(shots[i].stage == 5) {
            mvprintw(shots[i].xPos-1, shots[i].yPos," ");
            mvprintw(shots[i].xPos, shots[i].yPos-1,"   ");
            mvprintw(shots[i].xPos+1, shots[i].yPos," ");
            shots[i].stage = 0;
        }
    }
}




void manageBullets(Bullet bullets[MAX_MISSILES]) {
    
}




int main() {
    int housePos[HOUSES];
    Bullet bullet[MAX_MISSILES];
    int input, tempx, tempy, checker;
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


    /*for(int h = 1; h < HEIGHT-1; h++) {
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
    }*/

    wrefresh(game);

    Cursor cursor;
    cursor = createCursor();

    Shot shots[SHOTS];

    for(int i = 0; i < SHOTS; i++) {
        shots[i] = createShots();
    }

    
    
    while(1) {
        

        mvprintw(1,5,"%d %d",cursor.xPos, cursor.yPos);
        drawOrDeleteCursor(0,tempx,tempy);
        drawOrDeleteCursor(1,cursor.xPos,cursor.yPos);
        manageShots(shots);
        
        mvaddch(1,1, ' ');
        refresh();

        timeout(50);
        input = getch();
        

        if(input == KEY_UP) {
            
            checker = isValidToMoveTo((cursor.xPos - CROSSHAIR_SPEED), cursor.yPos);
            if(checker == 1) {
                tempx = cursor.xPos;
                tempy = cursor.yPos;
                cursor.xPos -= CROSSHAIR_SPEED;
            }
        }else if(input == KEY_DOWN) {
            checker = isValidToMoveTo((cursor.xPos + CROSSHAIR_SPEED), cursor.yPos);
            if(checker == 1) {
                tempx = cursor.xPos;
                tempy = cursor.yPos;
                cursor.xPos += CROSSHAIR_SPEED;
            }
        }else if(input == KEY_LEFT) {
            checker = isValidToMoveTo(cursor.xPos, (cursor.yPos-CROSSHAIR_SPEED));
            if(checker == 1) {
                tempx = cursor.xPos;
                tempy = cursor.yPos;
                cursor.yPos -= CROSSHAIR_SPEED;
            }
        }else if(input == KEY_RIGHT) {
            checker = isValidToMoveTo(cursor.xPos, (cursor.yPos+CROSSHAIR_SPEED));
            if(checker == 1) {
                tempx = cursor.xPos;
                tempy = cursor.yPos;
                cursor.yPos += CROSSHAIR_SPEED;
            }
        }else if(input == 's') {
            shoot(cursor.xPos, cursor.yPos, shots);
        }
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
    printf("\033[?1003l\n");
    wrefresh(game);
    refresh();
    delwin(game);
    endwin();
}