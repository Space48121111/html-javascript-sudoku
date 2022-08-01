from random import randint

# ? int vals of the grid
sudoku[][] = [] # 9x9
for i in range(0, 9):
    for j in range(0, 9):
        sudoku[i][j]

def getRandomInt(max):
    return randint(0, max)

def clearSudoku():
    for x in range(1, 9):
        for y in range(0, 9):
            sudoku[x][y] = 0

# ? new data type slot() cell()
def getCell(slot(x, y)):
        x = x/3
        y = y/3
    return cell(x, y) 

def getSlots(cell):
    slots = []
    for x in range(0, 3):
        for y in range(0, 3):
            coords_x = cell[x*3] + x
            coords_y = cell[y*3] + y
            slots.append(slot[(coords_x, coords_y)])
    return slots

def getVals(slots):
    values = []
    for i in range(0, length(slots)):
        x, y = slot[x], slot[y]
        values.append(sudoku[x][y])
    return values

def NotAppearedVal(cell):
    slots = getSlots(cell);
    values = getVals(slots);
    res = []

    for val in range(1, 9):
        bHasAppeared = False
        for i in range(0, length(values)):
            if values[i] == val:
                bHasAppeared == True
                break
        if not bHasAppeared:
            res.append(val)
    return res

def checkDuplicateX(slot, val):
    for x in range(0, 9):
        if x == slot[x]:
            continue;
        if val == sudoku[x][slot[y]]
            return True
    return False

def checkDuplicateY(slot, val):
    for y in range(0, 9):
        if y == slot[y]:
            continue;
        if val == sudoku[x][y1]:
            return True
    return False

def randVal(slot):
    cell = getCell(slot)
    notAppV = NotAppearedVal(cell)
    validVal = []
    rdm = getRandomInt(length(validVal))


    if length(notAppV) == 0:
        return False
    for i in range(0, length(notAppV)):
        val = notAppV[i]
        if not checkDuplicateX(slot, val) and not checkDuplicateY(slot, val):
            validVal.append(val)

    if length(validVal) == 0:
        return False

    x, y = slot[x], slot[y]
    sudoku[x][y] = validVal[rdm]
    return True

def generateWhiteSpaces():
    for i in range(0, 40):
        rdm_x = getRandomInt(9)
        rdm_y = getRandomInt(9)

        sudoku[rdm_x][rdm_y] = 0

def randomizeSudoku(ct):
    clearSudoku()
    bSuccess = True
    slot((0, 0))
    
    for x in range(0, 9) and bSuccess:
        for y in range(0, 9):
            if not randVal(slot(x, y)):
                bSuccess = False
                break
    
    if bSuccess:
        print('Finished', ct, 'iterations.')
        generateWhiteSpaces()
    else:
        randomizeSudoku(ct + 1)
        
def printSudoku():
    slot((0, 0))
    for y in range(0, 9):
        if y > 0 and y % 3 == 0:
            print('\n')
        print(' ')
        for x in range(0, 9):
            if x > 0 and x % 3 == 0
                print('| ')
            if sudoku[x][y] == 0:
                print('| ')
            else:
                print('|', sudoku[x][y])
        print('| \n')     

if __name__ == __main__:

    randomizeSudoku()
    printSudoku()




# end