import sandstone

def bobrick_talk():
    return "Hello child"

def rickbob_talk():
    print("Hello I am Rickbob and I will devour your soul")
    inp = input('You can say "okay": ')
    while inp:
        if inp == "okay":
            print("I will do it.")
            inp = input('You can say "no": ')
            if inp == "no":
                print("Just you watch")
                inp = input('You can say "i think not": ')
                if inp == "i think not":
                    print("I will")
                    inp = input('You can say "don\'t believe you": ')
                    if inp == "don't believe you":
                        print("Oh well then looks like I'll have to end the game")
                        return "quit"
                    else:
                        break
            else:
                break
        else:
            break
    return ""