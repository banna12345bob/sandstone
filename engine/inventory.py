from engine.FileRead import File
from engine import commands
from engine import interpreter

# Welcome to the inventory class possibly the worst coded part of the engine
class inventory:
    def __init__(self, area, room, roomsFile, objectFile):
        self.area = area
        self.room = room
        self.roomsFile = roomsFile
        self.objectFile = objectFile
        self.inventory = File().readFile("save.json")
        if self.inventory == 0:
            self.resetInventory()
            self.inventory = File().readFile("save.json")

    # This class returns the inventory with each item on a new line
    def getInventory(self, list=False):
        if list == False:
            a = ""
        elif list == True:
            a = []
        for i in self.inventory["inventory"]:
            if self.inventory["inventory"][i] == "":
                a = a
            else:
                if list == False:
                    a += self.inventory["inventory"][i] + "\n"
                elif list == True:
                    a.append(self.inventory["inventory"][i])
        if a == "":
            return "No items in inventory"
        if list == True:
            return a
        elif list == False:
            return a[0:-1]

    # Adds items to the inventory based on slot
    def addToInventory(self, object, checkExists = True, furnature="", slot=""):
        if slot != "" and checkExists == False:
            self.inventory["inventory"][slot] = object
            File().writeFile("save.json", self.inventory)
        elif checkExists == False:
            if object in interpreter.object(self.objectFile).getObjects():
                for i in self.inventory["inventory"]:
                    if self.inventory["inventory"][i] == "":
                        self.inventory["inventory"][i] = object
                        File().writeFile("save.json", self.inventory)
                        return f"Picked up {object}"
                return "Inventory full"
        else:
            if object in interpreter.object(self.objectFile).getObjects():
                if checkExists == True:
                    if interpreter.room(self.area, self.room, self.roomsFile).checkItemPickedUp(furnature, object) == False:
                        for i in self.inventory["inventory"]:
                            if self.inventory["inventory"][i] == "":
                                self.inventory["inventory"][i] = object
                                File().writeFile("save.json", self.inventory)
                                rooms = File().readFile(self.roomsFile)
                                rooms[str(self.area)][str(self.room)]["furnature"][furnature]["objects"][object]["pickedup"] = True
                                File().writeFile(self.roomsFile, rooms)
                                return f"Picked up {object}"
                        return "Inventory full"
                    else:
                        return "You already picked up the item silly"

    # Just removes items from the inventory
    def removeFromInventory(self, object, slot=""):
        if slot != "":
            self.inventory["inventory"][slot] = ""
            File().writeFile("save.json", self.inventory)
        else:
            for i in self.inventory["inventory"]:
                if self.inventory["inventory"][i] == object:
                    self.inventory["inventory"][i] = ""
                    File().writeFile("save.json", self.inventory)
                    return f"Dropped {object}"
            return "Item not in inventory"

    # Sets all invnetory slots to blank effectively wipping the inventory clean
    # This was the most dificult function to get working as I did a stupid eailer on and didn't notice
    def resetInventory(self):
        commands.commands(self.area, self.room, self.roomsFile).save()
        lInventory = self.inventory
        if lInventory == 0:
            lInventory = {}
        lInventory["inventory"] = {"1":"","2":"","3":"","4":"","5":""}
        File().writeFile("save.json", lInventory)
        furnatures = interpreter.room(self.area, self.room, self.roomsFile).getFurnature()
        for furnature in furnatures:
            objects = interpreter.room(self.area, self.room, self.roomsFile).getFunratureObjects(furnature)
            for object in objects:
                rooms = File().readFile(self.roomsFile)
                rooms[str(self.area)][str(self.room)]["furnature"][furnature]["objects"][object]["pickedup"] = False
                File().writeFile(self.roomsFile, rooms)
        return "Reset Inventory"

    # This function is never used and I don't know why it is here
    def getNumSlots(self):
        lInventory = self.inventory["inventory"]
        slots = 0
        for i in lInventory:
            slots += 1
        return slots
