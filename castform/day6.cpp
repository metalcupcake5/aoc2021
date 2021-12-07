#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using vecInt=std::vector<int>;
using str=std::string;
using vecLong=std::vector<long long>;

vecInt makeVec(){
    vecInt fishes{};
    for (int i;i<10;i++)
        fishes.push_back(0);
    str a;
    std::ifstream input;
    input.open("day6.txt");
    getline(input,a);
    for (char i:a){
        if (i!=','){
            fishes[static_cast<int>(i-'0')]++;
        }
    }
    return fishes;
}

long long howManyFromSpawn(const vecLong &factory,int day){
    long long fishes{1};
    if (day<9)
        return fishes;
    day -=9;

    for(int i{day};i>0;i-=7){
        fishes += factory[i];
    }
    return fishes;
}

vecLong fishFactory(int days){
    vecLong factory{};
    for(int i{0};i<=days;i++){
        factory.push_back(howManyFromSpawn(factory,i));
    }
    return factory;
}

long long fishAfterDaysV2(int days,int iniFish,const vecLong &factory){
    return factory[(9-iniFish) +days];

}

void PrintParts(const vecInt &fishes,const vecLong& factory,int days){
    long long sum{0};
    for (size_t i{0};i<fishes.size();i++){
        if (fishes[i]!=0){
            sum += fishAfterDaysV2(days, i+1,factory)*fishes[i];
        }
    }
    std::cout<<sum<<"\n";
}
int main(){
    vecInt fishes{makeVec()};
    long long sum{0};
    vecLong factory{fishFactory(257+9)};
    PrintParts(fishes, factory, 81);
    PrintParts(fishes, factory, 257);
    return 1;
}
