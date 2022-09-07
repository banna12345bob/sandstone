from engine import engine

class demo1(engine.application):
    def __init__(self, area, room):
        self.roomFile = "demo1Rooms.json"
        self.objectFile = "demo1Objects.json"
        super().__init__(area, room, self.roomFile, self.objectFile)

    def printNameandDes(self):
        name = engine.interpreter.room(self.area, self.room, self.roomFile).getRoomName()
        des = engine.interpreter.room(self.area, self.room, self.roomFile).getDesciption()
        return "You are in " + name + ":\nIt is " + des