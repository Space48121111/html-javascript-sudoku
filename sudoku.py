from random import randint

# 9x9 grid
sudoku = []
for i in range(9):
  col = []
  for j in range(9):
      col.append(0)
  sudoku.append(col)

def getRandomInt(max):
    return randint(0, max)

def clearSudoku():
    for i in range(9):
        for j in range(9):
            sudoku[i][j] = 0


def checkDuplicateX(x, y, v):
    for x1 in range(9):
        if x1 == x:
            continue;
        if v == sudoku[x1][y]:
            return True
    return False

def checkDuplicateY(x, y, v):
    for y1 in range(9):
        if y1 == y:
            continue;
        if v == sudoku[x][y1]:
            return True
    return False

def randVal():
    vals = []
    for x in range(9):
        for y in range(9):
            vals = []
            for v in range(1, 10):
                if not checkDuplicateX(x, y, v) and not checkDuplicateY(x, y, v):
                    vals.append(v)

            # it runs out of numbers 1-9
            if len(vals) == 0:
                return False

            # indices: 0->n-1 lens: 1->n
            # getRandomInt(8) + 1 no 0s
            rdm = getRandomInt(len(vals) - 1)
            sudoku[x][y] = vals[rdm]
    return True

def printSudoku():
    for row in sudoku:
        print(row)

if __name__ == '__main__':

    while randVal() == False:
        clearSudoku()

    printSudoku()








# end
