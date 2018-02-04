#include <iostream>
#include <string>
#include <map>
#include<iomanip>
using namespace std;
const int number=5;
 int redSequence[number]={2, 3, 4, 1, 0};
 int  blueSequence[number]={ 3, 0, 1, 2, 4 };
static int warrior_consume[number];
static string warriors[number]={"dragon" ,"ninja","iceman","lion","wolf"};
static int current=0;
static int num=current+1;


class headquarter {
string name;
int strength;
int *sequence;
    int exist[number]={0};
    bool lable=true;
    int position=0;
public:
    headquarter(string s,int total,int *pSequence) :name(s),strength(total),sequence(pSequence) {};

    //headquarter() : strength(0) {};
    int born_next();
    inline bool get_lable(){return lable;}

};
int headquarter::born_next(){
    (position)>4?position-=5:position;
    int flag=position;

    while(strength<warrior_consume[(sequence[position])]) {
        (++position)>4?position-=5:position;
        if((position)==flag) {
            cout <<setfill('0')<<setw(3)<<current <<" "<<name<< " headquarter stops making warriors "<<endl;
            lable=false;
            return 0;
        }

    }
    strength-=warrior_consume[(sequence[position])];

    cout<< setfill('0') << setw(3)<<current<<" "<<name<<" "<<warriors[sequence[position]]<<" "<<num<<
        " born with "<<warrior_consume[sequence[position]]<<", "<<exist[sequence[position]]<<
        " in "<<name<<" headquarter "<<endl;
    exist[sequence[position]]++;
    position++;
    return 0;
}

int main() {
    int total_strength;
    int pos=0;

    //static map<string,int> warrior_consume;
    cout<<"input"<<endl;
    cin>>total_strength;
    headquarter red("red",total_strength,redSequence);
    headquarter blue("blue",total_strength,&blueSequence[0]);
    //cout<<total_strength;
    while (cin>>warrior_consume[pos++]){
        cout<<warrior_consume[pos-1]<<endl;
    };
    while(red.get_lable() || blue.get_lable()){
        if(red.get_lable()) red.born_next();
        if(blue.get_lable()) blue.born_next();
     current++;
             num++;
    }
return 0;
}