#include <string>
#include <iostream>

using namespace std;


//Node struct, contains a data value to be used for program name.
struct Node {
    Node (string value) : data(value), next(NULL) {}
    string data;
    Node* next;
};

//List struct, contains all of the methods for manipulating the list, including best and worst fit.
struct List {
    //Decalres integers of the best and worst fit location.
    int bestFit;
    int worstFit;
    //Head and Tail pointers.
    Node *head;
    Node *tail;

    //Constructor for list given a value.
    List(string value) {
        head=NULL;
        tail = NULL;
        head = new Node(value);
        tail = head;
    }
    //Default constructor
    List() {
        head =NULL;
        tail = NULL;
        for (int j = 0; j < 32; j++) {
            insert("free");
        }
    }

    //Method for returning the size of the list.
    int sizeOfList() {
        int number = 0;
        Node *position = head;
        //While loop goes through the list, going from pointer to pointer, until it reaches a null pointer signaling the end of the lsit.
        while (position != NULL) {
            position = position->next;
            ++number;
        }
        //return statement gives back the size of the list to the method upon which sizeOfList was called.
        return number;
    }
    //Method which returns a boolean value, signaling that the size of the list is zero or not.
    bool empty(){
        return (sizeOfList() ==0);

    }
    //Method for inserting a value into the list.
    void insert(string value){
        //If the head is null, it inserts the value into the pointer.
        if(head == NULL)
        {
            head = new Node(value);
            tail = head;
        }
        else
        {
            tail -> next = new Node(value);
            tail = tail -> next;
        }
    }

    //Method for printing the number of fragments present in the list.
    void printFragments() {
        //Declares the variables needed for the method.

        Node *position = head;

        int number = 0;
        int freeSpots=0;



        //Loop to go through each entry of the list. and increment the number variable.
        for (int j = 0; j < 31; j++) {
            if (position->data == "free") {
                if (position->next->data != "free") {
                    number++;
                }
                freeSpots +=1;
            }
            position = position->next;


        }


        if (freeSpots>0)
            number +=1;
        //Prints out the number of fragments to the console.
        cout << "Fragments: " << number << endl;
    }


    //Method for printing out the entire list.
    void printList(){
        //If empty list, prints out empty to console.
        if (head == NULL){
            cout<<"Empty";
            return;
        }
        Node* position = head;
        {

        }
        //while loop to go through the list and print out the entire list.
        while (position!=NULL){
            for(int j = 0; j<8; j++){
                //If the position doesn't equal null, it prints out the data variable stored.
                if(position != NULL){
                    if(position->data != "free"){
                        cout<< position-> data<<"     ";
                    }
                    else {
                        cout<< position-> data<<"   ";
                    }
                    position = position ->next;
                }
            }
            cout<<"\n";
        }


    }
    //Method returns a boolean and is able to remove values from the list.
    bool remove(string value){
        Node * position = head;
        bool programExist = false;

        //goes through the list and if the value at the position in the list is equal to the value passed into the method
        //then the value is set to free.
        for(int j = 0; j<32; j++){
            if(position->data == value){
                position->data = "free";
            programExist= true;
            }
            if(position->next != NULL){
                position = position->next;
            }
        }
        //Returns false if there was an error and true if not.
        return programExist;
    }

    //Method to replace the memory in a given location.
    void replaceMemory(string name, int location)
    {
        Node* position = head;
        //Goes through the list and moves through the list one at a time to replace memory.
        for (int j=0; j< location;j++){
            position = position->next;

        }
        position -> data = name;
    }

    //Method of worst fit. Takes in a name value and location to add the program using worst fit methodology.
    bool worst(string value, int location){
        int numMax = 0;
        int number = 0;
        int startLocation;

        Node* position = head;

        //Checks if program already exists.
        for(int j=0; j<32; j++){
            if(position->data == value){
                cout<<"Found Program with the Same Name";
                return false;
            }
            //Finds spot that is big enough for program.
            if(position->data == "free"){
                startLocation = j;
                while(position->data =="free"){
                    if(position->next != NULL){
                        number++;
                        position= position->next;
                    }
                    else{
                        break;
                    }
                }
                //If the number of space is larger than the size of program, it is inserted into that space. Otherwise the loop continues.
                if (number >numMax){
                    numMax = number;
                    worstFit = startLocation;
                }
                number =0;
            }
            else if (position->next !=NULL){
                position=position->next;
            }
        }
        // Returns true if the number fits, false otherwise.
        if (numMax<33)
            return true;
        else
            return false;
    }

    //Method for finding insertion point using best methodology. Takes in a programName string and size of program.
    bool best(string programName, int size){
        Node* position = head;
        int initial=0;
        int number =0;
        int starting=0;
        int numMin = 0;

        //Goes through list to see if program already exists.
        for(int j=0; j<32; j++){
            if(position->data ==programName){
                cout<<"This program already exists\n"<<endl;

            }
            //Finds free space and if one isn't big enough, the loop starts from the beginning. .
            if(position->data =="free"){
                starting = j;
                while(position -> data == "free"){
                    if(position->next!= NULL){
                        number++;
                        position = position->next;

                    }
                    else{
                        break;
                    }
                }
                j +=  number;
                //If the space can accomodate the size of the program, the location of to start is recorded.
                if(number>=size){
                    if(initial ==0){
                        numMin = number;
                        initial++;
                        bestFit=starting;
                    }
                    if (number<numMin){
                        numMin = number;
                        bestFit=starting;
                    }
                }

                number =0;
            }
            else if(position ->next !=NULL){
                position = position->next;
            }
        }
        //Returns true if the minimum number is larger or equal to the size of the program. Otherwise returns false.
        if (numMin<33){
            return true;
        }
        else{
            return false;
        }
    }
};