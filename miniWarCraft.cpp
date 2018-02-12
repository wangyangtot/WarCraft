#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include<iomanip>
//#include <boost/smart_ptr/make_shared_object.hpp>
using namespace std;
const int number=5;
//typedef shared_ptr<warrior>  wptr;
int redSequence[number]={2, 3, 4, 1, 0};
int  blueSequence[number]={ 3, 0, 1, 2, 4 };
static int initElement[5];
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



class bomb {
protected:string weaponName;
public:
    //~bomb();
    //bomb():weaponName(nullptr){};
    bomb(string s):weaponName(s){};
    virtual int showWeaponforce(){return 0;};
    virtual void weaponBlunt(){};
    friend class warrior;
    string showweaponName(){return weaponName;}
    
};

class sword:public  bomb{
    int swordforce;
public:
    // ~sword(){~bomb();}
    //~sword(){delete sword;};
    sword(const string s,int n):bomb(s),swordforce(n){};
    inline int showWeaponforce(){ return swordforce; }
    inline void weaponBlunt(){
        swordforce*=0.8;}
    //if(weaponforce==0) ~sword(); }
};

class arrow:public bomb{
    int arrowshots;
    int arrowforce;
public:
    //~arrow();
    arrow(string s,int n):bomb(s),arrowshots(3),arrowforce(n){};
    int showWeaponforce(){return arrowshots;}
    inline void weaponBlunt(){--arrowshots;}
};



class warrior {
protected:
    int num;
    int strengthLeft;
    int element;
    
    string headName;
    int warriorForce;
    int city;
    shared_ptr<bomb> weapon[2];
    //friend city;
    
public:
    //friend headquarter;
    virtual int showSpecial(){return 10;};
    
    //warrior() : num(0), strengthLeft(0), element(0), {};
    
    warrior(int n, int sleft, int consu, string shname,int m) : num(n), strengthLeft(sleft), element(consu),
    headName(shname),warriorForce(m){if(headName=="red")city=0; else city=cityNumber+1;};
    // virtual bool feature(){};
    virtual void showfeature() {cout<<"null"<<endl;};
    
    virtual string showname(){return "";}
    int showWArriorForce(){return warriorForce;}
    
    inline int shownum() { return num; }
    
    shared_ptr<bomb> gainWeapon(string s);
    
    inline int showCity() { return city; }
    
    void forwardCity() { city++; }
    
    void backwardCity() { --city; }
    shared_ptr<bomb> getweapon(int n) { return weapon[n]; }
    
    void changeElement(int n) { element += n; }
    
    //virtual int getarrowNumber(){};
    int showElement() { return element; }
    virtual void showweapon(){cout<<"has no weapon"<<endl;};
    
    inline string showcolor() { return headName; }
    
    virtual bool haveArrow(){return false;};
    
    virtual int SwordForce(){return 0;}
    
    virtual bool haveBomb(){return false;}
    
    
    friend void firstBeatsecond(shared_ptr<warrior > partyone, shared_ptr<warrior > partytwo);
    
    friend string PK(shared_ptr<warrior > partyone, shared_ptr<warrior > partytwo);
    
    friend void beat(shared_ptr<warrior > partyone, shared_ptr<warrior > partytwo);
    
    friend void bang();
    friend void march();
    
    friend void warriorDead(shared_ptr<warrior > warriorPtr);
};

shared_ptr<bomb> warrior::gainWeapon(string s){
    if(s=="bomb")  return shared_ptr<bomb>(new bomb("bomb"));
    else if(s=="arrow") return shared_ptr<bomb>(new arrow("arrow",element*0.2));
    else  return shared_ptr<bomb>(new sword("sword",0)); }



class dragon: public warrior {
    string wname= "dragon" ;
    float morale;
    //shared_ptr<bomb> weapon;
    //bomb* weapon;
public:
    dragon(int n,int sleft,int consu,string s,int m):warrior(n,sleft,consu,s,m){
        morale=(float)(sleft-consu)/consu;
        weapon[0]=gainWeapon(WeaponsName[num%3]);}
    inline string showname(){return wname;};
    void showweapon()override{
        cout<<"has"<<weapon[0]->showweaponName()<<"("<<weapon[0]->showWeaponforce()<<")"<<endl;
    }
    void showfeature();
    inline bool haveArrow() override {
        if(weapon[0]->showweaponName()=="arrow") return true;
        return  false;
    }
    int SwordForce()override ;
    bool haveBomb() override;
    int showSpecial(){ return 10;}
};

int dragon::SwordForce() {
    if (weapon[0]->showweaponName() == "sword")
        return weapon[0]->showWeaponforce();
    return 0;}
