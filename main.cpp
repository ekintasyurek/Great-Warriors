//////////////////////////////////
/*          <Ekin Tasyurek>         */
/*          <150190108>           */
//////////////////////////////////

#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;


class Land{
    string name;
    string holding;
public:
    Land();//default constructor
    Land(string, string);  //constructor for taking the name and the holding attributes
    Land(Land&); //copy constructor

    Land* next = nullptr;

    string getName() const{return name;}//getter
    string getHolding() const{return holding;}//getter
    void setName(string newName){name=newName;}//setter
    void setHolding(string newHolding){name=newHolding;}//setter

};


class Character{
    string name;
    int manpower;
    int gold;
    int numOfLands;
    Land* lands;  //head of Lands linked list, the character has
public:
    Character();//default constructor
    Character(string, int, int, int); //constructor
    Character(Character&);//copy constructor
    //~Character();//destructor

    void getTaxes(Character*);// collect taxes for the character
    void addLand(Land);//add a land to the character
    void removeLand(string);//remove a land from the character

    string getName() {return name;}//getter
    int getManpower(){return manpower;}//getter
    int getGold(){return gold;}//getter
    int getNumOfLands(){return numOfLands;}//getter
    void setGold(int newGold){gold=newGold;}//setter
    void setManpower(int newManpower){manpower=newManpower;}//setter
    Land* getLands(){return lands;}//getter
};


class CharacterList{
    int size;
    Character *characters;

    friend void listCharacters(CharacterList&);//print all characters’ name
    friend void listLands(CharacterList&);//print all lands’ name, holding and the owner
public:
    CharacterList();//default constructor
    //~CharacterList();//destructor

    void addCharacter(Character);//add a character to the array
    void delCharacter(string);// delete a character from the array
    Character& getPlayer(string);//get reference to the player
    Character& getLandOwner(string);// get owner of the specified land based on lands’ name

    Character getCharacters(){return *characters;}//getter
    int getSize(){return size;}//getter
    void setCharacters(Character *newCharacter){characters = newCharacter;}

    void update(Character newCharacter){
        for(int i=0; i<size; i++){
            if(newCharacter.getName()==characters[i].getName()){
                characters[i]=newCharacter;
            }
        }
    }

};



Land::Land() {
    name = ' ';
    holding = ' ';
}

Land::Land(string newName, string newHolding) {
    name=newName;
    holding=newHolding;
};

Land::Land(Land &copyLand) {
    name=copyLand.name;
    holding=copyLand.holding;
};

Character::Character() {
    this->name= ' ';
    this->manpower=0;
    this->gold=0;
    this->numOfLands=0;
    this->lands= nullptr;
}

Character::Character(string newName, int newManpower, int newGold, int newNumOfLands) {
    this->name=newName;
    this->manpower=newManpower;
    this->gold=newGold;
    this->numOfLands=newNumOfLands;
    this->lands = nullptr;
};

Character::Character(Character& copyCharacter) {
    this->name=copyCharacter.name;
    this->manpower=copyCharacter.manpower;
    this->gold=copyCharacter.gold;
    this->numOfLands=copyCharacter.numOfLands;
    this->lands = copyCharacter.lands;
};

/*Character::~Character() {
    delete [] lands;
};*/

void Character::getTaxes(Character *player) {

    int village=0, city=0, castle=0;

    Land* p;
    for(p = player->getLands(); p!= nullptr; p= p->next){
        if(p->getHolding()=="village"){
            village++;
        }
        if(p->getHolding()=="city"){
            city++;
        }
        if(p->getHolding()=="castle"){
            castle++;
        }
    }

    int tax=5*village+7*castle+10*city;
    player->setGold(tax+player->getGold());

};


void Character::addLand(Land newLand) {

    Land *p= new Land;
    p->setName(newLand.getName());
    p->setHolding(newLand.getHolding());
    p->next=nullptr;

    if(lands==nullptr){
        lands=p;
        return;
    }

    Land *ptr=lands;

    while(ptr->next){
        ptr=ptr->next;
    }

    ptr->next=p;

};

