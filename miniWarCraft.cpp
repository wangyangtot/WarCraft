#include <iostream>
#include <string>
#include <vector>
#include <memory>
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
static int cityNumber;
static int arrowforce;
static city middleCity[];


class bomb {
protected:string weaponName;
public:
    ~weapons(){};
    bomb():weaponName(nullptr){};
    bomb(string s):weaponName(s){};
    virtual int showWeaponforce();
    virtual void weaponBlunt(){};
    friend warrior;
    string showweaponName(){return weaponName;}
    
};
class sword:public bomb{
    int weaponforce;
public:
    ~sword(){delete sword;};
    sword(string s,int n):weaponName(s),weaponforce(n){};
    inline int showWeaponforce(){ return weaponforce; }
    inline void weaponBlunt(){
        weaponforce*=0.8;
        if(weaponforce==0) ~sword(); }
};

class arrow:public bomb{
    int weaponshots;
    int arrowforce;
public:
    arrow(string s,int n):bomb(s),weaponshots(3),arrowforce(n){};
    int showWeaponforce(){return weaponshots;}
    inline void weaponBlunt(){--arrowforce;}
};


class warrior {
protected:
    int num;
    int strengthLeft;
    int element;
    string headName;
    int city;
    bomb *weapons[2];
    //friend city;
    
public:
    //friend headquarter;
    virtual int showSpecial() {};
    
    warrior() : num(0), strengthLeft(0), element(0), {};
    
    warrior(int n, int sleft, int consu, string shname) : num(n), strengthLeft(sleft), element(consu),
    headName(shname) {};
    
    virtual void feature() {};
    
    virtual string showname() { return "wolf"; };
    
    inline int shownum() { return num; }
    
    bomb *gainWeapon(string s);
    
    inline int showCity() { return city; }
    
    void forwardCity() { ++city; }
    
    void backwardCity() { --city; }
    
    inline bomb *getweapon(int n) { return weapons[n]; }
    
    void changeElement(int n) { element += n; }
    
    //virtual int getarrowNumber(){};
    int showElement() { return element; }
    
    inline string showcolor() { return headName; }
    
    inline int haveArrow() {
        if (weapons[0]->showweaponName == "arrow" || weapons[1]->showweaponName == "arrow")
            return true;
    }
    
    inline int SwordForce() {
        if ((weapons[0]->showweaponName() == "sword") || (weapons[1]->showweaponName() == "sword"))
            return weapons[0]->showWeaponforce() + weapons[1]->showWeaponforce();
    }
    
    inline bool haveBomb() {
        if ((weapons[0]->showweaponName() == "bomb") || weapons[1]->showweaponName() == "bomb)")
            return true;
    }
    
    static friend void firstBeatsecond(shared_ptr<warrior *> partyone, shared_ptr<warrior *> partytwo);
    
    static friend string PK(shared_ptr<warrior *> partyone, shared_ptr<warrior *> partytwo);
    
    static friend void beat(shared_ptr<warrior *> partyone, shared_ptr<warrior *> partytwo);
    
    static friend void bang();
    
    static friend warriorDead(shared_ptr<warrior *> warriorPtr);
};


bomb * warrior::gainWeapon(string s){
    if(s=="bomb") return new bomb("bomb");
    else if(s=="arrow") return new arrow("arrow",element*0.2);
    else return new sword("sword",0);
    
}




class dragon: public warrior {
    string wname= "dragon" ;
    float morale;
    //bomb* weapon;
public:
    dragon(int n,int sleft,int consu,string s):warrior(n,sleft,consu,s){
        morale=(float)(sleft-consu)/consu;
        weapons[0] = gainWeapon(WeaponsName[num%3]);}
    inline string showname(){return wname;};
    void feature();
    //inline int getarrowNumber(){ if(weapons[0]->showweaponName=="arrow")return true;}
};
void dragon::feature() {cout<<"It has a "<<weapons[0]<<" and it’s morale is "<<setprecision(3)<<morale<<endl;}


class ninjia:public warrior{
    string wname="ninjia";
    //bomb* weapon[2];
public:ninjia(int n,int sleft,int consu,string s):warrior(n,sleft,consu,s){
    weapons[0]=gainWeapon(WeaponsName[num%3]);
    weapons[1]=gainWeapon(WeaponsName[(num+1)%3]);
}
    string showname(){return wname;}
    void feature();
    
    
};
void ninjia::feature() {cout<<"It has a "<<weapons[0]<<" and a "<<weapons[1]<<endl;}


