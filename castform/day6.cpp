#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using vecInt=std::vector<int>;
using str=std::string;

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

long long howManyFromSpawn(const std::vector<long long> &factory,int day){
    long long fishes{1};
    if (day<9)
        return fishes;
    day -=9;

    for(int i{day};i>0;i-=7){
        fishes += factory[i];
    }
    return fishes;
}

std::vector<long long> fishFactory(int days){
    std::vector<long long> factory{};
    for(int i{0};i<days;i++){
        factory.push_back(howManyFromSpawn(factory,i));
    }
    return factory;
}

long long fishAfterDaysV2(int days,int iniFish,const std::vector<long long> &factory){
    long long fishes{0};
    int cT{days};
    if (cT<=iniFish)
        return fishes;
    cT-= iniFish;
    for(int i{cT};i>0;i-=7){
        fishes += factory[i];
    }
    return fishes;

}
int main(){
    vecInt fishes{makeVec()};
    long long sum{0};
    std::vector<long long> factory{fishFactory(257)};
    for (size_t i{0};i<fishes.size();i++){
        if (fishes[i]!=0){
            sum += fishAfterDaysV2(81, i+1,factory)*fishes[i]+fishes[i];
        }
    }

    std::cout<<sum<<"\n";
    sum=0;
    for (size_t i{0};i<fishes.size();i++){
        if (fishes[i]!=0){
            sum += fishAfterDaysV2(257, i+1,factory)*fishes[i]+fishes[i];
        }
    }

    std::cout<<sum<<"\n";
}