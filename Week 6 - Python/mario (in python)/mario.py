from cs50 import get_int

# prompting user for height h of the pyramind
h = get_int("Height: ")
# if h is less than 1 or greater than 8 then reprompt user for height
while (h < 1 or h > 8):
    h = get_int("Height: ")

# we iterate for every rows r within a height h using a for loop
for r in range(h):
    # number of spaces in a given row equals height - row number and we substract one bc end indexes are exclusive
    spaces = h - r - 1
    # number of ashes in a given row equals the row number, so row 1 has one hash ect.. We add one bc end indexes are exclusive
    hashes = r + 1
    # end="" overides python from going to the next line
    print(spaces * " ", end="")
    print(hashes * "#")

