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

for x in range(9):
    for y in range(9):
        rdm = getRandomInt(9)
        sudoku[x][y] = rdm

for row in sudoku:
    print(row)








# end
