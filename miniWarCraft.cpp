#include <iostream>
#include <string>
#include <vector>
#include<iomanip>
using namespace std;
const int number=5;
 int redSequence[number]={2, 3, 4, 1, 0};
 int  blueSequence[number]={ 3, 0, 1, 2, 4 };
static int initElement[number];
static int warriorForce[5];
static string Warriors_name[number]={"dragon" ,"ninja","iceman","lion","wolf"};
string WeaponsName[3]={"sword", "bomb","arrow"};
static int timepoints[10]={0,5,10,20,30,35,38,40,50,55};
static int hour=0;
static int minute=0;
static int Num=1;
static int timepoint=0;
static cityNumber;

class bomb {
protected:string weaponName;
public:
    ~weapons(){};
    bomb():weaponName(nullptr){};
    bomb(string s):weaponName(s){};
    virtual int showWeapon();

};
class sword:public bomb{
    int weaponforce;
public:
    sword(string s,int n):weaponName(s),weaponforce(n){};
    int showWeapon(){
        return weaponforce;
    }
};

class arrow:public bomb{
int weaponshots;
public:
    arrow(string s):weaponName(s),weaponshots(3){};
    int showWeapon(){return weaponshots;}
};


class warrior{
protected:
    int num;
    int strengthLeft;
    int element;
    string headName;
    //int city;
    //bomb * weapon;
    friend city;

public:
    virtual int showSpecial(){};
    warrior():num(0),strengthLeft(0),element(0),{};
    warrior(int n,int sleft,int consu):num(n),strengthLeft(sleft),element(consu){};
    virtual void feature(){};
    virtual string showname(){return "wolf";};
    inline int shownum(){return num;}
   bomb* haveWeapon(string s);
    inline int showCity(){return city;}
    void forwardCity(){++city;}
    void backwardCity(){--city;}

};

bomb * warrior::haveWeapon(string s){
if(s=="bomb") return new bomb("bomb");
    else if(s=="arrow") return new arrow("arrow");
    else return new sword("sword",0);

};




class dragon: public warrior {
    string wname= "dragon" ;
    float morale;
    weapons weapon;
public:
    dragon(int n,int sleft,int consu):warrior(n,sleft,consu){
        morale=(float)(sleft-consu)/consu;
        weapon = weapons(WeaponsName[num%3]);}
inline string showname(){return wname;};
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
    string showname(){return wname;}
    void feature();

};
void ninjia::feature() {cout<<"It has a "<<weapon[0]<<" and a "<<weapon[1]<<endl;}


class iceman:public warrior{
    string wname="iceman";
    string weapon;
public:
    iceman(int n,int sleft,int consu):warrior(n,sleft,consu){weapon=Weapons[num%3];}
        string showname(){return wname;}
    void feature();
};
void iceman::feature() {cout<<"it has a "<<weapon<<endl;}

class lion:public warrior{
    string wname="lion";
    int loyalty;

public: int showSpecial(){ return loyalty;}
    lion(int n,int sleft,int consu):warrior(n,sleft,consu){loyalty=strengthLeft-consu;}
    string showname(){return wname;}
    void feature();
    inline int showloyalty(){return loyalty;}
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
    int enemy;
    int cityposition;

    int exist[number]={0};
    bool tag =true;
    int position=0;
    int warriorNUm=0;


    vector<shared_ptr<warrior *> > headquarterWarriorpointers;
    friend city;
public:
    headquarter(string s,int ,int *pSequence,int m,int j) :name(s),strength(),sequence(pSequence),enemy(m),cityposition(j) {};
    void born_success();
    int born_next();
    inline bool deadOrAlive(){return tag ;}
    void lionRunAway();
    void march();
    bool checkGameOver();

};
void headquarter::born_success(){
   shared_ptr< warrior *> p;
   string tem=Warriors_name[sequence[position]];
    if (tem=="dragon"){p= new dragon(Num,strength,initElement[(sequence[position])]); }
        else if(tem=="ninjia") {p=new ninjia(Num,strength,initElement[(sequence[position])]); }
   else if (tem=="iceman") {p= new iceman (Num,strength,initElement[(sequence[position])]); }
        else if(tem=="wolf"){p=new warrior(Num,strength,initElement[(sequence[position])]);}
        else {p=new lion (Num,strength,initElement[(sequence[position])]); }
        headquarterWarriorpointers.push_back(p);
        //p->feature();

    exist[sequence[position]]++;
    strength-=initElement[(sequence[position])];
    cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<name<<" "<<p->showname();
    cout<<" "<<p->shownum()<<warriorNum<< " born"<<endl;
    p->feature();
    position++;

}
/*void headquarter::born_fail() {
    cout <<setfill('0')<<setw(3)<<Current <<" "<<name<< " headquarter stops making warriors "<<endl;
    lable=false;*/

int headquarter::born_next(){
    (position)>4?position-=5:position;
    if (strength>=initElement[(sequence[position])])
    {born_success();++warriorNUm;}
    return 0;
}

void headquarter::lionRunAway() {
    for(auto p:headquarterWarriorpointers)
        if(p->showname()=="lion"&&(p->showCity()!=enemy)&&p->showSpecial()<=0)
        {delete p;
            --warriorNUm;}

}
void headquarter::march() {
    if(name=="red") ++cityposition==cityNumber+2?cityposition=enemy:cityposition;
    else (--cityposition)==-1?cityposition=enemy:cityposition;
    for (int checkposition=0;checkposition<=cityNumber+1;++checkposition)



}
bool headquarter::checkGameOver(){
    int tem=0;
    for(auto p:headquarterWarriorpointers) if(p->showCity()==enemy) ++tem;
    if(tem>1) return true;
}


class city{
    //vector<shared_ptr<warrior *> >cityWarriorpointers;
    int cityelement;
public:
    city(int n):cityelement(n){};
    city():cityelement(0){};
    void cityIncreaseElement(){
        cityelement+=10;}

};

int main() {
    int initStrength,arrowforce,loyaltyDeacrease,endpoint;
    int pos=0;
    cin>>initStrength>>cityNumber>>arrowforce>>loyaltyDeacrease>>endpoint;
    headquarter red("red",initStrength,redSequence,cityNumber+1,0);
    headquarter blue("blue",initStrength,&blueSequence[0],0,cityNumber+1);
    city blueCity[cityNumber];
    city redCity[cityNumber];
    while (cin>>initElement[pos++]) continue;
    pos=0;
    while(cin>>warriorForce[pos++]) continue;
    	//cout<<initElement[pos-1]<<endl;
    while(red.deadOrAlive()&& blue.deadOrAlive() &&(hour*60+minute)<=endpoint){
        minute=timepoints[timepoint];
        switch(minute){
            case 0: {red.born_next();blue.born_next();break;}
            case 5: {red.lionRunAway();blue.lionRunAway();break;}
            case 10: {red.march();blue.march;
                if(red.checkGameOver()|| blue.checkGameOver()) return 0;
            }
            case 20:for(int i=0;i<cityNumber+1;i++){
                    blueCity[i].cityIncreaseElement();redCity[i].cityIncreaseElement();}
            case 30:for(red.)
     timepoint++;
    }


return 0;
}