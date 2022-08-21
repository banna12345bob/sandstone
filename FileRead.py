#https://www.w3schools.com/python/python_dictionaries_methods.asp
import json
from debugger import debugger

class File:
    def __init__(self) -> None:
        pass

    def readFile(self, file):
        try:
            if file:
                file = open(file)
                rFile = json.loads(file.read())
                file.close()
                return rFile
            else:
                return "File not defined"
        except:
            debugger().fatal(f"Failed to load file {file}")

    def writeFile(self, file, fWrite):
        file = open(file, "w")
        fWrite = json.dumps(fWrite, indent=4)
        file.write(fWrite)
        file.close()
        return file