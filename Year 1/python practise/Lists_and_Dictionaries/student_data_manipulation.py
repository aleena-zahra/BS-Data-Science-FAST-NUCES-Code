list_of_dictionaries=[]
for i in range (10):
    first_name= input("Enter first Name: ")
    last_name = input("Enter last Name: ")
    age = int(input("Enter age: "))
    degree_program = input("Enter degree Program: ")

    list_of_students = {
        "First Name" : first_name,
        "Last Name" : last_name ,
        "Age" : age ,
        "Degree" : degree_program ,
        
    }

    list_of_dictionaries.append(list_of_students)
    

print(list_of_dictionaries)

i = -1
while i >= -10:
#   print(list_of_dictionaries[i])
    print(f"First Name: {list_of_dictionaries[i]['First Name']} Last Name: {list_of_dictionaries[i]['Last Name']}  ")
    print(f"Age: {list_of_dictionaries[i]['Age']} Degree : {list_of_dictionaries[i]['Degree']}")
    print("-------------------------------------------------------------------------------------------")
    i = i-1
