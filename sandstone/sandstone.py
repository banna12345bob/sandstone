from sandstone import interpreter
from sandstone.debugger import debugger
from sandstone.commands import commandManager
from sandstone.commands import command
from sandstone import commands
from sandstone.inventory import inventory
from sandstone.FileRead import File

# This class is for all applications that will be run with the engine
class application:
    def __init__(self, area, room, roomsFile, objectFile, player=1, saveFile = "save.json"):
        self.area, self.room = area, room
        self.roomsFile, self.objectFile = roomsFile, objectFile
        self.player = player
        self.saveFile = saveFile
        self.commandManager = commandManager(self.area, self.room, self.roomsFile, self.objectFile, player=self.player, saveFile=self.saveFile)

    def commandRun(self, inp):
        giveCommand = self.commandManager.giveCommand(inp)
        # For this design if a function returns 0 it means that it didn't work
        if giveCommand != 0:
            if giveCommand != "Unknown command" and isinstance(giveCommand, list) and giveCommand.__len__() > 1:
                if giveCommand[0] != "cmd":
                    if interpreter.room(giveCommand[0], giveCommand[1], self.roomsFile, self.player).getRoomName() != 0:
                        self.area, self.room = giveCommand[0], giveCommand[1]
                        commandManager(self.area, self.room, self.roomsFile, self.objectFile, saveFile=self.saveFile).save()
                        return giveCommand
                    else:
                        self.area, self.room = 1, 1
                        return interpreter.room(self.area, self.room, self.roomsFile, self.player).getRoomName()
                else:
                    return giveCommand
            else:
                return giveCommand
        else:
            self.area, self.room = 1, 1
            return interpreter.room(self.area, self.room, self.roomsFile, self.player).getRoomName()
        
    def printNameandDes(self):
        name = interpreter.room(self.area, self.room, self.roomsFile, self.player).getRoomName()
        des = interpreter.room(self.area, self.room, self.roomsFile, self.player).getDesciption()
        return "You are in " + name + ":\nIt is " + des

    def entryPoint(self):
        version = File().readFile("version.json")["version"]
        version = [int(x) for x in version.split(".")]

        roomVersion = str(File().readFile(self.roomsFile)["version"])
        roomVersion = [int(x) for x in roomVersion.split(".")]

        objectVersion = str(File().readFile(self.objectFile)["version"])
        objectVersion = [int(x) for x in objectVersion.split(".")]

        if (objectVersion == roomVersion):
            if (roomVersion[0] == version[0] and roomVersion[1] == version[1] and roomVersion[2] == version[2]):
                debugger().info("This application is running the right version of Sandstone")
            elif (roomVersion[0] == version[0] and roomVersion[1] <= version[1] and roomVersion[2] <= version[2]):
                debugger().warning("This application is running on a older version of Sandstone")
            else:
                debugger().fatal("This application is running on a newer version of Sandstone")
        else:
            debugger().fatal("Object file and room file version missmatch")


        inp = input("Command: ")
        while inp:
            try:
                app = application(self.area, self.room, self.roomsFile, self.objectFile, self.player, self.saveFile)
                cmd = app.commandRun(inp)
                if cmd != "quit":
                    if isinstance(cmd, list) and cmd.__len__() > 1:
                        if cmd[0] != "cmd":
                            print(app.printNameandDes())
                            self.area, self.room = app.area, app.room
                        else:
                            return cmd
                    else:
                        print(cmd)
                        self.area, self.room = app.area, app.room
                else:
                    break
                inp = input("Command: ")
            except:
                debugger().fatal("UNCAUGHT ERROR")
                quit()
        
    def run(self):
        File().deleteFile("commands.json")
        commandManager(self.area, self.room, self.roomsFile, self.objectFile, self.saveFile, self.player).mountCommand([commands.help, commands.look, commands.use, commands.quit, commands.exit, commands.inv, commands.pickup, commands.drop, commands.save, commands.load, commands.dir, commands.talk, commands.kill])
        commandManager(self.area, self.room, self.roomsFile, self.objectFile, self.saveFile, self.player).mountCommand([commands.resetinv, commands.give, commands.open, commands.debug], True)
        app = application(self.area, self.room, self.roomsFile, self.objectFile, self.player, self.saveFile)
        print(app.printNameandDes())
        a = self.entryPoint()
        while a:
            debugger().error("There are no application commands defined in this app.\nDid you add some in while the program was running?")
            a = self.entryPoint()