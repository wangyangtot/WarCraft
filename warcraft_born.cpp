#include <iostream>
#include <string>
#include <map>
using namespace std;
 int warrior_consume[5];
static string warriors[5]={"dragon" ,"ninja","iceman","lion","wolf"};
class headquarter {
protected: int strength;
public:
    headquarter(int total) : strength(total) {};

    headquarter() : strength(0) {};

    virtual int born_next()=0;

};

class redquarter: public headquarter {
    const int sequence[5]={2, 3, 4, 1, 0};
    int borns[5] = {0};
    //const string sequence[5]={"iceman","lion","wolf","ninja","dragon"};
    int position;
    int time=0;
    bool lable = true;
public:
    inline bool get_lable() { return lable; }

    redquarter(int total) : headquarter(total), position(0) {cout<<total<<" "<<position<<endl;}

    int born_next();
};

int redquarter::born_next(){
	(position)>4?position-=5:position;
	int flag=position;

    while(strength<warrior_consume[(sequence[position])]) {
    	(++position)>4?position-=5:position;
        if((position)==flag) {
            cout << time+1 << "red headquarter stops making warriors"<<endl;
            lable=false;
            return 0;
        }
        
    }
    strength-=warrior_consume[(sequence[position])];
    
    cout<< time<<"red"<<" "<<warriors[sequence[position]]<<" "<<++time<<
    " born with "<<warrior_consume[sequence[position]]<<", "<<borns[sequence[position]]<<
        " in red headquarter "<<endl;
        borns[sequence[position]]++;
        position++;
return 0;
}





int main() {
    int consume,total_strength;
    int pos=0;
    //static map<string,int> warrior_consume;
    cout<<"input"<<endl;
    cin>>total_strength;
    redquarter red(total_strength);
    //cout<<total_strength;
    while (cin>>warrior_consume[pos++]){
    	cout<<warrior_consume[pos-1]<<endl;
    };
    while(red.get_lable()==true){
    red.born_next();}
return 0;
}