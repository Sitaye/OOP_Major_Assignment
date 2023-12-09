class Unit
{
    public:
        int position_x, position_y;
        int getX()
        {
            return position_x;
        }
        int getY()
        {
            return position_y;
        }
};
class Ghost : public Unit
{
    public:
        static int frozen;
        char pre='o';
        Ghost(int x0,int y0)
        {
            position_x=x0;
            position_y=y0;
        }
        void move(int pacX, int pacY)
        {
            char now=map[position_x][position_y];
            if (position_x < pacX && map[position_x+1][position_y]!='#' && map[position_x+1][position_y] != 'X' && map[position_x+1][position_y] != '?') {
                map[position_x][position_y]=pre;
                pre=map[position_x+1][position_y];
                map[position_x+1][position_y]=now;
                position_x++;
            } else if (position_x > pacX && map[position_x-1][position_y]!='#' && map[position_x-1][position_y] != 'X' && map[position_x-1][position_y] != '?') {
                map[position_x][position_y]=pre;
                pre=map[position_x-1][position_y];
                map[position_x-1][position_y]=now;
                position_x--;
            } else if (position_y < pacY && map[position_x][position_y+2]!='#' && map[position_x][position_y+2] != 'X' && map[position_x][position_y+2] != '?') {
                map[position_x][position_y]=pre;
                pre=map[position_x][position_y+2];
                map[position_x][position_y+2]=now;
                position_y+=2;
            } else if (position_y > pacY && map[position_x][position_y-2] != '#' && map[position_x][position_y-2] != 'X' && map[position_x][position_y-2] != '?') {
                map[position_x][position_y]=pre;
                pre=map[position_x][position_y-2];
                map[position_x][position_y-2]=now;
                position_y-=2;
            }
        }
        bool checkCollision(int pacX, int pacY)
        {
            return (position_x == pacX && position_y == pacY);
        }
};
int Ghost::frozen = 0;
class Pacman : public Unit
{
    private:
        int goal = 0, smallballnum, bigballnum;
        char direction='~',win=false,presentation=false;
    public:
        Pacman(int mapnum)
        {
            if(mapnum==1){
                position_x=Player_x_1;
                position_y=Player_y_1;
                smallballnum=small_total_1;
                bigballnum=big_total_1;
            }
            else if(mapnum==2){
                position_x=Player_x_2;
                position_y=Player_y_2;
                smallballnum=small_total_2;
                bigballnum=big_total_2;
            }
        }
        void move()
        {
            if(direction!='~'){
                int dx,dy;
                switch(direction){
                    case 'w':dx=-1,dy=0;break;
                    case 's':dx=1,dy=0;break;
                    case 'a':dx=0,dy=-2;break;
                    case 'd':dx=0,dy=2;break;
                }
                if(map[position_x+dx][position_y+dy]=='o'){
                    goal+=5;
                    smallballnum--;
                }
                else if(map[position_x+dx][position_y+dy]=='$'){
                    goal+=15;
                    Ghost::frozen = 10;
                    reverse = false;
                    bigballnum--;
                }
                else if(map[position_x+dx][position_y+dy]=='?'){
                    goal+=100;
                    win=true;
                }
                if(map[position_x+dx][position_y+dy]!='#'){
                    map[position_x][position_y]=' ';
                    map[position_x+dx][position_y+dy]='@';
                    if(dy==0)
                        position_x+=dx;
                    else
                        position_y+=dy;
                }
            }
        }
        void FinalGoal()
        {
            std::cout<<"You've got: "<<goal<<"         The [o] : "<<smallballnum<<"        The [$] : "<<bigballnum<<"\n";
        }
        void Chage_Direction(char direct)
        {
            direction=direct;
        }
        int getGoal()
        {
            return goal;
        }
        void Chage_Presentation()
        {
            presentation=true;
        }
        bool checkpresentation()
        {
            return presentation;
        }
        bool checkwin()
        {
            return win;
        }
};