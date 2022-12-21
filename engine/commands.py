from engine import interpreter
from engine.debugger import debugger
from engine.FileRead import File
from engine.inventory import inventory

class command:
    def __init__(self):
        self.description = ""

    def run(self, lCommand):
        return lCommand

# ------------- Engine Inbuilt Commands -------------

class help(command):
    def __init__(self):
        self.description = "command (optional)\nDisplays a list of commands if the parameters is left blank otherwise displays the discription of the command"
        self.commands = File().readFile("commands.json")
    
    def run(self, lCommand):
        if len(lCommand) > 1:
            if debugger().debuggerEnabled:
                if lCommand[1] in self.commands["debug"]:
                    return(lCommand[1] + ":\n" + self.commands["debug"][lCommand[1]])
                elif lCommand[1] in self.commands:
                    return(lCommand[1] + ":\n" + self.commands[lCommand[1]])
                else:
                    return("Unknown command")
            else:
                if lCommand[1] in self.commands and lCommand[1] != "debug":
                    return(lCommand[1] + ":\n" + self.commands[lCommand[1]])
                else:
                    return("Unknown command")
        else:
            if debugger().debuggerEnabled:
                a = ""
                for i in self.commands:
                    if i == "debug":
                        a += "DEBUG ONLY:\n"
                        for b in self.commands["debug"]:
                            a += "    " + b + "\n"
                    else:
                        a += i +"\n"
                return a[0:-1]
            else:
                a = ""
                for i in self.commands:
                    if i != "debug":
                        a += i +"\n"
                return a[0:-1]

class look(command):
    def __init__(self):
        self.description = "Gets a description of something\nSytax:\nroom, furnature item"

    def run(self, lCommand):
        if len(lCommand) > 1:
            if lCommand[1] == "room":
                return "You are in " + interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getRoomName() + ":\nIt is " + self.look()
            elif lCommand[1] in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getFurnature():
                return self.furnatureLook(lCommand[1])
            else:
                return "No description found"
        else:
            return "You are in " + interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getRoomName() + ":\nIt is " + self.look()

class use(command):
    def __init__(self):
        self.description = "object\nUses an object"

    def run(self, lCommand):
        if len(lCommand) > 1:
            if lCommand[1] in inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).getInventory(True):
                if interpreter.object(self.objectFile).getUse(lCommand[1]) == 0:
                    return f'No item named "{lCommand[1]}"'
                else:
                    return interpreter.object(self.objectFile).getUse(lCommand[1])
            else:
                return f'No item named "{lCommand[1]}" in inventory'
        else:
            return "You can't use nothing"

class quit(command):
    def __init__(self):
        self.description = "(Also exit)\nQuits the program"

    def run(self, lCommand):
        return "quit"

class exit(quit):
    def __init__(self):
        self.description = "(Also quit)\nQuits the program"

    def run(self, lCommand):
        return quit().run(lCommand)

class inv(command):
    def __init__(self):
        self.description = "Opens inventory"

    def run(self, lCommand):
        items = inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).getInventory()
        return items

class pickup(command):
    def __init__(self):
        self.description = "object\nPick ups object specified"

    def run(self, lCommand):
        if len(lCommand) > 1:
            for furnature in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, player=self.player).getFurnature():
                if lCommand[1] in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getFunratureObjects(furnature):
                    return inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).addToInventory(lCommand[1], True, "", furnature)
            return f'No item named "{lCommand[1]}" in room'
        else:
            return "You picked up nothing (hint: try a second command argument eg. pickup jailkey)"

class drop(command):
    def __init__(self):
        self.description = "Drops the item specified"

    def run(self, lCommand):
        if len(lCommand) > 1:
            return inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).removeFromInventory(lCommand[1])
        else:
            return "You dropped nothing"

class save(command):
    def __init__(self, area, room, roomsFile = "rooms.json", objectFile = "objects.json", saveFile = None, player=1):
        self.area = area
        self.room = room
        self.roomsFile = roomsFile
        self.objectFile = objectFile
        self.player = player
        self.saveFile = saveFile
        self.description = "Saves the game"
    
    def run(self, lCommand):
        commandManager(self.area, self.room, self.roomsFile, self.objectFile, self.saveFile, self.player).save()
        return "Saved file"

