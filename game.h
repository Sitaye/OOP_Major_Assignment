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
void game(int modenum)
{
    int Init_Height,Init_Width,MAX_GOAL,Final_Goal_X,Final_Goal_Y;
    std::string address;
    if(modenum==1){
        address = "map1.txt";
        Init_Height=Init_Height_1;
        Init_Width=Init_Width_1;
        MAX_GOAL=MAX_GOAL_1;
        Final_Goal_X=Final_Goal_X_1;
        Final_Goal_Y=Final_Goal_Y_1;
    }
    else{
        address = "map2.txt";
        Init_Height=Init_Height_2;
        Init_Width=Init_Width_2;
        MAX_GOAL=MAX_GOAL_2;
        Final_Goal_X=Final_Goal_X_2;
        Final_Goal_Y=Final_Goal_Y_2;
    }
    std::ifstream mapl(address);
    int len=1;
    std::string s;
    while(std::getline(mapl,s))
        map[len++]=s;
    mapl.close();
    reverse=true;
    Pacman pacman(modenum);
    Ghost ghost1(modenum,1),ghost2(modenum,2),ghost3(modenum,3),ghost4(modenum,4);
    char moved;
    while(1){
        system("cls");
        for(int i=1;i<=Init_Height;i++){
            for(int j=0;j<=Init_Width-1;j++)
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
        if(ghost1.checkCollision(pacman.getX(), pacman.getY()) || ghost2.checkCollision(pacman.getX(), pacman.getY()) || ghost3.checkCollision(pacman.getX(), pacman.getY()) || ghost4.checkCollision(pacman.getX(), pacman.getY())) {
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
        if(pacman.getGoal()==MAX_GOAL){
            map[Final_Goal_X][Final_Goal_Y]='?';
            pacman.Chage_Presentation();
        }
    }
}
