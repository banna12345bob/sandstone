from engine.FileRead import File
from engine.debugger import debugger


class room:
    file = "rooms.json"

    def __init__(self, area = 1, room = 1, dFile = file):
        self.file = File().readFile(dFile)
        if self.file == 0:
            debugger().fatal(f"Failed to read {dFile}")
        self.room = room
        self.area = area

    def getAreaName(self):
        try:
            return self.file[str(self.area)]["name"]
        except:
            debugger().error(f"Area {self.area} not found")

    def getRoomName(self):
        try:
            return self.file[str(self.area)][str(self.room)]["name"]
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0
        


    def getDesciption(self):
        rFile = self.file
        room = self.room
        area = self.area
        try:
            return rFile[str(area)][str(room)]["description"]
        except:
            debugger().error(f"Room {area}:{room} not found")
            return 0


    def getFurnature(self):
        rFile = self.file
        room = self.room
        area = self.area
        furnatures = []
        try:
            for furnature in rFile[str(area)][str(room)]["furnature"]:
                furnatures.append(furnature)
            return furnatures
        except:
            debugger().error(f"Room {area}:{room} not found")
            return 0

    def getFurnatureDescription(self, furnature):
        rFile = self.file
        room = self.room
        area = self.area
        description = ""
        furnature = furnature.lower()
        try:
            if furnature in self.getFurnature():
                description = rFile[str(area)][str(room)]["furnature"][furnature]["description"]
            return description
        except:
            debugger().error(f"Room {area}:{room} not found")
            return 0

    def getFunratureObjects(self, furnature):
        rFile = self.file
        room = self.room
        area = self.area
        objects = []
        furnature = furnature.lower()
        try:
            if furnature in self.getFurnature():
                for i in rFile[str(area)][str(room)]["furnature"][furnature]["objects"]:
                    objects.append(i)
            return objects
        except:
            debugger().error(f"Room {area}:{room} not found")
            return 0

    def getFunratureObjectDescriptions(self, furnature, object):
        rFile = self.file
        room = self.room
        area = self.area
        furnature = furnature.lower()
        des = "No object description found"
        object = object.lower()
        try:
            if object in self.getFunratureObjects(furnature):
                des = rFile[str(area)][str(room)]["furnature"][furnature]["objects"][object]
            return des
        except:
            debugger().error(f"Room {area}:{room} not found")
            return 0

    def getDirections(self):
        rFile = self.file
        room = self.room
        area = self.area
        rDirections = []
        try:
            for direction in rFile[str(area)][str(room)]["directions"]:
                rDirections.append(direction)
            return rDirections
        except:
            debugger().error(f"Room {area}:{room} not found")
            return 0

    def getDirection(self, direction):
        rFile = self.file
        room = self.room
        area = self.area
        rDirections = ""
        direction = direction.lower()
        try:
            if direction in self.getDirections():
                rDirections = rFile[str(area)][str(room)]["directions"][direction]
                rDirections = rDirections.split(":")
            return rDirections
        except:
            # Just a quick error catcher 
            # NOTE: this is not a "quick" error cathcer as I build a debug interface for it
            debugger().error(f"Room {area}:{room} not found")
            return 0

# This class is not currently being used like anywhere exept for inside of itself
class object:
    file = "objects.json"

    def __init__(self, room = 0, dFile = file):
        self.file = File().readFile(dFile)
        if self.file == 0:
            debugger().fatal(f"Failed to read {dFile}")

    def getObjects(self):
        objects = []
        for i in self.file:
            objects.append(i)
        return objects
    
    def getDescription(self, object):
        rFile = self.file
        object = object.lower()
        if object in self.getObjects():
            return rFile[object]["description"]
        else:
            return "Object not found"

    def getColour(self, object):
        rFile = self.file
        object = object.lower()
        if object in self.getObjects():
            return rFile[object]["colour"]
        else:
            return "Object not found"
