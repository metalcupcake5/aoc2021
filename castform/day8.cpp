#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class segment;

using str=std::string;
using vecStr=std::vector<str>;
using vecSeg=std::vector<segment>;

class segment{
    private:
        vecStr inputs;
        vecStr outputs;
        //obvious in shape [1,4,7,8]
        vecStr obvious{"","","",""};
    public:
        segment(vecStr Linputs,vecStr Loutputs)
            : inputs{Linputs},outputs{Loutputs}
        {

        }
    int find8714inOutputs(){
        int sum{0};
        for (str i:outputs){
            if (i.size()<5||i.size()==7)
                sum++;
        }
        return sum;
    }
    void printInp(){
        for (str i:inputs){
            std::cout << i<<" ";
        }
        std::cout<<"\n";
    }
    void printOut(){
        for (str i:outputs){
            std::cout << i<<" ";
        }
        std::cout<<"\n";

    }
    void findObvious(){
        for (str i:inputs){
            switch(i.size()){
                case 2: obvious[0]=i;
                    break;
                case 3: obvious[2]=i;
                    break;
                case 4: obvious[1]=i;
                    break;
                case 7: obvious[3]=i;
            }
        }

    }
    char findFive(str cur){
        int sm1{0};
        int sm2{0};
        for (char i:cur){
            if (obvious[2].find(i)!= str::npos)
                sm1++;
            if (obvious[1].find(i)!= str::npos)
                sm2++;
        }
        if (sm1==3)
            return '3';
        if (sm2==3)
            return '5';
        return '2';
    }
    char findSix(str cur){
        int sm1{0};
        int sm2{0}; 
        for (char i:cur){
            if (obvious[1].find(i)!=str::npos)
                sm1++;
            if (obvious[2].find(i)!=str::npos)
                sm2++;
        }
        if (sm1==4)
            return '9';
        if (sm2==3)
            return '0';
        return '6';
    }
    int findOutput(){
      str outs{};
      findObvious();
      for (str i:outputs){
          switch (i.size()){
                case 2: outs+='1';
                    break;
                case 3: outs+='7';
                    break;
                case 4: outs+='4';
                    break;
                case 5: outs+=findFive(i);
                    break;
                case 6: outs+=findSix(i);
                    break;
                case 7: outs+='8';
                    break;
          }
      }
    return std::stoi(outs);

    }
};

vecSeg makeList(){
    vecSeg list{};
    std::ifstream inps;
    inps.open("day8.txt");
    str a{};
    vecStr tmpInp{};
    vecStr tmpOut{};
    size_t plc{};
    while (std::getline(inps,a)){
        for (int i{0};i<10;i++){
            plc= a.find(' ');
            tmpInp.push_back(a.substr(0,plc));
            a.erase(0,plc+1);
        }
        a.erase(0,2);
        for (int i{0};i<3;i++){
            plc=a.find(' ');
            tmpOut.push_back(a.substr(0,plc));
            a.erase(0,plc+1);
        }
        tmpOut.push_back(a);
        list.push_back(segment(tmpInp,tmpOut));
        tmpInp.clear();
        tmpOut.clear();
    }
    return list;
}

int main(){
    vecSeg list{makeList()};
    int sum{0};
    int sum2{0};
    for (segment i:list){
        sum += i.find8714inOutputs();
        sum2 += i.findOutput();
    }
    std::cout << sum<<"\n"<<sum2<<"\n";
}