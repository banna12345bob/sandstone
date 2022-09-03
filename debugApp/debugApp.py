from engine import engine

# This interfaces with application.
# It inherents all the functions from engine.application and then sets area and room correctly
class debugApp(engine.application):
    def __init__(self, area, room):
        super().__init__(area, room, "debugRooms.json", "debugObjects.json")