#https://www.w3schools.com/python/python_dictionaries_methods.asp
import json
def readFile(file):
  file = open(file)
  rFile = json.loads(file.read())
  file.close()
  return rFile

def writeFile(file, fWrite):
  file = open(file, "w")
  fWrite = json.dumps(fWrite, indent=4)
  file.write(fWrite)
  file.close()
  return file