import turtle
from turtle import Screen
import random
import winsound
import time
#move character left and right to 3/5 specific 'blocks'
#turtles keep coming down at random > i have functions for that
#when they arent in the screen anymore, make a new turtle and it starts coming down
#first do basic functionality then add complexity

#screen properties
screen = Screen()
#screen.bgpic("pic.gif")
#screen.bgcolor("light green")
screen.bgpic("forest1.gif")
bg1= True
screen.title("aleena's turtle dodge game")
screen.setup(600,600)
screen.listen()
winsound.PlaySound('bgmusic.wav',winsound.SND_ASYNC)
#global variables
colors = ["blue", "light blue" ,"yellow",  "green"  ]
step = 200
speed = 100
score=0
game_is_running = True
start_time = 0
#main_character_properties

main_character = turtle.Turtle()
main_character.shape("turtle")
main_character.begin_fill()
main_character.shapesize(4,4,4)
main_character.color("red")
main_character.end_fill()
main_character.penup()
main_character.goto(0,-200)


#for score board
score_board = turtle.Turtle()
score_board.hideturtle()
score_board.color("blue")
score_board.shape("square")
score_board.penup()
score_board.goto(0, 250)

def write_score():
    global score_board
    score_board.clear()
    score_board.write(f'Turtle Score: {int(score)}', align="center", font=("Times New Roman", 20 , "bold"))

def start_timer():
    global start_time
    start_time = time.time()
    
def get_time_spent():
    time_spent = time.time()-start_time

#set properties of turtles to dodge
turtles = []
def make_turtles_to_dodge():
    for i in range (-1,2):
        turtle_to_dodge = turtle.Turtle()
        turtle_to_dodge.hideturtle()
        turtle_to_dodge.setheading(270)
        turtle_to_dodge.shape("turtle")
        turtle_to_dodge.shapesize(4,4,4)
        turtle_to_dodge.color(random.choice(colors))
        turtle_to_dodge.penup()
        turtle_to_dodge.goto(0+200*i,200)
        turtle_to_dodge.showturtle()
        turtles.append(turtle_to_dodge)
        
def change_background():
    global bg1
    if bg1== True:
        screen.bgpic("forest.gif")
        bg1 = False
    else:
        screen.bgpic("forest1.gif")
        bg1 = True

 #functions that define movement    
def go_left():
    x=main_character.xcor()
    main_character.setx(x-step) 
def go_right():
    x=main_character.xcor()
    main_character.setx(x+step)     
def go_down():
    y=main_character.ycor()
    main_character.sety(y-speed)
def go_up():
    y=main_character.ycor()
    main_character.sety(y+speed)
 
screen.onkeypress(go_right,"Right")
screen.onkeypress(go_left,"Left")
screen.onkeypress(go_up,"Up")
screen.onkeypress(go_down,"Down")
screen.onkeypress(change_background,"space")
def move_turtles_to_dodge():
    for turtle_to_dodge in turtles: 
        y=turtle_to_dodge.ycor()
        turtle_to_dodge.sety(y-(random.randint(100,150))) #y-speed

def keep_turtles_in_screen():
    global score
    for turtle_to_dodge in turtles:
        y=turtle_to_dodge.ycor()
        if y <= -330:
            score+=10
            write_score()
            turtle_to_dodge.hideturtle()
            turtle_to_dodge.color(random.choice(colors))
            turtle_to_dodge.sety(200)
            turtle_to_dodge.showturtle()
def collision_detection():
    global game_is_running
    for turtle_to_dodge in turtles: 
        if main_character.distance(turtle_to_dodge)<70:
            game_is_running = False

def game_over_screen():
    screen.clearscreen()
    screen.bgcolor("black")
    screen.bgpic("gameover_bg1.gif")
    winsound.PlaySound('gameoverbgsound.wav',winsound.SND_ASYNC)
    game_over_screen = turtle.Turtle()
    game_over_screen.hideturtle()
    game_over_screen.shape("square")
    game_over_screen.color("white")
    game_over_screen.write("Game Over", align="center", font=("Times New Roman", 50 , "bold"))

    
#initialize gamee
start_timer()
make_turtles_to_dodge()
while game_is_running == True:
    write_score()
    move_turtles_to_dodge()
    #go through turtles and check if one is out of screen if so make it appear at the start of screen
    keep_turtles_in_screen()
    collision_detection()
game_over_screen()

screen.exitonclick()