class load(command):
    def __init__(self):
        self.description = "Loads the pervious save"

    def run(self, lCommand):
        file = File().readFile(self.saveFile)
        if file != 0:
            lFile = []
            lFile.append(file["currentArea"])
            lFile.append(file["currentRoom"])
            return lFile
        else:
            return "No save file found"

class dir(command):
    def __init__(self):
        self.description = "Tells you which directions you can go"

    def run(self, lCommand):
        return "The directions you can go are "+interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getDirections(False)

class talk(command):
    def __init__(self):
        self.description = "Talk to an NPC specified"

    def run(self, lCommand):
        if len(lCommand) > 1:
            if interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).checkNpcKilled(lCommand[1]) != True:
                x = (interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getNpcDialouge(lCommand[1]))
                if x != False:
                    if x == "quit":
                        return "quit"
                    try:
                        print(x["start"])
                    except:
                        print(x)
                    if interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).checkItemGiven(lCommand[1]) == False:
                        inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, self.player, self.saveFile).addToInventory(x["gives"], npc=lCommand[1])
                        return f"{lCommand[1]} gave you {x['gives']}"
                    else:
                        return f"{lCommand[1]} has already given you an item"
                else:
                    return ""
            else:
                return "Their dead stop trying to talk to them"
        else:
            return "You talk to thin air but then you relise you're going crazy"

class kill(command):
    def __init__(self):
        self.description = "Kills an NPC specified"

    def run(self, lCommand):
        if len(lCommand) > 1:
            drops = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getNpcDrops(lCommand[1])
            if "sword" in inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).getInventory(True):
                if lCommand[1] in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getNpcs():
                    if interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).checkNpcKilled(lCommand[1]) == False:
                        interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).killNpc(lCommand[1], player=self.player)
                        if drops != "":
                            inv = inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).addToInventory(drops, True, lCommand[1])
                            if inv != 0:
                                return f"You killed {lCommand[1]}. It drops {drops}"
                        return f"You killed {lCommand[1]}"
                    else:
                        return "Their already dead"
            else:
                return "You try to kill them with your hand but can't"
        else:
            return "You try to kill the air but you can't get a hold of them"

class resetinv(command):
    def __init__(self):
        self.description = "Resets the inventory\nDEBUG ONLY"

    def run(self, lCommand):
        if debugger().debuggerEnabled:
            return inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).resetInventory()
        return "Unknown command"

class give(command):
    def __init__(self):
        self.description = "give object slot\nGives an object\nDEBUG ONLY"
    
    def run(self, lCommand):
        if len(lCommand) > 1:
            if debugger().debuggerEnabled:
                try:
                    if lCommand[2] != "":
                        inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).addToInventory(lCommand[1], False, False, "", lCommand[2])
                except:
                    inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).addToInventory(lCommand[1], False)
                return f"Gave item {lCommand[1]}"
            return "Unknown command"
        else:
            return "Two arguments required"

class open(command):
    def __init__(self):
        self.description = "Prints out the contents of a specified JSON file\nDEBUG ONLY"
    
    def run(self, lCommand):
        if len(lCommand) > 1:
            if debugger().debuggerEnabled:
                return File().readFile(lCommand[1])
            return "Unknown command"
        else:
            return "Two arguments required"

class debug(command):
    def __init__(self):
        self.description = "(info or warning or error or fatal) msg\nLogs a debug message\nDEBUG ONLY"
    
    def run(self, lCommand):
        if len(lCommand) > 1:
            if debugger().debuggerEnabled:
                match lCommand[1]:
                    case "info":
                        return debugger(True).info(lCommand[2:len(lCommand)])
                    case "warning":
                        return debugger(True).warning(lCommand[2:len(lCommand)])
                    case "error":
                        return debugger(True).error(lCommand[2:len(lCommand)])
                    case "fatal":
                        return debugger(True).fatal(lCommand[2:len(lCommand)])
                    case _:
                        return "Unknown command"
            else:
                return "Unknown command"
        else:
            return "Two arguments required"

