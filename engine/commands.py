from engine import interpreter
from engine.debugger import debugger
from engine.FileRead import File
from engine.inventory import inventory

class commands:
    def __init__(self, area, currentRoom, roomsFile = "rooms.json", objectFile = "objects.json"):
        self.currentRoom = currentRoom
        self.currentArea = area
        self.roomsFile = roomsFile
        self.objectFile = objectFile

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
                "use":"object\nUses an object",
                "pickup":"object\nPick ups object specified",
                "load":"Loads the pervious save",
                "dir":"Tells you which directions you can go",
                "talk":"Talk to an NPC specified",
                "kill":"Kills an NPC specified",
                "debug":{
                    "resetinv":"Resets the inventory\nDEBUG ONLY",
                    "give":"give object slot\nGives an object\nDEBUG ONLY",
                    "open":"Prints out the contents of a specified JSON file\nDEBUG ONLY",
                    "debug":"(info or warning or error or fatal) msg\nLogs a debug message\nDEBUG ONLY"
                }
            }

            # I can't find a way to make this work with the match case statement so I'm just gonna leave it here for now
            if command[0] in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getDirections():
                return self.direction(command[0], inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile))

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
                        return "You are in " + interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getRoomName() + ":\nIt is " + self.look()
                    elif command[1] in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getFurnature():
                        return self.furnatureLook(command[1])
                    else:
                        return "No description found"
                
                case "use":
                    if command[1] in inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile).getInventory(True):
                        if interpreter.object(self.objectFile).getUse(command[1]) == 0:
                            return f'No item named "{command[1]}"'
                        else:
                            return interpreter.object(self.objectFile).getUse(command[1])
                    else:
                        return f'No item named "{command[1]}" in inventory'

                case "quit"|"exit":
                    return "quit"
                    quit()

                case "inv":
                    items = inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile).getInventory()
                    return items

                # TODO Fix up the fact that you can pickup an item multipule times (FIXED)
                # Maybe add a function that reads and edits rooms.json adding a pickedup tag to objects
                case "pickup":
                    for furnature in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getFurnature():
                        if command[1] in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getFunratureObjects(furnature):
                            return inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile).addToInventory(command[1], True, "", furnature)
                    return f'No item named "{command[1]}" in room'

                case "drop":
                    return inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile).removeFromInventory(command[1])

                case "save":
                    self.save()
                    return "Saved file"

                case "load":
                    file = File().readFile("save.json")
                    if file != 0:
                        lFile = []
                        lFile.append(file["currentArea"])
                        lFile.append(file["currentRoom"])
                        return lFile
                    else:
                        return "No save file found"

                case "dir":
                    return "The directions you can go are "+interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getDirections(False)

                case "talk":
                    if command[1] in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getNpcs():
                            if interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).checkNpcKilled(command[1]) != True:
                                if interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).checkItemGiven(command[1]) != True:
                                    print(f"{command[1]}:")
                                    diag = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getNpcDialouge(command[1])
                                    diag = diag.split(":")
                                    try:
                                        gives = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getNpcGives(command[1], diag[0], diag[1])
                                    except:
                                        gives = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getNpcGives(command[1], diag[0])
                                    if gives != "":
                                        if gives != "quit":
                                            inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile).addToInventory(gives, True, command[1])
                                            return f"He gives you a {gives}"
                                        else:
                                            return "quit"
                                else:
                                    interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getNpcDialouge(command[1])
                            else:
                                return "Their dead stop trying to talk to them"

                case "kill":
                    if "sword" in inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile).getInventory(True):
                        if command[1] in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getNpcs():
                            interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).killNpc(command[1])
                            return f"You killed {command[1]}"
                    else:
                        return "You try to kill them with your hand but can't"

                #-------------------------------------- DEBUG COMMANDS --------------------------------------#
                case "resetinv":
                    if debugger().debuggerEnabled:
                        return inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile).resetInventory()
                    return "Unknown command"

                case "give":
                    if debugger().debuggerEnabled:
                        try:
                            if command[2] != "":
                                inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile).addToInventory(command[1], False, False, "", command[2])
                        except:
                            inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile).addToInventory(command[1], False)
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
                                return debugger(True).info(command[2:len(command)])
                            case "warning":
                                return debugger(True).warning(command[2:len(command)])
                            case "error":
                                return debugger(True).error(command[2:len(command)])
                            case "fatal":
                                return debugger(True).fatal(command[2:len(command)])
                            case _:
                                return "Unknown command"
                    else:
                        return "Unknown command"
                case _:
                    return "Unknown command"
        except:
            return 0

    def direction(self, direction, inv):
        iDirection = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getDirection(direction, inv)
        if iDirection == "":
            return "Unknown command"
        elif iDirection == 0:
            return 0
        else:
            return iDirection

    def look(self):
        iDescription = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getDesciption()
        if iDescription == 0:
            return 0
        else:
            return iDescription
    
    def furnatureLook(self, furnature):
        iDescription = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile).getFurnatureDescription(furnature)
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
        save["currentRoom"] = int(self.currentRoom)
        save["currentArea"] = int(self.currentArea)
        File().writeFile("save.json", save)