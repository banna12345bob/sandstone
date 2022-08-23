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

            # I can't find a way to make this work with the match case statement
            if command[0] in interpreter.room(self.currentRoom).getDirections():
                return int(self.direction(command[0]))

            match command[0]:
                case "look":
                    if command[1] == "room":
                        return self.look()
                    elif command[1] in interpreter.room(self.currentRoom).getFurnature():
                        return self.furnatureLook(command[1])
                    else:
                        return "No description found"
                
                case "quit"|"exit":
                    quit()

                case "inv":
                    items = inventory().getInventory()
                    return items

                case "save":
                    self.save()
                    return "Saved file"

                case "load":
                    return int(File().readFile("save.json")["currentRoom"])

            #------------------ DEBUG COMMANDS ------------------#
                case "resetinv":
                    if debugger().debuggerEnabled:
                        inventory().resetInventory(self.currentRoom)
                        return "Inventory reset"
                    return "Unknown command"

                case "give":
                    if debugger().debuggerEnabled:
                        inventory().addToInventory(command[1], command[2])
                        return f"Gave item {command[2]}"
                    return "Unknown command"

                case "open":
                    if debugger().debuggerEnabled:
                        return File().readFile(command[1])
                    return "Unknown command"

                case "debug":
                    if debugger().debuggerEnabled:
                        match command[1]:
                            case "info":
                                return debugger().info(command[2])
                            case "warning":
                                return debugger().warning(command[2])
                            case "error":
                                return debugger().error(command[2])
                            case "fatal":
                                return debugger().fatal(command[2])
                            case _:
                                return "Unknown command"
                    else:
                        return "Unknown command"
                case _:
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