void Character::removeLand(string newLandName) {
    Land* ptrLand = lands;
    Land* ptrLand2= lands;
    Land* ptrLand3=lands;
    numOfLands --;

    if(lands->getName()==newLandName){
        lands=lands->next;
        ptrLand3->next= nullptr;
        delete ptrLand3;
    }

    else{
        while(ptrLand!=nullptr){
            if(newLandName==ptrLand->getName()){
                ptrLand2->next=ptrLand->next;
                ptrLand3=ptrLand;
                ptrLand3->next= nullptr;
                delete ptrLand3;
            }

            ptrLand2=ptrLand;
            ptrLand=ptrLand->next;


        }

        delete ptrLand3;
    }
};

CharacterList::CharacterList() {
    this->size = 0;
    this->characters = new Character [1];
};

/*CharacterList::~CharacterList() {
    delete []characters;
};*/

void CharacterList::addCharacter(Character newCharacter) {
    if (size == 0){
        size = 1;
        characters[0] = newCharacter;
        return;
    }

    CharacterList *newList = new CharacterList;
    this->size++;
    newList->size = this->size;
    newList->characters = new Character[this->size];
    for(int i = 0; i < this->size-1 ;i++){
        newList->characters[i] = this->characters[i];
    }
    newList->characters[this->size-1] = newCharacter;

    delete[] characters;

    this->characters = new Character[this->size];
    for(int i = 0; i < this->size ;i++){
        this->characters[i] =  newList->characters[i];
    }

    delete[] newList->characters;
    delete newList;

};

void CharacterList::delCharacter(string characterName) {
    if(this->size == 1){
        delete[] characters;
        this->size=0;
        return;
    }

    CharacterList *p = new CharacterList;

    for(int i = 0; i < this->size-2; i++){
        if(characterName == this->characters[i].getName()){
            continue;
        }
        p->addCharacter(this->characters[i]);
    }
    for(int i = 0; i < this->size-1; i++){
        this->characters[i] = p->characters[i];
    }
    this->size--;

};

Character&  CharacterList::getPlayer(string characterName) {
    for(int i = 0; i<size+1; i++){
        if(this->characters[i].getName()== characterName){
            return this->characters[i];
        }
    }

    return characters[0];
};

Character& CharacterList::getLandOwner(string characterName) {
    for(int i=0; i<size+1; i++){
        Land *land;
        land=characters[i].getLands();
        if(land->getName()!=characterName){
            land->next=land->next->next;
        }
        else{
            return getPlayer(this->characters[i].getName());
        }
    }

    return characters[0];
};

void listCharacters(CharacterList&);
void listLands(CharacterList&);
void readData(string, CharacterList&);
void printGameMenu();
bool endOfTurn(Character&, int);

