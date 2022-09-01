from engine import interpreter
from engine.debugger import debugger
from engine.commands import commands
from engine.inventory import inventory
from engine.FileRead import File

# This class is for all applications that will be run with the engine
class application:
    def __init__(self, area, room, roomsFile, objectFile):
        self.area = area
        self.room = room
        self.roomsFile = roomsFile
        self.objectFile = objectFile
    
    def commandRun(self, inp):
        giveCommand = commands(self.area, self.room, self.roomsFile, self.objectFile).giveCommand(inp)
        # For this design if a function returns 0 it means that it didn't work
        if giveCommand != 0:
            if giveCommand != "Unknown command" and isinstance(giveCommand, list):
                if interpreter.room(giveCommand[0], giveCommand[1], self.roomsFile).getRoomName() != 0:
                    self.area = giveCommand[0]
                    self.room = giveCommand[1]
                    return interpreter.room(self.area, self.room, self.roomsFile).getRoomName()
                else:
                    self.area = 1
                    self.room = 1
                    return interpreter.room(self.area, self.room, self.roomsFile).getRoomName()
            else:
                return giveCommand
        else:
            self.area = 1
            self.room = 1
            return interpreter.room(self.area, self.room, self.roomsFile).getRoomName()