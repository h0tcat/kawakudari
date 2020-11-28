#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

typedef struct
{
    int x;
    int y;
    int point;
    char *chara;

} Canue;

void setup()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    nodelay(stdscr, true);
    scrollok(stdscr, true);
}

void generateRock()
{
    int rockX = (rand() % 30) + 1;
    int rockY = 20;
    char *rockChar = "*";

    mvprintw(rockY, rockX, rockChar);
    scrl(1);
}

char pointScoreChars[128];
void gameloop(Canue *player)
{
    srand((unsigned)time(0UL));

    char position_chr;

    while (1)
    {

        switch (getch())
        {
        case KEY_LEFT:
            player->x--;
            break;
        case KEY_RIGHT:
            player->x++;
            break;
        }

        //プレイヤーの移動制限コード
        if (player->x <= 0)
            player->x = 0;
        else if (player->x >= 30)
            player->x = 30;

        position_chr = mvinch(player->y, player->x);

        if (position_chr == '*')
        {
            mvprintw(player->y, player->x, "CRASH!");
            
            sprintf(pointScoreChars, "SCORE: %05d", player->point);
            mvprintw(25, 15, pointScoreChars);
            nodelay(stdscr, false);
            getch();
            break;
        }

        mvprintw(player->y, player->x, player->chara);
        generateRock();
        usleep(82000);
        player->point++;
    }
}

int main(void)
{

    setup();
    Canue player = {
        .chara = "O",
        .x = 15,
        .y = 5,
        .point = 0,
    };
    gameloop(&player);
    endwin();
    return 0;
}