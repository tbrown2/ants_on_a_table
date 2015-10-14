#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>

class Ant{
private:
    string color; //can be red and blue
    string hierarchy; // different classes, with different attacks, Queen = 0, worker = 1, soldier = 2
    Tablenode* location; // where this ant is
    string joiner; // the ant class that joined with, initially set to nobody
    bool joined; // indicator to whether the ant has joined with another ant
    int attackpower;
    bool dead;
public:
    Ant(){};
    void set_up(string color_, string hierarchy_, int attackpower_)
    {
        color = color_;
        hierarchy = hierarchy_;
        attackpower = attackpower_;
        dead = false;
        joined = false;
        location = NULL;
        joiner = "";
    };
    string getcolor(){ return color;}
    string gethierarchy() {return hierarchy;}
    bool getjoined() {return joined;}
    string getjoiner() {return joiner;}
    int getattackpower() {return attackpower;}
    Tablenode * getlocation() {return location;}
    void joinup(Ant antpartner);
    void attack(Ant enemy);
    void isdead();
    void SetLocation (Tablenode * new_location);
};
void Ant:: SetLocation (Tablenode * new_location)
{
    location = new_location;
}
void Ant:: isdead(){ dead = true; return;}
void Ant:: joinup (Ant partner)
{
    joined = true;
    attackpower = attackpower + partner.getattackpower();
    joiner = partner.hierarchy;
    cout << color << " " << hierarchy << " and " << partner.gethierarchy() << " have joined forces!\n";
}
void Ant:: attack(Ant enemy)
{
    if (attackpower > enemy.getattackpower()) //this ant wins
    {
        enemy.isdead();
        //location = enemy.getlocation();
        if (enemy.getjoined() == false) cout << "A" << enemy.getcolor() << " " << enemy.gethierarchy() << " has died in a raid! \n";
        else cout << "A couple of " << enemy.getcolor() << " ants failed to halt the enemy's advance!\n";
    }
    else if (attackpower < enemy.getattackpower())//this ant loses
    {
        dead = true;
        if (joined == false)cout <<"A" << color << " " << hierarchy << " has died trying to slay its foe.\n";
        else cout << "Two " << color << " ants have been slaughtered today. May they rest in peace...\n";
    }
    else  //they have equal attack power
    {
        cout << "An equal footing between foes! ";
        int temp;
        srand(time(NULL));
        temp = rand() % 8;
        if (temp % 2 == 0){enemy.isdead(); cout << "And the " << enemy.getcolor()<< " died. Whoops.\n";}
        else {dead = true; cout << "The " << color << " party lost";}
    }
}
