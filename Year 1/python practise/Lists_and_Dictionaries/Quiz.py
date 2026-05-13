from quizData import question_data
score = 0
for i in range (12):
    print(question_data[i]["text"])
    user_answer = input("Is this true?")
    if(user_answer == question_data[i]["answer"]):
        print("Yayy correct" , end= "\n\n")
        score += 1
    else:
        print("Oh no its wrong" , end= "\n\n")
    print("Your Score is", score , "out of ", i+1 , end="\n\n")
