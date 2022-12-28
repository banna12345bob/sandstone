#https://www.w3schools.com/python/python_dictionaries_methods.asp
import json
import os
from engine.debugger import debugger

class File:
    def __init__(self) -> None:
        self.directory = os.curdir
        pass

    def readFile(self, file):
        exists = os.path.exists(f"{self.directory}/{file}")
        if file != "data/options.json":
                if exists:
                    file = open(f"{self.directory}/{file}")
                    fRead = file.read().replace("\n", "")
                    rFile = json.loads(fRead)
                    file.close()
                    return rFile
                else:
                    debugger().warning(f"File {self.directory}/{file} not found")
                    return 0
        else:
            return 0

    def writeFile(self, file, fWrite):
        file = open(f"{self.directory}/{file}", "w")
        fWrite = json.dumps(fWrite, indent=4)
        file.write(fWrite)
        file.close()
        return
    
    def deleteFile(self, file):
        exists = os.path.exists(f"{self.directory}/{file}")
        if exists:
            os.remove(f"{self.directory}/{file}")
            debugger().info(f"Removed {self.directory}/{file}")
            return 1
        else:
            debugger().warning(f"No file named {self.directory}/{file} to delete")
            return 0