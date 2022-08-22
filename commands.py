import interpreter
from debugger import debugger
from FileRead import File
from inventory import inventory

# I just realised that there is a way easier way to do this using dicionaries but I can't be bothered to figure that out

class commands:
    def __init__(self, currentRoom):
        self.currentRoom = currentRoom

    def giveCommand(self, command):
        try:
            command = command.lower()
            command = command.split(" ")
            if command[0] in interpreter.room(self.currentRoom).getDirections():
                return int(self.direction(command[0]))
            elif command[0] == "look":
                if command[1] == "room":
                    return self.look()
                elif command[1] in interpreter.room(self.currentRoom).getFurnature():
                    return self.furnatureLook(command[1])
                else:
                    return "No description found"
            elif command[0] == "quit" or command[0] ==  "exit":
                quit()
            elif command[0] == "inv":
                items = inventory().getInventory()
                return items
            #------------------ DEBUG COMMANDS ------------------#
            elif command[0] == "resetinv" and debugger().debuggerEnabled:
                inventory().resetInventory(self.currentRoom)
                return "Inventory reset"
            elif command[0] == "give" and debugger().debuggerEnabled:
                inventory().addToInventory(command[1], command[2])
                return f"Gave item {command[2]}"
            elif command[0] == "open" and debugger().debuggerEnabled:
                return File().readFile(command[1])
            elif command[0] == "save" and debugger().debuggerEnabled:
                self.save()
                return "Saved file"
            elif command[0] == "load" and debugger().debuggerEnabled:
                return int(File().readFile("save.json")["currentRoom"])
            elif command[0] == "debug" and debugger().debuggerEnabled:
                if command[1] == "info":
                    return debugger().info(command[2])
                elif command[1] == "warning":
                    return debugger().warning(command[2])
                elif command[1] == "error":
                    return debugger().error(command[2])
                elif command[1] == "fatal":
                    return debugger().fatal(command[2])
                else:
                    return "Unknown command"
            else:
                return "Unknown command"
        except:
            return 0

    def direction(self, direction):
        currentRoom = self.currentRoom
        iDirection = interpreter.room(currentRoom).getDirection(direction)
        if iDirection == "":
            return "Unknown command"
        elif iDirection == 0:
            return 0
        else:
            return iDirection

    def look(self):
        currentRoom = self.currentRoom
        iDescription = interpreter.room(currentRoom).getDesciption()
        if iDescription == 0:
            return 0
        else:
            return iDescription
    
    def furnatureLook(self, furnature):
        currentRoom = self.currentRoom
        iDescription = interpreter.room(currentRoom).getFurnatureDescription(furnature)
        if iDescription == 0:
            return 0
        elif iDescription == "":
            return "No furnature description found"
        else:
            return iDescription

    def save(self):
        save = File().readFile("save.json")
        save["currentRoom"] = self.currentRoom
        return File().writeFile("save.json", save)