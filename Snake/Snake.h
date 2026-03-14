#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<memory>
#define MAX_WIDTH 40
#define MAX_HEIGHT 30
class NODE {
    private:
        int x,y;
    public:
        NODE(int xVal,int yVal):x(xVal),y(yVal){}
        ~NODE(){}
};
using FOOD=NODE;
using node=NODE;
class snake {
    private:
        NODE x;
        std::unique_ptr<snake> nxt,frm;
    public:
        snake(NODE xVal,auto NXT,auto FRM):x(xVal),nxt(NXT),frm(FRM){}
        ~snake(){}
};
struct SNAKE {
    int *head,length;
    SNAKE(){ head=nullptr; length=0; }
    void init(int x,int y) {
        
    }
};