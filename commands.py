import interpreter
from debugger import debugger
from FileRead import File
from inventory import inventory

class commands:
    def __init__(self, currentRoom):
        self.currentRoom = currentRoom

    def giveCommand(self, command):
        try:
            command = command.lower()
            command = command.split(" ")
            # This just is a list of all the commands
            commands = {
                "help":"command (optional)\nDisplays a list of commands if the parameters is left blank otherwise displays the discription of the command",
                "look":"Gets a description of something\nSytax:\nroom, furnature item",
                "quit":"(Also exit)\nQuits the program",
                "inv":"Opens inventory",
                "save":"Saves the game",
                "load":"Loads the pervious save",
                "pickup":"Pick ups object specified",
                "debug":{
                    "resetinv":"Resets the inventory\nDEBUG ONLY",
                    "give":"give slot object\nGives an object\nDEBUG ONLY",
                    "open":"Prints out the contents of a specified JSON file\nDEBUG ONLY",
                    "debug":"(info or warning or error or fatal) msg\nLogs a debug message\nDEBUG ONLY"
                }
            }

            # I can't find a way to make this work with the match case statement
            if command[0] in interpreter.room(self.currentRoom).getDirections():
                return int(self.direction(command[0]))

            match command[0]:
                case "help":
                    if len(command) > 1:
                        if debugger().debuggerEnabled:
                            if command[1] in commands["debug"]:
                                return(command[1] + ":\n" + commands["debug"][command[1]])
                            elif command[1] in commands:
                                return(command[1] + ":\n" + commands[command[1]])
                            else:
                                return("Unknown command")
                        else:
                            if command[1] in commands and command[1] != "debug":
                                return(command[1] + ":\n" + commands[command[1]])
                            else:
                                return("Unknown command")
                    else:
                        if debugger().debuggerEnabled:
                            a = ""
                            for i in commands:
                                if i == "debug":
                                    a += "DEBUG ONLY:\n"
                                    for b in commands["debug"]:
                                        a += b + "\n"
                                else:
                                    a += i +"\n"
                            return a[0:-1]
                        else:
                            a = ""
                            for i in commands:
                                a += i +"\n"
                            return a[0:-7]

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
                    items = inventory(self.currentRoom).getInventory()
                    return items

                case "pickup":
                    for furnature in interpreter.room(self.currentRoom).getFurnature():
                        if command[1] in interpreter.room().getFunratureObjects(furnature):
                            return inventory().addToInventory(command[1])
                        else:
                            return f"No item named {command[1]} in room"

                case "save":
                    self.save()
                    return "Saved file"

                case "load":
                    return int(File().readFile("save.json")["currentRoom"])

                #------------------ DEBUG COMMANDS ------------------#
                case "resetinv":
                    if debugger().debuggerEnabled:
                        inventory(self.currentRoom).resetInventory(self.currentRoom)
                        return "Inventory reset"
                    return "Unknown command"

                case "give":
                    if debugger().debuggerEnabled:
                        inventory(self.currentRoom).addToInventory(command[1], command[2])
                        return f"Gave item {command[1]}"
                    return "Unknown command"

                case "open":
                    if debugger().debuggerEnabled:
                        return File().readFile(command[1])
                    return "Unknown command"

                case "debug":
                    if debugger().debuggerEnabled:
                        match command[1]:
                            case "info":
                                return debugger().info(command[2:len(command)])
                            case "warning":
                                return debugger().warning(command[2:len(command)])
                            case "error":
                                return debugger().error(command[2:len(command)])
                            case "fatal":
                                return debugger().fatal(command[2:len(command)])
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
        if save == 0:
            save = {}
        save["currentRoom"] = self.currentRoom
        return File().writeFile("save.json", save)