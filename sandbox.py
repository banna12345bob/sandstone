from engine import engine

# This interfaces with application.
# It inherents all the functions from engine.application and then sets area and room correctly
class sandbox(engine.application):
    def __init__(self, area, room):
        self.roomFile = "sandbox/sandboxRooms.json"
        self.objectFile = "sandbox/sandboxObjects.json"
        super().__init__(area, room, self.roomFile, self.objectFile)

sandbox(1, 1).entryPoint()