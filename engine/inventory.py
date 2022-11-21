from engine.FileRead import File
from engine import commands
from engine import interpreter

# Welcome to the inventory class possibly the worst coded part of the engine
class inventory:
    def __init__(self, area, room, roomsFile, objectFile, player, saveFile):
        self.area = area
        self.room = room
        self.roomFile = roomsFile[0:-5]+str(player)+roomsFile[-5:len(roomsFile)]
        self.roomsFile = roomsFile
        self.player = player
        self.objectFile = objectFile
        self.saveFile = saveFile
        try:
            self.inventory = File().readFile(self.saveFile)
        except:
            self.inventory = 0
            self.resetInventory()
            self.inventory = File().readFile(self.saveFile)

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
    def addToInventory(self, object, checkExists = True, npc = "", furnature="", slot=""):
        if slot != "" and checkExists == False:
            self.inventory["inventory"][slot] = object
            File().writeFile(self.saveFile, self.inventory)
        elif checkExists == False:
            if object in interpreter.object(self.objectFile).getObjects():
                for i in self.inventory["inventory"]:
                    if self.inventory["inventory"][i] == "":
                        self.inventory["inventory"][i] = object
                        File().writeFile(self.saveFile, self.inventory)
                        return f"Picked up {object}"
                i = int(i)
                i += 1
                self.inventory["inventory"][str(i)] = object
                File().writeFile(self.saveFile, self.inventory)
                return f"Picked up {object}"
                # return "Inventory full"
        else:
            if object in interpreter.object(self.objectFile).getObjects():
                if checkExists == True:
                    if interpreter.room(self.area, self.room, self.roomsFile, self.player).checkItemPickedUp(furnature, object) == False:
                        if interpreter.room(self.area, self.room, self.roomsFile, self.player).checkItemGiven(npc) == False:
                            for i in self.inventory["inventory"]:
                                if self.inventory["inventory"][i] == "":
                                    self.inventory["inventory"][i] = object
                                    File().writeFile(self.saveFile, self.inventory)
                                    if npc == "":
                                        try:
                                            rooms = File().readFile(self.roomFile)
                                        except:
                                            rooms = File().readFile(self.roomsFile)
                                        rooms[str(self.area)][str(self.room)]["furnature"][furnature]["objects"][object]["pickedup"] = True
                                        File().writeFile(self.roomFile, rooms)
                                    else:
                                        try:
                                            rooms = File().readFile(self.roomFile)
                                        except:
                                            rooms = File().readFile(self.roomsFile)
                                        rooms[str(self.area)][str(self.room)]["npcs"][npc]["given"] = True
                                        File().writeFile(self.roomFile, rooms)
                                    return f"Picked up {object}"
                            return "Inventory full"
                        else:
                            return 0
                    else:
                        return "You already picked up the item silly"

    # Just removes items from the inventory
    def removeFromInventory(self, object, slot=""):
        if slot != "":
            self.inventory["inventory"][slot] = ""
            File().writeFile(self.saveFile, self.inventory)
        else:
            for i in self.inventory["inventory"]:
                if self.inventory["inventory"][i] == object:
                    self.inventory["inventory"][i] = ""
                    File().writeFile(self.saveFile, self.inventory)
                    return f"Dropped {object}"
            return "Item not in inventory"

    # Sets all invnetory slots to blank effectively wipping the inventory clean
    # This was the most dificult function to get working as I did a stupid eailer on and didn't notice
    def resetInventory(self, fromSave = False):
        if fromSave == False:
            commands.commands(self.area, self.room, self.roomsFile, saveFile=self.saveFile).save()
        lInventory = self.inventory
        if lInventory == 0:
            lInventory = {}
        lInventory["inventory"] = {"1":"","2":"","3":"","4":"","5":""}
        File().writeFile(self.saveFile, lInventory)
        furnatures = interpreter.room(self.area, self.room, self.roomsFile, self.player).getFurnature()
        for furnature in furnatures:
            objects = interpreter.room(self.area, self.room, self.roomsFile, self.player).getFunratureObjects(furnature)
            for object in objects:
                try:
                    rooms = File().readFile(self.roomFile)
                except:
                    rooms = File().readFile(self.roomsFile)
                rooms[str(self.area)][str(self.room)]["furnature"][furnature]["objects"][object]["pickedup"] = False
                File().writeFile(self.roomFile, rooms)
        npcs = interpreter.room(self.area, self.room, self.roomsFile, self.player).getNpcs()
        for npc in npcs:
            try:
                rooms = File().readFile(self.roomFile)
            except:
                rooms = File().readFile(self.roomsFile)
            rooms[str(self.area)][str(self.room)]["npcs"][npc]["given"] = False
            File().writeFile(self.roomFile, rooms)
        return "Reset Inventory"

    # This function is never used and I don't know why it is here
    def getNumSlots(self):
        lInventory = self.inventory["inventory"]
        slots = 0
        for i in lInventory:
            slots += 1
        return slots
