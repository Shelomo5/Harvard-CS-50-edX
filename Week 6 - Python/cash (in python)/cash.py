from cs50 import get_float

# declare variable coins to keep track of the number of coins used
coins = 0

# Using while loop to prompt user for how much change is owed and loop can only be broken if input is positive
while True:
    dollarchange = get_float("Number of dollars using: ")
    if dollarchange > 0:
        break
# Converting dollars to cents(Cchange).
Cchange = dollarchange * 100

# While loop continues to check if the amount of change remaining is greater than the value of a coin(quarters, dimes, nickels, and pennies)
# If greater, variable coins is increased by 1 and the amount of change (variable Cchange) left is updated
while Cchange >= 25:
    coins += 1
    Cchange = Cchange - 25

while Cchange >= 10:
    coins += 1
    Cchange = Cchange - 10

while Cchange >= 5:
    coins += 1
    Cchange = Cchange - 5

while Cchange >= 1:
    coins += 1
    Cchange = Cchange - 1

# print the total number of coins used for the owed change
print(coins)
