#include"Snake.h"
#include <random>
#include<map>
SNAKE s;
std::set<std::pair<int,int>> snakePlace,foodPlace,nullPlace;
std::mt19937 rnd(time(nullptr));
char nowDir;
std::map<char,std::pair<int,int>> mp;
void begin() {
    mp['w']={1,0};
    mp['a']={0,-1};
    mp['s']={-1,0};
    mp['d']={0,1};
    while(1) {
        if(_kbhit()) {
            char c=_getch();
            if(c=='w'||c=='a'||c=='s'||c=='d')
                nowDir=c;
        }
        auto [x,y]=s.getHead()->getData().getData();
        Sleep(s.getSpeed());
    }
}