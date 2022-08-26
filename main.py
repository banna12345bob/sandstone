from engine.commands import commands
from engine import interpreter

room = 1
print(interpreter.room(room).getName())
inp = input("Command: ")
while inp:
    try:
        giveCommand = commands(room).giveCommand(inp)
        # For this design if a function returns 0 it means that it didn't work
        if giveCommand != 0:
            if giveCommand != "Unknown command" and isinstance(giveCommand, int):
                if interpreter.room(giveCommand).getName() != 0:
                    print(interpreter.room(giveCommand).getName())
                    room = giveCommand
                else:
                    room = 1
            else:
                print(giveCommand)
        else:
            room = 1
        inp = input("Command: ")
    except:
        break