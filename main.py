from engine import engine
from demo1.demo1 import demo1
# Please not this only works when one installs colorama I would recommended running via launch.bat

area, room = 1, 1
print(demo1(area, room).printNameandDes())
inp = input("Command: ")
while inp:
    try:
        debugapp = demo1(area, room)
        cmd = debugapp.commandRun(inp)
        if cmd != "quit":
            if isinstance(cmd, list):
                area, room = debugapp.area, debugapp.room
                print(demo1(area, room).printNameandDes())
            else:
                print(cmd)
        else:
            break
        inp = input("Command: ")
    except:
        engine.debugger().fatal("UNCAUGHT ERROR")
        quit()