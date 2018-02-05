#include <iostream>
#include <string>
#include <vector>
#include<iomanip>
using namespace std;
const int number=5;
 int redSequence[number]={2, 3, 4, 1, 0};
 int  blueSequence[number]={ 3, 0, 1, 2, 4 };
static int Warrior_consume[number];
static string Warriors_name[number]={"dragon" ,"ninja","iceman","lion","wolf"};
string Weapons[3]={"sword", "bomb","arrow"};
static int Current=0;
static int Num=1;


class warrior{
protected:
    int num;
    int strengthLeft;
    int consume;
    float morale;
    int loyalty;


public:
    warrior():num(0),strengthLeft(0),consume(0),morale(0),loyalty(0){};
    warrior(int n,int sleft,int consu):num(n),strengthLeft(sleft),consume(consu),morale(0),loyalty(0){};
    virtual void feature(){};
    virtual void showname(){cout<<"wolf";};
    inline int shownum(){return num;}
};
class dragon: public warrior {
    string wname= "dragon" ;
    string weapon;
public:
    dragon(int n,int sleft,int consu):warrior(n,sleft,consu){
        morale=(float)(sleft-consu)/consu;
        weapon=weapon[num%3];}
inline void showname(){cout<<wname;};
        void feature();
};
void dragon::feature() {cout<<"It has a "<<weapon<<" and it’s morale is "<<setprecision(3)<<morale<<endl;}


class ninjia:public warrior{
    string wname="ninjia";
    string weapon[2];
public:ninjia(int n,int sleft,int consu):warrior(n,sleft,consu){
        weapon[0]=Weapons[num%3];
        weapon[1]=Weapons[(num+1)%3];
    }
    void showname(){cout<<wname;}
    void feature();

};
void ninjia::feature() {cout<<"It has a "<<weapon[0]<<" and a "<<weapon[1]<<endl;}


class iceman:public warrior{
    string wname="iceman";
    string weapon;
public:
    iceman(int n,int sleft,int consu):warrior(n,sleft,consu){weapon=Weapons[num%3];}
        void showname(){cout<<wname;}
    void feature();
};
void iceman::feature() {cout<<"it has a "<<weapon<<endl;}

class lion:public warrior{
    string wname="lion";
public:
    lion(int n,int sleft,int consu):warrior(n,sleft,consu){loyalty=strengthLeft-consu;}
    void showname(){cout<<wname;}
    void feature();
};
void lion::feature() {cout<<"It’s loyalty is "<<loyalty<<endl;}


/*class wolf:public warrior{
    string wname="wolf";
public:wolf(int n, int sleft,int consu):warrior(n,sleft,consu){};
    void showname(){cout<<wname;}
    void feature();
};
void wolf::feature() {};*/


class headquarter {
string name;
int strength;
int *sequence;
    int exist[number]={0};
    bool lable=true;
    int position=0;
    vector<warrior *> warriors;
public:
    headquarter(string s,int total,int *pSequence) :name(s),strength(total),sequence(pSequence) {};

    //headquarter() : strength(0) {};
    void born_success();
    void born_fail();
    int born_next();
    inline bool get_lable(){return lable;}


};
void headquarter::born_success(){
    warrior *p;
   string tem=Warriors_name[sequence[position]];
    if (tem=="dragon"){p=new dragon(Num,strength,Warrior_consume[(sequence[position])]); }
        else if(tem=="ninjia") {p=new ninjia(Num,strength,Warrior_consume[(sequence[position])]); }
   else if (tem=="iceman") {p= new iceman (Num,strength,Warrior_consume[(sequence[position])]); }
        else if(tem=="wolf"){p=new warrior(Num,strength,Warrior_consume[(sequence[position])]);}
        else {p=new lion (Num,strength,Warrior_consume[(sequence[position])]); }
        warriors.push_back(p);
        //p->feature();

    exist[sequence[position]]++;
    strength-=Warrior_consume[(sequence[position])];
    cout<< setfill('0') << setw(3)<<Current<<" "<<name<<" ";
    p->showname();
    cout<<" "<<p->shownum()<<
        " born with "<<Warrior_consume[sequence[position]]<<", "<<exist[sequence[position]]<<
        " in "<<name<<" headquarter "<<endl;
    p->feature();

    position++;

}
void headquarter::born_fail() {
    cout <<setfill('0')<<setw(3)<<Current <<" "<<name<< " headquarter stops making warriors "<<endl;
    lable=false;

}
int headquarter::born_next(){
    (position)>4?position-=5:position;
    int flag=position;

    while(strength<Warrior_consume[(sequence[position])]) {
        (++position)>4?position-=5:position;
        if((position)==flag) {
            born_fail();
            return 0;
        }

    }
    born_success();
    return 0;
}

int main() {
    int total_strength;
    int pos=0;
    cout<<"input"<<endl;
    cin>>total_strength;
    headquarter red("red",total_strength,redSequence);
    headquarter blue("blue",total_strength,&blueSequence[0]);
    while (cin>>Warrior_consume[pos++]){
    	cout<<Warrior_consume[pos-1]<<endl;
    };
    while(red.get_lable() || blue.get_lable()){
        if(red.get_lable()) red.born_next();
        if(blue.get_lable()) blue.born_next();
     Current++;
             Num++;
    }
return 0;
}