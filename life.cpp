#include "life.hpp"

static int wide = 25;
static int len = 50;
static size_t lifeCycle = 0;//生命周期
int main(int argc,char** argv)
{
    if(argc < 2)
    {
        cout << "use:" << argv[0] << " cfgfile" << endl;
        return 0;
    }
    
    string fileName = argv[1];
    vector<int> pointVec;
    //获取cfgfile中设定的坐标点
    GetPoint(pointVec,fileName);
    //copy
    vector<int> aftVec(pointVec.begin(),pointVec.end());
    while(1)
    {
        lifeCycle++;
        DisLife(aftVec);
        aftVec = OneCycle(aftVec);
        //sleep(1);    
        usleep(500000);
    }

    return 0;
}

//获取file中设置的坐标点，二维降维成一维点存入vec
void GetPoint(vector<int>& vec,const string file)
{
    ifstream infile;
    infile.open(file,ifstream::in);
    assert(infile.is_open());
    
    string temp;
    string::size_type pos;
    int xp = 0,yp = 0,point = 0;
    while(getline(infile,temp))
    {
        //点信息获取完成，退出
        if(temp.find("-1,-1") != string::npos)
        {
            break;
        }
        if((pos = temp.find(",")) != string::npos)
        {
            xp = stoi(temp.substr(0,pos));
            yp = stoi(temp.substr(pos+1));
            point = xp * len + yp;//二维坐标点降维成一维
            vec.push_back(point);
        }

    }
    infile.close();
    cout << "vec size:" << vec.size() << endl;
}

//Display 存在的点显示成:"+";不存在的点显示成:"-"
void DisLife(vector<int>& vec)
{
    cout << "Life(" << lifeCycle << "):" << endl;

    int po = 0;
    for(int i = 0;i < wide;i++)     //x轴
    {
        for(int j = 0;j < len;j++)  //y轴
        {
            po = i * len + j;
            auto it = find(vec.begin(),vec.end(),po);
            if(it != vec.end())
                cout << "+";
            else
                cout << "-";
        }
        cout << endl;
    }
    cout << "\n\n" << endl;
}

//经过一周期后点的变化
vector<int> OneCycle(vector<int>& vec)
{
    vector<int> after;

    //全图每个点都check一遍，check每个点周围8个点
    for(int i = 0;i < wide;i++)
    {
        for(int j = 0;j < len;j++)
        {
            int count = GetCount(i,j,vec);
            //判断
            int pi = i * len + j;
            if(count == 2)
            {
                auto it = find(vec.begin(),vec.end(),pi);
                if(it != vec.end())
                {
                    after.push_back(pi);
                }

            }
            else if(count == 3)
            {
                after.push_back(pi);
            }

        }
    }

    vec.clear();
    return after;
}

//获取周围8个位置的细胞数
int GetCount(int x,int y,const vector<int> &vec)
{
    int count = 0;
    for(int row = x-1;row <= x+1;row++)
    {
        for(int col = y-1;col <= y+1;col++)
        {
            //排除自己的坐标
            if(row == x && col == y)
                continue;

            //周围8个点坐标
            int px = row*len + col;
            auto it = find(vec.begin(),vec.end(),px);
            if(it != vec.end())
            {
                count++;
            }
        }
    }

    return count;
}
