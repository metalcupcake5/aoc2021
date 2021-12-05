#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//format x1y1x2y2
using vecCoord = std::vector<std::vector<int>>;

int abs(int num){
    if (num < 0)
        return num*-1;
    return num;
}

vecCoord makeCoords(){
    vecCoord coords{};
    std::ifstream input;
    std::string a{};
    std::vector<int> coord{};
    input.open("day5.txt");
    size_t cur{};
    while (std::getline(input,a)){
        cur=a.find(',');
        coord.push_back(std::stoi(a.substr(0,cur)));
        a.erase(0,cur+1);
        cur=a.find(" ");
        coord.push_back(std::stoi(a.substr(0,cur)));
        a.erase(0,cur+4);
        cur=a.find(',');
        coord.push_back(std::stoi(a.substr(0,cur)));
        a.erase(0,cur+1);
        coord.push_back(std::stoi(a));
        coords.push_back(coord);
        coord.clear();
    }
    input.close();
    return coords;

}

vecCoord makeBlank(int sizeOfBlank){
    vecCoord blank{};
    for (int y{0};y<sizeOfBlank;y++){
        blank.push_back({});
        for (int x{0};x<sizeOfBlank;x++)
            blank[y].push_back(0);
    }
    return blank;
}

int verticalLine(vecCoord &blank, int x,int yI,int yM){
    int sum{0};
    for (int i{yI};i<=yM;i++){
        blank[i][x]++;
        if (blank[i][x]==2){
            sum++;
        }
        }
    return sum;
}
int horiLine(vecCoord &blank, int y, int xI, int xM){
    int sum{0};
    for(int i{xI};i<=xM;i++){
        blank[y][i]++;
        if (blank[y][i]==2)
            sum++;
    }
    return sum;
}
int diagLine(vecCoord &blank,int x1,int x2, int y1, int y2){
    if(abs(x1-x2)!=abs(y1-y2))
        return 0;
    int sum{0};
    int yInc{1};
    int curY{y1};
    if (y1>y2)
        yInc= -1;
    if (x1>x2){
        for (int x{x1};x>=x2;x--){
            blank[curY][x]++;
            if (blank[curY][x]==2)
                sum++;
            curY +=yInc;
        }
    }
    else{
        for (int x{x1};x<=x2;x++){
            blank[curY][x]++;
            if (blank[curY][x]==2)
                sum++;
            curY+= yInc;
        }
    }
    return sum;
}
int addLineTooBlank(vecCoord &blank, int x1, int x2, int y1,int y2){
    int sum{0};
    if (x1==x2){
        if (y1<y2)
            sum += verticalLine(blank, x1, y1, y2);
        else
            sum += verticalLine(blank, x1, y2, y1);
    }
    else if (y1==y2){
        if (x1<x2)
            sum += horiLine(blank, y1, x1, x2);
        else
            sum += horiLine(blank, y1, x2, x1);
    }
    return sum;    
}

int main(){
    int sum{0};
    vecCoord coords{makeCoords()};
    vecCoord blank{makeBlank(999)};
    for (std::vector<int> i:coords){
        sum += addLineTooBlank(blank,i[0],i[2],i[1],i[3]);
    }
    std::cout<<sum<<"\n";
    for(std::vector<int> i:coords)
        sum +=diagLine(blank, i[0], i[2], i[1], i[3]);
    std::cout<< sum<<"\n";
}