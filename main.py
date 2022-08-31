from engine import engine

# Please not this only works when one installs colorama I would recommended running via launch.bat
area = 1
room = 1
print(engine.interpreter.room(area, room).getRoomName())
inp = input("Command: ")
# This interfaces with application I want to have each indivial application inheritant from engine.application
while inp:
    try:
        app = engine.application(area, room).commandRun(inp)
        if app == 0:
            break
        else:
            if isinstance(app, list):
                area = app[0]
                room = app[1]
            else:
                if app != "quit":
                    print(app)
                else:
                    break
        inp = input("Command: ")
    except:
        engine.debugger().fatal("UNCAUGHT ERROR")