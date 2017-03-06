#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize)
{
    bool traveled[nMapWidth*nMapHeight];
    for(int i=0;i<nMapWidth*nMapHeight;i++)
    {
        traveled[i] = false;
    }
    vector<tuple<int, int, int>> tree;
    tree.push_back(make_tuple(0, nStartX+nMapWidth*nStartY, 0));
    queue<int> nodes;
    nodes.push(0);
    while(nodes.size()>0)
    {
        int currpos = get<1>(tree[nodes.front()]);
        int currsize = get<2>(tree[nodes.front()]);
        if(pMap[currpos]==0)
        {
            nodes.pop();
            continue;
        }
        if(currpos==(nTargetX+nMapWidth*nTargetY))
        {
            if(currsize>nOutBufferSize)
                return currsize;
            else
            {
                int index = nodes.front();
                for(int i=currsize-1;i>=0;i--)
                {
                    pOutBuffer[i] = get<1>(tree[index]);
                    index = get<0>(tree[index]);
                }
                return currsize;
            }
        }
        if(currpos%nMapWidth-1>=0&&!traveled[currpos-1]&&pMap[currpos-1]==1)
        {
            tree.push_back(make_tuple(nodes.front(), currpos-1, currsize+1));
            nodes.push(tree.size()-1);
            traveled[currpos-1] = true;
        }
        if(currpos%nMapWidth+1<nMapWidth&&!traveled[currpos+1]&&pMap[currpos+1]==1)
        {
            tree.push_back(make_tuple(nodes.front(), currpos+1, currsize+1));
            nodes.push(tree.size()-1);
            traveled[currpos+1] = true;
        }
        if(currpos-nMapWidth>=0&&!traveled[currpos-nMapWidth]&&pMap[currpos-nMapWidth]==1)
        {
            tree.push_back(make_tuple(nodes.front(), currpos-nMapWidth, currsize+1));
            nodes.push(tree.size()-1);
            traveled[currpos-nMapWidth] = true;
        }
        if(currpos+nMapWidth<nMapWidth*nMapHeight&&!traveled[currpos+nMapWidth]&&pMap[currpos+nMapWidth]==1)
        {
            tree.push_back(make_tuple(nodes.front(), currpos+nMapWidth, currsize+1));
            nodes.push(tree.size()-1);
            traveled[currpos+nMapWidth] = true;
        }
        traveled[currpos] = true;
        nodes.pop();
    }
    return -1;
}
