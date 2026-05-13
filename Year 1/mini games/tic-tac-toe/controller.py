import model 

BOARD_HEIGHT = 600
BOARD_WIDTH = 600
BOX_HEIGHT = BOARD_HEIGHT/3
BOX_WIDTH = BOARD_WIDTH/3
GRID_PEN_WIDTH = 10
x=0
y=0
is_game_ended=0
count=0
def get_column_number(y):
    if y>=-BOARD_HEIGHT/2 and y<=-BOX_HEIGHT/2: return 2
    elif y>=-BOX_HEIGHT/2 and y<=BOX_HEIGHT/2: return 1
    elif y<=BOARD_HEIGHT/2 and y>=BOX_HEIGHT/2: return 0 
    return None
def get_row_number(x):
    if x>=-BOARD_WIDTH/2 and x<=-BOX_WIDTH/2: return 0
    elif x>=-BOX_WIDTH/2 and x<=BOX_WIDTH/2: return 1
    elif x<=BOARD_WIDTH/2 and x>=BOX_WIDTH/2: return 2
    return None

def won_game():
    if (model.check_win()):
        return True
    return False

def onMouseClick(x_cor, y_cor):
    global count,x,y
    x= x_cor
    y= y_cor
    count+=1
    row = get_row_number(x)
    column = get_column_number(y)
    player= get_player()
    return model.make_mark(player,row,column)
def getBoxNum(row,col):
    global x,y
    row = get_row_number(x)
    col = get_column_number(y)
    if   (row==0 and col==0):
        return 1
    elif (row==0 and col==1):
        return 4
    elif (row==0 and col==2):
        return 7
    elif (row==1 and col==0):
        return 2
    elif (row==1 and col==1):
        return 5
    elif (row==1 and col==2):
        return 8
    elif (row==2 and col==0):
        return 3
    elif (row==2 and col==1):
        return 6
    elif (row==2 and col==2):
        return 9



def get_player():
    global count
    player=count%2
    return player
    