void dragon::showfeature() {cout<<"It has a "<<weapon[0]<<" and it’s morale is "<<setprecision(3)<<morale<<endl;}
bool dragon::haveBomb(){
    if (weapon[0]->showweaponName() == "bomb") return true;
    return true;
}





class ninjia:public warrior{
    string wname="ninjia";
    //shared_ptr<bomb> weapon[2];
public:
    ninjia(int n,int sleft,int consu,string s,int m):warrior(n,sleft,consu,s,m){
        weapon[0]= gainWeapon(WeaponsName[num%3]);
        weapon[1]=gainWeapon(WeaponsName[(num+1)%3]);
    };
    void showweapon()override{
        shared_ptr<bomb> first,second;
        if(weapon[0]->showweaponName()=="arrow") {first=weapon[0];second=weapon[1];}
        else if(weapon[1]->showweaponName()=="arrow"){first=weapon[1];second=weapon[0];}
        else if(weapon[0]->showweaponName()=="bomb"){first=weapon[0];second=weapon[1];}
        else {first=weapon[1];second=weapon[0];}
        
        cout<<"has"<<first->showweaponName()<<"("<<first->showWeaponforce()<<")";
        cout<<second->showweaponName()<<"("<<second->showWeaponforce()<<")"<<endl;
    }
    
    string showname(){return wname;}
    void showfeature();
    inline bool haveArrow() override {
        if(weapon[0]->showweaponName()=="arrow" || weapon[1]->showweaponName()=="arrow") return true;
        return  false; }
    
    int SwordForce() override;
    bool haveBomb() override ;
    int showSpecial(){ return 10;}
};
int ninjia::SwordForce() {
    if ((weapon[0]->showweaponName() == "sword") || (weapon[1]->showweaponName() == "sword"))
        return weapon[0]->showWeaponforce() + weapon[1]->showWeaponforce();
    return 0;
}
bool ninjia::haveBomb() {
    if ((weapon[0]->showweaponName() == "bomb") || weapon[1]->showweaponName() == "bomb)")
        return true;
    return false;
}

void ninjia::showfeature() {cout<<"It has a "<<weapon[0]<<" and a "<<weapon[1]<<endl;}





class iceman:public warrior{
    string wname="iceman";
    //shared_ptr<bomb> weapon;
public:
    iceman(int n,int sleft,int consu,string s,int m):warrior(n,sleft,consu,s,m){weapon[0]=gainWeapon(WeaponsName[num%3]);}
    inline string showname(){return wname;}
    void showfeature();
    void showweapon()override{
        cout<<"has"<<weapon[0]->showweaponName()<<"("<<weapon[0]->showWeaponforce()<<")"<<endl;
    }
    inline bool haveArrow() override {
        if(weapon[0]->showweaponName()=="arrow") return true;
        return  false; }
    int SwordForce() override;
    bool haveBomb() override ;
    int showSpecial(){ return 10;}
};
bool iceman::haveBomb() {
    if ((weapon[0]->showweaponName()=="bomb"))return true;
    return false;
}
int iceman::SwordForce() {
    if (weapon[0]->showweaponName() == "sword")
        return weapon[0]->showWeaponforce();
    return 0;
}
void iceman::showfeature() {cout<<"it has a "<<weapon<<endl;}




class lion:public warrior{
    string wname="lion";
    int loyalty;
    
public: int showSpecial(){ return loyalty;}
    lion(int n,int sleft,int consu,string s,int m):warrior(n,sleft,consu,s,m){cout<<"lion born"<<endl;loyalty=strengthLeft-consu;}
    string showname(){return wname;}
    void showfeature();
    inline bool haveArrow(){return false;};
    inline int showloyalty(){return loyalty;}
    inline int SwordForce(){return 0;}
    bool haveBomb(){return false;};
};
void lion::showfeature() {cout<<"It’s loyalty is "<<loyalty<<endl;}


