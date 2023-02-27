//Skeleton Code by: Jorge Fonseca
//Assignment Created by Jorge Fonseca
//All Copyrights to Jorge Fonseca, Do not share outside of UNLV CS202 class.

//########This file will parse gadget.go and build a header file that has
//all our gadget classes and also the magicfunction######

//"Shut me down, Machines making machines, how peverse!" -C3PO
/* Sample:
class Binoculars : public gadget_t{
public:
    Binoculars() : gadget_t("Binoculars"){}
    void gogogadget(){
        std::cout << "Binoculars lower down out of his hat and over his eyes." << endl;
    }
};
//Also need magic function, for that makes Massive Meme If Statement that basically 
//also uses the file to generate one case for each gadget
void magicfunction(gadget_t **g, string gadgetName){
    if(gadgetName == "Binoculars"){
        *g = new Binoculars;
        return;
    }
    ///...
    if(gadgetName == "Springs"){
        *g = new Springs;
        return;
    }
    std::cout << "ERROR: Could not add Invalid Gadget: '" << gadgetName << "'" << endl;
}
*/
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

struct gadget {
    string name;
    string description;
};

vector<gadget> readFile(string);
void buildClasses(ofstream&, vector<gadget>);
void buildFunction(ofstream&, vector<gadget>);

int main(int argc, char **argv){
    if(argc != 3){
        cout << "ERROR: Usage: [Executeable] [Gadget File] [Header File Name]\n"
             << "Sample: ./a.out gadgets.source gadgets.h" << endl;
        return 1;
    }
    vector<gadget> list = readFile(argv[1]);
    //for(auto& i : list)cout << i.name << "\n" << i.description << endl;//Debug
    ofstream fout; fout.open(argv[2]);
    buildClasses(fout, list);
    buildFunction(fout, list);
    fout.close();
    return 0;
}

vector<gadget> readFile(string fname){
    ifstream f; f.open(fname.c_str());
    vector<gadget> list;
    string tempName;
    getline(f, tempName); //throw away first line

    f >> tempName; //skips Gadget

    while(!f.eof()){
    
        gadget newGadget; 

        f >> tempName; //grabs the name
    
        newGadget.name = tempName; //stores name

        getline(f, tempName, ':'); //throwaway

        getline(f, tempName); //grabs description

        newGadget.description = tempName; //stores description

        list.push_back(newGadget); //pushes new gadget back
              
        f >> tempName; //skips Gadget
    }
    f.close();
    return list;
}

void buildClasses(ofstream &fout, vector<gadget> gadgets){
    //YOUR CODE HERE

    //Go through the vector and generate a class for each of the gadgets.

     /*Each generated class should use the name of the gadget as the name of the class
    and inherit from the type gadget_t with public inheritance
    The declaration of the class should contain two functions: a constructor and a function
    that couts the description of this gadget. The constructor should call the gadget_t
    constructor using the name of the gadget as a string. The other function should be
    called gogogadget(), and is the function that actually uses the gagdet. This will implement
    the abstract virtual gogogadget from the gadget_t class. This should print the
    description of this gadget as a string..*/
    

    //Example taken from the PDF. This would be the class generated for a gadget with the name "Binoculars"
    //and the description is the part being cout'd. You can copy paste this and fill in the blanks with
    //Your variables from the vector.

    /* Sample:
    class Binoculars : public gadget_t{
    public:
    Binoculars() : gadget_t("Binoculars"){}
    void gogogadget(){
        std::cout << "Binoculars lower down out of his hat and over his eyes." << endl;
    }
    };*/

    //builds classes
    for (int j = 0; j < gadgets.size(); j++) {
        //each gadget
        fout << "class " << gadgets[j].name << " : public gadget_t{" << endl;
        fout << "public:" << endl;
        fout << gadgets[j].name << "() : gadget_t(\"" << gadgets[j].name << "\"){}" << endl;
        fout << "void gogogadget(){" << endl;
        fout << "std::cout << \"" << gadgets[j].description << "\" << endl;" << endl;
        fout << "}" << endl;
        fout << "};" << endl;
    }



}

void buildFunction(ofstream &fout, vector<gadget> gadgets){
    //YOUR CODE HERE

    /*This function should build the magicfunction that instantiates one of the classes you
    generated in buildClasses() from a string. See the top of this file for an explanation.
    I would recommend having a default case that sets g to NULL if the strings don't match.

    magicfunction should set a gadget_t type pointer and should be at global scope
    (not contained in a class).
    
    For the previous example, this would generate:

        if(gadgetName == "Binoculars"){
        *g = new Binoculars;
        return;
    }

    in a big if statement chain. You can rewrite this as a switch if you prefer.
    */

    /*void magicfunction(gadget_t * *g, string gadgetName) {
        if (gadgetName == "Binoculars") {
            *g = new Binoculars;
            return;
        }
        ///...
        if (gadgetName == "Springs") {
            *g = new Springs;
            return;
        }
        std::cout << "ERROR: Could not add Invalid Gadget: '" << gadgetName << "'" << endl;
    }
    */
    
    //the magic function
    fout << "void magicfunction(gadget_t **g, string gadgetName) { " << endl;
        
        //output loop
        for (int k = 0; k < gadgets.size(); k++) {

            fout << "if(gadgetName == \"" << gadgets[k].name << "\"){" << endl;
            fout << "*g = new " << gadgets[k].name << ";" << endl;
            fout << "return;" << endl;
            fout << "}" << endl;
            fout << endl;

        }

        //errors if gadget name is not recognized or valid
        fout << "std::cout << \"ERROR: Could not add Invalid Gadget: \'\" << gadgetName << \"\'\" << endl;" << endl;
        fout << "}" << endl;
}
