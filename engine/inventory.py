from engine.FileRead import File
from engine import commands

# Welcome to the inventory class possibly the worst coded part of the engine
class inventory:
    def __init__(self, area, room):
        self.area = area
        self.room = room
        self.inventory = File().readFile("save.json")
        if self.inventory == 0:
            self.resetInventory()
            self.inventory = File().readFile("save.json")

    # This class returns the inventory with each item on a new line
    def getInventory(self):
        a = ""
        for i in self.inventory["inventory"]:
            if self.inventory["inventory"][i] == "":
                a = a
            else:
                a += self.inventory["inventory"][i] + "\n"
        if a == "":
            return "No items in inventory"
        return a[0:-1]

    # Adds items to the inventory based on slot
    # TODO Add a check to see if the object that is being added is an actual object as defined by objects.json
    def addToInventory(self, object, slot=""):
        lInventory = self.inventory
        if slot != "":
            lInventory["inventory"][slot] = object
            File().writeFile("save.json", lInventory)
        else:
            for i in lInventory["inventory"]:
                if lInventory["inventory"][i] == "":
                    lInventory["inventory"][i] = object
                    File().writeFile("save.json", lInventory)
                    return f"Picked up {object}"
            return "Inventory full"

    # Just removes items from the inventory
    def removeFromInventory(self, object, slot=""):
        lInventory = self.inventory
        if slot != "":
            lInventory["inventory"][slot] = ""
            File().writeFile("save.json", lInventory)
        else:
            for i in lInventory["inventory"]:
                if lInventory["inventory"][i] == object:
                    lInventory["inventory"][i] = ""
                    File().writeFile("save.json", lInventory)
                    return f"Dropped {object}"
            return "Item not in inventory"

    # Sets all invnetory slots to blank effectively wipping the inventory clean
    # This was the most dificult function to get working as I did a stupid eailer on and didn't notice
    def resetInventory(self):
        commands.commands(self.area, self.room).save()
        lInventory = File().readFile("save.json")
        if lInventory == 0:
            lInventory = {}
        lInventory["inventory"] = {"1":"","2":"","3":"","4":"","5":""}
        File().writeFile("save.json", lInventory)
        return "Reset Inventory"

    # This function is never used and I don't know why it is here
    def getNumSlots(self):
        lInventory = self.inventory["inventory"]
        slots = 0
        for i in lInventory:
            slots += 1
        return slots
