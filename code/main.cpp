#include "TypeDef.h"
#include "FuncState.h"

int main(int argc, char* argv[]){

//    char *input_file = "D:/code/instances/regular/cycle10.mtx";
    char input_file[] = "D:/code/instances/harwell-boeing/bcsstk05 ";
    printf("The instance name    : %s \n",input_file);
    InstanceData ins{};
    ins.readFile(input_file);
    Attribute attr;
    attr.seed = 66;
    srand(attr.seed);
    Solution sol(ins);
    sol.initialingSolRandom(ins);
    attr.baseTenure = 20 + ins.vertexNum/3;
    attr.randomTenure = 20 + ins.vertexNum/6;
    attr.timeLimit = 1.0;
    attr.improveCut = 1000000;
    sol.printHostGraph();

    tabuSearch(sol,ins,attr);

    attr.printInformation();
    sol.check(ins);
    return 0;
}