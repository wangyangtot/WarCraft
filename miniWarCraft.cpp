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
//static int Num=1;
static int timepoint=0;
static int cityNumber;
static int arrowforce;
static int loyaltyDeacrease;



class bomb {
protected:string weaponName;
public:
    //~bomb();
    //bomb():weaponName(nullptr){};
    bomb(string s):weaponName(s){};
    virtual int showWeaponforce(){return 1;};
    virtual bool weaponBlunt(){};
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
    inline bool weaponBlunt(){
        swordforce*=0.8;
        if(swordforce==0)return false;
        return true;}
    
};

class arrow:public bomb{
    int arrowshots;
    int arrowforce;
public:
    //~arrow();
    arrow(string s,int n):bomb(s),arrowshots(3),arrowforce(n){};
    int showWeaponforce(){return arrowshots;}
    inline bool weaponBlunt(){--arrowshots;
        if(arrowforce==0) return false;
        return true;}
};



class warrior {
protected:
    int num;
    int strengthLeft;
    int element;
    
    string headName;
    int warriorForce;
    int city;
    shared_ptr<bomb> weapon[3];
    bool dead=false;
    //friend city;
    
public:
    void makeDead(){dead=true;}
    virtual int showSpecial(){return 10;};
    void removeWeapon(int n){weapon[n]= nullptr;}
    
    //warrior() : num(0), strengthLeft(0), element(0), {};
    
    warrior(int n, int sleft, int consu, string shname,int m) : num(n), strengthLeft(sleft), element(consu),
    headName(shname),warriorForce(m){if(headName=="red")city=0; else city=cityNumber+1;};
    virtual int actionFeature(int i,shared_ptr<warrior> &wptr){return 0;};
    virtual void showfeature() {};
    
    virtual string showname(){return "";}
    int showWArriorForce(){return warriorForce;}
    
    inline int shownum() { return num; }
    
    shared_ptr<bomb> gainWeapon(string s);
    
    inline int showCity() { return city; }
    bool showdead(){return dead;}
    void forwardCity() { city++; }
    
    void backwardCity() { --city; }
    shared_ptr<bomb> getweapon(int n) { return weapon[n]; }
    
    void changeElement(int n) { element += n; }
    
    //virtual int getarrowNumber(){};
    int showElement() { return element; }
    virtual void showweapon(){cout<<" has no weapon"<<endl;};
    
    inline string showcolor() { return headName; }
    
    virtual int haveArrow(){return 3;};
    
    virtual int SwordForce(){return 0;}
    
    virtual bool haveBomb(){return false;}
    virtual bool haveSword(){return false;}
    
    
    friend void firstBeatsecond(shared_ptr<warrior > partyone, shared_ptr<warrior > partytwo);
    
    friend string PK(shared_ptr<warrior > partyone, shared_ptr<warrior > partytwo);
    
    friend void beat(shared_ptr<warrior > partyone, shared_ptr<warrior > partytwo);
    
    //friend void bang(headquarter &red,headquarter &blue);
    //friend void march(headquarter &red,headquarter &blue);
    //friend void killedByArrow(headquarter &red, headquarter &blue);
    
    friend void warriorDead(shared_ptr<warrior > &warriorPtr);
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
    inline string showname(){return wname;}
    void showweapon()override{
        if(!weapon[0]) warrior::showweapon();return;
        cout<<" has "<<weapon[0]->showweaponName()<<"("<<weapon[0]->showWeaponforce()<<")"<<endl;
    }
    void showfeature();
    inline int haveArrow() override {
        if(weapon[0]->showweaponName()=="arrow") return 0;
        return  3;
    }
    int SwordForce()override ;
    bool haveBomb() override;
    int showSpecial(){ return 10;}
    bool haveSword()override {
        if(weapon[0]->showweaponName()=="sword") return true;
        return  false;}
    int actionFeature(int i,shared_ptr<warrior> &wptr) override;
};

int dragon::actionFeature(int i,shared_ptr<warrior> &wptr) {
    if(i==2) morale+=0.2;
    else if(i==-1) morale-=0.2;//1 present success -1 means fall; 0 means check;
    if(morale>0.8) cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<headName<<num<<" yelled in city "<<city<<endl;
    return 0;}

int dragon::SwordForce() {
    if (weapon[0]->showweaponName() == "sword")
        return weapon[0]->showWeaponforce();
    return 0;}
