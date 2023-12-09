int menu()
{
    std::ifstream begin("begin.txt");
    std::string s;
    while(std::getline(begin,s))
        std::cout<<s<<"\n";
    begin.close();
    int choose;
    std::cin>>choose;
    return choose;
}
void about()
{
    system("cls");
    std::ifstream aboutinfo("aboutinfo.txt");
    std::string s;
    while(std::getline(aboutinfo,s))
        std::cout<<s<<"\n";
    aboutinfo.close();
    char option;
    std::cin>>option;
    system("cls");
}
void back_to_menu()
{
    std::cout<<"\n\nWould you like to return to menu?(Y/N): ";
    char option;
    std::cin>>option;
    if(option=='N' || option=='n')
        loading=false;
    else
        system("cls");
}
void saved(int goal,int mapmode)
{
    std::ofstream save("list.txt",std::ios_base::app);
    std::string name,mapm = (mapmode==1)?"Class":"Hard";
    std::cout<<"Please input your name: ";
    std::cin>>name;
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    save << localTime->tm_year + 1900 << "-" << localTime->tm_mon + 1 << "-" << localTime->tm_mday <<" "<<localTime->tm_hour<<":"<<localTime->tm_min<<":"<<localTime->tm_sec<<" "<<"\t"<< mapm <<"\t"<< name<<"\t"<<goal<<"\n";
    std::cout<<"Goals Saved!\n";
    save.close();
    back_to_menu();
}
void showlist()
{
    system("cls");
    std::ifstream listoutput("list.txt");
    std::string s;
    while(std::getline(listoutput,s))
        std::cout<<s<<"\n";
    listoutput.close();
    back_to_menu();
}
void game1()
{
    std::ifstream map1("map1.txt");
    int len=1;
    std::string s;
    while(std::getline(map1,s))
        map[len++]=s;
    map1.close();
    reverse=true;
    Pacman pacman(Player_x_1,Player_y_1,1);
    Ghost ghost1(Ghost1_x_1,Ghost1_y_1),ghost2(Ghost2_x_1,Ghost2_y_1),ghost3(Ghost3_x_1,Ghost3_y_1),ghost4(Ghost4_x_1,Ghost4_y_1);
    char moved;
    while(1){
        system("cls");
        for(int i=1;i<=Init_Height_1;i++){
            for(int j=0;j<=Init_Width_1-1;j++)
                std::cout<<map[i][j];
            std::cout<<"\n";
        }
        pacman.FinalGoal();
        if(pacman.checkwin()){
            std::cout<<"Congratulations! You are the winner!\n";
            saved(pacman.getGoal(),1);
            break;
        }
        if(pacman.checkpresentation())
            std::cout<<"Go to the birthplace to catch the '?' !\n";
        if (ghost1.checkCollision(pacman.getX(), pacman.getY()) || ghost2.checkCollision(pacman.getX(), pacman.getY()) || ghost3.checkCollision(pacman.getX(), pacman.getY()) || ghost4.checkCollision(pacman.getX(), pacman.getY())) {
            std::cout << "Game Over!\n";
            saved(pacman.getGoal(),1);
            break;
        }
        if(_kbhit()){
            moved = _getch();
            pacman.Chage_Direction(moved);
        }
        pacman.move();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if(reverse){
            ghost1.move(pacman.getX(), pacman.getY());
            ghost2.move(pacman.getX(), pacman.getY());
            ghost3.move(pacman.getX(), pacman.getY());
            ghost4.move(pacman.getX(), pacman.getY());
        }
        if(Ghost::frozen==0)
            reverse=!reverse;
        else
            Ghost::frozen--;
        if(pacman.getGoal()==MAX_GOAL_1){
            map[Final_Goal_X_1][Final_Goal_Y_1]='?';
            pacman.Chage_Presentation();
        }
    }
}
void game2()
{
    std::ifstream map2("map2.txt");
    int len=1;
    std::string s;
    while(std::getline(map2,s))
        map[len++]=s;
    map2.close();
    reverse=true;
    Pacman pacman(Player_x_2,Player_y_2,2);
    Ghost ghost1(Ghost1_x_2,Ghost1_y_2),ghost2(Ghost2_x_2,Ghost2_y_2),ghost3(Ghost3_x_2,Ghost3_y_2),ghost4(Ghost4_x_2,Ghost4_y_2);
    char moved;
    while(1){
        system("cls");
        for(int i=1;i<=Init_Height_2;i++){
            for(int j=0;j<=Init_Width_2-1;j++)
                std::cout<<map[i][j];
            std::cout<<"\n";
        }
        pacman.FinalGoal();
        if(pacman.checkwin()){
            std::cout<<"Congratulations! You are the winner!\n";
            saved(pacman.getGoal(),2);
            break;
        }
        if(pacman.checkpresentation())
            std::cout<<"Go to the birthplace to catch the '?' !\n";
        if (ghost1.checkCollision(pacman.getX(), pacman.getY()) || ghost2.checkCollision(pacman.getX(), pacman.getY()) || ghost3.checkCollision(pacman.getX(), pacman.getY()) || ghost4.checkCollision(pacman.getX(), pacman.getY())) {
            std::cout << "Game Over!\n";
            saved(pacman.getGoal(),2);
            break;
        }
        if(_kbhit()){
            moved = _getch();
            pacman.Chage_Direction(moved);
        }
        pacman.move();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if(reverse){
            ghost1.move(pacman.getX(), pacman.getY());
            ghost2.move(pacman.getX(), pacman.getY());
            ghost3.move(pacman.getX(), pacman.getY());
            ghost4.move(pacman.getX(), pacman.getY());
        }
        if(Ghost::frozen==0)
            reverse=!reverse;
        else
            Ghost::frozen--;
        if(pacman.getGoal()==MAX_GOAL_2){
            map[Final_Goal_X_2][Final_Goal_Y_2]='?';
            pacman.Chage_Presentation();
        }
    }
}
