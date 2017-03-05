#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

void step(string* room, int a, int b, vector<pair<int, int>>& fire)
{
    vector<pair<int, int>> next;
    for(pair<int, int> sclel:fire)
    {
        int x = get<0>(sclel);
        int y = get<1>(sclel);
        if(x-1>=0&&room[x-1][y]=='.')
        {
            room[x-1][y] = '*';
            next.push_back(make_pair(x-1, y));
        }
        if(x+1<a&&room[x+1][y]=='.')
        {
            room[x+1][y] = '*';
            next.push_back(make_pair(x+1, y));
        }
        if(y-1>=0&&room[x][y-1]=='.')
        {
            room[x][y-1] = '*';
            next.push_back(make_pair(x, y-1));
        }
        if(y+1<b&&room[x][y+1]=='.')
        {
            room[x][y+1] = '*';
            next.push_back(make_pair(x, y+1));
        }
    }
    fire.clear();
    for(pair<int, int> sclel:next)
    {
        fire.push_back(sclel);
    }
}

int main()
{
    int cases;
    cin>>cases;
    while(cases-->0)
    {
        int b, a;
        cin>>b>>a;
        string room[a];
        for(int i=0;i<a;i++)
        {
            cin>>room[i];
        }
        vector<pair<int, int>> fire;
        queue<tuple<int, int, int>> look;
        for(int i=0;i<a;i++)
        {
            for(int j=0;j<b;j++)
            {
                if(room[i][j]=='*')
                {
                    fire.push_back(make_pair(i, j));
                }
                if(room[i][j]=='@')
                {
                    look.push(make_tuple(i, j, 1));
                    room[i][j] = '.';
                }
            }
        }
        int currtime = 0;
        bool won = false;
        while(look.size()>0)
        {
            int x = get<0>(look.front());
            int y = get<1>(look.front());
            int time = get<2>(look.front());
            if(time>currtime)
            {
                currtime++;
                step(room, a, b, fire);
                continue;
            }
            look.pop();
            if(room[x][y]=='#')
            {
                continue;
            }
            if(x==0||y==0||x==a-1||y==b-1)
            {
                won = true;
                cout<<time<<endl;
                break;
            }
            room[x][y] = '#';
            if(room[x-1][y]=='.')
            {
                look.push(make_tuple(x-1, y, time+1));
            }
            if(room[x+1][y]=='.')
            {
                look.push(make_tuple(x+1, y, time+1));
            }
            if(room[x][y-1]=='.')
            {
                look.push(make_tuple(x, y-1, time+1));
            }
            if(room[x][y+1]=='.')
            {
                look.push(make_tuple(x, y+1, time+1));
            }
        }
        if(!won)cout<<"IMPOSSIBLE"<<endl;

    }

    return 0;
}
