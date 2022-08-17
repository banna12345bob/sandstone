import FileRead
import interpreter


class room:
    file = "rooms.json"

    def __init__(self, room = 0, dFile = file):
        self.file = FileRead.readFile(dFile)
        self.room = room

    def getName(self):
        return self.file[str(self.room)]["name"]


    def getDesciption(self):
        rFile = self.file
        room = self.room
        return rFile[str(room)]["description"]


    def getFurnature(self):
        rFile = self.file
        room = self.room
        furnatures = []
        for furnature in rFile[str(room)]["furnature"]:
            furnatures.append(furnature)
        return furnatures

    def getFurnatureDescription(self, furnature):
        rFile = self.file
        room = self.room
        description = "No furnature description found"
        furnature = furnature.lower()
        if furnature in self.getFurnature():
            description = rFile[str(room)]["furnature"][furnature]["description"]
        return description

    def getFunratureObjects(self, furnature):
        rFile = self.file
        room = self.room
        objects = []
        furnature = furnature.lower()
        if furnature in self.getFurnature():
            for i in rFile[str(room)]["furnature"][furnature]["objects"]:
                objects.append(i)
        return objects

    def getFunratureObjectDescriptions(self, furnature, object):
        rFile = self.file
        room = self.room
        furnature = furnature.lower()
        des = "No object description found"
        object = object.lower()
        if object in self.getFunratureObjects(furnature):
            des = rFile[str(room)]["furnature"][furnature]["objects"][object]
        return des

    def getDirections(self, direction):
        rFile = self.file
        room = self.room
        direction = direction.lower()
        if direction in rFile[str(room)]["directions"]:
            rDirections = rFile[str(room)]["directions"][direction]
        return rDirections

class object:
    file = "objects.json"

    def __init__(self, room = 0, dFile = file):
        self.file = FileRead.readFile(dFile)

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

    def getColour(self, object):
        rFile = self.file
        object = object.lower()
        if object in self.getObjects():
            return rFile[object]["colour"]