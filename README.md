# Sandstone
Sandstone is a very simple game engine I'm working on in python. It is used for text based adventure games but I may extend it's funcionality later on.\
## Documentation
Coming soon for the time being just refer to demo1 and sandbox
### Creating an application
All applications inherent from `engine.appliaction`\
Each application must must have a starting area and room and a room file and an object file.\
Example code snippet from demo1:
```python
class demo1(engine.application):
    def __init__(self, area, room):
        self.roomFile = "demo1/demo1Rooms.json"
        self.objectFile = "demo1/demo1Objects.json"
        super().__init__(area, room, self.roomFile, self.objectFile, saveFile="save.json")
```
This app then must be ran using:
```python
application.run()
```
Code snippet from demo1:
```python
demo1(1, 1).run()
```
