from engine import engine
from demo1.demo1 import demo1
# Please not this only works when one installs colorama I would recommended running via launch.bat

area, room = 1, 1
print(engine.interpreter.room(area, room, "demo1Rooms.json").getRoomName() + ":\n" + engine.interpreter.room(area, room, "demo1Rooms.json").getDesciption())
inp = input("Command: ")
while inp:
    try:
        debugapp = demo1(area, room)
        cmd = debugapp.commandRun(inp)
        if cmd != "quit":
            print(cmd)
            area, room = debugapp.area, debugapp.room
        else:
            break
        inp = input("Command: ")
    except:
        engine.debugger().fatal("UNCAUGHT ERROR")