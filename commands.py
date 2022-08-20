import interpreter

class commands:

    def __init__(self, currentRoom):
        self.currentRoom = currentRoom

    def direction(self, direction):
        currentRoom = self.currentRoom
        iDirection = interpreter.room(currentRoom).getDirection(direction)
        if iDirection == "":
            return "Unknown command"
        elif iDirection == 0:
            return 0
        else:
            currentRoom = iDirection
            return iDirection