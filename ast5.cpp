//Skeleton Code by: Jorge Fonseca
//Assignment Created by Jorge Fonseca
//All Copyrights to Jorge Fonseca, Do not share outside of UNLV CS202 class.
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//Everything is an entity type. They're like midichlorians
class ent_t{
    public:
        ent_t(string name) : name(name) {}
        virtual ~ent_t() = 0; //Virtual Destructor
        string getName() const {return name;}
    private:
        string name;
};
ent_t::~ent_t(){} //This makes it so you cannot make ent obj but you can of any derived class :D

//Abstract Super Class of All Gadget types
class gadget_t : public ent_t{
public:
    gadget_t(string name) : ent_t(name){}
    //YOUR CODE HERE: One line of code where you make a PURE VIRTUAL void function called gogogadget() with no parameters.
    virtual void gogogadget() = 0; //Pure Virtual Function
};

//Inspector Gadget Type
class IG_t : public ent_t {
public:
    IG_t(int l = 3, int w = 3, string file = "gadgets.list") : ent_t("Inspector Gadget")
    {
        //YOUR CODE HERE (Finish the Constructor)
        //Allocate the gadgets array using l and w
        /*Open the gadgets.list file and read all of the gadgets. Use the magicfunction to instantiate 
        each of the gadgets given in the file. Create a gadget_t pointer and have it be set in magic pointer.
        Then put the object being pointed to into the gadgets array*/
        
        //allows other functions to use l and w
        this->l = l;
        this->w = w;

        //declare new gadget array
        gadgets = new gadget_t**[w];

        //declare second dimension of array
        for (int i = 0; i < w; i++) {

            gadgets[i] = new gadget_t*[l];
        }
        
        //initialize gadget array to null
        for (int r = 0; r < w; r++) {

            for (int c = 0; c < l; c++) {

                gadgets[r][c] = NULL;

            }
        }

        

        build(file);
    }

    //build function declaration
    void build(string);

    ~IG_t(){

        //deallocates array after code runs
        for (int k = 0; k < l; k++) 
        {
            for (int y = 0; y < w; y++) 
            {
                delete gadgets[k][y];
            }
            delete[] gadgets[k];
        }
        delete[] gadgets;

    }

    void gogogadget(string);
    void printGadgets(); //Prints all gadget names
    void gogogadgetALL(); //Triggers all gadgets lol
private:
    int l,w;
    gadget_t ***gadgets;
    static bool upgrade; //Whether or not this is the first time we are reading gadgets
};

bool IG_t::upgrade = false;

void IG_t::printGadgets(){ //Prints all gadget names
    cout << "List of Currently Available Gadgets:" << endl;
    //YOUR CODE HERE

    //outer layer loop
    for (int x = 0; x < w; x++) {

        //inner layer loop
        for (int y = 0; y < l; y++){

            if (gadgets[x][y] != NULL) {
                
                //output name with commas
                cout << gadgets[x][y]->getName() << ", ";

            }

        }
        cout << endl;
    }
    cout << endl;
}

void IG_t::gogogadgetALL(){ //Triggers all gadgets lol
    cout << "Go go Gadget All!\n" << endl;
    //YOUR CODE HERE

    //outer layer loop
    for (int x = 0; x < w; x++) {

        cout << endl; 

        //inner layer loop
        for (int y = 0; y < l; y++) {

            //display name, then display gadget description
            if (gadgets[x][y] != NULL) {

                //display name and description
                cout << gadgets[x][y]->getName() << ":" << endl;
                 gadgets[x][y]->gogogadget();

            }
            
            cout << endl;
        }
    }

}

#include "gadgets.h"  //THIS INCLUDES THE AUTO GENERATED FILE

//Opens Gadget File and Builds List. It is a separate function incase we want
//to upgrade gadgets mid way. 
void IG_t::build(string file){
 
    //Read gadgets from files. If this is not the first time reading, print "Hmm... upgrades"
    //Otherwise, set the upgrade flag to true after adding to the array with the items
    //YOUR CODE HERE

    ifstream readFile;  //new inputfil
    string tempRead;    //temporary file for reading and passing

    //open file
    readFile.open(file);

    //check file open
    if (!readFile.is_open()) {

        //error if file didnt open, faulty file
        cout << "ERROR: The input file did not open! Exiting program..." << endl;

    }
    else 
    {
        //if program has read gadgets already
        if (upgrade) {

            cout << "Hmm...upgrades." << endl;

        }

        //read gadgets
        for (int x = 0; x < l && !readFile.eof(); x++) {

            for (int y = 0; y < w && !readFile.eof(); y++) {

                //deallocatation
                if (gadgets[x][y] != NULL) {

                    delete gadgets[x][y];
                }
                //allocation
                getline(readFile, tempRead);

                //check for eof trigger
                if (readFile.eof()) {
                    return;
                }

                //call function to make new gadgets in array
                magicfunction(&gadgets[x][y], tempRead);


            }

            //sets upgrades to true for read
            upgrade = true;
        }
    }

}

//For calling go-go gadget. We need to search which pointer, 
//if any are pointing to a gadget by this name
void IG_t::gogogadget(string match){
    //Search through the gadgets array and try to find a gadget that has a name that matches the
    //given one. If you find it, use its gogogadget() function.
    
    //YOUR CODE HERE

    //outer loop
    for (int x = 0; x < l; x++) {

        //inner loop
        for (int y = 0; y < w; y++) {

            //if gadget is not NULL
            if (gadgets[x][y] != NULL) {

                //if the names match , activate gadget
                if (gadgets[x][y]->getName() == match) {

                    cout << "Go Go Gadget " << gadgets[x][y]->getName() << ":";
                    gadgets[x][y]->gogogadget();

                }
            }
        }
    }
}

int main() 
{
    Binoculars Test;
    IG_t InspectorGadget;
    InspectorGadget.gogogadget("Binoculars");
    InspectorGadget.printGadgets(); //Prints all gadget names
    InspectorGadget.build("gadgets.list2"); //This will cout 'hmm upgrades' 
    //cause you are calling build more than once. Use Static for that.
    //ent_t e("Test"); //Should give an error by design
    InspectorGadget.gogogadgetALL(); //Triggers all gadgets lol
    InspectorGadget.gogogadget("Plane");
    InspectorGadget.gogogadget("Parachute");
    InspectorGadget.gogogadget("Wings");
    InspectorGadget.gogogadget("Glider");
    InspectorGadget.gogogadget("Chopper");
    //Now we are ready to take down THE CLAW! :D GO GO GADGET GG EZ!
    return 0;
}
