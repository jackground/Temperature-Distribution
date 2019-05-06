/*******************************************************************************
 *  AUTHOR       : John Hawley
 *  Assignment #9: Temperature Distribution
 *  CLASS        : CS 002
 *  SECTION      : MW: 10:45a - 12:50p, TR: 10:45a - 12:10p
 *  Due Date     : 05/07/19
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
/*******************************************************************************
 *
 *  Temperature Distribution
 *______________________________________________________________________________
 *
 * _____________________________________________________________________________
 * INPUT:
 *   inputFileName : The input file name -> input from user
 *   outputFileName: The output file name -> input from user
 *
 * OUTPUT:
 *   outputFileName  : The output file name input by user
 *   grid[ROWS][COLS]: The array 2D grid representation of the temerature
 *                     distribution in a thin metal plate
 ******************************************************************************/

int main()
{
    // Constants
    // Number of rows in the array
    const int ROWS = 6;
    // Number of columns in the array
    const int COLS = 8;

    // Variables
    ifstream inputFile;         // CALC - The input file stream object
    string inputFileName;       // IN & CALC - The input file name -> input from
                                //     user
    ofstream outputFile;        // CALC - The output file stream object
    string outputFileName;      // IN & CALC & OUT - The output file name ->
                                //     input from user
    double topTemp;             // CALC - Initial temperature for the top side
                                //     of the plate -> read from input file
    double rightTemp;           // CALC - Initial temperature for the right side
                                //     of the plate -> read from input file
    double bottomTemp;          // CALC - Initial temperature for the bottom
                                //     side of the plate -> read from input file
    double leftTemp;            // CALC - Initial temperature for the left side
                                //     of the plate -> read from input file
    double equilibTolerance;    // CALC - Thermal equilibrium tolerance level ->
                                //     read from input file
    double oldValue;            // CALC - The value at an index of the grid
                                //     array before it is updated
    double newValue;            // CALC - The updated value at an index of the
                                //     grid array
    double difference;          // CALC - The numerical difference between
                                //     newValue and oldValue
    double maxDifference;       // CALC - The largest value of difference
    double grid[ROWS][COLS];    // CALC & OUT - The array 2D grid representation
                                //     of the temerature distribution in a thin
                                //     metal plate

    // Variable initialization
    topTemp = 0.0;
    rightTemp = 0.0;
    bottomTemp = 0.0;
    leftTemp = 0.0;
    equilibTolerance = 0.0;
    oldValue = 0.0;
    newValue = 0.0;
    difference = 0.0;
    maxDifference = 0.0;

    // INPUT - Get the input and output file names from the user

    cout << "Enter input file name: ";
    cin >> inputFileName;
    cout << endl << endl;

    cout << "Enter output file name: ";
    cin >> outputFileName;
    cout << endl << endl;

    // PROCCESSING - Open input file to set variable values then close file.

    inputFile.open(inputFileName.c_str());

    // Check to verify input file was found and opened sucessfully
    if (inputFile)
    {
        inputFile >> topTemp >> rightTemp >> bottomTemp >> leftTemp
                  >> equilibTolerance;

        inputFile.close();
    }
    else
    {
        // Output error message if input file could not be opened
        cout << "Error opening the file.\n";
    }


    for (int i = 0; i < ROWS; i++)
    {
       for (int j = 0; j < COLS; j++)
       {
           if (i == 0)
           {
               grid[i][j] = topTemp;
           }
           else if (i != 5)
           {
               if (j == 0)
               {
                   grid[i][j] = leftTemp;
               }
               else if (j == 7)
               {
                   grid[i][j] = rightTemp;
               }
               else
               {
                   grid[i][j] = 0;
               }
           }
           else
           {
               grid[i][j] = bottomTemp;
           }
       }
    }

    do
    {
        for (int i = 1; i < ROWS - 1; i++)
        {
            for (int j = 1; j < COLS - 1; j++)
            {
                oldValue = grid[i][j];

                newValue = (grid[i-1][j] + grid[i][j+1] +
                        grid[i+1][j] + grid[i][j-1]) / 4;

                grid[i][j] = newValue;

                difference = newValue - oldValue;

                if (i==1 && j == 1)
                {
                    maxDifference = difference;
                }
                else if (difference > maxDifference)
                {
                    maxDifference = difference;
                }
            }
        }
    } while (maxDifference >= equilibTolerance);


    outputFile.open(outputFileName.c_str());

    for (int i = 1; i < ROWS - 1; i++)
    {
        for (int j = 1; j < COLS - 1; j++)
        {
            outputFile << setw(10) << grid[i][j];
        }
        outputFile << endl;
    }

    outputFile.close();

    // OUTPUT -
    for (int i = 1; i < ROWS - 1; i++)
    {
        for (int j = 1; j < COLS - 1; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
