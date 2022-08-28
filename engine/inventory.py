from engine.FileRead import File
from engine import commands

class inventory:
    def __init__(self, area, room):
        self.area = area
        self.room = room
        self.inventory = File().readFile("save.json")
        if self.inventory == 0:
            self.resetInventory()
            self.inventory = File().readFile("save.json")

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

    def resetInventory(self):
        commands.commands(self.area, self.room).save()
        lInventory = File().readFile("save.json")
        if lInventory == 0:
            lInventory = {}
        lInventory["inventory"] = {"1":"","2":"","3":"","4":"","5":""}
        File().writeFile("save.json", lInventory)
        return "Reset Inventory"

    def getNumSlots(self):
        lInventory = self.inventory["inventory"]
        slots = 0
        for i in lInventory:
            slots += 1
        return slots
