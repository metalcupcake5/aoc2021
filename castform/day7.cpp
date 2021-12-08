#include <iostream>
#include <fstream>
#include <vector>
#include <string>
 
using str=std::string;
using vecInt=std::vector<int>;

int abs(int num){
    if (num<0)
        return num*-1;
    return num;
}
std::vector<long> listOfSum(int length){
    std::vector<long> listF{0,1};
    for (int i{2};i<=length;i++){
        listF.push_back(listF[i-1]+i);
    }
    return listF;

}
vecInt makeCrabs(){
    str a{};
    vecInt crabs{};
    std::ifstream input{};
    input.open("day7.txt");
    std::getline(input,a);
    input.close();
    for(size_t i{a.find(',')};i!=str::npos;i=a.find(',')){
        crabs.push_back(std::stoi(a.substr(0,i)));
        a.erase(0,i+1);
    }
    crabs.push_back(std::stoi(a));
    return crabs;
}

int fuelFromNum(const vecInt &crabs, int position){
    int sum{0};
    for (int i:crabs){
        sum += abs(i-position);
    }
    return sum;
}

long fuelFromNum2(const vecInt &crabs, int position, const std::vector<long> &listF){
    int sum{0};
    for (int i:crabs){
        sum +=listF[abs(i-position)];
    }
    return sum;
}

int main(){
    vecInt crabs{makeCrabs()};
    long curnt{0};
    long past{fuelFromNum(crabs, 0)};
    std::vector<long> liftF{listOfSum(2000)};
    for (int i{1};i<1200;i++){
        curnt = fuelFromNum(crabs, i);
        if (curnt>past)
            break;
        past=curnt;
    }
    std::cout<<past<<"\n";
    past={fuelFromNum2(crabs, 0, liftF)};
    for (int i{1};i<1200;i++){
        curnt = fuelFromNum2(crabs, i,liftF);
        if (curnt>past)
            break;
        past=curnt;
    }
    std::cout<<past<<"\n";
    return 1;
}