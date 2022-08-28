from engine.commands import commands
from engine import interpreter
from engine.debugger import debugger

room = 1
area = 1
print(interpreter.room(area, room).getRoomName())
inp = input("Command: ")
while inp:
    try:
        giveCommand = commands(area, room).giveCommand(inp)
        # For this design if a function returns 0 it means that it didn't work
        if giveCommand != 0:
            if giveCommand != "Unknown command" and isinstance(giveCommand, list):
                if interpreter.room(giveCommand[0], giveCommand[1]).getRoomName() != 0:
                    print(interpreter.room(giveCommand[0], giveCommand[1]).getRoomName())
                    area = giveCommand[0]
                    room = giveCommand[1]
                else:
                    area = 1
                    room = 1
            else:
                print(giveCommand)
        else:
            area = 1
            room = 1
        inp = input("Command: ")
    except:
        debugger.fatal("UNCAUGHT ERROR")