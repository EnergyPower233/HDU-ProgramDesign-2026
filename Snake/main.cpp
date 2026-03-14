#include"Snake.h"
int main() {
    while(1) {
        auto result=menu();
        switch(result) {
            case 1:
                init();
                begin();
                break;
            case 2:
                help();
                break;
            case 3:
                about();
                break;
            case 4:
                exit(0);
        }
    }
}