void dragon::showfeature() {cout<<" its morale is "<<setprecision(3)<<morale<<endl;}
bool dragon::haveBomb(){
    if (weapon[0]->showweaponName() == "bomb") return true;
    return false;
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
        if(!weapon[0]&& !weapon[1]){ warrior::showweapon();return;}
        shared_ptr<bomb> first,second;
        if(weapon[0]->showweaponName()=="arrow") {first=weapon[0];second=weapon[1];}
        else if(weapon[1]->showweaponName()=="arrow"){first=weapon[1];second=weapon[0];}
        else if(weapon[0]->showweaponName()=="bomb"){first=weapon[0];second=weapon[1];}
        else {first=weapon[1];second=weapon[0];}
        
        cout<<" has "<<first->showweaponName()<<"("<<first->showWeaponforce()<<"),";
        cout<<second->showweaponName()<<"("<<second->showWeaponforce()<<")"<<endl;
    }
    
    string showname(){return wname;}
    inline int haveArrow() override {
        if(weapon[0]->showweaponName()=="arrow") return 0;
        if(weapon[1]->showweaponName()=="arrow") return 1;
        return  3; }
    
    int SwordForce() override;
    bool haveBomb() override ;
    int showSpecial(){ return 10;}
    bool haveSword()override {
        if(weapon[0]->showweaponName()=="sword"||weapon[1]->showweaponName()=="sword") return true;
        return  false;}
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






class iceman:public warrior{
    string wname="iceman";
    int step;
    //shared_ptr<bomb> weapon;
public:
    iceman(int n,int sleft,int consu,string s,int m):warrior(n,sleft,consu,s,m){weapon[0]=gainWeapon(WeaponsName[num%3]);step=0;}
    inline string showname(){return wname;}
    void showweapon()override{
        if(!weapon[0]){warrior::showweapon();return;}
        cout<<" has "<<weapon[0]->showweaponName()<<"("<<weapon[0]->showWeaponforce()<<")"<<endl;
    }
    bool haveSword()override {
        if(weapon[0]->showweaponName()=="sword") return true;
        return  false;}
    inline int haveArrow() override {
        if(weapon[0]->showweaponName()=="arrow") return 0;
        return  3; }
    int SwordForce() override;
    bool haveBomb() override ;
    int showSpecial(){ return 10;}
    int actionFeature(int i,shared_ptr<warrior> &wptr) override{
        if(step==3) {
            element -= 9 > 0 ? element : 1;
            warriorForce += 20;
        }
    }
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





class lion:public warrior{
    string wname="lion";
    int loyalty;
    
public: int showSpecial(){ return loyalty;}
    lion(int n,int sleft,int consu,string s,int m):warrior(n,sleft,consu,s,m){cout<<"lion born"<<endl;loyalty=strengthLeft-consu;}
    string showname(){return wname;}
    void showfeature();
    inline int showloyalty(){return loyalty;}
    inline int SwordForce(){return 0;}
    bool haveBomb(){return false;};
    int actionFeature(int i,shared_ptr<warrior> &wptr) override {
        if(i==-1) loyalty-=loyaltyDeacrease;                 //-1 means lose the battle, 0 means dead
        if(i==-2)   wptr->changeElement(element);
        return 0;}
};
void lion::showfeature() {cout<<"It’s loyalty is "<<loyalty<<endl;}


class wolf:public warrior{
    string wname="wolf";
    int waitposition=0;
public:wolf(int n, int sleft,int consu,string s,int m):warrior(n,sleft,consu,s,m){};
    string showname(){return wname;}
    inline int SwordForce(){return 0;}
    bool haveBomb(){return false;}
    int showSpecial(){ return 10;}
    int actionFeature(int i,shared_ptr<warrior> &wptr) override;
    void showweapon() override{
        if(waitposition==0) cout<<" has no weapon "<<endl;
        else {
            cout << " has ";
            for (int i = 0; i < waitposition; i++) {
                cout << weapon[i]->showweaponName() << "(" << weapon[i]->showWeaponforce() << ") " << endl;
            }
        }
    }
};

int wolf::actionFeature(int i,shared_ptr<warrior> &wptr) {
    if(i==2) {
        for(int i=0;i<2;i++){
            if(waitposition==3) return 0;
            string tem=wptr->getweapon(i)->showweaponName();
            if(!tem.empty()&&tem!=getweapon(0)->showweaponName()&& tem!=getweapon(1)->showweaponName()&& tem!=getweapon(2)->showweaponName())
                weapon[waitposition]=wptr->getweapon(i);
            waitposition++;
        }
    }
}


class headquarter {
    string name;
    int strength;
    int *sequence;
    int enemy;
    int cityposition;
    
