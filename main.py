from engine import engine
from debugApp.debugApp import debugApp
# Please not this only works when one installs colorama I would recommended running via launch.bat

area, room = 1, 1
print(engine.interpreter.room(area, room, "debugRooms.json").getRoomName())
inp = input("Command: ")
while inp:
    try:
        debugapp = debugApp(area, room)
        cmd = debugapp.commandRun(inp)
        if cmd != "quit":
            print(cmd)
            area, room = debugapp.area, debugapp.room
        else:
            break
        inp = input("Command: ")
    except:
        engine.debugger().fatal("UNCAUGHT ERROR")