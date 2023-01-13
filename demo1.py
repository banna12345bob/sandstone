from sandstone import sandstone

class demo1(sandstone.application):
    def __init__(self, area, room):
        self.roomFile = "demo1/demo1Rooms.json"
        self.objectFile = "demo1/demo1Objects.json"
        super().__init__(area, room, self.roomFile, self.objectFile, saveFile="save.json")

demo1(1, 1).run()