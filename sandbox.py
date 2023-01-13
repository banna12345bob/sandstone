from sandstone import sandstone

# This interfaces with application.
# It inherents all the functions from sandstone.application and then sets area and room correctly
class sandbox(sandstone.application):
    def __init__(self, area, room):
        self.roomFile = "sandbox/sandboxRooms.json"
        self.objectFile = "sandbox/sandboxObjects.json"
        super().__init__(area, room, self.roomFile, self.objectFile)
    
    def run(self):
        sandstone.commandManager(self.area, self.room, self.roomsFile, self.objectFile, self.saveFile, self.player).mountCommand([sandstone.commands.help, sandstone.commands.look, sandstone.commands.use, sandstone.commands.quit, sandstone.commands.exit, sandstone.commands.inv, sandstone.commands.pickup, sandstone.commands.drop, sandstone.commands.save, sandstone.commands.load, sandstone.commands.dir, sandstone.commands.talk, sandstone.commands.kill])
        sandstone.commandManager(self.area, self.room, self.roomsFile, self.objectFile, self.saveFile, self.player).mountCommand([sandstone.commands.resetinv, sandstone.commands.give, sandstone.commands.open, sandstone.commands.debug], True)
        app = sandbox(self.area, self.room)
        print(app.printNameandDes())
        a = self.entryPoint()
        while a:
            lCommand = a[1]
            try:
                a = globals()[lCommand[0]]
                print(a(self.area, self.room, self.roomsFile, self.objectFile, self.saveFile, self.player).run())
            except:
                sandstone.debugger().error(f"There seems to be a command named {lCommand[0]} in commands.json but no command with that name has been mounted\nDid you add it in while the game was running?")
            a = self.entryPoint()

class testcmd(sandstone.command):
    def __init__(self, area, room, roomsFile, objectFile, saveFile, player):
        super().__init__(area, room, roomsFile, objectFile, saveFile, player)
        self.description = "Testing command"

    def run(self):
        return "Ran application command"

class sand(sandstone.command):
    def __init__(self, area, room, roomsFile, objectFile, saveFile, player):
        super().__init__(area, room, roomsFile, objectFile, saveFile, player)
        self.description = "Sandbox only command"

    def run(self):
        return "I hate sand. It's rough, course and it gets everywhere"

sandstone.File().deleteFile("commands.json")
sandbox(1, 1).commandManager.mountCommand(testcmd)
sandbox(1, 1).commandManager.mountCommand(sand, True)
sandbox(1, 1).run()