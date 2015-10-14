#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

class Tablenode{
public:
    /**4 DIRECTIONS**/
    Tablenode *North;
    Tablenode *East;
    Tablenode *South;
    Tablenode *West;
    bool filled;
    bool IsEmpty()
    { if (filled = true){return true;} else {return false;}}
    Tablenode() //constructor
    {
        North = NULL; East = NULL;
        South = NULL; West = NULL;
        filled = false;
    }
};

class Table { //tracks where the table begins
public:
    Tablenode *Root;
    Table(){Root = NULL;}
    int createtable (int length);
};
int Table:: createtable(int length) //input a dimension to create the table
{
    /** 4 POINTERS TO TRACK WHICH NODES TO CONNECT **/
    Tablenode * topRight = Root;
    Tablenode * topLeft = Root;
    Tablenode * bottomRight = Root;
    Tablenode * bottomLeft = Root;
    topRight = new Tablenode();
    bottomLeft = new Tablenode();
    Root = topRight;
    topLeft = topRight;
    for (int i = 0; i<length; i++) //taking square left to right, different for very beginning
    {
        bottomRight = new Tablenode();
        topRight = new Tablenode;
        topRight->West = topLeft; topLeft->East = topRight;
        bottomRight->West = bottomLeft; bottomLeft->East = bottomRight;
        topLeft->South = bottomLeft; bottomLeft->North = topLeft;
        topRight->South = bottomRight; bottomRight->North = topRight;
        topLeft = topRight;
        bottomLeft = bottomRight;
    }
    for (int n = 0; n<length; n++){ //tracking the square downwards
        for (int i = 0; i<length; i++) {topLeft = topLeft->West;} //must make sure that the topLeft goes all the way back to the left
        topLeft = topLeft->South; //bring it down once
        topRight = topLeft->East;
        bottomLeft = new Tablenode();
        for (int i = 0; i<length; i++) //making the square go left to right, its different than the top because you do not have to relink the topLeft and topRight
        {
            bottomRight = new Tablenode();
            bottomRight->West = bottomLeft; bottomLeft->East = bottomRight;
            topLeft->South = bottomLeft; bottomLeft->North = topLeft;
            topRight->South = bottomRight; bottomRight->North = topRight;
            topLeft = topLeft->East;
            topRight = topRight->East;
            bottomLeft = bottomRight;
        }
    }

}
class Ant{
public:
    string color; //can be red and blue
    string hierarchy; // different classes, with different attacks, Queen = 0, worker = 1, soldier = 2
    Tablenode* location; // where this ant is
    string joiner; // the ant class that joined with, initially set to nobody
    bool joined; // indicator to whether the ant has joined with another ant
    int attackpower;
    bool dead;
    Ant(){};
    /**SET THE ANTS VARIABLES**/
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
    /**VARIOUS GETTERS AND SETTERS I THOUGHT USEFUL**/
    string getcolor(){ return color;}
    string gethierarchy() {return hierarchy;}
    bool getjoined() {return joined;}
    string getjoiner() {return joiner;}
    int getattackpower() {return attackpower;}
    Tablenode * getlocation() {return location;}
    void isdead();
    void SetLocation (Tablenode * new_location);
    void turn ();
};
void Ant:: SetLocation (Tablenode * new_location)
{
    location = new_location;
}
void Ant:: isdead(){ dead = true; return;}

