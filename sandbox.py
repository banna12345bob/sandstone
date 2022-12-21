from engine import engine

# This interfaces with application.
# It inherents all the functions from engine.application and then sets area and room correctly
class sandbox(engine.application):
    def __init__(self, area, room):
        self.roomFile = "sandbox/sandboxRooms.json"
        self.objectFile = "sandbox/sandboxObjects.json"
        super().__init__(area, room, self.roomFile, self.objectFile)

class testcmd(engine.command):
    def __init__(self):
        self.description = "Testing command"
    
    def run(self):
        return "Ran application command"

sand = sandbox(1,1)
sand.commandManager.mountCommand(testcmd)

sand.entryPoint()