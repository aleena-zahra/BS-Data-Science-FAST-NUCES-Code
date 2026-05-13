import turtle
from turtle import Screen
import winsound
import time
#global variables
game_is_playing = True
player1_score = 0
player2_score = 0
MOVEMENT_IN_Y_DIRECTION = 4
MOVEMENT_IN_X_DIRECTION = 4
PADDLE_SPEED = 50
X_PADDLE_BOUNDARY =200
Y_PADDLE_BOUNDARY = 180
SCREEN_WIDTH = 400
SCREEN_HEIGHT = 400
ball = turtle.Turtle()
left_paddle = turtle.Turtle()
right_paddle = turtle.Turtle()
screen = Screen()

#screen properties
screen.bgcolor("black")
screen.screensize(SCREEN_WIDTH,SCREEN_HEIGHT)
screen.setup(450,450)

#ball properties
BALL_COLOR = "white"
BALL_SHAPE = "circle"
BALL_SIZE = 1.5

def initialize_ball():
    
    ball.penup()
    ball.shape(BALL_SHAPE)
    ball.color(BALL_COLOR)
    ball.shapesize(BALL_SIZE,BALL_SIZE,BALL_SIZE)
    ball.goto(0,0)
    ball.showturtle()
    
#score board properties
SCORE_BOARD_COLOR="white"
SCORE_BOARD_SHAPE="square"
#initialize score board
score_board = turtle.Turtle()
score_board.hideturtle()
score_board.color(SCORE_BOARD_COLOR)
score_board.shape(SCORE_BOARD_SHAPE)  
score_board.penup()
score_board.goto(0, Y_PADDLE_BOUNDARY)

#paddle properties
PADDLE_SHAPE="square"
PADDLE_ANGLE = 90
PADDLE_STRETCH = 4
#left paddle properties
LEFT_PADDLE_COLOR="green"
#right paddle properties
RIGHT_PADDLE_COLOR="green"

def draw_left_paddle():
    left_paddle.penup()
    left_paddle.goto(-X_PADDLE_BOUNDARY,0)
    left_paddle.shape(PADDLE_SHAPE)
    left_paddle.color(LEFT_PADDLE_COLOR)
    left_paddle.shapesize(1,PADDLE_STRETCH,1)
    left_paddle.setheading(PADDLE_ANGLE)
    
def draw_right_paddle():
    right_paddle.penup()
    right_paddle.setheading(PADDLE_ANGLE)
    right_paddle.goto(X_PADDLE_BOUNDARY,0)
    right_paddle.shape(PADDLE_SHAPE)
    right_paddle.color(RIGHT_PADDLE_COLOR)
    right_paddle.shapesize(1,PADDLE_STRETCH,1)
#ask players their names
player1_name = turtle.textinput("Enter Your Name", "Player 1")
player2_name = turtle.textinput("Enter Your Name", "Player 2")
def write_score():
    global score_board
    score_board.clear()
    score_board.write(f'{player1_name}: {int(player1_score)} \n{player2_name}: {int(player2_score)}', align="center", font=("Times New Roman", 15 , "bold"))
    
def move_ball():
    global MOVEMENT_IN_X_DIRECTION
    global MOVEMENT_IN_Y_DIRECTION
    global x_position
    global y_position
    x_position = ball.setx(ball.xcor() + MOVEMENT_IN_X_DIRECTION )
    y_position = ball.sety(ball.ycor() + MOVEMENT_IN_Y_DIRECTION )

def play_paddle_collision_sound():
    winsound.PlaySound("paddle_sound.wav",winsound.SND_ASYNC)
def play_score_sound():
     winsound.PlaySound("score.wav",winsound.SND_ASYNC)   
    
def detect_collision_with_paddle():
    global MOVEMENT_IN_X_DIRECTION
    global player1_score
    global player2_score
    
    # Check collision with right paddle
    if ball.distance(right_paddle)<50:
        play_paddle_collision_sound()
        MOVEMENT_IN_X_DIRECTION *= -1 

    # Check collision with left paddle
    if ball.distance(left_paddle)<50:
        play_paddle_collision_sound()
        MOVEMENT_IN_X_DIRECTION *= -1  
        
      
def detect_collision_with_wall():
    global MOVEMENT_IN_Y_DIRECTION
    global MOVEMENT_IN_X_DIRECTION
    global player1_score
    global player2_score
    if ball.xcor()> (SCREEN_WIDTH/2 +40):
        player2_score += 1  
        play_score_sound()
        time.sleep(0.25)
        ball.hideturtle()
        MOVEMENT_IN_X_DIRECTION *=-1
        initialize_ball()
        write_score()
    if ball.xcor() < -(SCREEN_WIDTH/2 +40) :
        player1_score += 1
        play_score_sound()
        time.sleep(0.25)
        ball.hideturtle()
        MOVEMENT_IN_X_DIRECTION *=-1
        initialize_ball()
        write_score()
    elif ball.ycor()> (SCREEN_HEIGHT/2) or ball.ycor() < -(SCREEN_HEIGHT/2 ):
        MOVEMENT_IN_Y_DIRECTION *= -1

def right_paddle_go_down():
    if right_paddle.ycor()>-Y_PADDLE_BOUNDARY:
        right_paddle.backward(PADDLE_SPEED) 
def right_paddle_go_up():
    if right_paddle.ycor()<Y_PADDLE_BOUNDARY:
        right_paddle.forward(PADDLE_SPEED)
def left_paddle_go_down():
    if left_paddle.ycor()>-Y_PADDLE_BOUNDARY:
        left_paddle.backward(PADDLE_SPEED)    
def left_paddle_go_up():
    if left_paddle.ycor()<Y_PADDLE_BOUNDARY:
        left_paddle.forward(PADDLE_SPEED)

def set_level():
    global player2_score
    global player1_score
    global MOVEMENT_IN_Y_DIRECTION
    global MOVEMENT_IN_X_DIRECTION
    if player1_score>=50 or player2_score>=50:
        MOVEMENT_IN_Y_DIRECTION += 1
        MOVEMENT_IN_X_DIRECTION += 1   
        player1_score=0
        player2_score=0
        
screen.listen()
screen.onkeypress(right_paddle_go_up , "Up")
screen.onkeypress(right_paddle_go_down , "Down")
screen.onkeypress(left_paddle_go_up , "w")
screen.onkeypress(left_paddle_go_down , "s")

def initialize_game():
    initialize_ball()
    write_score()
    draw_left_paddle()
    draw_right_paddle()

#MAIN GAME LOOP
initialize_game()
while game_is_playing:
    
    move_ball()
    detect_collision_with_paddle()
    detect_collision_with_wall()
    set_level()
screen.exitonclick()
