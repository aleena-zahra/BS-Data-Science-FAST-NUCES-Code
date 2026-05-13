from higherLowerLogo import logo
from higherLowerLogo import vs
from higherLowerGameData import data

for i in range (3):
    print(logo)
    print(f"Name: {data[i]['name']}")
    print(f"Description: {data[i]['description']}")
    print(f"Info: {data[i]['country']}")
    print(vs)
    print(f"Name: {data[i+1]['name']}")
    print(f"Description: {data[i+1]['description']}")
    print(f"Info: {data[i+1]['country']}")    
    user_input = input("Who has higher followers A or B? ")
    if data[i]["follower_count"] >= data[i+1]["follower_count"]:
        answer="A"
    elif data[i]["follower_count"] <= data[i+1]["follower_count"]:
        answer="B"   
    if user_input == answer:
        print("Yayy you are correct")
    else:
        print("Oh no u are wrong") 
    print(f"Followers of A were: {data[i]['follower_count']}")
    print(f"Followers of B were: {data[i+1]['follower_count']}")


