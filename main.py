import commands
from commands import commands

room = 0
inp = input("Command: ")
while inp:
    try:
        giveCommand = commands(room).giveCommand(inp)
        # For this design if a function returns 0 it means that it didn't work
        if giveCommand != 0:
            print(giveCommand)
            if giveCommand != "Unknown command":
                room = giveCommand
        else:
            room = 0
        inp = input("Command: ")
    except:
        break