int main() {
    cout << "Welcome to the Great Warriors. Create your character and attack other lands to be a great warrior.\n" << endl;

    CharacterList charList;             // list object to store the characters

    string fileName = "characters.txt"; // read characters.txt file
    readData(fileName, charList);

    /* creating player's character */
    string name, land, general;
    cout << "Enter your name: ";
    cin >> name;

    cout << "Enter name of your capital: ";
    cin >> land;

    cout << "Enter name of your general: ";
    cin >> general;


    ///// FILL HERE /////

    /*  Create your constant general object and your own character object,
    then add your character into characters list */


    Land *myLand= new Land(land,"village");
    Character *player = new Character(name, 3, 20, 1);
    player->addLand(*myLand);

    charList.addCharacter(*player);

    ///// FILL HERE /////


    // In-game loop
    int choice = 0, round = 0;
    while (choice != 6) {
        printGameMenu();

        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "You have rested in your palace." << endl;
                cout << "You've talked with your general " << general /* get the name of general*/ << "." << endl;

                round++;
                break;
            }
            case 2: {
                listLands(charList);
                cout << "Enter name of the land to attack." << endl;

                string land;
                cin >> land;

                ///// FILL HERE /////

                /*	Get the attacked player and execute the attack considering the manpower each side has:

                    -	If you won, attacked side will lose all manpower and the attacked land will be yours.
                        You will also lose some manpower (as much as attacked lose).
                        Print this: cout << "You've won the battle and conquered " << land << "." << endl;

                    -	If you lose, you will lose all your manpower.
                        Print this: cout << "You've lost the battle and " << __number of manpower you lost__ << " manpower." << endl;
                */

                Character attackedPlayer = charList.getLandOwner(land);
                if(attackedPlayer.getManpower()<=player->getManpower()){

                    cout << "You've won the battle and conquered " << land << "." << endl;

                    Land *ptr=attackedPlayer.getLands();
                    while(ptr->getName()!=land){
                        ptr=ptr->next;
                    }
                    string attackedLandHolding=ptr->getHolding();
                    Land gainedLand(land, attackedLandHolding);

                    player->addLand(gainedLand);
                    attackedPlayer.removeLand(land);

                    player->setManpower(player->getManpower()-attackedPlayer.getManpower());
                    attackedPlayer.setManpower(0);

                    charList.update(attackedPlayer);
                    charList.update(*player);

                    if(attackedPlayer.getNumOfLands()==0){
                        charList.delCharacter(attackedPlayer.getName());
                    }
                }
                else{
                    cout << "You've lost the battle and " << player->getManpower() << " manpower." << endl;
                    player->setManpower(0);
                    charList.update(*player);
                }

                ///// FILL HERE /////

                round++;
                break;
            }
            case 3:
                cout << "How much manpower do you need? (1 manpower=5 gold)" << endl;

                int order;
                cin >> order;

                ///// FILL HERE /////

                /* Check if you have enough money to get the requested manpower:

                    - 	If you have, you got the manpower you want.
                        Print this: cout << "Order successful. You have " << __number of manpower you have after purchase__ << " manpower." << endl;

                    -	If you do not, print this: cout << "You do not have enough money." << endl;
                */

                if(player->getGold()>=(order*5)){
                    player->setManpower(player->getManpower()+order);
                    player->setGold(player->getGold()-(order*5));
                    cout << "Order successful. You have " << player->getManpower() << " manpower." << endl;
                }
                else{
                    cout << "You do not have enough money." << endl;
                }

                charList.update(*player);

                ///// FILL HERE /////

                round++;
                break;
            case 4:
                listCharacters(charList);
                break;
            case 5:
                listLands(charList);
                break;
            case 6:
                return 0;
            default:
                cout << "You entered an invalid value. Try again." << endl;
        }

        ///// FILL HERE /////

        /*	Check if the game is over in two cases:

            -	Call the endOfTurn function which is defined below in the code.
                endOfTurn function executes the necessary end of turn process and
                returns a bool value which indicates if you can continue the game or not.

            -	Terminate the program if you are the only great warrior left.
                Print this: cout << __your player name__ << " is the only great warrior now." << endl;
        */

        endOfTurn(*player,round);


        if(charList.getSize()==1){
            cout << player->getName() << " is the only great warrior now." << endl;
        }

        ///// FILL HERE /////
    }
}

void readData(string fileName, CharacterList& charList) {

    fstream dataFile(fileName.c_str());

    if (dataFile.is_open()) {

        string word;
        while (dataFile >> word) {

            string name, title;
            int money, manpower, numOfLands;

            name = word;
            dataFile >> manpower;
            dataFile >> money;
            dataFile >> numOfLands;

            ///// FILL HERE /////

            /* Create a new character with read data */

            Character newCharacter(name, manpower, money, numOfLands);

            ///// FILL HERE /////

            string landName, holding;

            for (int i = 0; i < numOfLands; i++) {
                dataFile >> landName;
                dataFile >> holding;

                ///// FILL HERE /////

                /* Create a new land object with read data and assign the land to the character you have created */

                Land newLand(landName, holding);
                newCharacter.addLand(newLand);

                ///// FILL HERE /////
            }

            ///// FILL HERE /////

            /* Add the character into character list */

            charList.addCharacter(newCharacter);

            ///// FILL HERE /////

        }

        dataFile.close();
    }
    else cout << "Unable to open the file" << endl;

    return;
}

