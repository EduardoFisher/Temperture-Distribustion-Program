/*************************************************************
*  AUTHOR       : Eduardo Fisher
*  LAB 09       : Temperature Distribution
*  CLASS        : CS02
*  SECTION      : MW: 7:00am - 8:25am F: 7:00am - 11:15am
*  Due Date     : 11/10/2016
**************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int const ROWS = 6;
int const COLUMNS = 8;
int const SIZE = 5;

void getNameFiles(string& inName, string& outName);
void setFileNumbers(ifstream &inFile, double file[], int size);
void setDistribustionArray(double temp[][COLUMNS], int rows,
                           double initialtemp[]);
bool updateTemp(double temp[][COLUMNS], int size, double filenum[]);
void outputFinalTemp(double const finalTemp[][COLUMNS], int rows);
void sendFinalTemp(ofstream &outFile, double const finalTemp[][COLUMNS],
                   int rows);

/*************************************************************************
* PrintHeader
* This function recieves an asignment name, type and number then outputs
*   the appropriate header.
*  - Returns nothing -> This will output the class heading.
************************************************************************/
void printHeader(string asName, //IN - Assignment Name
                 char asType,   //IN - Assignment Type - LAB or Assignment
                 int asNum);    //IN - Assignment Number


int main()
{
    printHeader("Temperature Distribution", 'A', 9);
    ifstream inFile;
    ofstream outFile;
    string outName;
    string inName;
    double distribution[ROWS][COLUMNS];
    double temp[SIZE];
    bool tolerance;

    tolerance = true;

    getNameFiles(inName, outName);
    inFile.open(inName.c_str());
    outFile.open(outName.c_str());

    setFileNumbers(inFile, temp, SIZE);
    setDistribustionArray(distribution, ROWS, temp);
    while( tolerance == true )
    {
        tolerance = updateTemp(distribution, ROWS, temp);
    }

    outputFinalTemp(distribution, ROWS);
    sendFinalTemp(outFile, distribution, ROWS);

    outFile.close();
    inFile.close();


    return 0;
}

void sendFinalTemp(ofstream &outFile, double const finalTemp[][COLUMNS],
                   int rows)
{
    for(int i = 1; i < rows - 1; i++)
    {
        for(int j = 1; j < COLUMNS - 1; j++)
        {
            outFile << setw(12) << finalTemp[i][j] << " ";
        }
        outFile << endl;
    }
}

void outputFinalTemp(double const finalTemp[][COLUMNS], int rows)
{
    for(int i = 1; i < rows - 1; i++)
    {
        for(int j = 1; j < COLUMNS - 1; j++)
        {
            cout << setw(12) << finalTemp[i][j] << " ";
        }
        cout << endl;
    }
}

bool updateTemp(double temp[][COLUMNS], int size, double filenum[])
{
    double oldValue;
    double tolerance;
    bool eqi = false;
    for(int i = 1; i < size - 1; i++)
    {
        for(int j = 1; j < COLUMNS - 1; j++)
        {
            oldValue = temp[i][j];
            temp[i][j] = (temp[i-1][j] + temp[i][j+1] + temp[i+1][j] +
                    temp[i][j-1]) / 4;
            tolerance = abs(oldValue - temp[i][j]);
            if(tolerance > filenum[4])
            {
                eqi = true;
                break;
            }
        }
    }
    return eqi;
}

void setFileNumbers(ifstream &inFile, double file[], int size)
{
    if(inFile)
    {
        for(int i = 0; i < size; i++)
            inFile >> file[i];
    }
}

void setDistribustionArray(double temp[][COLUMNS], int rows,
                           double initialTemp[])
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            if( i == 0)
                temp[i][j] = initialTemp[0];
            else if( j == 0 && (i > 0 && i < 5) )
                temp[i][j] = initialTemp[3];
            else if( i == 5 )
                temp[i][j] = initialTemp[2];
            else if( j == 7 && (i > 0 && i < 5) )
                temp[i][j] = initialTemp[1];
            else
                temp[i][j] = 0;

        }
    }
}

void getNameFiles(string& inName, string& outName)
{
    cout << "Please enter the input file name: ";
    getline(cin, inName);
    cout << endl;
    cout << "Please enter the output file name: ";
    getline(cin, outName);
    cout << endl;
}

/***********************************************************************
*
* FUNCTION PrintHeader
* ________________________________________________________________________
* This function recieves an asignment name, type and number then outputs
*  the appropriate header -
*  returns nothing.
* ________________________________________________________________________
* PRE-CONDITIONS
*  The following will need defined values
*      asName: Assignment Name
*      asType: Assignment Type
*      asNum : Assignment Number
*
* POST-CONDITIONS
*  This funcion will output the class heading.
************************************************************************/
void printHeader(string asName, //IN - Assignment Name
                 char asType,   //IN - Assignment Type - LAB or Assignment
                 int asNum)     //IN - Assignment Number
{
  if(asType == 'A')
  {
      cout << "*****************************************************"
              "*****\n";
      cout << "   Programmed by: Eduardo Fisher\n";
      cout << "   CS02         : MW: 7:00am - 8:25am F: 7:00am - 11:1"
              "5am\n";
      cout << "   Assignment 0" << asNum << ": " << asName << endl;
      cout << "******************************************************"
              "****\n";
  }
  if(asType == 'L')
  {
      cout << "*****************************************************"
              "*****\n";
      cout << "   Programmed by: Eduardo Fisher\n";
      cout << "   CS02         : MW: 7:00am - 8:25am F: 7:00am - 11:1"
              "5am\n";
      cout << "   Lab 0" << asNum << "       : " << asName << endl;
      cout << "******************************************************"
              "****\n";
  }
}
