// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

int sudoku[9][9];

int getRandomInt(int max)
{
    return rand() % max;
}

void clearSudoku()
{
     for (int x=0; x<9; x++)
     {
         for (int y=0; y<9; y++)
         {
             sudoku[x][y] = 0;
         }
     }
}

struct sCell
{
    sCell(int nx, int ny)
    {
        x = nx;
        y = ny;
    }

    int x;
    int y;
};

struct sSlot
{
    sSlot(int nx, int ny)
    {
        x = nx;
        y = ny;
    }

    int x;
    int y;
};


sCell getCell(int x, int y)
{
    return sCell( x/3, y/3);
}

vector<sSlot> getCellSlots(sCell cell)
{
    vector<sSlot> slots;
    for (int x=0; x<3; x++)
    {
        for (int y=0; y<3; y++)
        {
            slots.push_back( sSlot( (cell.x*3) + x, (cell.y*3) + y) );
        }
    }

    return slots;
}

vector<int> getSlotValues(vector<sSlot> slots)
{
    vector<int> values;
    for (unsigned int i=0; i<slots.size(); i++)
    {
        const sSlot &slot = slots[i];
        // define slot slots[i]

        values.push_back(sudoku[slot.x][slot.y]);

        // undef slot
    }

    return values;
}

vector<int> getUnusedCellValues(sCell cell)
{
    vector<sSlot> slots = getCellSlots(cell);
    vector<int> values = getSlotValues(slots);

    vector<int> outValues;

    //Go through each number from 1 to 9
    for (int value=1; value<=9; value++)
    {
        bool bIsValueUsed = false;

        for (int i=0; i<9; i++)
        {
            if (values[i] == value)
            {
                bIsValueUsed = true;
                break;
            }
        }

        if (!bIsValueUsed)
        {
            outValues.push_back(value);
        }
    }

    return outValues;
}

bool checkDuplicateX(int x, int y, int value)
{
    for (int x1=0; x1<9; x1++)
    {
        if (x1 == x)
            continue;

        if (value == sudoku[x1][y])
            return false;
    }

    return true;
}

bool checkDuplicateY(int x, int y, int value)
{
    for (int y1=0; y1<9; y1++)
    {
        if (y1 == y)
            continue;

        if (value == sudoku[x][y1])
            return false;
    }

    return true;
}

bool randomizeValueForSlot(int x, int y)
{
    sCell cell = getCell(x, y);

    //cout << "Slot [" << x << "," << y << " cell " << cell.x << "," << cell.y << "\n";

    vector<int> unusedValues = getUnusedCellValues(cell);
    if (unusedValues.size() == 0)
    {
        return false;
    }

    vector<int> validValues;
    for (unsigned int i=0; i<unusedValues.size(); i++)
    {
        int value = unusedValues[i];
        if (checkDuplicateX(x, y, value) && checkDuplicateY(x, y, value))
        {
            validValues.push_back(value);
        }
    }

    if (validValues.size() == 0)
    {
       // cout << "No slots without duplicates!";
        return false;
    }

    int rdm = getRandomInt(validValues.size());
    sudoku[x][y] = validValues[rdm];
    return true;
}

void generateWhiteSpaces()
{
    for (int i=0; i<40; i++)
    {
        int rdm_x = getRandomInt(9);
        int rdm_y = getRandomInt(9);

        sudoku[rdm_x][rdm_y] = 0;
    }
}

void randomizeSudoku(int count)
{
     clearSudoku();

     bool bSuccess = true;

     for (int x=0; x<9 && bSuccess; x++)
     {
         for (int y=0; y<9; y++)
         {
             if (!randomizeValueForSlot(x, y))
             {
                 bSuccess = false;
                 break;
             }
         }
     }

     if (bSuccess)
     {
         cout << "Finished generating after " << count << " iterations!\n\n";

         generateWhiteSpaces();
     }
     else
     {
         randomizeSudoku(count + 1);
     }
}

void printSudoku()
{
     for (int x=0; x<9; x++)
     {
         for (int y=0; y<9; y++)
         {
             if (sudoku[x][y] == 0)
             {
                 std::cout << "| ";
             }
             else
             {
                std::cout << "|" << sudoku[x][y];
             }
         }

         std::cout << "|\n";
     }
}

int main()
{
    srand((unsigned int)time(NULL));

     randomizeSudoku(1);
     printSudoku();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
