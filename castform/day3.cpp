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
        std::cout<<curnt.size()<<"\n";
    }   
    input.close();
    return vec;
}

bvec makeGamma(const std::vector<str> &vec){
    size_t tmp{};
    bvec gamma{};
    size_t half{vec.size()/2};
    for (size_t i{0};i<vec[0].size();i++){
        for (str x:vec)
            if (x[i]=='1')
                tmp++;
        if (tmp>half)
            gamma.push_back(true);
        else
            gamma.push_back(false);
        tmp=0;
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

int main(){
    std::vector<str> vec{makeVec()};
    bvec gamma{makeGamma(vec)};
    bvec epsilon{epsilonFromGamma(gamma)};
    int dgamma{binaryToDec(gamma)};
    int depsilon{binaryToDec(epsilon)};
    std::cout << dgamma*depsilon<<"\n";
}