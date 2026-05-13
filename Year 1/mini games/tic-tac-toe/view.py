import turtle
from turtle import Screen
import controller

#global variables
SCREEN_WIDTH = 700
SCREEN_HEIGHT = 700
BOARD_HEIGHT = 600
BOARD_WIDTH = 600
BOX_HEIGHT = BOARD_HEIGHT/3
BOX_WIDTH = BOARD_WIDTH/3
SCREEN_COLOR = 'light blue'
board_length = (SCREEN_HEIGHT-(SCREEN_HEIGHT/4)) 
grid_length=board_length/3
top_of_board=((((SCREEN_HEIGHT/2)-(SCREEN_HEIGHT/4))-(board_length/2))+board_length/2)+grid_length/4

#screen properties
screen = turtle.Screen()
screen.setup(SCREEN_WIDTH , SCREEN_HEIGHT)
screen.title("Aleena's Tic Tac Toe Game")
screen.bgcolor(SCREEN_COLOR)
screen.onscreenclick(controller.onMouseClick)
screen.listen()
 
def draw_circle(num):
    circle = turtle.Turtle()
    circle.hideturtle()
    circle.color("red")
    circle.penup()
    if num == 1:
        circle.goto(-BOX_WIDTH, BOX_HEIGHT / 2)
    elif num == 2:
        circle.goto(0, BOX_HEIGHT / 2)
    elif num == 3:
        circle.goto(BOX_WIDTH, BOX_HEIGHT / 2)
    elif num == 4:
        circle.goto(-BOX_WIDTH, -BOX_HEIGHT /2)
    elif num == 5:
        circle.goto(0, -BOX_HEIGHT/2)
    elif num == 6:
        circle.goto(BOX_WIDTH, -BOX_HEIGHT/2)
    elif num == 7:
        circle.goto(-BOX_WIDTH, -(BOX_HEIGHT+BOX_HEIGHT/2))
    elif num == 8:
        circle.goto(0, -(BOX_HEIGHT+BOX_HEIGHT/2))
    elif num == 9:
        circle.goto(BOX_WIDTH, -(BOX_HEIGHT+BOX_HEIGHT/2))
    circle.write('O', font=("Comic Sans MS", int(BOX_HEIGHT / 2), "bold"), align='center')

def draw_cross(num):
    cross = turtle.Turtle()
    cross.hideturtle()
    cross.color("blue")
    cross.penup()
    if num == 1:
        cross.goto(-BOX_WIDTH, BOX_HEIGHT / 2)
    elif num == 2:
        cross.goto(0, BOX_HEIGHT / 2)
    elif num == 3:
        cross.goto(BOX_WIDTH, BOX_HEIGHT / 2)
    elif num == 4:
        cross.goto(-BOX_WIDTH, -BOX_HEIGHT/2)
    elif num == 5:
        cross.goto(0, -BOX_HEIGHT/2)
    elif num == 6:
        cross.goto(BOX_WIDTH, -BOX_HEIGHT/2)
    elif num == 7:
        cross.goto(-BOX_WIDTH, -(BOX_HEIGHT+BOX_HEIGHT/2))
    elif num == 8:
        cross.goto(0, -(BOX_HEIGHT+BOX_HEIGHT/2))
    elif num == 9:
        cross.goto(BOX_WIDTH, -(BOX_HEIGHT+BOX_HEIGHT/2))
    cross.write('X', font=("Comic Sans MS", int(BOX_HEIGHT / 2), "bold"), align='center')

def draw_grid():
    grid = turtle.Turtle()
    grid.hideturtle()
    grid.penup()
    grid.pencolor('green')
    grid.pensize(10)
    #first line
    grid.goto(0-(BOX_WIDTH+BOX_WIDTH/2),0+(BOX_HEIGHT/2))
    grid.pendown()
    grid.forward(BOARD_HEIGHT)
    grid.penup()
    #second line
    grid.goto(0-(BOX_WIDTH+BOX_WIDTH/2),0-(BOX_HEIGHT/2))
    grid.pendown()
    grid.forward(BOARD_HEIGHT)
    grid.penup()
    #third line
    grid.goto(0-(BOX_HEIGHT/2), 0-(BOX_WIDTH+BOX_WIDTH/2))
    grid.setheading(90)
    grid.pendown()
    grid.forward(BOARD_HEIGHT)
    grid.penup()
    #fourth line
    grid.goto(0+(BOX_HEIGHT/2), 0+(BOX_WIDTH+BOX_WIDTH/2))
    grid.pendown()
    grid.backward(BOARD_HEIGHT)

def draw_win_screen():
    screen.clear()
    win = turtle.Turtle()
    win.hideturtle()
    player = controller.get_player()
    player+=1
    win.penup()
    if(player ==1):
        win.color("red")  # Set text color
    else:
        win.color("blue")
    win.goto(0, 50)  # Position text slightly above the center
    win.write(f"Player {player} Won!", align="center", font=("Arial", 32, "bold"))

def draw_tie_screen():
    screen.clear()
    tie = turtle.Turtle()
    tie.hideturtle()
    tie.color("navy")  # Set text color
    tie.penup()
    tie.goto(0, 50)  # Position text slightly above the center
    tie.write("It's a Tie!", align="center", font=("Arial", 32, "bold"))
    tie.goto(0, -50)  # Position text slightly below the center
    tie.write("Better luck next time!", align="center", font=("Arial", 24, "normal"))

box_Num=-1
def clicked_coordinates(x,y):
    global box_Num
    result = controller.onMouseClick(x,y)
    box_Num = controller.getBoxNum(x,y)
    if result == 3:
        draw_tie_screen()
    elif result == 1: 
        draw_circle(box_Num)
    elif result == 2:
        draw_cross(box_Num)
    elif result == 4:      
        draw_win_screen()
draw_grid()
screen.listen()
screen.onscreenclick(clicked_coordinates)

turtle.mainloop()