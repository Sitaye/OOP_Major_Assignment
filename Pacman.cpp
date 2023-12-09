#include<bits/stdc++.h>
#include<conio.h>
#include"const.h"
#include"unit.h"
#include"game.h"
using i64 = long long;
int main()
{
    while(loading){
        switch(menu()){
            case 1:game1();break;
            case 2:game2();break;
            case 3:showlist();break;
            case 4:about();break;
            default:loading=false;break;
        }
    }
    return 0;
}