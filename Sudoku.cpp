// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

int sudoku[9][9];

//=======================================================================
//inline for running small functions faster
//=======================================================================
inline int getRandomInt(int max)
{
    return rand() % max;
}

//=======================================================================
//
//=======================================================================
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

//=======================================================================
//struct create a new data type
//=======================================================================
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

//=======================================================================
//
//=======================================================================
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

//=======================================================================
//& reference
//=======================================================================
sCell getCell(const sSlot &slot)
{
    return sCell( slot.x/3, slot.y/3);
}

//=======================================================================
//
//=======================================================================
vector<sSlot> getSlots(sCell cell)
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

//=======================================================================
//
//=======================================================================
vector<int> getVals(vector<sSlot> slots)
{
    vector<int> values;
    for (unsigned int i=0; i<slots.size(); i++)
    {
        const sSlot &slot = slots[i];
        values.push_back(sudoku[slot.x][slot.y]);
    }

    return values;
}

//=======================================================================
//
//=======================================================================
vector<int> NotAppearedVal(sCell cell)
{
    vector<sSlot> slots = getSlots(cell);
    vector<int> values = getVals(slots);

    vector<int> outValues;

    //Go through each number from 1 to 9
    for (int value=1; value<=9; value++)
    {
        bool bHasAppeared = false;

        for (int i=0; i<values.size(); i++)
        {
            if (values[i] == value)
            {
                bHasAppeared = true;
                break;
            }
        }

        if (!bHasAppeared)
        {
            outValues.push_back(value);
        }
    }

    return outValues;
}

//=======================================================================
//
//=======================================================================
bool checkDuplicateX(const sSlot &slot, int value)
{
    for (int x1=0; x1<9; x1++)
    {
        // ignore itself
        if (x1 == slot.x)
            continue;

        // same y coord, iterate/check thru x1 in the same row
        if (value == sudoku[x1][slot.y])
            return true;
    }

    return false;
}

//=======================================================================
//
//=======================================================================
bool checkDuplicateY(const sSlot &slot, int value)
{
    for (int y1=0; y1<9; y1++)
    {
        if (y1 == slot.y)
            continue;

        if (value == sudoku[slot.x][y1])
            return true;
    }

    return false;
}

//=======================================================================
//
//=======================================================================
bool randVal(sSlot slot)
{
    sCell cell = getCell(slot);

    //cout << "Slot [" << x << "," << y << " cell " << cell.x << "," << cell.y << "\n";

    vector<int> notAppV = NotAppearedVal(cell);
    if (notAppV.size() == 0)
    {
        return false;
    }

    vector<int> validValues;
    for (unsigned int i=0; i<notAppV.size(); i++)
    {
        int value = notAppV[i];
        if (!checkDuplicateX(slot, value) && !checkDuplicateY(slot, value))
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
    sudoku[slot.x][slot.y] = validValues[rdm];
    return true;
}

//=======================================================================
//
//=======================================================================
void generateWhiteSpaces()
{
    for (int i=0; i<40; i++)
    {
        // generate 0-8
        int rdm_x = getRandomInt(9);
        int rdm_y = getRandomInt(9);

        sudoku[rdm_x][rdm_y] = 0;
    }
}

//=======================================================================
//
//=======================================================================
void randomizeSudoku(int count)
{
     clearSudoku();

     bool bSuccess = true;

     sSlot slot(0,0);

     for (slot.x=0; slot.x<9 && bSuccess; slot.x++)
     {
         for (slot.y=0; slot.y<9; slot.y++)
         {
             if (!randVal(slot))
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

//=======================================================================
//
//=======================================================================
void printSudoku()
{
    sSlot slot(0,0);
    for (slot.y=0; slot.y<9; slot.y++)
    {
        if (slot.y > 0 && (slot.y % 3) == 0)
        {
            std::cout << "\n";
        }

        std::cout << " ";

        for (slot.x=0; slot.x<9; slot.x++)
        {
            if (slot.x > 0 && (slot.x % 3) == 0)
            {
                std::cout << "| ";
            }

            //If 0 then it's an empty space, print it as such
            if (sudoku[slot.x][slot.y] == 0)
            {
                std::cout << "| ";
            }
            else
            {
               std::cout << "|" << sudoku[slot.x][slot.y];
            }
        }
        // each row's line break
        std::cout << "| \n";
     }
}

//=======================================================================
// srand to change the beginning of the random vals
//=======================================================================
int main()
{
    srand((unsigned int)time(NULL));

    randomizeSudoku(1);
    printSudoku();
}
