#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using str=std::string;
using bvec = std::vector<bool>;

int exponent(int x,int exp){
    int sum{1};
    for(int i{0};i<exp; i++)
        sum*=x;
    return sum;
}

std::vector<str> makeVec(){
    std::vector<str> vec{};
    std::ifstream input;
    input.open("day3.txt");
    str curnt{};
    while(std::getline(input,curnt)){
        vec.push_back(curnt);
    }   
    input.close();
    return vec;
}

bool find_max(int i,const std::vector<str> &vec){
    size_t tmp{0};
    size_t half{vec.size()/2};
    if(vec.size()%2==1)
        half++;
    for (str x:vec){
        if (x[i]=='1')
            tmp++;
    }
    if (tmp>=half)
        return true;
    return false;
}

bvec makeGamma(const std::vector<str> &vec){
    bvec gamma{};
    for (size_t i{0};i<vec[0].size();i++){
        gamma.push_back(find_max(i,vec));
    }
    return gamma;
}

bvec epsilonFromGamma(const bvec &gamma){
    bvec epsilon{};
    for (bool i:gamma){
        if (i)
            epsilon.push_back(false);
        else
            epsilon.push_back(true);
    }
    return epsilon;
}

int binaryToDec(const bvec &binary){
    size_t curnt{binary.size()-1};
    int dec{};
    for (bool i:binary){
        if (i)
            dec += exponent(2, curnt);
        curnt--;
    }
    return dec;
}

int strToDec(str binary){
    bvec bin{};
    for (char i:binary){
        if (i=='1')
            bin.push_back(true);
        else
            bin.push_back(false);
    }
    return binaryToDec(bin);
}

void purge(int i,std::vector<str> &vec,char max){
    for (int x{static_cast<int>(vec.size()-1)};x>=0;x--){
        if (vec[x][i]!= max)
            vec.erase(vec.begin()+x);
    }
}

int pt2(std::vector<str> vec,bool minmax){
    int i{0};
    bool max{};
    char crnt{};
    char o1;
    char o2;
    if (minmax==true){
        o1='1';
        o2='0';
    }  
    else{
        o1='0';
        o2='1';
    }
    while (true){
        if (find_max(i, vec)==true)
            crnt=o1;
        else
            crnt=o2;
        purge(i,vec,crnt);
        if (vec.size()==1)
            break;   
        i++;
    }
    return strToDec(vec[0]);
}

int main(){
    std::vector<str> vec{makeVec()};
    bvec gamma{makeGamma(vec)};
    bvec epsilon{epsilonFromGamma(gamma)};
    int dgamma{binaryToDec(gamma)};
    int depsilon{binaryToDec(epsilon)};
    std::cout << dgamma*depsilon<<"\n";
    std::cout << pt2(vec,true)*pt2(vec,false)<<"\n";
}
