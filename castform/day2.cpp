#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct command{
    int direction;
    int amount;
};

std::vector<command> makeCommandList(){
    std::vector<command> cmdList{};
    std::ifstream input;
    input.open("day2.txt");
    std::string inps;
    command tmp;
    while (std::getline(input,inps)){
        tmp.amount =static_cast<int>(inps[inps.size()-1]-'0');
        if (inps[0]=='f')
            tmp.direction =1;
        else if(inps[0]=='d')
            tmp.direction =2;
        else if (inps[0]=='u'){
            tmp.direction=2;
            tmp.amount *= -1;
        }
        cmdList.push_back(tmp);
    }
    return cmdList;

}

int pt1(std::vector<command> cmdList){
    int x{0};
    int y{0};
    for (command i:cmdList){
        if (i.direction==1)
            x+=i.amount;
        else
            y+=i.amount;

    }
    return x*y;

}

int pt2(std::vector<command> cmdList){
    int depth{0};
    int x{0};
    int aim{0};
    for(command i:cmdList){
        if (i.direction==1){
            depth += i.amount*aim;
            x+= i.amount;
        }
        else 
            aim += i.amount;
    }

    return x*depth;
}

int main(){
    std::vector<command> cmdList{makeCommandList()};
    std::cout << pt1(cmdList)<<"\n";
    std::cout <<pt2(cmdList)<<"\n";
}