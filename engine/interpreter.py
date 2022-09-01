from engine.FileRead import File
from engine.debugger import debugger

class room:
    def __init__(self, area, room, iFile):
        self.file = File().readFile(iFile)
        if self.file == 0:
            debugger().fatal(f"Failed to read {iFile}")
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
        try:
            return self.file[str(self.area)][str(self.room)]["description"]
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0


    def getFurnature(self):
        furnatures = []
        try:
            for furnature in self.file[str(self.area)][str(self.room)]["furnature"]:
                furnatures.append(furnature)
            return furnatures
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getFurnatureDescription(self, furnature):
        description = ""
        furnature = furnature.lower()
        try:
            if furnature in self.getFurnature():
                description = self.file[str(self.area)][str(self.room)]["furnature"][furnature]["description"]
            return description
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getFunratureObjects(self, furnature):
        objects = []
        furnature = furnature.lower()
        try:
            if furnature in self.getFurnature():
                for i in self.file[str(self.area)][str(self.room)]["furnature"][furnature]["objects"]:
                    objects.append(i)
            return objects
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getFunratureObjectLocation(self, furnature, object):
        furnature = furnature.lower()
        des = "No object description found"
        object = object.lower()
        try:
            if object in self.getFunratureObjects(furnature):
                des = self.file[str(self.area)][str(self.room)]["furnature"][furnature]["objects"][object]["location"]
            return des
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getDirections(self):
        rDirections = []
        try:
            for direction in self.file[str(self.area)][str(self.room)]["directions"]:
                rDirections.append(direction)
            return rDirections
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getDirection(self, direction):
        rDirections = ""
        direction = direction.lower()
        try:
            if direction in self.getDirections():
                rDirections = self.file[str(self.area)][str(self.room)]["directions"][direction]
                rDirections = rDirections.split(":")
            return rDirections
        except:
            # Just a quick error catcher 
            # NOTE: this is not a "quick" error cathcer as I build a debug interface for it
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0
    
    def checkItemPickedUp(self, furnature, object):
        furnature = furnature.lower()
        pickedUp = False
        object = object.lower()
        try:
            if object in self.getFunratureObjects(furnature):
                try:
                    pickedUp = self.file[str(self.area)][str(self.room)]["furnature"][furnature]["objects"][object]["pickedup"]
                except:
                    return pickedUp
            return pickedUp
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

class object:
    def __init__(self, iFile):
        self.file = File().readFile(iFile)
        if self.file == 0:
            debugger().fatal(f"Failed to read {iFile}")

    def getObjects(self):
        objects = []
        for i in self.file:
            objects.append(i)
        return objects
    
    def getUse(self, object):
        object = object.lower()
        try:
            if object in self.getObjects():
                return self.file[object]["use"]
            else:
                return 0
        except:
            return "This object has no uses defined"

    def getDescription(self, object):
        object = object.lower()
        if object in self.getObjects():
            return self.file[object]["description"]
        else:
            return "Object not found"

    def getColour(self, object):
        object = object.lower()
        if object in self.getObjects():
            return self.file[object]["colour"]
        else:
            return "Object not found"
