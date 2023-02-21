#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//declare arrays
int deptPrefs[5][5];
int progPrefs[5][5];
int overlapsArr[5][5];
int dept[5];

//declare variables
int var;
int counter;
int x;
int y;

void getData(std::string fileName) //function to read in the data
{
    ifstream inFile;
    inFile.open(fileName);

    if(inFile.is_open())
    {
        for(int i = 0; i < 5; i++) //nested forloops to read in the department top preferences
        {
            for(int j = 0; j < 5; j++)
            {
                inFile >> var; //take in the value here
                deptPrefs[i][j] = (var - 1);
            }
        }

        for(int i = 0; i < 5; i++) //nested forloops to read in the programmers top preferences
        {
            for(int j = 0; j < 5; j++)
            {
                inFile >> var; //take in the value here
                progPrefs[i][j] = var - 1;
            }
        }
        inFile.close(); //close file
    }
return;
}

void overlaps(int arr[]) //function to look if there are overlaps in top preferences and puts them in an arr
{
    for(int i = 0; i < 5; i++) //look 5 times 
    {
        counter = 0;

        for(int j = 0; j < 5; j++)
        {
            if(i != j) //need this to ensure we aren't looking at the same department
            {
                if(arr[i] == arr[j]) //if arr i and arr j are equal to eachother meaning there is conflict
                {
                    overlapsArr[0][0] = i; //set the first index equal to i. 
                    overlapsArr[0][1] = j; //and set the second index equal to j. these are the departments in conflict
                    counter = 1; //set counter to one

                    break;


                }
            }
        }
        if(counter == 1) //if the counter has been set to one we then break
        {
            break;
        }

    }
    return;
}

void getPrefs()
{

    for(int i = 0; i < 6; i++) //repeat this the correct number of times
    {
        overlapsArr[0][0] = 0;
        overlapsArr[0][1] = 0;

        overlaps(deptPrefs[0]); //run checking for overlaps

        if(overlapsArr[0][0] == 0 && overlapsArr[0][1] == 0) //if there are no conflicts
        {
         break;
        }
        else
        {
            int programmer= deptPrefs[0][overlapsArr[0][0]];
            x = overlapsArr[0][0]; //set value of x
            y = overlapsArr[0][1]; //set value of y

            for(int j = 0; j < 5; j++)
            {
                if(progPrefs[j][programmer] == x) //what to do if the programmers higher preference is x
                {
                    dept[x] = programmer; //x gets the programmer
                    for(int k = 0; k < 5; k++)
                    {
                        deptPrefs[k][y] = deptPrefs[k + 1][y]; //increment the preference of y by taking out the one before
                    }
                    break;
                }else if(progPrefs[j][programmer] == y) //what to do if the programmers higher preference is y
                {
                    dept[y] = programmer; //y gets the programmer
                    for(int k = 0; k < 5; k++)
                    {
                        deptPrefs[k][x] = deptPrefs[k + 1][x]; //increment the preference of x by taking out the one before
                    }
                    break;
                }else
                {
                    continue; //otherwise contnue
                }
            }
        }

    }
}

int main()
{

    getData("input.txt"); //call function to read in the data
    getPrefs(); //call function

    for(int i = 0; i < 5; i++)
    {
        dept[i] = deptPrefs[0][i]; //assign the correct preferences
    }

    for(int i = 0; i < 5; i++)
    {
        cout<<"Department #" << i  +  1 << " will get programmer #" << dept[i] + 1 << endl; //print out final decisions
    }

}