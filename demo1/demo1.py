from engine import engine

class demo1(engine.application):
    def __init__(self, area, room):
        super().__init__(area, room, "demo1Rooms.json", "demo1Objects.json")