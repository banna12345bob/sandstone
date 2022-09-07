from engine import engine

class demo1(engine.application):
    def __init__(self, area, room):
        self.roomFile = "demo1Rooms.json"
        self.objectFile = "demo1Objects.json"
        super().__init__(area, room, self.roomFile, self.objectFile)