class wolf:public warrior{
    string wname="wolf";
public:wolf(int n, int sleft,int consu,string s,int m):warrior(n,sleft,consu,s,m){};
    string showname(){return wname;}
    void feature();
    inline bool haveArrow(){return false;};
    inline int SwordForce(){return 0;}
    bool haveBomb(){return false;}
    int showSpecial(){ return 10;}
};
void wolf::feature() {};


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
    
    
protected:  vector<shared_ptr<warrior> > headquarterWarriorpointers;
public:
    headquarter(string s,int n ,int *pSequence,int m,int j) :name(s),strength(n),sequence(pSequence),enemy(m),cityposition(j) {cout<<"headquaater creat"<<endl;};
    void born_success();
    int born_next();
    inline bool deadOrAlive(){return tag ;}
    void lionRunAway();
    bool checkGameOver();
    int getRedcity();
    int getBlueCity();
    string showHeadquartername(){return name;}
    int showElement(){return strength;}
    void warriorGainelement(int position,int value){
        (*(headquarterWarriorpointers.begin()+=position))->changeElement(value);}
    inline void headquarterGainElement(int value){strength+=value;}
    int getRedcity(int position);
    int getBluecity(int position);
    //void arrowWarriorshot();
    vector<int> arrowWarriorcity();
    void attackByArrow(int city);
    friend void march(headquarter& red,headquarter & blue);
};






int headquarter::getRedcity(int position) {
    //shared_ptr<warrior * > p;
    auto p = *(headquarterWarriorpointers.begin() + position);
    
    return (p)->showCity();
}

int headquarter::getBluecity(int position){
    return (*(headquarterWarriorpointers.end()-=(1+position)))->showCity();
}


/*void headquarter::born_fail() {
 cout <<setfill('0')<<setw(3)<<Current <<" "<<name<< " headquarter stops making warriors "<<endl;
 lable=false;*/


int headquarter::born_next(){
    //cout<<name<<position<<endl;
    
    (position)>4?position-=5:position;
    //cout<<"headquarterposition"<<endl<<position<<endl;
    //cout<<initElement[(sequence[position])];
    if (strength>=initElement[(sequence[position])])
    {cout<<"bornnrxt"<<endl;born_success();++warriorNum;}
    return 0;
    
}

void headquarter::lionRunAway() {
    for (auto p:headquarterWarriorpointers) {
        cout<<p->showname()<<endl;
        if ((p)->showname() == "lion" && (p)->showCity() != enemy && p->showSpecial() <= 0) {
            p = nullptr;
            --warriorNum;
        }
        
    }
}

bool headquarter::checkGameOver(){
    int tem=0;
    for(auto p:headquarterWarriorpointers) {if(p->showCity()==enemy) ++tem;}
    cout<<tem<<endl;
    if(tem>1) return true;
}


class city{
    
    int cityelement;
    string flag;
    friend class headquarter;
    string winHearquarter;
protected:vector<shared_ptr<warrior> >cityWarriorpointers;
public:
    city(int n,int m):cityelement(n),flag(nullptr){};
    city():cityelement(0){};
    ~city(){ cityWarriorpointers.clear();}
    void cityIncreaseElement(){
        cityelement+=10;}
    int comsumeAllElement(){ int tem=cityelement;cityelement=0;return tem;}
    void bornInheadquarter(shared_ptr<warrior > p){cityWarriorpointers.push_back(p);}
    //int showCityElement(){return cityelement;}
    //int changeCityElement;
    //friend void headquarter::born_success();
    void resetCityWarriorpointers();
    friend void killedByArrow();
    friend void march(headquarter &red,headquarter &blue);
    friend void battle(headquarter &red,headquarter &blue);
    friend void bang();
    friend void takeCityElement(headquarter &red,headquarter &blue);
    inline void win(string s) {
        if (winHearquarter == s) flag = s;
        else winHearquarter = s;
    }
    
    inline void showWarriorweapon(headquarter &head) {
        for (auto p:cityWarriorpointers) {
            if (p->showcolor() == head.showHeadquartername())
                //blue dragon 2 has arrow(3)
            {
                cout << head.showHeadquartername() <<" "<< p->showname() <<" "<< p->shownum();
                p->showweapon();
                
            }
        }
    }
};




static city middleCity[30];
void headquarter::born_success() {
    cout << "born success" << endl;
    shared_ptr<warrior> p;
    string tem = Warriors_name[sequence[position]];
    //cout<<tem<<endl;
    if (tem == "dragon"){ p = shared_ptr<warrior>(new dragon(Num, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));cout << p->showname();}
    else if (tem == "ninjia") {
        p = shared_ptr<warrior>(new ninjia(Num, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));
        cout << p->showname();
    }
    else if (tem == "iceman") {
        p = shared_ptr<warrior>(new iceman(Num, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));
        cout << p->showname();
    }
    else if (tem == "wolf") {
        p = shared_ptr<warrior>(new wolf(Num, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));
        cout << p->showname();
    }
    else {
        cout << tem << endl;
        p = shared_ptr<warrior>(new lion(Num, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));
        p->showfeature();
        cout << (p->showname())<<endl;
    }
    headquarterWarriorpointers.push_back(p);
    if(name=="red") middleCity[0].bornInheadquarter(p);
    else if(name=="blue") middleCity[cityNumber+1].bornInheadquarter(p);
    exist[sequence[position]]++;
    strength-=initElement[(sequence[position])];
    cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<name<<" "<<(p)->showname();
    cout<<" "<<(p)->shownum()<<warriorNum<< " born"<<endl;
    //(p)->feature();
    position++;
}

