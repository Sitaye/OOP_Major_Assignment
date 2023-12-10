#include<iostream>
#include<conio.h>
#include<thread>
#include<ctime>
#include<fstream>
#include<string>
#include"const.h"
#include"unit.h"
#include"game.h"
using i64 = long long;
int main()
{
    while(loading){
        switch(menu()){
            case 1:game(1);break;
            case 2:game(2);break;
            case 3:showlist();break;
            case 4:about();break;
            default:loading=false;break;
        }
    }
    return 0;
}