    int exist[number]={0};
    bool tag =true;
    int position=0;
    int warriorNum=1;
    
    
protected:  vector<shared_ptr<warrior> > headquarterWarriorpointers;
public:
    headquarter(string s,int n ,int *pSequence,int m,int j) :name(s),strength(n),sequence(pSequence),enemy(m),cityposition(j) {};
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
    friend void headquarterClearDead(headquarter &head);
    friend void resetCityWarriorpointers(headquarter &head,headquarter &blue);
    friend void killedByArrow(headquarter &red, headquarter &blue);
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
    //cout<<"born_next"<<endl;
    
    (position)>4?position-=5:position;
    //cout<<"headquarterposition"<<endl<<position<<endl;
    //cout<<initElement[(sequence[position])];
    if (strength>=initElement[(sequence[position])])
        //cout<<"bornnrxt"<<endl;
        born_success();
    return 0;
    
}

void headquarter::lionRunAway() {
    for (auto p:headquarterWarriorpointers) {
        cout<<p->showname()<<endl;
        if ((p)->showname() == "lion" && (p)->showCity() != enemy && p->showSpecial() <= 0) {
            warriorDead(p);
        }
    }
    headquarterClearDead(*this);
    
}

bool headquarter::checkGameOver(){
    int tem=0;
    for(auto p:headquarterWarriorpointers) {if(p->showCity()==enemy) ++tem;}
    cout<<tem<<endl;
    if(tem>1) return true;
}


class city {
    
    int cityelement;
    string flag;
    
    friend class headquarter;
    
    string winHearquarter;
protected:
    vector<shared_ptr<warrior> > cityWarriorpointers;
public:
    city(int n, int m) : cityelement(n) {};
    
    city() : cityelement(0) {};
    
    ~city() { cityWarriorpointers.clear(); }
    
    void cityIncreaseElement() {
        cityelement += 10;
    }
    
    int comsumeAllElement() {
        int tem = cityelement;
        cityelement = 0;
        return tem;
    }
    
    void bornInheadquarter(shared_ptr<warrior> p) { cityWarriorpointers.push_back(p); }
    
    //int showCityElement(){return cityelement;}
    //int changeCityElement;
    //friend void headquarter::born_success();
    friend void resetCityWarriorpointers(headquarter &head, headquarter &blue);
    
    friend void killedByArrow(headquarter &red, headquarter &blue);
    
    friend void march(headquarter &red, headquarter &blue);
    
    friend void battle(headquarter &red, headquarter &blue);
    
    friend void bang(headquarter &red, headquarter &blue);
    
    friend void takeCityElement(headquarter &red, headquarter &blue);
    
