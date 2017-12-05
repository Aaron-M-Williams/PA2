#include <iostream>
#include "List.h"
#include <math.h>



using namespace std;

int main (int argumentin, const char * argument[])
{
    //Initializes Variables that will be used in next Section
    string fitType = "text";
    bool bestFit;
    List list;


    //steps to take in argument from command line. If input is best (ignoring case) or worst( ignoring case)
    //the variable bestFit is set accordingly.
    if (argument[1] != 0)
    {
        fitType = argument[1];

    }

    //If best fit argument is passed in, sets bestFit variable to true.
    if ((fitType =="best") ^ (fitType=="Best")){
        bestFit = true;
        cout<<"Utilizing the best fit algorithm"<<endl;
    }

    //If worst fit argument is passed in, sets bestFit variable to false.
    else if ((fitType == "worst") ^ (fitType=="Worst")){
        bestFit = false;
        cout<<"Utilizing the worst fit algorithm"<<endl;

    }

    //If the arguments are invalid or there are none, the program defaults to best fit
    //by setting the bestFit variable to true.
    else{
        bestFit = true;
        cout<<"No argument or invalid. Defaulting to best fit algorithm"<<endl;
    }


    //Initializes variables for the do while loop and switch statement following.
    char option;
    //Do While Loop which is the main body of the program and keeps running until the exit
    //value is passed in (choice 5).

    do{
        cout<<" 1. Add Program\n 2. Kill Program \n 3. Fragmentation \n 4. Print Memory \n 5. Exit \n"<<endl;
        //Variable which is taken in, will be used for switch statements
        cout<<"choice - ";
        cin>>option;

        switch (option)
          {
              //Case 1, option to insert program into the list. Takes in a program name and size
              //to be used to insert the program.
            case '1':{
                //Variables declared which will be used in Case 1.
                string programName;
                double programSize;
                cout<<"Program Name?";
                cin>>programName;
                cout<<"Program Size (KB):";
                cin>>programSize;

                //Checks if the input is a valid number (not character or string).
                while(cin.good()==false) {
                    cout << "Error, Please try again."<<endl;
                    cin.clear();
                    cin.ignore();
                    cout<<"Program Size (KB): ";
                    cin>>programSize;
                }

                //Converts the size of the program into pages by dividing the size by 4.0.
                int sizeKB = ceil(programSize/4.0);

                //Checks for extraneous values. Returns error if size is too large.
                if (sizeKB>32) {
                    cout << "Not not enough memory to add, " << programName << endl;
                    break;
                }
                //Deicdes if best fit or worst fit should be used to insert program.
                //If bestFit is true, the best method is called using name and size of program.
                if (bestFit == true){
                    if(list.best(programName, sizeKB)){
                        for(int j = list.bestFit; j<sizeKB + list.bestFit; j++){
                            list.replaceMemory(programName, j);
                   }
                   cout<<"Program "<< programName<< " added to List, " <<sizeKB<<" pages consumed.\n"<<endl;



                }//If error, program is not added to the list and an error is printed out.
                    else {
                        cout<<"\nProgram "<< programName<< " was unable to be added.\n"<<endl;

                }

            }
                    //If worst case is selected, method calls upon worst case method utilizing
                    //program name and size parameters.
                else{
                    if(list.worst(programName, sizeKB)){
                        for(int j=list.worstFit; j<sizeKB +list.worstFit;j++){
                            list.replaceMemory(programName, j);
                    }
                    cout<<"Program "<<programName<< " added to List, " <<sizeKB <<" pages consumed.\n"<<endl;
                }
                        //If failure, program is not added and error is printed to console.
                else{
                    cout<<"\n Program "<< programName<< " was unable to be added.\n";
                }
            }
            break;
        }

        //Case two, deletes a program stored in the list.
            case '2': {
                //Variables which will be used in case 2 are declared.
                string programName;
                cout<<"Name of Program to Delete: ";
                cin>>programName;

                //Program name is taken in and then passed along to the remove method within List.h
                //If the program is found, it is deleted, if it is not found, an error is printed to the console.
                if(list.remove(programName)){
                    cout<<"\nProgram "<<programName<<" was deleted. \n";

            }
                //Code to print error to console if program is not found.
                else{
                     cout<<"\nProgram "<<programName<<" was NOT found and was NOT deleted\n";
            }
            break;


        }
           //Case three, prints out the number of fragmens present in the list.
            case '3':{
                //Prints new line and then calls upon the printFragments method in List.h
                cout<<"\n"<<endl;
                list.printFragments();
                break;
        }
            //Case four, prints out the list, utilizing the printList method within List.h.
            case '4':{
                cout<<"\n"<<endl;
                list.printList();
                break;
        }
             //Case five, prints to the console that the program is exiting, and subsequently exits with a return value of 1.
            case '5':{
                cout<<"Exiting Entire Program"<<endl;
                return 0;
        }
           //If the case is invalid, default case is called upon and prints to the console that an invalid option
           //has been selected.
        default: cout<< option <<" Is an invalid option.\n";

    }}while(option !=5);
    //final return value of main function.
    return 0;

}