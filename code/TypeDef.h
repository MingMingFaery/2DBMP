#ifndef TYPEDEF_H
#define TYPEDEF_H
#include<iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <list>

using namespace std;

#define MAXVALUE 99999999
#define EMPTY (-1)

typedef struct MoveCandidate{
    MoveCandidate copyMove() const;
    explicit MoveCandidate(int move=EMPTY,int host=EMPTY, int swap=EMPTY);
    int index;
    int hostIndex;
    int swapIndex;
    int moveValue;
    int tieValue;
}MoveCandidate;
//记录迭代过程中的一些信息
typedef struct Attribute{
    explicit Attribute();
    void printInformation(bool result=true,bool parameter=false,bool time= false,bool other= false) const;
    //parameter
    int seed;
    int baseTenure;
    int randomTenure;
    double timeLimit;
    int improveCut;
    //result
    int iter;
    int stagnate;
    int obj;
    int tie;
    //run time
    double t;
    double totalTime;     // 禁忌搜索总时间
    double findBestTime;  // 找到最优解所需要的时间
    double moveTime;      //搜索邻域占用的时间
    double inLoopTime;
    double miLoopTime;
    double lengthTime;
    double regionTime;
    //frequency
    int searchNum;
    int emptyNum;
    //iteration
    list<int> objectValues;
    list<int> tieValues;
}Attribute;

class InstanceData{
public:
    void readFile(char file[]);
    ~InstanceData();
    void printGraph() const;

    int **graph;
    int **edge;
    int **vertexEdge;
    int **vertexVertex;
    int vertexNum;
    int edgeNum;
    char graphInformation[];
};

class Solution{
public:
    explicit Solution(const InstanceData& ins,int obj=MAXVALUE,int tie=MAXVALUE);
    ~Solution();
    void initialingSolSequential(const InstanceData& ins);
    void initialingSolRandom(const InstanceData& ins);
    void printHostGraph(bool judge= false) const;
    void coverSol(const Solution& sol);
    void getLength(const InstanceData& ins,bool judge= false);
    void execute(MoveCandidate move,const InstanceData& ins);
    bool check(const InstanceData& ins) const;

    int *injection; //对应关系
    int **hostGraph;
    int objectValue;
    int tieValue;
    int hostGraphSize;
    int hostVertexNum;
    int edgeNum;
    int vertexNum;
    int **edgeLength;
};

class TabuTable{
public:
    TabuTable(const InstanceData& ins,int bTenure,int rTenure);
    ~TabuTable();
    void tabu(MoveCandidate move,int iter,const Solution& sol) const;
    void printTabuTable();

    int tabuTableSize[2]{0};
    int baseTenure;
    int randomTenure;
    int** tabuTable;
};

typedef struct DynamicM{
    explicit DynamicM(const Solution& sol);
    ~DynamicM();
    int vertexNum;
    int hostVertexNum;
    int *judgeVertex;
    int *region ;
    int *lengthNum ;
    int *cutLengthNum ;
    int *addLengthNum ;
    int** regions;
    int *tempList;
}DynamicM;
#endif