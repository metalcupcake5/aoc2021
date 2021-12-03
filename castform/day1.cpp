#include <iostream>
#include <vector>
#include <fstream> 
#include <string>

std::vector<int> makeVec(){
    std::ifstream input;
    std::vector<int> list{};
    input.open("day1.txt");
    std::string a{};
    if (input.is_open()){
        while (input){
            std::getline(input,a);
            list.push_back(std::stoi(a));
        }
        input.close();    
    }
    list.pop_back();
    return list;
} 


int main(){
    std::vector<int> list{makeVec()};
    int counter{0};
    int old{list[0]};
    for (int i: list){
        
        if (i > old)
            counter++;
        old = i;
    }
    std::cout << "day 1 p1 : " << counter << "\n";

    std::vector<int> buff{list[0],list[1],list[2]};
    counter = 0;
    for (int i: list){
        buff.push_back(i);
        if (i>buff[0])
            counter++;
        buff.erase(buff.begin());
    }
    std::cout << "pt2 : " << counter << "\n";
}