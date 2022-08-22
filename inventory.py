import interpreter
from FileRead import File

class inventory:
    def __init__(self):
        self.inventory = File().readFile("save.json")["inventory"]

    def getInventory(self):
        return self.inventory

    def addToInventory(self, slot, object):
        lInventory = self.inventory[slot] = object
        File().writeFile("save.json", lInventory)

    def resetInventory(self):
        lInventory = File().readFile("save.json")
        lInventory["inventory"] = {"1":"","2":"","3":"","4":"","5":""}
        File().writeFile("save.json", lInventory)
        return