class iceman:public warrior{
    string wname="iceman";
    //bomb* weapon;
public:
    iceman(int n,int sleft,int consu,string s):warrior(n,sleft,consu,s){weapons[0]=gainWeapon(WeaponsName[num%3]);}
    string showname(){return wname;}
    void feature();
};
void iceman::feature() {cout<<"it has a "<<weapons[0]<<endl;}

class lion:public warrior{
    string wname="lion";
    int loyalty;
    
public: int showSpecial(){ return loyalty;}
    lion(int n,int sleft,int consu,string s):warrior(n,sleft,consu,s){loyalty=strengthLeft-consu;}
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
    int warriorNum=0;
    
    
    vector<shared_ptr<warrior * > > headquarterWarriorpointers;
    //friend city::march();
public:
    headquarter(string s,int ,int *pSequence,int m,int j) :name(s),strength(),sequence(pSequence),enemy(m),cityposition(j) {};
    void born_success();
    int born_next();
    inline bool deadOrAlive(){return tag ;}
    void lionRunAway();
    void waarriorMarch();
    bool checkGameOver();
    int getRedcity();
    int getBlueCity();
    int showElement(){return strength;}
    void warriorGainelement(int position,int value){
        (**(headquarterWarriorpointers.begin()+=position))->changeElement(value);}
    inline void headquarterGainElement(int value){strength+=value;}
    int getRedcity(int position);
    int getBluecity(int position);
    //void arrowWarriorshot();
    vector<int> arrowWarriorcity();
    void attackByArrow(int city);
    //void march();
    void headquarter::killedByArrow();
};


static void march() {
    for(int i=0;i<=cityNumber+2;i++) {
        middleCity[i].resetCityWarriorpointers();
        for (auto p:middleCity[i].cityWarriorpointers) {
            if ((*p)->showcolor() == "red") (*p)->forwardCity();
            else if ((*p)->showcolor() == "blue") (*p)->backwardCity();
        }
    }
    for (int i = 0; i <= cityNumber + 2; i++)
        for (auto c:middleCity[i].cityWarriorpointers) {
            int tem = (*c)->showCity();
            middleCity[tem].cityWarriorpointers.push_back(c);
        }
}




static void killedByArrow() {
    //vector<shared_ptr<warrior *> > hasArrow;
    for (int i = 0; i < cityNumber + 2; i++) {
        for (auto p:middleCity[i].cityWarriorpointers) {
            if ((*p)->haveArrow()) {
                int arrowcity = (*p)->showCity();
                if ((*p)->showcolor() == "red") {
                    for (auto c: middleCity[arrowcity + 1].cityWarriorpointers) {
                        if ((*c)->showcolor() == "blue" && ((*c)->showElement() > arrowforce))
                            (*c)->changeElement(0 - arrowforce);
                        else if ((*c)->showcolor() == "blue" && (*c)->showElement() <= arrowforce) (*c) = nullptr;
                    }
                } else if ((*p)->showcolor() == "blue") {
                    for (auto c: middleCity[arrowcity - 1].cityWarriorpointers) {
                        if ((*c)->showcolor() == "red" && ((*c)->showElement() > arrowforce))
                            (*c)->changeElement(0 - arrowforce);
                        else if ((*c)->showcolor() == "red" && (*c)->showElement() <= arrowforce) (*c) = nullptr;
                    }
                    
                }
            }
        }
        
    }
}



int headquarter::getRedcity(int position) {
    //shared_ptr<warrior * > p;
    auto p = *(headquarterWarriorpointers.begin() + position);
    
    return (*p)->showCity();
}

int headquarter::getBluecity(int position){
    return (**(headquarterWarriorpointers.end()-=(1+position)))->showCity();
}


/*void headquarter::born_fail() {
 cout <<setfill('0')<<setw(3)<<Current <<" "<<name<< " headquarter stops making warriors "<<endl;
 lable=false;*/
