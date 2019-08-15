#ifndef __LIFE_HPP__
#define __LIFE_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <assert.h>
#include <unistd.h>

using namespace std;

void GetPoint(vector<int>& vec,const string file);
void DisLife(vector<int>& vec);
vector<int> OneCycle(vector<int>& vec);
//获取周围8个位置的细胞数
int GetCount(int x,int y,const vector<int> &vec);

#endif /*life.hpp*/
