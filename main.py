import FileRead
import interpreter

# Honestly I am suprised that any of this works
# objects = FileRead.readFile("objects.json")
# rooms = FileRead.readFile("rooms.json")
# for lis in objects:
#     for room in rooms:
#         for i in rooms[room]["furnature"]:
#             if lis in rooms[room]["furnature"][i]["objects"]:
#                 print(f'The {objects[lis]["colour"]} {lis} is {rooms[room]["furnature"][i]["objects"][lis]}')
#     print(f"colour: {objects[lis]['colour']}")
#     print(f"material: {objects[lis]['material']}")

room = 0
print(interpreter.room(room).getName())
print(interpreter.room(room).getDesciption())
print(interpreter.room(room).getFurnature())
print(interpreter.room(room).getFurnatureDescription("chair"))
print(interpreter.room(room).getDirections("north"))
print(interpreter.room(room).getFunratureObjects("chair"))
print(interpreter.room(room).getFunratureObjectDescriptions("chair", "spoon"))

print(interpreter.object().getObjects())
print(interpreter.object().getDescription("spoon"))
print(interpreter.object().getColour("spoon"))