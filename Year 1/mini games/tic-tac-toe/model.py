import controller

    
#check winning conditions as bool functions
#controller sends if game over or not
block=[]
   
def init_tictactoe_list():
    for i in range(3):
        row = []
        for j in range(3):
            row.append('-')
        block.append(row)
def check_rows():
    for i in range(3):
        if block[i][0] != '-' and block[i][0]==block[i][1]==block[i][2]:
            print("row ",i)
            return True
    return False
def check_cols():
    for i in range(3):
        if block[0][i] != '-' and block[0][i]==block[1][i]==block[2][i]:
            print("col ",i)
            return True
    return False
def check_diagonals():
    if block[0][0] != '-' and block[0][0]==block[1][1]==block[2][2]:
        print("right diagonal")
        return True
    elif block[2][0] != '-' and block[2][0]==block[1][1]==block[0][2]:
        print("left diagonal")
        return True
    return False
def check_win():
    if all(all(cell == '-' for cell in row) for row in block):
        return False
    return check_rows() or check_cols() or check_diagonals()
    
            
def make_mark(player,row,column):
        if (check_win()):
            return 4
        elif all(all(cell != '-' for cell in row) for row in block):
            return 3 #tie
        elif player == 1:
            block[row][column] = "*"
            print(player,"with mark",block[row][column])
            return 1  #make mark with player 1
        else:
            block[row][column] = "#"
            print(player,"with mark",block[row][column])
            return 2 #make mark with player 2
    

    
def gameover():
    global block
    # Check for a winner
    if (block[0][0] == block[0][1] == block[0][2] != '-') or \
       (block[1][0] == block[1][1] == block[1][2] != '-') or \
       (block[2][0] == block[2][1] == block[2][2] != '-') or \
       (block[0][0] == block[1][0] == block[2][0] != '-') or \
       (block[0][1] == block[1][1] == block[2][1] != '-') or \
       (block[0][2] == block[1][2] == block[2][2] != '-') or \
       (block[0][0] == block[1][1] == block[2][2] != '-') or \
       (block[2][0] == block[1][1] == block[0][2] != '-'):
           return 1  # Game over, there is a winner

    # Check for a tie (all cells filled)
    elif all(all(cell != '-' for cell in row) for row in block):
        return -1  # Game over, it's a tie

    else: return 0  # Game is not over yet

init_tictactoe_list()

