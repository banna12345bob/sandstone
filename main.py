from engine import engine
# Please not this only works when one installs colorama I would recommended running via launch.bat

# This interfaces with application.
# It inherents all the functions from engine.application and then sets area and room correctly
class debugApp(engine.application):
    def __init__(self, area, room):
        super().__init__(area, room, "rooms.json", "objects.json")

area, room = 1, 1
print(engine.interpreter.room(area, room, "rooms.json").getRoomName())
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