#ifndef FUNCSTATE_H
#define FUNCSTATE_H
#include "TypeDef.h"

//禁忌搜索
void tabuSearch(Solution &sol,InstanceData &ins,Attribute &attr);

//搜索move邻域
void moveNeigh(Solution &sol, InstanceData &ins,const TabuTable& tabuTable, MoveCandidate *moves, int &moveNum, DynamicM& dynamic,Attribute& attr);

//计算距离：给定两个二维坐标，计算曼哈顿距离
int getDistances(int loc1,int loc2,int loc3);

//判断某个顶点是否位于最大边
void getJudgeVertex(int* judgeVertex,const Solution& sol,double &runtime);

//获取边长数量，复杂度 m
void getLengthNum(const Solution& sol,int* lengthNum);

//减去和移动点相关边的长度数量
void cutLength(const Solution& sol,const InstanceData& ins,int* lengthNum,int index,double &runtime,int swapIndex=EMPTY);

//增加和移动点相关边的长度数量，复杂度2m/n
void addLength(const Solution& sol,const InstanceData& ins,int* lengthNum,MoveCandidate move,double &runtime);

//计算目标值，复杂度 n^0.5
int getObject(const int* lengthNum,int obj,double &);

//计算平局评价值，复杂度 n^0.5
int getTieValue(const int* lengthNum,int objValue,double &,int accuracy=3,int magnitude=1000);

//计算每个顶点的可接受区域
void getRegions(const Solution& sol, int** regions, double &runtime);

//对移动顶点index相连顶点的可接受区域regions取交集
void vertexRegion(const DynamicM& dynamic,int index,const InstanceData& ins,const Solution& sol,double &runtime);

//对两个列表取交集，复杂度 n
void intersection(int* list0,const int* list1,int size);

//输出操作集信息
void printMoves(MoveCandidate*,int ,int hostSize);

//输出移动信息
void printMove(MoveCandidate,int hostSize);

//保存链表信息
void saveResult(const list<int>&,char*);

#endif
