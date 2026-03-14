#include"Snake.h"
#include <random>
#include<map>
SNAKE s;
std::set<std::pair<int,int>> foodPlace;
std::mt19937 rnd(time(nullptr));
char nowDir;
std::map<char,std::pair<int,int>> mp;
void begin() {
    Sleep(s.getSpeed());
    mp['w']={1,0};
    mp['a']={0,-1};
    mp['s']={-1,0};
    mp['d']={0,1};
    while(1) {
        if(_kbhit()) {
            char c=_getch();
            if(c=='w'||c=='a'||c=='s'||c=='d')
                nowDir=c,print();
        }
        auto [x,y]=s.getHead()->getData().getData();
        auto [dx,dy]=mp[nowDir];
        x+=dx,y+=dy;
        switch(check(x,y)) {
            case 0:
                GameOver();
                break;
            case 1:
                s.moveSnake(x,y);
                break;
            case 2:
                s.cut(x,y);
                break;
            case 4:
                s.getFood(FOOD(x,y));
                break;
        }
        print();
    }
}