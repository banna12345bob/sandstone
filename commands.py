import interpreter
from debugger import debugger

class commands:

    def __init__(self, currentRoom):
        self.currentRoom = currentRoom

    def giveCommand(self, command):
        try:
            if command in interpreter.room(self.currentRoom).getDirections():
                return self.direction(command)
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