void headquarter::born_success(){
    shared_ptr< warrior *> p;
    string tem=Warriors_name[sequence[position]];
    if (tem=="dragon"){p= shared_ptr<warrior*>(new dragon(Num,strength,initElement[(sequence[position])],name)); }
    else if(tem=="ninjia") {p=shared_ptr<warrior*>(new ninjia(Num,strength,initElement[(sequence[position])],name)); }
    else if (tem=="iceman") {p= shared_ptr<warrior*>(new iceman (Num,strength,initElement[(sequence[position])],name)); }
    else if(tem=="wolf"){p=shared_ptr<warrior*>(new warrior(Num,strength,initElement[(sequence[position])],name));}
    else {p=shared_ptr<warrior*>(new lion (Num,strength,initElement[(sequence[position])],name)); }
    headquarterWarriorpointers.push_back(p);
    if(name=="red") middleCity[0].bornInheadquarter(p);
    else if(name=="blue") middleCity[cityNumber].bornInheadquarter(p);
    //p->feature();
    
    exist[sequence[position]]++;
    strength-=initElement[(sequence[position])];
    cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<name<<" "<<(*p)->showname();
    cout<<" "<<(*p)->shownum()<<warriorNum<< " born"<<endl;
    (*p)->feature();
    position++;
    
}
int headquarter::born_next(){
    (position)>4?position-=5:position;
    if (strength>=initElement[(sequence[position])])
    {born_success();++warriorNum;}
    return 0;
    
}

void headquarter::lionRunAway() {
    for (auto p:headquarterWarriorpointers) {
        if ((*p)->showname() == "lion" && ((*p)->showCity() != enemy) && (*p)->showSpecial() <= 0) {
            p = nullptr;
            --warriorNum;
        }
        
    }
}




}
bool headquarter::checkGameOver(){
    int tem=0;
    for(auto p:headquarterWarriorpointers) if((*p)->showCity()==enemy) ++tem;
    if(tem>1) return true;
}


class city{
    vector<shared_ptr<warrior *> >cityWarriorpointers;
    int cityelement;
    string flag;
    friend class headquarter;
    string winHearquarter;
public:
    city(int n,int m):cityelement(n),flag(nullptr){};
    city():cityelement(0){};
    ~city(){ cityWarriorpointers.clear();}
    void cityIncreaseElement(){
        cityelement+=5;}
    int comsumeAllElement(){ int tem=cityelement;cityelement=0;return tem;}
    void bornInheadquarter(shared_ptr<warrior *> p){cityWarriorpointers.push_back(p);}
    //int showCityElement(){return cityelement;}
    //int changeCityElement;
    //friend void headquarter::born_success();
    void resetCityWarriorpointers();
    static friend void killedByArrow();
    static friend void march();
    static friend void battle(headquarter *red,headquarter *blue);
    static friend void bang();
    inline void win(string s){
        if(winHearquarter== s)  flag=s;
        else winHearquarter=s;
    }
    
    //void resetID(int n){ID=n;}
    //void IDForward(){}
};
void city::resetCityWarriorpointers() {
    while(!cityWarriorpointers.empty()) cityWarriorpointers.pop_back();
}


/*void headquarter::march() {
 //if(name=="red") {for(auto p:headquarterWarriorpointers) (*p)->forwardCity();
 {for(auto p:cityWarriorpointers)if ((p)->showcolor()=="red")
 {for(auto p:headquarterWarriorpointers) (*p)->backwardCity();}
 */
static void warriorDead(shared_ptr<warrior *> warriorPtr){
    (*warriorPtr)=nullptr;}
static void getPrize(shared_ptr<warrior *>,int n){
    
}

static void firstBeatsecond(shared_ptr<warrior *> partyone,shared_ptr<warrior *> partytwo){
    int tem=(*partyone)->showElement()+(*partyone)->SwordForce();
    if ( (*partyone)->getweapon(0)->showweaponName()=="sword") (*partyone)->getweapon(0)->weaponBlunt();
    if((*partyone)->getweapon(1)->showweaponName()=="sword") (*partyone)->getweapon(1)->weaponBlunt();
    (*partytwo)->changeElement(0-tem);
}


static string PK(shared_ptr<warrior *> partyone,shared_ptr<warrior *> partytwo) {
    firstBeatsecond(partyone,partytwo);
    if((*partytwo)->showElement()<=0) {warriorDead(partytwo);return (*partyone)->showcolor();}
    firstBeatsecond(partytwo,partyone);
    if((*partytwo)->showElement()<=0) { warriorDead(partyone); return (*partytwo)->showcolor();}
    return nullptr;
}