int main()
{
    srand(time(NULL));
    cout << "Hello, this is a ants on a table simulator. The rules are simple:\n";
    cout << "- Ants from two teams - blue and red- battle it out for supremacy on a table.\n";
    cout << "- Ants can come in three classes - Queens, soldiers, and drones- with different attacks.\n";
    cout << "- Drones have attack of 1, Soldiers have attack of 2, and Queens have 0 attack.\n";
    cout << "- Drones and soldiers can team up with one other drone or soldier from the same team to add their attacks together.\n";
    cout << "- If one attack is greater than another , then the ant with the lesser dies\n";
    cout << "- If attacks are equal a dice is rolled to see who wins.\n";
    cout << "- Once one of the Queens has been killed, then it's game over, and the team with the dead Queen loses.";
    cout << "\n\n----------------------------------------------------------\n\t";
    cout << "\tLet's get started!\n----------------------------------------------------------" << endl;

    /** PREPARING VARIABLES FOR ANTS ON A TABLE  AND SETTING UP TABLE**/
    Table table; //graph where ants will populate
    bool red_flag = false, blue_flag = false; //flags to make sure we know if the Queen has died
    int table_dimension; //int from user input that will determine the size of our table

    cout << "Please enter the dimensions of the square table: ";
    cin >> table_dimension;
    while (table_dimension<3)
    { cout << "The amount you entered is too small, please enter a number greater than 3: "; cin >> table_dimension; }
    table.createtable(table_dimension); //creating table

    /** CREATING ANT TEAMS IF ODD ONE ARRAY IF EVEN A DIFFERENTLY SIZED ARRAY **/
    int area = table_dimension*table_dimension; //array to keep track of whose turn it is
    int area2 = (table_dimension*table_dimension) - table_dimension;
    Ant ant_turns[area];
    Ant ant_turns2[area2];
    if (table_dimension%2 == 1) //for odd dimensions
    {
        string red = "red", blue = "blue", Queen = "Queen", Drone = "Drone", Soldier = "Soldier";
        Ant red_queen;
        red_queen.set_up(red, Queen, 0);
        Ant blue_queen;
        blue_queen.set_up(blue, Queen, 0);
        ant_turns2[0] = red_queen; //red will always go first
        ant_turns2[1] = blue_queen;
        for (int i = 2; i<area2; i++) //basically to create a free row in the middle, removing two Queens that were created
        {
            if (i < area2/2)
            {
                Ant red_soldier; red_soldier.set_up(red, Soldier, 2);
                Ant blue_soldier; blue_soldier.set_up(blue, Soldier, 2);
                ant_turns2[i] = red_soldier;
                i++;
                ant_turns2[i] = blue_soldier;
            }
            else
            {
                Ant red_drone; red_drone.set_up(red, Drone, 1);
                Ant blue_drone; blue_drone.set_up(blue, Drone, 1);
                ant_turns2[i] = blue_drone;
                i++;
                ant_turns2[i] = red_drone;
            }
        }
    }
    else  //even dimensions
    {
        string red = "red", blue = "blue", Queen = "Queen", Drone = "Drone", Soldier = "Soldier";
        Ant red_queen; red_queen.set_up(red, Queen, 0);
        Ant blue_queen; blue_queen.set_up(blue, Queen, 0);
        ant_turns[0] = red_queen; //red will always go first
        ant_turns[1] = blue_queen;
        for (int i = 2; i<area; i++) //basically to create a free row in the middle, removing two Queens that were created
            {
                if (i <= area/2){
                Ant red_soldier; red_soldier.set_up(red, Soldier, 2);
                Ant blue_soldier; blue_soldier.set_up(blue, Soldier, 2);
                ant_turns[i] = red_soldier;
                i++;
                ant_turns[i] = blue_soldier;
                }
                else {
                Ant red_drone; red_drone.set_up(red, Drone, 1);
                Ant blue_drone; blue_drone.set_up(blue, Drone, 1);
                ant_turns[i] = red_drone;
                i++;
                ant_turns[i] = blue_drone;
                }
            }
    }

    int red_num = 0; int blue_num = 1;

    /**POPULATING TABLE WITH THROUGH MY ANT ARRAY**/
    if (table_dimension%2 == 1) // for odd dimensions
        {
            Tablenode* mover = table.Root;
            for (int n = 1; n<table_dimension; n++){
                for (int i = 1; i<table_dimension; i++)
                {
                    if (n <= table_dimension/2){
                    Ant temp = ant_turns2[red_num];
                    temp.SetLocation(mover);
                    ant_turns2[red_num] = temp;
                    red_num= red_num + 2;
                    mover = mover->East;
                    }
                    else {
                    Ant temp = ant_turns2[blue_num]; blue_num;
                    temp.SetLocation(mover);
                    ant_turns2[blue_num] = temp;
                    blue_num = blue_num + 2;
                    mover = mover->East;
                    }
                }
                for (int s = 1; s<table_dimension; s++){mover = mover->West;}
                mover = mover->South;
                if (n == (table_dimension/2)) {mover = mover->South;}
            }
        }
    else //for even dimensions
        {
            Tablenode* mover = table.Root;
            for (int n = 1; n<table_dimension; n++){
                for (int i = 1; i<table_dimension; i++)
                {
                   if (n <= table_dimension/2){
                    Ant temp = ant_turns[red_num];
                    temp.SetLocation(mover);
                    ant_turns[red_num] = temp;
                    red_num= red_num + 2;
                    mover->filled = true;
                    mover = mover->East;
                    }
                    else {
                    Ant temp = ant_turns[blue_num]; blue_num;
                    temp.SetLocation(mover);
                    ant_turns[blue_num] = temp;
                    blue_num = blue_num + 2;
                    mover->filled = true;
                    mover = mover->East;
                    }
            }
            for (int s = 1; s<table_dimension; s++){mover = mover->West;}
            mover = mover->South;
        }
    }

    /** STARTING THE GAME **/
    Tablenode * graveyard = new Tablenode(); //So I won't have to test pointers against NULLS and get a segmentation fault, I have a graveyard
    if (table_dimension%2 == 1)
    {
        while (red_flag == false && blue_flag == false) //Queens are still alive
        {
            for (int q = 0; q < area2; q++) //loop through each Ant so they can take turns
            {
                int r = (rand()%4) +1; //r represents the direction I am going in
                bool ant_block = false; bool Null_dir = false; int ants_index;
                Ant this_ant = ant_turns2[q]; //this ants turn
                string Queen = "Queen", blue = "blue", red = "red";

                if (this_ant.gethierarchy() == Queen){} //bypass queens they cant move

                else if (this_ant.getlocation() == graveyard){} //bypass dead ants

                else if (this_ant.getlocation() == NULL){}

                else if (r==1)
                {
                    for (int i = 0; i<area2; i++)
                    {
                        if (this_ant.getlocation()->North == NULL) {Null_dir = true; break;} //making sure the ant does not move into NULL territory
                        Ant test_ant = ant_turns2[i]; //temporary filler
                        if (test_ant.getlocation() == this_ant.getlocation()->North)
                        {
                                cout << "There is an ant blocking the way.\n"; ant_block = true; ants_index = i;
                        }
                    }// for-loop to compare directions
                    ///////////////////////////////////////////////////////////////////////////////////////
                    if (ant_block == false && Null_dir == false)
                    {
                        this_ant.location = this_ant.location->North;
                        ant_turns2[q] = this_ant;
                    }// if the ant doesn't match anything else in the array

                    ///////////////////////////////////////////////////////////////////////////////////////
                    else if (ant_block == true)
                    {
                        Ant other_ant = ant_turns2[ants_index];
                        if (other_ant.getcolor() == this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen){ cout << "It's your queen.";}
                            if (other_ant.getjoined() == false)
                            {
                                this_ant.joined = true;
                                this_ant.attackpower += other_ant.attackpower;
                                this_ant.location = this_ant.location->North;
                                other_ant.location = graveyard;
                                cout << "Two " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " ants have joined together.\n";
                            }//if team member has no partner
                            else
                            {
                                cout << "A "<< this_ant.getcolor()<< " " << this_ant.gethierarchy()<< " could not move.\n";
                            }//if the team member is neither a queen nor is alone
                        }// If ants are the same color

                        else if (other_ant.getcolor() != this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen)
                            {
                                cout << "A " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " has killed a Queen! His team wins!!\n";
                                if (this_ant.getcolor() == blue) {red_flag = true; break;}
                                else {blue_flag = true; break;}
                            }
                            else if (this_ant.getattackpower() > other_ant.getattackpower())
                            {
                                this_ant.location = this_ant.location->North;
                                ant_turns2[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns2[ants_index] = other_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } //this ant wins
                            else if (this_ant.getattackpower() < other_ant.getattackpower())
                            {
                                this_ant.location = graveyard;
                                ant_turns2[q] = this_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } // this ant loses
                            else if (this_ant.getattackpower() == other_ant.getattackpower())
                            {
                                cout << "Two ants have matching attacks. A die is rolled to see who wins...";
                                int randomnumber = rand()%2;
                                if (randomnumber == 1)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = this_ant.location->North;
                                ant_turns2[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns2[ants_index] = other_ant;
                                }//this ant wins
                                else if (randomnumber == 0)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = graveyard;
                                ant_turns2[q] = this_ant;
                                }//other ant wins
                            } //they both have the same attack
                        }//ants do not have matching color
                    }// if the ant matches something else in the array
                    ///////////////////////////////////////////////////////////////////////////////////////
                } //NORTH
                /*****************************************************************************************************************/
                else if (r==2)
                {
                    for (int i = 0; i<area2; i++)
                    {
                        if (this_ant.location->South == NULL) {Null_dir = true; break;} //making sure the ant does not move into NULL territory
                        Ant test_ant = ant_turns2[i]; //temporary filler
                        if (test_ant.getlocation() == this_ant.getlocation()->South) { ant_block = true; ants_index = i;}
                    }// for-loop to compare directions
                    ///////////////////////////////////////////////////////////////////////////////////////
                    if (ant_block == false && Null_dir == false)
                    {
                        this_ant.location = this_ant.location->South;
                        ant_turns2[q] = this_ant;
                    }// if the ant doesn' match anything else in the array

                    ///////////////////////////////////////////////////////////////////////////////////////
                    else if (ant_block == true && Null_dir == false)
                    {
                        Ant other_ant = ant_turns2[ants_index];
                        if (other_ant.getcolor() == this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen) break;
                            if (other_ant.joined == false)
                            {
                                this_ant.joined = true;
                                this_ant.attackpower += other_ant.attackpower;
                                this_ant.location = this_ant.location->South;
                                other_ant.location = graveyard;
                                cout << "Two " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " ants have joined together.\n";
                            }//if team member has no partner
                            else
                            {
                                cout << "A "<< this_ant.getcolor()<< " " << this_ant.gethierarchy()<< " could not move.\n";
                            }//if the team member is neither a queen nor is alone
                        }// If ants are the same color

                        else if (other_ant.getcolor() != this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen)
                            {
                                cout << "A " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " has killed a Queen! His team wins!!\n";
                                if (this_ant.getcolor() == blue) {red_flag = true; break;}
                                else {blue_flag = true; break;}
                            }
                            else if (this_ant.getattackpower() > other_ant.getattackpower())
                            {
                                this_ant.location = this_ant.location->South;
                                ant_turns2[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns2[ants_index] = other_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } //this ant wins
                            else if (this_ant.getattackpower() < other_ant.getattackpower())
                            {
                                this_ant.location = graveyard;
                                ant_turns2[q] = this_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } // this ant loses
                            else if (this_ant.getattackpower() == other_ant.getattackpower())
                            {
                                cout << "Two ants have matching attacks. A die is rolled to see who wins...";
                                int randomnumber = rand()%2;
                                if (randomnumber == 1)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = this_ant.location->South;
                                ant_turns2[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns2[ants_index] = other_ant;
                                }//this ant wins
                                else if (randomnumber == 0)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = graveyard;
                                ant_turns2[q] = this_ant;
                                }//other ant wins
                            } //they both have the same attack
                        }//ants do not have matching color
                    }// if the ant matches something else in the array
                    ///////////////////////////////////////////////////////////////////////////////////////
                } //SOUTH
                /****************************************************************************************************/
                else if (r==3)
                {
                    for (int i = 0; i<area2; i++)
                    {
                        if (this_ant.location->West == NULL) {Null_dir = true; break;} //making sure the ant does not move into NULL territory
                        Ant test_ant = ant_turns2[i]; //temporary filler
                        if (test_ant.location == this_ant.location->West) { ant_block = true; ants_index = i;}
                    }// for-loop to compare directions
                    ///////////////////////////////////////////////////////////////////////////////////////
                    if (ant_block == false && Null_dir == false)
                    {
                        this_ant.location = this_ant.location->West;
                        ant_turns2[q] = this_ant;
                    }// if the ant doesn' match anything else in the array

                    ///////////////////////////////////////////////////////////////////////////////////////
                    else if (ant_block == true && Null_dir == false)
                    {
                        Ant other_ant = ant_turns2[ants_index];
                        if (other_ant.getcolor() == this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen){}
                            else if (other_ant.getjoined() == false)
                            {
                                this_ant.joined = true;
                                this_ant.attackpower += other_ant.attackpower;
                                this_ant.location = this_ant.location->West;
                                other_ant.location = graveyard;
                                cout << "Two " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " ants have joined together.\n";
                            }//if team member has no partner
                            else
                            {
                                cout << "A "<< this_ant.getcolor()<< " " << this_ant.gethierarchy()<< " could not move.\n";
                            }//if the team member is neither a queen nor is alone
                        }// If ants are the same color

                        else if (other_ant.getcolor() != this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen)
                            {
                                cout << "A " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " has killed a Queen! His team wins!!\n";
                                if (this_ant.getcolor() == blue) {red_flag = true; break;}
                                else {blue_flag = true; break;}
                            }
                            else if (this_ant.getattackpower() > other_ant.getattackpower())
                            {
                                this_ant.location = this_ant.location->West;
                                ant_turns2[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns2[ants_index] = other_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } //this ant wins
                            else if (this_ant.getattackpower() < other_ant.getattackpower())
                            {
                                this_ant.location = graveyard;
                                ant_turns2[q] = this_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } // this ant loses
                            else if (this_ant.getattackpower() == other_ant.getattackpower())
                            {
                                cout << "Two ants have matching attacks. A die is rolled to see who wins...";
                                int randomnumber = rand()%2;
                                if (randomnumber == 1)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = this_ant.location->West;
                                ant_turns2[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns2[ants_index] = other_ant;
                                }//this ant wins
                                else if (randomnumber == 0)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = graveyard;
                                ant_turns2[q] = this_ant;
                                }//other ant wins
                            } //they both have the same attack
                        }//ants do not have matching color
                    }// if the ant matches something else in the array
                    ///////////////////////////////////////////////////////////////////////////////////////
                } //WEST
                /*******************************************************************************************/
                else if (r==4)
                {
                    for (int i = 0; i<area2; i++)
                    {
                        if (this_ant.location->East == NULL) {Null_dir = true; break;} //making sure the ant does not move into NULL territory
                        Ant test_ant = ant_turns2[i]; //temporary filler
                        if (test_ant.location == this_ant.location->East) { ant_block = true; ants_index = i;}
                    }// for-loop to compare directions
                    ///////////////////////////////////////////////////////////////////////////////////////
                    if (ant_block == false && Null_dir == false)
                    {
                        this_ant.location = this_ant.location->East;
                        ant_turns2[q] = this_ant;
                    }// if the ant doesn't match anything else in the array

                    ///////////////////////////////////////////////////////////////////////////////////////
                    else if (ant_block == true && Null_dir == false)
                    {
                        Ant other_ant = ant_turns2[ants_index];
                        if (other_ant.getcolor() == this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen){}
                            else if (other_ant.getjoined() == false)
                            {
                                this_ant.joined = true;
                                this_ant.attackpower += other_ant.attackpower;
                                this_ant.location = this_ant.location->East;
                                other_ant.location = graveyard;
                                cout << "Two " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " ants have joined together.\n";
                            }//if team member has no partner
                            else
                            {
                                cout << "A "<< this_ant.getcolor()<< " " << this_ant.gethierarchy()<< " could not move.\n";
                            }//if the team member is neither a queen nor is alone
                        }// If ants are the same color

                        else if (other_ant.getcolor() != this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen)
                            {
                                cout << "A " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " has killed a Queen! His team wins!!\n";
                                if (this_ant.getcolor() == blue) {red_flag = true; break;}
                                else {blue_flag = true; break;}
                            }
                            else if (this_ant.getattackpower() > other_ant.getattackpower())
                            {
                                this_ant.location = this_ant.location->East;
                                ant_turns2[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns2[ants_index] = other_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } //this ant wins
                            else if (this_ant.getattackpower() < other_ant.getattackpower())
                            {
                                this_ant.location = graveyard;
                                ant_turns2[q] = this_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } // this ant loses
                            else if (this_ant.getattackpower() == other_ant.getattackpower())
                            {
                                cout << "Two ants have matching attacks. A die is rolled to see who wins...";
                                int randomnumber = rand()%2;
                                if (randomnumber == 1)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = this_ant.location->East;
                                ant_turns2[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns2[ants_index] = other_ant;
                                }//this ant wins
                                else if (randomnumber == 0)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = graveyard;
                                ant_turns2[q] = this_ant;
                                }//other ant wins
                            } //they both have the same attack
                        }//ants do not have matching color
                    }// if the ant matches something else in the array
                    ///////////////////////////////////////////////////////////////////////////////////////
                } //EAST

                if (red_flag == true || blue_flag == true){ break;} //command to help break out of the loop
            }// end of the loop through each ants turn
        } // end of the flag while-loop
    }
    else if (table_dimension%2 == 0)
    {
        while (red_flag == false && blue_flag == false) //Queens are still alive
        {
            for (int q = 0; q < area; q++) //loop through each Ant so they can take turns
            {
                int r = (rand()%4) +1; //r represents the direction I am going in
                bool ant_block = false; bool Null_dir = false; int ants_index;
                Ant this_ant = ant_turns[q]; //this ants turn
                string Queen = "Queen", blue = "blue", red = "red";

                if (this_ant.gethierarchy() == Queen){} //bypass queens they cant move

                else if (this_ant.getlocation() == graveyard){} //bypass dead ants

                else if (this_ant.getlocation() == NULL){}

                else if (r==1)
                {
                    for (int i = 0; i<area; i++)
                    {
                        if (this_ant.getlocation()->North == NULL) {Null_dir = true; break;} //making sure the ant does not move into NULL territory
                        Ant test_ant = ant_turns[i]; //temporary filler
                        if (test_ant.getlocation() == this_ant.getlocation()->North)
                        {
                                cout << "There is an ant blocking the way.\n"; ant_block = true; ants_index = i;
                        }
                    }// for-loop to compare directions
                    ///////////////////////////////////////////////////////////////////////////////////////
                    if (ant_block == false && Null_dir == false)
                    {
                        this_ant.location = this_ant.location->North;
                        ant_turns[q] = this_ant;
                    }// if the ant doesn't match anything else in the array

                    ///////////////////////////////////////////////////////////////////////////////////////
                    else if (ant_block == true)
                    {
                        Ant other_ant = ant_turns[ants_index];
                        if (other_ant.getcolor() == this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen){ cout << "It's your queen.";}
                            if (other_ant.getjoined() == false)
                            {
                                this_ant.joined = true;
                                this_ant.attackpower += other_ant.attackpower;
                                this_ant.location = this_ant.location->North;
                                other_ant.location = graveyard;
                                cout << "Two " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " ants have joined together.\n";
                            }//if team member has no partner
                            else
                            {
                                cout << "A "<< this_ant.getcolor()<< " " << this_ant.gethierarchy()<< " could not move.\n";
                            }//if the team member is neither a queen nor is alone
                        }// If ants are the same color

                        else if (other_ant.getcolor() != this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen)
                            {
                                cout << "A " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " has killed a Queen! His team wins!!\n";
                                if (this_ant.getcolor() == blue) {red_flag = true; break;}
                                else {blue_flag = true; break;}
                            }
                            else if (this_ant.getattackpower() > other_ant.getattackpower())
                            {
                                this_ant.location = this_ant.location->North;
                                ant_turns[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns[ants_index] = other_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } //this ant wins
                            else if (this_ant.getattackpower() < other_ant.getattackpower())
                            {
                                this_ant.location = graveyard;
                                ant_turns[q] = this_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } // this ant loses
                            else if (this_ant.getattackpower() == other_ant.getattackpower())
                            {
                                cout << "Two ants have matching attacks. A die is rolled to see who wins...";
                                int randomnumber = rand()%2;
                                if (randomnumber == 1)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = this_ant.location->North;
                                ant_turns[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns[ants_index] = other_ant;
                                }//this ant wins
                                else if (randomnumber == 0)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = graveyard;
                                ant_turns[q] = this_ant;
                                }//other ant wins
                            } //they both have the same attack
                        }//ants do not have matching color
                    }// if the ant matches something else in the array
                    ///////////////////////////////////////////////////////////////////////////////////////
                } //NORTH
                /*****************************************************************************************************************/
                else if (r==2)
                {
                    for (int i = 0; i<area; i++)
                    {
                        if (this_ant.location->South == NULL) {Null_dir = true; break;} //making sure the ant does not move into NULL territory
                        Ant test_ant = ant_turns[i]; //temporary filler
                        if (test_ant.getlocation() == this_ant.getlocation()->South) { ant_block = true; ants_index = i;}
                    }// for-loop to compare directions
                    ///////////////////////////////////////////////////////////////////////////////////////
                    if (ant_block == false && Null_dir == false)
                    {
                        this_ant.location = this_ant.location->South;
                        ant_turns[q] = this_ant;
                    }// if the ant doesn' match anything else in the array

                    ///////////////////////////////////////////////////////////////////////////////////////
                    else if (ant_block == true && Null_dir == false)
                    {
                        Ant other_ant = ant_turns[ants_index];
                        if (other_ant.getcolor() == this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen) break;
                            if (other_ant.joined == false)
                            {
                                this_ant.joined = true;
                                this_ant.attackpower += other_ant.attackpower;
                                this_ant.location = this_ant.location->South;
                                other_ant.location = graveyard;
                                cout << "Two " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " ants have joined together.\n";
                            }//if team member has no partner
                            else
                            {
                                cout << "A "<< this_ant.getcolor()<< " " << this_ant.gethierarchy()<< " could not move.\n";
                            }//if the team member is neither a queen nor is alone
                        }// If ants are the same color

                        else if (other_ant.getcolor() != this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen)
                            {
                                cout << "A " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " has killed a Queen! His team wins!!\n";
                                if (this_ant.getcolor() == blue) {red_flag = true; break;}
                                else {blue_flag = true; break;}
                            }
                            else if (this_ant.getattackpower() > other_ant.getattackpower())
                            {
                                this_ant.location = this_ant.location->South;
                                ant_turns[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns[ants_index] = other_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } //this ant wins
                            else if (this_ant.getattackpower() < other_ant.getattackpower())
                            {
                                this_ant.location = graveyard;
                                ant_turns[q] = this_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } // this ant loses
                            else if (this_ant.getattackpower() == other_ant.getattackpower())
                            {
                                cout << "Two ants have matching attacks. A die is rolled to see who wins...";
                                int randomnumber = rand()%2;
                                if (randomnumber == 1)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = this_ant.location->South;
                                ant_turns[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns[ants_index] = other_ant;
                                }//this ant wins
                                else if (randomnumber == 0)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = graveyard;
                                ant_turns[q] = this_ant;
                                }//other ant wins
                            } //they both have the same attack
                        }//ants do not have matching color
                    }// if the ant matches something else in the array
                    ///////////////////////////////////////////////////////////////////////////////////////
                } //SOUTH
                /****************************************************************************************************/
                else if (r==3)
                {
                    for (int i = 0; i<area; i++)
                    {
                        if (this_ant.location->West == NULL) {Null_dir = true; break;} //making sure the ant does not move into NULL territory
                        Ant test_ant = ant_turns[i]; //temporary filler
                        if (test_ant.location == this_ant.location->West) { ant_block = true; ants_index = i;}
                    }// for-loop to compare directions
                    ///////////////////////////////////////////////////////////////////////////////////////
                    if (ant_block == false && Null_dir == false)
                    {
                        this_ant.location = this_ant.location->West;
                        ant_turns[q] = this_ant;
                    }// if the ant doesn' match anything else in the array

                    ///////////////////////////////////////////////////////////////////////////////////////
                    else if (ant_block == true && Null_dir == false)
                    {
                        Ant other_ant = ant_turns[ants_index];
                        if (other_ant.getcolor() == this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen){}
                            else if (other_ant.getjoined() == false)
                            {
                                this_ant.joined = true;
                                this_ant.attackpower += other_ant.attackpower;
                                this_ant.location = this_ant.location->West;
                                other_ant.location = graveyard;
                                cout << "Two " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " ants have joined together.\n";
                            }//if team member has no partner
                            else
                            {
                                cout << "A "<< this_ant.getcolor()<< " " << this_ant.gethierarchy()<< " could not move.\n";
                            }//if the team member is neither a queen nor is alone
                        }// If ants are the same color

                        else if (other_ant.getcolor() != this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen)
                            {
                                cout << "A " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " has killed a Queen! His team wins!!\n";
                                if (this_ant.getcolor() == blue) {red_flag = true; break;}
                                else {blue_flag = true; break;}
                            }
                            else if (this_ant.getattackpower() > other_ant.getattackpower())
                            {
                                this_ant.location = this_ant.location->West;
                                ant_turns[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns[ants_index] = other_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } //this ant wins
                            else if (this_ant.getattackpower() < other_ant.getattackpower())
                            {
                                this_ant.location = graveyard;
                                ant_turns[q] = this_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } // this ant loses
                            else if (this_ant.getattackpower() == other_ant.getattackpower())
                            {
                                cout << "Two ants have matching attacks. A die is rolled to see who wins...";
                                int randomnumber = rand()%2;
                                if (randomnumber == 1)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = this_ant.location->West;
                                ant_turns[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns[ants_index] = other_ant;
                                }//this ant wins
                                else if (randomnumber == 0)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = graveyard;
                                ant_turns[q] = this_ant;
                                }//other ant wins
                            } //they both have the same attack
                        }//ants do not have matching color
                    }// if the ant matches something else in the array
                    ///////////////////////////////////////////////////////////////////////////////////////
                } //WEST
                /*******************************************************************************************/
                else if (r==4)
                {
                    for (int i = 0; i<area; i++)
                    {
                        if (this_ant.location->East == NULL) {Null_dir = true; break;} //making sure the ant does not move into NULL territory
                        Ant test_ant = ant_turns[i]; //temporary filler
                        if (test_ant.location == this_ant.location->East) { ant_block = true; ants_index = i;}
                    }// for-loop to compare directions
                    ///////////////////////////////////////////////////////////////////////////////////////
                    if (ant_block == false && Null_dir == false)
                    {
                        this_ant.location = this_ant.location->East;
                        ant_turns[q] = this_ant;
                    }// if the ant doesn't match anything else in the array

                    ///////////////////////////////////////////////////////////////////////////////////////
                    else if (ant_block == true && Null_dir == false)
                    {
                        Ant other_ant = ant_turns[ants_index];
                        if (other_ant.getcolor() == this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen){}
                            else if (other_ant.getjoined() == false)
                            {
                                this_ant.joined = true;
                                this_ant.attackpower += other_ant.attackpower;
                                this_ant.location = this_ant.location->East;
                                other_ant.location = graveyard;
                                cout << "Two " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " ants have joined together.\n";
                            }//if team member has no partner
                            else
                            {
                                cout << "A "<< this_ant.getcolor()<< " " << this_ant.gethierarchy()<< " could not move.\n";
                            }//if the team member is neither a queen nor is alone
                        }// If ants are the same color

                        else if (other_ant.getcolor() != this_ant.getcolor())
                        {
                            if (other_ant.gethierarchy() == Queen)
                            {
                                cout << "A " << this_ant.getcolor() << " " << this_ant.gethierarchy() << " has killed a Queen! His team wins!!\n";
                                if (this_ant.getcolor() == blue) {red_flag = true; break;}
                                else {blue_flag = true; break;}
                            }
                            else if (this_ant.getattackpower() > other_ant.getattackpower())
                            {
                                this_ant.location = this_ant.location->East;
                                ant_turns[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns[ants_index] = other_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } //this ant wins
                            else if (this_ant.getattackpower() < other_ant.getattackpower())
                            {
                                this_ant.location = graveyard;
                                ant_turns[q] = this_ant;
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                            } // this ant loses
                            else if (this_ant.getattackpower() == other_ant.getattackpower())
                            {
                                cout << "Two ants have matching attacks. A die is rolled to see who wins...";
                                int randomnumber = rand()%2;
                                if (randomnumber == 1)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has killed a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = this_ant.location->East;
                                ant_turns[q] = this_ant;
                                other_ant.location = graveyard;
                                ant_turns[ants_index] = other_ant;
                                }//this ant wins
                                else if (randomnumber == 0)
                                {
                                cout << "A " << this_ant.getcolor()<< " " << this_ant.gethierarchy() << " has been killed by a " << other_ant.getcolor() << " " << other_ant.gethierarchy() << ".\n";
                                this_ant.location = graveyard;
                                ant_turns[q] = this_ant;
                                }//other ant wins
                            } //they both have the same attack
                        }//ants do not have matching color
                    }// if the ant matches something else in the array
                    ///////////////////////////////////////////////////////////////////////////////////////
                } //EAST

                if (red_flag == true || blue_flag == true){ break;} //command to help break out of the loop
            }// end of the loop through each ants turn
        } // end of the flag while-loop
    } //end of else even dimensions
    return 0;
}