class commandManager:
    def __init__(self, area, currentRoom, roomsFile = "rooms.json", objectFile = "objects.json", saveFile = None, player=1):
        self.currentRoom = currentRoom
        self.currentArea = area
        self.roomsFile = roomsFile
        self.objectFile = objectFile
        self.player = player
        self.saveFile = saveFile
        # This just is a list of all the commands
        try:
            self.commands = File().readFile("commands.json")
        except:
            self.commands = ""


    def giveCommand(self, lCommand):
        try:
            lCommand = lCommand.lower()
            lCommand = lCommand.split(" ")

            # I can't find a way to make this work with the match case statement so I'm just gonna leave it here for now
            if lCommand[0] in interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getDirections():
                return self.direction(lCommand[0], inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile))

            # could probably find a smarter way to do this
            if lCommand[0] in self.commands:
                if lCommand[0] == "help":
                    return(help().run(lCommand))
                elif lCommand[0] == "look":
                    return(look().run(lCommand))
                elif lCommand[0] == "use":
                    return(use().run(lCommand))
                elif lCommand[0] == "quit":
                    return quit().run(lCommand)
                elif lCommand[0] == "exit":
                    return exit().run(lCommand)
                elif lCommand[0] == "inv":
                    return inv().run(lCommand)
                elif lCommand[0] == "pickup":
                    return pickup().run(lCommand)
                elif lCommand[0] == "drop":
                    return drop().run(lCommand)
                elif lCommand[0] == "save":
                    return save(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, self.saveFile, self.player).run(lCommand)
                elif lCommand[0] == "load":
                    return load().run(lCommand)
                elif lCommand[0] == "dir":
                    return dir().run(lCommand)
                elif lCommand[0] == "talk":
                    return talk().run(lCommand)
                elif lCommand[0] == "kill":
                    return kill().run(lCommand)
                elif lCommand[0] == "resetinv":
                    return resetinv().run(lCommand)
                elif lCommand[0] == "give":
                    return give().run(lCommand)
                elif lCommand[0] == "open":
                    return open().run(lCommand)
                elif lCommand[0] == "debug":
                    return debug().run(lCommand)
                else:
                    return "Client commands currently not supported"
            else:
                return "Unknown command"
        except:
            return 0

    def direction(self, direction, inv):
        iDirection = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getDirection(direction, player=self.player , inv=inv)
        if iDirection == "":
            return "Unknown command"
        elif iDirection == 0:
            return 0
        else:
            return iDirection

    def look(self):
        iDescription = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getDesciption()
        if iDescription == 0:
            return 0
        else:
            return iDescription
    
    def furnatureLook(self, furnature):
        iDescription = interpreter.room(self.currentArea, self.currentRoom, self.roomsFile, self.player).getFurnatureDescription(furnature)
        if iDescription == 0:
            return 0
        elif iDescription == "":
            return "No furnature description found"
        else:
            return iDescription

    def save(self):
        try:
            save = File().readFile(self.saveFile)
        except:
            save = {}
        save["currentRoom"] = int(self.currentRoom)
        save["currentArea"] = int(self.currentArea)
        File().writeFile(self.saveFile, save)
        empty = False
        try:
            for i in save["inventory"]:
                if save["inventory"][i] == "":
                    empty = True
                else:
                    empty = False
        except:
            if empty == False:
                inventory(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile).resetInventory(True)

    def mountCommand(self, lCommand, isDebug = False):
        lCommand: command or list
        if not isDebug:
            if isinstance(lCommand, list):
                for cmd in lCommand:
                    if cmd.__name__ != "save":
                        self.commands[cmd.__name__] = cmd().description
                    else:
                        self.commands[cmd.__name__] = cmd(self.currentArea, self.currentRoom, self.roomsFile, self.objectFile, self.saveFile, self.player).description
                    File().writeFile("commands.json", self.commands)
            elif issubclass(lCommand, command):
                self.commands[lCommand.__name__] = lCommand().description
                File().writeFile("commands.json", self.commands)
                return self.commands
        elif isDebug:
            if isinstance(lCommand, list):
                for cmd in lCommand:
                    try:
                        self.commands["debug"][cmd.__name__] = cmd().description
                    except:
                        self.commands["debug"] = {}
                        self.commands["debug"][cmd.__name__] = cmd().description
                    File().writeFile("commands.json", self.commands)
            elif issubclass(lCommand, command):
                self.commands["debug"][lCommand.__name__] = lCommand().description
                File().writeFile("commands.json", self.commands)
                return self.commands