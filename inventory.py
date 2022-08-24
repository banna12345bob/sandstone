from FileRead import File
import commands

class inventory:
    def __init__(self):
        try:
            self.inventory = File().readFile("save.json")
        except:
            self.inventory = File().readFile("save.json")

    def getInventory(self):
        a = ""
        for i in self.inventory["inventory"]:
            if self.inventory["inventory"][i] == "":
                a += "No item" + "\n"
            else:
                a += self.inventory["inventory"][i] + "\n"
        return a[0:-1]

    def addToInventory(self, slot, object):
        lInventory = self.inventory
        lInventory["inventory"][slot] = object
        File().writeFile("save.json", lInventory)

    def resetInventory(self, currentRoom):
        commands.commands(currentRoom).save()
        lInventory = File().readFile("save.json")
        lInventory["inventory"] = {"1":"","2":"","3":"","4":"","5":""}
        File().writeFile("save.json", lInventory)
        return

    def getNumSlots(self):
        lInventory = self.inventory["inventory"]
        slots = 0
        for i in lInventory:
            slots += 1
        return slots