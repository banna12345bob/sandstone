import interpreter
from debugger import debugger

# I just realised that there is a way easier way to do this using dicionaries but I can't be bothered to figure that out

class commands:
    def __init__(self, currentRoom):
        self.currentRoom = currentRoom

    def giveCommand(self, command):
        try:
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
            elif command[0] == "quit":
                quit()
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