//void resetID(int n){ID=n;}
//void IDForward(){}
void city::resetCityWarriorpointers() {
    while(!cityWarriorpointers.empty()) cityWarriorpointers.pop_back();
}


/*void headquarter::march() {
 //if(name=="red") {for(auto p:headquarterWarriorpointers) (*p)->forwardCity();
 {for(auto p:cityWarriorpointers)if ((p)->showcolor()=="red")
 {for(auto p:headquarterWarriorpointers) (*p)->backwardCity();}
 */
void warriorDead(shared_ptr<warrior > warriorPtr){
    (warriorPtr)=nullptr;}

//void getPrize(shared_ptr<warrior *>,int n){}

void firstBeatsecond(shared_ptr<warrior > partyone,shared_ptr<warrior > partytwo){
    int tem=(partyone)->showElement()+(partyone)->SwordForce();
    if ( (partyone)->getweapon(0)->showweaponName()=="sword") (partyone)->getweapon(0)->weaponBlunt();
    if((partyone)->getweapon(1)->showweaponName()=="sword") (partyone)->getweapon(1)->weaponBlunt();
    (partytwo)->changeElement(0-tem);
}


string PK(shared_ptr<warrior > partyone,shared_ptr<warrior > partytwo) {
    firstBeatsecond(partyone,partytwo);
    if((partytwo)->showElement()<=0) {warriorDead(partytwo);return (partyone)->showcolor();}
    firstBeatsecond(partytwo,partyone);
    if((partytwo)->showElement()<=0) { warriorDead(partyone); return (partytwo)->showcolor();}
    return "";
}

void battle(headquarter &red,headquarter & blue) {
    for (int i = 0; i < cityNumber + 2;i++) {
        if (middleCity[i].cityWarriorpointers.size() == 2) {
            shared_ptr<warrior > redParty,blueParty;
            shared_ptr<warrior > partyone = *(middleCity[i].cityWarriorpointers.begin());
            auto partytwo = *(middleCity[i].cityWarriorpointers.end() - 1);
            string firstcolor = (partyone)->showcolor();
            string secondcolor = (partytwo)->showcolor();
            if (firstcolor == "red") {
                redParty= partyone;
                blueParty = partytwo;
            } else {
                blueParty = partyone;
                redParty = partytwo;
            }
            
            if (middleCity[i].flag =="red" ||(middleCity[i].flag=="" && i % 2 != 0)) {
                if(PK(redParty,blueParty)=="red")
                    (redParty)->changeElement(red.showElement()>8?8:red.showElement());
                red.headquarterGainElement(middleCity[i].comsumeAllElement());
                middleCity[i].win("red");}
            else if(middleCity[i].flag=="blue" ||(middleCity[i].flag=="" && i%2==0))
            {  if(PK(redParty,blueParty)=="blue")
                middleCity[i].win("blue");
                
                (blueParty)->changeElement(blue.showElement()>8?8:blue.showElement());
                blue.headquarterGainElement(middleCity[i].comsumeAllElement());}
        }
    }
}
void bang(){
    for(int i=0;i<cityNumber+2;++i){
        if(middleCity[i].cityWarriorpointers.size()==2){
            shared_ptr<warrior > partyone = *(middleCity[i].cityWarriorpointers.begin());
            shared_ptr<warrior > partytwo = *(middleCity[i].cityWarriorpointers.end() - 1);
            if(((partyone)->haveBomb()&&(partyone)->showElement()<(partytwo)->showElement())||
               ((partytwo)->haveBomb()&&(partytwo)->showElement()<(partyone)->showElement()))
                warriorDead(partyone);
            warriorDead(partytwo);
        }
    }
}
void march(headquarter & red,headquarter &blue) {
    for (int i = 0; i < cityNumber + 2; i++) {
        for (auto p:middleCity[i].cityWarriorpointers) {
            if ((p)->showcolor() == "red") (p)->forwardCity();
            
            else if ((p)->showcolor() == "blue") (p)->backwardCity();
            cout<<p->showcolor()<<p->showname()<<p->shownum()<<" marched to city "<<p->showCity()<<" with "<<p->showElement()<<" and force "<<p->showWArriorForce()<<endl;
        }
        middleCity[i].resetCityWarriorpointers();
    }
    for (auto c:red.headquarterWarriorpointers) {
        int tem = c->showCity();
        middleCity[tem].cityWarriorpointers.push_back(c);
    }
    for (auto c:blue.headquarterWarriorpointers) {
        int tem = c->showCity();
        cout<<c->showname()<<endl;
        middleCity[tem].cityWarriorpointers.push_back(c);
    }
}




