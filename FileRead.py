#https://www.w3schools.com/python/python_dictionaries_methods.asp
import json
from operator import imod
from debugger import debugger

def readFile(file):
    try:
        file = open(file)
        rFile = json.loads(file.read())
        file.close()
        return rFile
    except:
        debugger().fatal(f"Failed to load {file}")

def writeFile(file, fWrite):
    file = open(file, "w")
    fWrite = json.dumps(fWrite, indent=4)
    file.write(fWrite)
    file.close()
    return file