static void battle(headquarter * red,headquarter * blue) {
    for (int i = 0; i < cityNumber + 2;i++) {
        if (middleCity[i].cityWarriorpointers.size() == 2) {
            shared_ptr<warrior *> redParty,blueParty;
            shared_ptr<warrior *> partyone = *(middleCity[i].cityWarriorpointers.begin());
            auto partytwo = *(middleCity[i].cityWarriorpointers.end() - 1);
            string firstcolor = (*partyone)->showcolor();
            string secondcolor = (*partytwo)->showcolor();
            if (firstcolor == "red") {
                redParty= partyone;
                blueParty = partytwo;
            } else {
                blueParty = partyone;
                redParty = partytwo;
            }
            
            if (middleCity[i].flag =="red" ||(middleCity[i].flag== nullptr&&i % 2 != 0)) {
                if(PK(redParty,blueParty)=="red")
                    (*redParty)->changeElement(red->showElement()>8?8:red->showElement());
                red->headquarterGainElement(middleCity[i].comsumeAllElement());
                middleCity[i].win("red");}
            else if(middleCity[i].flag=="blue" ||(middleCity[i].flag== nullptr && i%2==0))
            {  if(PK(redParty,blueParty)=="blue")
                middleCity[i].win("blue");
                
                (*blueParty)->changeElement(blue->showElement()>8?8:blue->showElement());
                blue->headquarterGainElement(middleCity[i].comsumeAllElement());}
        }
    }
}
static void bang(){
    for(int i=0;i<cityNumber+2;++i){
        if(middleCity[i].cityWarriorpointers.size()==2){
            shared_ptr<warrior *> partyone = *(middleCity[i].cityWarriorpointers.begin());
            shared_ptr<warrior *> partytwo = *(middleCity[i].cityWarriorpointers.end() - 1);
            if(((*partyone)->haveBomb()&&(*partyone)->showElement()<(*partytwo)->showElement())||
               ((*partytwo)->haveBomb()&&(*partytwo)->showElement()<(*partyone)->showElement()))
                warriorDead(partyone);
            warriorDead(partytwo);
        }
    }
}


int main() {
    int initStrength, loyaltyDeacrease, endpoint;
    int pos = 0;
    cin >> initStrength >> cityNumber >> arrowforce >> loyaltyDeacrease >> endpoint;
    headquarter red("red", initStrength, redSequence, cityNumber + 1, 0);
    headquarter blue("blue", initStrength, &blueSequence[0], 0, cityNumber + 1);
    city middleCity[cityNumber + 2];
    //for (int i=0;i!=cityNumber+3;i++)
    // middleCity[i].resetID(i);
    //city BlueCity[cityNumber+2];
    while (cin >> initElement[pos++]) continue;
    pos = 0;
    while (cin >> warriorForce[pos++]) continue;
    //cout<<initElement[pos-1]<<endl;
    while (red.deadOrAlive() && blue.deadOrAlive() && (hour * 60 + minute) <= endpoint) {
        minute = timepoints[timepoint];
        switch (minute) {
            case 0: {
                red.born_next();
                blue.born_next();
                break;
            }
            case 5: {
                red.lionRunAway();
                blue.lionRunAway();
                break;
            }
            case 10: {
                march();
                if (red.checkGameOver() || blue.checkGameOver()) return 0;
                break;
            }
            case 20: {
                for (int i = 1; i < cityNumber + 2; i++) {
                    middleCity[i].cityIncreaseElement();
                    
                }
                break;
            }
            case 30: {
                int redtem = 0;
                int bluetem = 0;
                while (redtem != cityNumber - 1 && bluetem != cityNumber - 1) {
                    if (red.getRedcity(redtem) > blue.getBluecity(bluetem)) {
                        red.warriorGainelement(redtem, middleCity[red.getRedcity(redtem)].comsumeAllElement());
                        ++redtem;
                    } else if (red.getRedcity(redtem) < blue.getBluecity(bluetem)) {
                        blue.warriorGainelement(bluetem, middleCity[blue.getBluecity(bluetem)].comsumeAllElement());
                        ++bluetem;
                    } else {
                        ++redtem;
                        ++bluetem;
                    }
                }
                while (redtem != cityNumber - 1) {
                    red.warriorGainelement(redtem, middleCity[red.getRedcity(redtem)].comsumeAllElement());
                    ++redtem;
                }
                while (bluetem != cityNumber - 1) {
                    blue.warriorGainelement(bluetem, middleCity[blue.getBluecity(bluetem)].comsumeAllElement());
                    ++bluetem;
                }
                break;
            }
            case 35: {
                killedByArrow();
                break;
            }
            case 38:
                bang();
                break;
            case 40:
                battle(&red,&blue);
                break;
                
                
                ++timepoint;
        }
        
        
        return 0;
    }
}