void killedByArrow() {
    //vector<shared_ptr<warrior *> > hasArrow;
    for (int i = 0; i < cityNumber + 2; i++) {
        for (auto p:middleCity[i].cityWarriorpointers) {
            if ((p)->haveArrow()) {
                int arrowcity = (p)->showCity();
                if ((p)->showcolor() == "red") {
                    for (auto c: middleCity[arrowcity + 1].cityWarriorpointers) {
                        if ((c)->showcolor() == "blue" && ((c)->showElement() > arrowforce))
                            (c)->changeElement(0 - arrowforce);
                        else if ((c)->showcolor() == "blue" && (c)->showElement() <= arrowforce) (c) = nullptr;
                    }
                } else if ((p)->showcolor() == "blue") {
                    for (auto c: middleCity[arrowcity - 1].cityWarriorpointers) {
                        if ((c)->showcolor() == "red" && ((c)->showElement() > arrowforce))
                            (c)->changeElement(0 - arrowforce);
                        else if ((c)->showcolor() == "red" && (c)->showElement() <= arrowforce) (c)= nullptr;
                    }
                    
                }
            }
        }
        
    }
}

void takeCityElement(headquarter &red,headquarter &blue) {
    for (int i = 1; i < cityNumber + 1; i++) {
        if (middleCity[i].cityWarriorpointers.size() == 1) {
            auto tem = *(middleCity[i].cityWarriorpointers.begin());
            if (tem->showcolor() == "red") red.headquarterGainElement(middleCity[i].comsumeAllElement());
            else blue.headquarterGainElement(middleCity[i].comsumeAllElement());
            cout<<tem->showcolor()<<" "<<tem->showname()<<" "<<tem->shownum()<<" earned 10 elements for his headquarter"<<endl;
        }
    }
}


int main() {
    int initStrength, loyaltyDeacrease, endpoint;
    int pos = 0;
    cin >> initStrength >> cityNumber >> arrowforce >> loyaltyDeacrease >> endpoint;
    headquarter red = headquarter("red", initStrength, redSequence, cityNumber + 1, 0);
    headquarter blue = headquarter("blue", initStrength, &blueSequence[0], 0, cityNumber + 1);
    //city middleCity[cityNumber + 2];
    //for (int i=0;i!=cityNumber+3;i++)
    // middleCity[i].resetID(i);
    //city BlueCity[cityNumber+2];
    while (pos < 5) {
        cin >> initElement[pos++];
        cout << initElement[pos - 1];
    }
    pos = 0;
    while (pos < 5) {
        cin >> warriorForce[pos++];
        cout << warriorForce[pos - 1];
    }
    //red.born_next();blue.born_next();
    //cout<<initElement[pos-1]<<endl;
    //timepoint=0;
    while (hour*60+minute<=endpoint){
        cout<<timepoint<<endl;
        minute = timepoints[timepoint];
        cout << minute << endl;
        switch (minute) {
            case 0: {
                red.born_next();
                blue.born_next();
                break;
            }
            case 5: {
                red.lionRunAway();
                
                blue.lionRunAway();
                cout<<"run finish"<<endl;
                break;
            }
            case 10: {
                march(red,blue);
                if (red.checkGameOver() || blue.checkGameOver()) return 0;
                cout<<"check over"<<endl;
                break;
            }
            case 20: {
                for (int i = 1; i < cityNumber + 2; i++) {
                    middleCity[i].cityIncreaseElement();
                }
                break;
            }
            case 30: {takeCityElement(red,blue);
                break;}
            case 35: {
                killedByArrow();
                break;
            }
            case 38:
                bang();
                break;
            case 40:
                battle(red, blue);
                break;
                
            case 50:
                cout<< red.showElement()<<" elements in red headquarter"<<endl;
                cout<<blue.showElement()<<" elements in blue headquarter"<<endl;
                break;
            case 55:for(int i=1;i<cityNumber+1;i++){
                middleCity[i].showWarriorweapon(red);
                middleCity[i].showWarriorweapon(blue);}
                break;
        }
        if(++timepoint>9)
        {timepoint-=9;++hour;}
        //cout<<timepoint<<endl;
        //if(timepoint==9)++hour;
    }
    return 0;
}