void printGameMenu() {
    cout << endl;
    cout << "1. Stay in your palace" << endl;
    cout << "2. Attack to a land" << endl;
    cout << "3. Buy manpower" << endl;
    cout << "4. List characters" << endl;
    cout << "5. List lands" << endl;
    cout << "6. Exit" << endl;
    cout << endl;
}

void listCharacters(CharacterList& charList) {
    cout << endl;

    ///// FILL HERE /////

    /* Print out the names of each character in character list in a loop */

    for(int i=0; i<charList.size; i++){
        cout<<charList.characters[i].getName() << endl;
    }

    ///// FILL HERE /////

}

void listLands(CharacterList& charList) {
    cout << endl;

    ///// FILL HERE /////

    /*	Loop over each character in characters list and print out their lands in following format:
        cout << __name of land__ << " " << __type of land__ << " owned by " << __name of player__ << endl;
        (i.e. Gotham city owned by Batman)
    */


    for(int i = 0; i < charList.getSize();i++){
        Land *p = charList.characters[i].getLands();
        for(int j = 0; j< charList.characters[i].getNumOfLands();j++){
            cout<<p->getName()<< " "<<p->getHolding()<<" owned by "<<charList.characters[i].getName()<<endl;

            if(p -> next != NULL){
                p = p -> next;
            }
        }

    }


///// FILL HERE /////

cout << endl;
}

bool endOfTurn(Character& player, int round) { //return a bool value that indicates if the game is over or not.

    ///// FILL HERE /////

    /* End of turn evaluations:
        -	Collect taxes and feed soldiers

        -	Check the number of lands you have and if you do not have any lands left, the game is over
            Print this:	cout << "You are no longer a great warrior. You survived " << round << " turns." << endl;
                        cout << endl;
                        cout << "GAME OVER." << endl;

        -	Check the number of manpower you have and if you do not have any manpower left, you lose one of your lands randomly.
            Print this:	cout << "You lost one of your lands to rebellions since you don't have enough army." << endl;

        -	Check the amount of money you have, if you do not have enough money to feed your soldiers you lose
            the soldiers that you cannot feed. 1 gold for each soldier is needed. If you have 5 gold and 6 soldiers 1 soldier will
            run away from your army.
            Print this: cout << __number of runaway soldiers__ << " soldiers run away from your army because you don't have enough gold to feed them." << endl;

        -	At last, print your status in the following format:
            cout << "Turn " << round << ": " << " " << __name of your player__ << " has " << __number of lands you have__
        << " land(s), " << __number of manpower you have__ << " manpower and " << __number of golds you have__ << " golds." << endl;

    */

    player.getTaxes(&player);

    int playersNumOfLands= player.getNumOfLands();
    if(playersNumOfLands==0){
        cout << "You are no longer a great warrior. You survived " << round << " turns." << endl;
        cout << endl;
        cout << "GAME OVER." << endl;
        return false;
    }

    int playersManpower=player.getManpower();
    if(playersManpower==0){
        Land *landToRemove;
        landToRemove=player.getLands();
        player.removeLand(landToRemove->getName());
        cout << "You lost one of your lands to rebellions since you don't have enough army." << endl;
    }

    if(player.getGold()<player.getManpower()){
        int runawaySoldiers=player.getManpower()-player.getGold();
        player.setManpower(player.getManpower()-runawaySoldiers);
        cout << runawaySoldiers << " soldiers run away from your army because you don't have enough gold to feed them." << endl;
    }

    cout << "Turn " << round << ": " << " " << player.getName() << " has " << player.getNumOfLands()
         << " land(s), " << player.getManpower() << " manpower and " << player.getGold() << " golds." << endl;

    return true;
    ///// FILL HERE /////

}





