
from coffeeData import resources
from coffeeData import MENU

money = 0



def show_report():
    print(f"Water: {resources['water']}")
    print(f"Milk: {resources['milk']}")
    print(f"Coffee: {resources['coffee']}")
    print("Money: " , money)
    
def take_order():
    order = input("What would you like?")
    if order == "espresso" or order == "cappuccino" or order == "latte":
        print("Getting your ", order , "ready!")
    else: 
        print("Not avaliable")
    return order


def process_money():
    quarters = int(input("Enter quarters:"))
    dimes = int(input("Enter dimes:"))
    nickles = int(input("Enter nickles:"))
    pennies = int(input("Enter pennies:"))
    dollars = 0.25*quarters+0.1*dimes+0.05*nickles+0.01*pennies
    return dollars

def check_money(dollars):
    if order == "espresso":
        if dollars>= MENU["espresso"]["cost"]:
            return True
        else:
            return False
    if order == "cappuccino":
        if dollars>= MENU["cappuccino"]["cost"]:
            return True
        else:
            return False
    if order == "latte":
        if dollars>= MENU["latte"]["cost"]:
            return True
        else:
            return False
            

def check_resources():
    resources["water"] >= MENU[order]["ingredients"]["water"] 
    resources["milk"] >= MENU[order]["ingredients"]["milk"] 
    resources["coffee"] >= MENU[order]["ingredients"]["coffee"]

def make_coffee():
    resources["water"] = resources["water"] - MENU[order]["ingredients"]["water"] 
    resources["milk"] = resources["milk"] - MENU[order]["ingredients"]["milk"] 
    resources["coffee"] = resources["coffee"] - MENU[order]["ingredients"]["coffee"]
    print("Your coffee is ready!!")

#call functions    
show_report()
order = take_order()
dollars = process_money()
valid_condition = check_money(dollars)
if valid_condition == True:
    valid_condition = check_resources()
    if valid_condition == True:
        make_coffee()
    else:
      print("Not Enough Resources. Money Refunded")  
else:
    print("Not enough Cash. Money Refunded")
show_report()
