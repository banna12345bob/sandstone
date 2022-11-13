from engine import interpreter
from engine.debugger import debugger
from engine.commands import commands
from engine.inventory import inventory
from engine.FileRead import File

# This class is for all applications that will be run with the engine
class application:
    def __init__(self, area, room, roomsFile, objectFile, player=1):
        self.area, self.room = area, room
        self.roomsFile, self.objectFile = roomsFile, objectFile
        self.player = player

    def commandRun(self, inp):
        giveCommand = commands(self.area, self.room, self.roomsFile, self.objectFile, player=self.player).giveCommand(inp)
        # For this design if a function returns 0 it means that it didn't work
        if giveCommand != 0:
            if giveCommand != "Unknown command" and isinstance(giveCommand, list):
                if interpreter.room(giveCommand[0], giveCommand[1], self.roomsFile, self.player).getRoomName() != 0:
                    self.area, self.room = giveCommand[0], giveCommand[1]
                    commands(self.area, self.room, self.roomsFile, self.objectFile).save()
                    return giveCommand
                else:
                    self.area, self.room = 1, 1
                    return interpreter.room(self.area, self.room, self.roomsFile, self.player).getRoomName()
            else:
                return giveCommand
        else:
            self.area, self.room = 1, 1
            return interpreter.room(self.area, self.room, self.roomsFile, self.player).getRoomName()
        
    def printNameandDes(self):
        name = interpreter.room(self.area, self.room, self.roomsFile, self.player).getRoomName()
        des = interpreter.room(self.area, self.room, self.roomsFile, self.player).getDesciption()
        return "You are in " + name + ":\nIt is " + des