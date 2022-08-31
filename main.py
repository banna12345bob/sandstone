from engine import engine

# Please not this only works when one installs colorama I would recommended running via launch.bat
room = 1
area = 1
print(engine.interpreter.room(area, room).getRoomName())
inp = input("Command: ")
while inp:
    try:
        giveCommand = engine.commands(area, room).giveCommand(inp)
        # For this design if a function returns 0 it means that it didn't work
        if giveCommand != 0:
            if giveCommand != "Unknown command" and isinstance(giveCommand, list):
                if engine.interpreter.room(giveCommand[0], giveCommand[1]).getRoomName() != 0:
                    print(engine.interpreter.room(giveCommand[0], giveCommand[1]).getRoomName())
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
        if giveCommand == "quit":
            break
        inp = input("Command: ")
    except:
        engine.debugger.fatal("UNCAUGHT ERROR")