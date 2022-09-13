from engine.FileRead import File
from engine.debugger import debugger

class room:
    def __init__(self, area, room, iFile):
        self.file = File().readFile(iFile)
        self.roomFile = iFile
        if self.file == 0:
            debugger().fatal(f"Failed to read {iFile}")
        self.room = room
        self.area = area

    def getAreaName(self):
        try:
            return self.file[str(self.area)]["name"]
        except:
            debugger().error(f"Area {self.area} not found")

    def getRoomName(self):
        try:
            return self.file[str(self.area)][str(self.room)]["name"]
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getDesciption(self):
        try:
            return self.file[str(self.area)][str(self.room)]["description"]
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getFurnature(self):
        furnatures = []
        try:
            for furnature in self.file[str(self.area)][str(self.room)]["furnature"]:
                furnatures.append(furnature)
            return furnatures
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getFurnatureDescription(self, furnature):
        description = ""
        furnature = furnature.lower()
        try:
            if furnature in self.getFurnature():
                description = self.file[str(self.area)][str(self.room)]["furnature"][furnature]["description"]
            return description
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getFunratureObjects(self, furnature):
        objects = []
        furnature = furnature.lower()
        try:
            if furnature in self.getFurnature():
                for i in self.file[str(self.area)][str(self.room)]["furnature"][furnature]["objects"]:
                    objects.append(i)
            return objects
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getFunratureObjectLocation(self, furnature, object):
        furnature = furnature.lower()
        des = "No object description found"
        object = object.lower()
        try:
            if object in self.getFunratureObjects(furnature):
                des = self.file[str(self.area)][str(self.room)]["furnature"][furnature]["objects"][object]["location"]
            return des
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getNpcs(self):
        npcs = []
        try:
            for npc in self.file[str(self.area)][str(self.room)]["npcs"]:
                npcs.append(npc)
            return npcs
        except:
            return npcs

    # Jank out of 10 is 11
    def getNpcDialouge(self, npc):
    # Welcome to the worst function out of all the functions on the planet
    # This is over engineered on a level that would supprise so many people and it only supports conversations where the user interacts twice.
    # I could probably make it better with some sleep and a greater knowledge of python but I can't be bothered.
    # By making it better I could scale it so that it takes many inputs from the user not just two
        try:
            says = ""
            npc = npc.lower()
            inps = ""
            inpsArray = []
            if npc in self.getNpcs():
                try:
                    opt = "placeholder"
                    while opt:
                        says = self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"]["start"]
                        for opts in self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"]:
                            if opts != "start":
                                inps += opts + ", "
                                inpsArray.append(opts)
                        opt = input(f"{says}\nYou can respond with {inps[0:-2]}: ")
                        if opt in inpsArray:
                            print(self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"][opt]["start"])
                            opt1 = opt
                            break
                    try:
                        inps = ""
                        inpsArray = []
                        while opt:
                            for opts in self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"][opt1]:
                                if opts != "start":
                                    if opts != "gives":
                                        inps += opts + ", "
                                        inpsArray.append(opts)
                                    else:
                                        raise
                            if inps == None:
                                break
                            else:
                                opt = input(f"You can respond with {inps[0:-2]}: ")
                            if opt in inpsArray:
                                try:
                                    print(self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"][opt1][opt]["start"])
                                except:
                                    print(self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"][opt1][opt])
                                opt2 = opt
                                break
                        return opt1+":"+opt2
                    except:
                        return opt1
                except:
                    says = self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"]
                    return says
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getNpcGives(self, npc, opt1 = "", opt2 = ""):
        gives = ""
        npc = npc.lower()
        try:
            if npc in self.getNpcs():
                try:
                    gives = self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"][opt1][opt2]["gives"]
                except:
                    try:
                        gives = self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"][opt1]["gives"]
                    except:
                        try:
                            gives = self.file[str(self.area)][str(self.room)]["npcs"][npc]["says"]["gives"]
                        except:
                            gives = ""
            return gives
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getNpcDrops(self, npc):
        drops = ""
        npc = npc.lower()
        try:
            if npc in self.getNpcs():
                try:
                    drops = self.file[str(self.area)][str(self.room)]["npcs"][npc]["drops"]
                except:
                    drops = ""
                return drops
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def checkItemGiven(self, npc):
        npc = npc.lower()
        given = False
        try:
            if npc in self.getNpcs():
                try:
                    given = self.file[str(self.area)][str(self.room)]["npcs"][npc]["given"]
                except:
                    return given
            return given
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def checkNpcKilled(self, npc):
        npc = npc.lower()
        killed = False
        try:
            if npc in self.getNpcs():
                try:
                    killed = self.file[str(self.area)][str(self.room)]["npcs"][npc]["killed"]
                except:
                    return killed
            return killed
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def killNpc(self, npc):
        npc = npc.lower()
        file = self.file
        try:
            if npc in self.getNpcs():
                file[str(self.area)][str(self.room)]["npcs"][npc]["killed"] = True
                File().writeFile(self.roomFile, self.file)
                return f"Killed {npc}"
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getDirections(self, list = True):
        try:
            if list:
                rDirections = []
                for direction in self.file[str(self.area)][str(self.room)]["directions"]:
                    rDirections.append(direction)
                return rDirections
            else:
                rDirections = ""
                for direction in self.file[str(self.area)][str(self.room)]["directions"]:
                    rDirections += direction + ", "
                return rDirections[0:-2]
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

    def getDirection(self, direction, inv = ""):
        rDirections = ""
        direction = direction.lower()
        try:
            if direction in self.getDirections():
                try:
                    if self.file[str(self.area)][str(self.room)]["directions"][direction]["locked"] == True and debugger().ignoreLocks == False:
                        if self.file[str(self.area)][str(self.room)]["directions"][direction]["unlockedBy"] in inv.getInventory(True):
                            self.file[str(self.area)][str(self.room)]["directions"][direction]["locked"] = False
                            File().writeFile(self.roomFile, self.file)
                            print(self.file[str(self.area)][str(self.room)]["directions"][direction]["unlockMsg"])
                            rDirections = self.file[str(self.area)][str(self.room)]["directions"][direction]["room"]
                            rDirections = rDirections.split(":")
                            if self.file[str(self.area)][str(self.room)]["directions"][direction]["breaks"][0] == True:
                                inv.removeFromInventory(self.file[str(self.area)][str(self.room)]["directions"][direction]["unlockedBy"])
                            return rDirections
                        else:
                            return self.file[str(self.area)][str(self.room)]["directions"][direction]["lockedMsg"]
                    elif debugger().ignoreLocks == True:
                        rDirections = self.file[str(self.area)][str(self.room)]["directions"][direction]["room"]
                        rDirections = rDirections.split(":")
                        return rDirections
                    else:
                            rDirections = self.file[str(self.area)][str(self.room)]["directions"][direction]["room"]
                            rDirections = rDirections.split(":")
                            return rDirections
                except:
                    rDirections = self.file[str(self.area)][str(self.room)]["directions"][direction]
                    rDirections = rDirections.split(":")
                    return rDirections
        except:
            # Just a quick error catcher 
            # NOTE: this is not a "quick" error cathcer as I build a debug interface for it
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0
    
    def checkItemPickedUp(self, furnature, object):
        furnature = furnature.lower()
        pickedUp = False
        object = object.lower()
        try:
            if object in self.getFunratureObjects(furnature):
                try:
                    pickedUp = self.file[str(self.area)][str(self.room)]["furnature"][furnature]["objects"][object]["pickedup"]
                except:
                    return pickedUp
            return pickedUp
        except:
            debugger().error(f"Room {self.area}:{self.room} not found")
            return 0

class object:
    def __init__(self, iFile):
        self.file = File().readFile(iFile)
        if self.file == 0:
            debugger().fatal(f"Failed to read {iFile}")

    def getObjects(self):
        objects = []
        for i in self.file:
            objects.append(i)
        return objects
    
    def getUse(self, object):
        object = object.lower()
        try:
            if object in self.getObjects():
                return self.file[object]["use"]
            else:
                return 0
        except:
            return "This object has no uses defined"
