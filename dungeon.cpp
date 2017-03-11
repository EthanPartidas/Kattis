#include <iostream>
#include <string>
#include <tuple>
#include <queue>
using namespace std;

bool push_node(int a, int b, int c, string** dungeon, int x, int y, int z, queue<tuple<int, int, int, int>>& look, int time)
{
    if(!(0<=x&&x<a&&0<=y&&y<b&&0<=z&&z<c))
        return false;
    if(dungeon[x][y][z]=='E')
    {
        cout<<"Escaped in "<<time<<" minute(s)."<<endl;
        return true;
    }
    if(dungeon[x][y][z]!='#')
    {
        dungeon[x][y][z] = '#';
        look.push(make_tuple(x, y, z, time));
    }
    return false;
}

int main()
{
    int a, b, c;
    while(cin>>a>>b>>c)
    {
        if(a==0&&b==0&&c==0)
            break;
        bool won = false;
        queue<tuple<int, int, int, int>> look;
        string** dungeon;
        dungeon = new string*[a];
        for(int i=0;i<a;i++)
        {
            dungeon[i] = new string[b];
            for(int j=0;j<b;j++)
            {
                cin>>dungeon[i][j];
                for(int k=0;k<c;k++)
                {
                    if(dungeon[i][j][k]=='S')
                        won = push_node(a, b, c, dungeon, i, j, k, look, 0);
                }
            }
        }
        while(look.size()>0&&!won)
        {
            int x = get<0>(look.front());
            int y = get<1>(look.front());
            int z = get<2>(look.front());
            int time = get<3>(look.front());
            look.pop();
            int dirs[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
            for(auto dir:dirs)
            {
                if(push_node(a, b, c, dungeon, x+dir[0], y+dir[1], z+dir[2], look, time+1))
                {
                    won = true;
                    break;
                }
            }
        }
        if(!won)
            cout<<"Trapped!"<<endl;
    }

    return 0;
}