    inline void win(string s,int i) {
        if (winHearquarter == s) cout << setfill('0') << setw(3) << hour << " " << setfill('0') << setw(2) << minute << " "
            <<s<<" flag raised in city "<<i<<endl;
        else winHearquarter = s;
    }
    void showWarriorweapon(headquarter &head);
};


void city::showWarriorweapon(headquarter &head) {
    for (auto p:cityWarriorpointers) {
        if (p->showcolor() == head.showHeadquartername())
            //blue dragon 2 has arrow(3)
        {
            if (p->getweapon(0)!= nullptr && p->getweapon(0)->showWeaponforce() == 0) p->removeWeapon(0);
            if (p->getweapon(1)!= nullptr && p->getweapon(1)->showWeaponforce() == 0) p->removeWeapon(1);
            cout << setfill('0') << setw(3) << hour << " " << setfill('0') << setw(2) << minute << " "
            << head.showHeadquartername() << " " << p->showname() << " " << p->shownum();
            p->showweapon();
            
        }
    }
}



static city middleCity[30];
void headquarter::born_success() {
    //cout << "born success" << endl;
    shared_ptr<warrior> p;
    string tem = Warriors_name[sequence[position]];
    //cout<<tem<<endl;
    if (tem == "dragon"){ p = shared_ptr<warrior>(new dragon(warriorNum, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));}
    else if (tem == "ninjia") {
        p = shared_ptr<warrior>(new ninjia(warriorNum, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));
    }
    else if (tem == "iceman") {
        p = shared_ptr<warrior>(new iceman(warriorNum, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));
        
    }
    else if (tem == "wolf") {
        p = shared_ptr<warrior>(new wolf(warriorNum, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));
        
    }
    else {
        //cout << tem << endl;
        p = shared_ptr<warrior>(new lion(warriorNum, strength, initElement[(sequence[position])], name,warriorForce[sequence[position]]));
        
    }
    headquarterWarriorpointers.push_back(p);
    if(name=="red") middleCity[0].bornInheadquarter(p);
    else if(name=="blue") middleCity[cityNumber+1].bornInheadquarter(p);
    exist[sequence[position]]++;
    strength-=initElement[(sequence[position])];
    cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<name<<" "<<(p)->showname();
    cout<<" "<<warriorNum++<< " born"<<endl;
    p->showfeature();
    //(p)->feature();
    position++;
}

//void resetID(int n){ID=n;}
//void IDForward(){}
void  resetCityWarriorpointers(headquarter &red,headquarter &blue) {
    cout<<"reset begin"<<endl;
    for(int i=0;i<2+cityNumber;i++){
        while (!middleCity[i].cityWarriorpointers.empty()) middleCity[i].cityWarriorpointers.pop_back();}
    //cout<<red.headquarterWarriorpointers.size();
    for (auto c:red.headquarterWarriorpointers) {
        int tem = c->showCity();
        //cout<<tem<<endl;
        middleCity[tem].cityWarriorpointers.push_back(c);
    }
    for (auto c:blue.headquarterWarriorpointers){
        int tem=c->showCity();
        middleCity[tem].cityWarriorpointers.push_back(c);
    }
}



void warriorDead(shared_ptr<warrior > &warriorPtr){
    cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<warriorPtr->showname()<<" was killed in city "<<warriorPtr->showCity()<<endl;
    (*warriorPtr).dead=true;}

void headquarterClearDead(headquarter &head){
    int position=0;
    for(auto p:head.headquarterWarriorpointers){
        if(p->showdead()==true) head.headquarterWarriorpointers.erase(head.headquarterWarriorpointers.begin()+position);
        ++position;
    }
    cout<<"headwarriorNUM"<<head.headquarterWarriorpointers.size()<<endl;
}

//void getPrize(shared_ptr<warrior *>,int n){}

void firstBeatsecond(shared_ptr<warrior > partyone,shared_ptr<warrior > partytwo){
    cout<<partytwo->showElement()<<endl;
    int tem=(partyone)->showWArriorForce()+(partyone)->SwordForce();
    cout<<tem<<endl;
    if ( (partyone)->haveSword()) {cout<<"have sword"<<endl;
        if(!(partyone)->getweapon(0)->weaponBlunt())partyone->removeWeapon(0);
        if(!(partyone)->getweapon(1)->weaponBlunt()) partyone->removeWeapon(1);}
    (partytwo)->changeElement((0-tem));
    cout<<partytwo->showElement()<<endl;
    
}


string PK(shared_ptr<warrior > partyone,shared_ptr<warrior > partytwo) {
    cout<<partyone->showname()<<endl;
    cout<<"pk"<<endl;
    firstBeatsecond(partyone,partytwo);
    cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<partyone->showcolor()<<" "<<partyone->showname()<<" "
    <<partyone->shownum()<<" attacked "<<partytwo->showcolor()<<" "<<partytwo->showname()<<" "<<partytwo->shownum()<<" "<<" in city "<<partyone->showCity()
    <<" with "<<partyone->showElement()<<" and force "<<partyone->showWArriorForce()<<endl;
    if((partytwo)->showElement()<=0) {warriorDead(partytwo);partyone->actionFeature(2,partytwo);return (partyone)->showcolor();}
    partyone->actionFeature(1,partytwo);
    if(partytwo->showname()=="ninjia") return "";
    cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<partytwo->showcolor()<<" "<<partytwo->showname()<<" "
    <<partytwo->shownum()<<" fight back against " <<partyone->showcolor()<<" "<<partyone->showname()<<" "<<partyone->shownum()<<" "
    <<" in city "<<partyone->showCity()<<endl;
    firstBeatsecond(partytwo,partyone);
    
    if((partytwo)->showElement()<=0) { partytwo->actionFeature(2,partyone); warriorDead(partyone); return (partytwo)->showcolor();}
    else partytwo->actionFeature(1,partyone);
    return "";
}

void battle(headquarter &red,headquarter & blue) {
    cout<<"battle begin"<<endl;
    for (int i = 0; i < cityNumber + 2; i++) {
        if (middleCity[i].cityWarriorpointers.size() == 2) {
            cout<<i<<endl;
            shared_ptr<warrior> redParty, blueParty;
            shared_ptr<warrior> partyone = *(middleCity[i].cityWarriorpointers.begin());
            auto partytwo = *(middleCity[i].cityWarriorpointers.end() - 1);
            string firstcolor = (partyone)->showcolor();
            string secondcolor = (partytwo)->showcolor();
            cout<<firstcolor<<secondcolor<<endl;
            if (firstcolor == "red") {
                redParty = partyone;
                blueParty = partytwo;
            } else {
                blueParty = partyone;
                redParty = partytwo;
            }
            //cout<<middleCity[i].flag<<endl;
            if (middleCity[i].flag == "red" || (middleCity[i].flag.empty() && i % 2 != 0)) {
                if (PK(redParty, blueParty) == "red") {
                    (redParty)->changeElement(red.showElement() > 8 ? -8 : -red.showElement());
                    red.headquarterGainElement(middleCity[i].comsumeAllElement());
                    middleCity[i].win("red",i);
                    headquarterClearDead(red);
                }
            } else if (middleCity[i].flag == "blue" || (middleCity[i].flag.empty() && i % 2 == 0)) {
                cout<<"blue"<<endl;
                if (PK(blueParty, redParty) == "blue") {
                    middleCity[i].win("blue",i);
                    
                    (blueParty)->changeElement(blue.showElement() > 8 ? -8 : -blue.showElement());
                    blue.headquarterGainElement(middleCity[i].comsumeAllElement());
                    headquarterClearDead(blue);
                }
            }
        }
    }
}
void bang(headquarter &red,headquarter &blue) {
    cout << "bang check" << endl;
    for (int i = 0; i < cityNumber + 2; i++) {
        if (middleCity[i].cityWarriorpointers.size() == 2) {
            cout << " 2 in city" << i << endl;
            shared_ptr<warrior> partyone = *(middleCity[i].cityWarriorpointers.begin());
            shared_ptr<warrior> partytwo = *(middleCity[i].cityWarriorpointers.end() - 1);
            cout << partyone->showname() << " " << partytwo->showname() << endl;
            int temone = (partyone)->showElement() + partyone->showWArriorForce();
            int temtwo = (partytwo)->showWArriorForce() + partytwo->showElement();
            if (((partyone)->haveBomb() && temone < temtwo)){
                cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<partyone->showcolor()<<" ";
                cout<<partyone->showname()<<" "<<partyone->shownum()<<" used bomb and killed "<<partytwo->showcolor()<<" "
                <<partytwo->showname()<<" "<<partytwo->shownum()<<endl;warriorDead(partyone);
                warriorDead(partytwo);}
            if ((partytwo)->haveBomb() && temtwo < temone) {
                cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<partytwo->showcolor()<<" ";
                cout<<partytwo->showname()<<" "<<partytwo->shownum()<<" used bomb and killed "<<partyone->showcolor()<<" "
                <<partyone->showname()<<" "<<partyone->shownum()<<endl;
                warriorDead(partyone);
                warriorDead(partytwo);
            }
        }
    }
    headquarterClearDead(red);
    headquarterClearDead(blue);
    resetCityWarriorpointers(red,blue);
    
}

void march(headquarter & red,headquarter &blue) {
    for (int i = 0; i < cityNumber + 2; i++) {
        for (auto p:middleCity[i].cityWarriorpointers) {
            if ((p)->showcolor() == "red" && p->showCity() != cityNumber + 1) {
                (p)->forwardCity();
                p->actionFeature(3,p);
                cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" " << p->showcolor()<<" "<< p->showname() <<" "<<p->shownum() << " marched to city " << p->showCity()
                << " with " << p->showElement() << " and force " << p->showWArriorForce() << endl;
            } else if ((p)->showcolor() == "blue" && p->showCity() != 0) {
                (p)->backwardCity();p->actionFeature(3,p);
                cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" " << p->showcolor()<<" "<< p->showname() << p->shownum() << " marched to city " << p->showCity()
                << " with " << p->showElement() << " and force " << p->showWArriorForce() << endl;
            }
        }
        
    }
    resetCityWarriorpointers(red,blue);
    
}




void killedByArrow(headquarter &red,headquarter &blue) {
    //vector<shared_ptr<warrior *> > hasArrow;
    for (int i = 0; i < cityNumber + 2; i++) {
        for (auto p:middleCity[i].cityWarriorpointers) {
            if ((p)->haveArrow()!=3) {
                int arrowcity = (p)->showCity();
                if ((p)->showcolor() == "red") {
                    if(arrowcity==cityNumber) break;
                    for (auto c: middleCity[arrowcity + 1].cityWarriorpointers) {
                        cout<< setfill('0') << setw(3)<<hour<<" "
                        <<setfill('0') <<setw(2)<<minute<<" red "<<p->showname()<<" "<<p->shownum()<<" shot";
                        if ((c)->showcolor() == "blue" && ((c)->showElement() > arrowforce))
                        {cout<<" "<<endl;(c)->changeElement(0 - arrowforce); c->actionFeature(-1,p); p->getweapon(p->haveArrow())->weaponBlunt();}
                        else if ((c)->showcolor() == "blue" && (c)->showElement() <= arrowforce){
                            cout<<" and killed "<<c->showname()<<" "<<c->shownum()<<endl;
                            c->makeDead();
                            p->getweapon(p->haveArrow())->weaponBlunt(); c->actionFeature(-2,p);middleCity[i].win("red",i);
                            
                            p->changeElement(blue.showElement() > 8 ? -8 : -blue.showElement());
                            red.headquarterGainElement(middleCity[i].comsumeAllElement());
                        }
                    }
                } else if ((p)->showcolor() == "blue") {
                    if(arrowcity==1) break;
                    for (auto c: middleCity[arrowcity - 1].cityWarriorpointers) {
                        cout<< setfill('0') << setw(3)<<hour<<" "
                        <<setfill('0') <<setw(2)<<minute<<" blue "<<p->showname()<<" "<<p->shownum()<<" shot";
                        if ((c)->showcolor() == "red" && ((c)->showElement() > arrowforce))
                        { cout<<" "<<endl;(c)->changeElement(0 - arrowforce); c->actionFeature(-1,p);p->getweapon(p->haveArrow())->weaponBlunt();
                        }
                        else if ((c)->showcolor() == "red" && (c)->showElement() <= arrowforce) {
                            cout<<" and killed "<<c->showname()<<" "<<c->shownum()<<endl;
                            c->makeDead(); c->actionFeature(-2,p);p->getweapon(p->haveArrow())->weaponBlunt();
                            middleCity[i].win("blue",i);
                            p->changeElement(blue.showElement() > 8 ? -8 : -blue.showElement());
                            blue.headquarterGainElement(middleCity[i].comsumeAllElement());
                        }
                    }
                    
                }
            }
        }
        
        
    }
    headquarterClearDead(red);
    headquarterClearDead(blue);
}


void takeCityElement(headquarter &red,headquarter &blue) {
    for (int i = 1; i < cityNumber + 1; i++) {
        if (middleCity[i].cityWarriorpointers.size() == 1) {
            auto tem = *(middleCity[i].cityWarriorpointers.begin());
            if (tem->showcolor() == "red") red.headquarterGainElement(middleCity[i].comsumeAllElement());
            else blue.headquarterGainElement(middleCity[i].comsumeAllElement());
            cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2)<<minute<<" "<<tem->showcolor()<<" "<<tem->showname()<<" "<<tem->shownum()<<" earned 10 elements for his headquarter"<<endl;
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
        //cout<<timepoint<<endl;
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
                headquarterClearDead(red);
                headquarterClearDead(blue);
                cout<<"run finish"<<endl;
                break;
            }
            case 10: {
                march(red,blue);
                if (red.checkGameOver()){ cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2);
                    cout<<minute<<" blue headquarter was taken "<<endl; return 0;}
                else if(blue.checkGameOver()){cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2);
                    cout<<minute<<" red headquarter was taken "<<endl; return 0;}
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
                killedByArrow(red,blue);
                break;
            }
            case 38:
                bang(red,blue);
                break;
            case 40:
                battle(red, blue);
                break;
                
            case 50:
                cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2);
                cout<<minute<<" "<<red.showElement()<<" elements in red headquarter"<<endl;
                cout<< setfill('0') << setw(3)<<hour<<" "<<setfill('0')<<setw(2);
                cout<<minute<<" "<<blue.showElement()<<" elements in blue headquarter"<<endl;
                break;
            case 55:for(int i=0;i<cityNumber+2;i++){
                middleCity[i].showWarriorweapon(red);
                middleCity[i].showWarriorweapon(blue);}
                break;
        }
        if(++timepoint>9)
        {timepoint-=10;++hour;}
        //cout<<timepoint<<endl;
        //if(timepoint==9)++hour;
    }
    return 0;
}
