from time import sleep
try:
    from include.colorama import colorama
except:
    next
from engine import FileRead

# Don't look here it's really ugly but it works
class debugger:
    def __init__(self, command = False):
        self.command = command
        self.debuggerEnabled = FileRead.File().readFile("data/options.json")["debuggerEnabled"]
        if self.debuggerEnabled == True:
            self.ignoreLocks = FileRead.File().readFile("data/options.json")["ignoreLocks"]
        else:
            self.ignoreLocks = False
        try:
            colorama.init()
        except:
            self.debuggerEnabled = False

    def fatal(self, msg):
        a = msg
        if isinstance(msg, list):
            a = ""
            for i in msg:
                a += i + " "
        print(colorama.ansi.Back.RED + "FATAL: " + a + colorama.ansi.Style.RESET_ALL)
        sleep(5)
        return "quit"

    def error(self, msg):
        if self.debuggerEnabled == True:
            a = msg
            if isinstance(msg, list):
                a = ""
                for i in msg:
                    a += i + " "
            if self.command:
                return(colorama.ansi.Fore.RED + "ERROR: " + a + colorama.ansi.Style.RESET_ALL)
            print(colorama.ansi.Fore.RED + "ERROR: " + a + colorama.ansi.Style.RESET_ALL)
        else:
            return

    def warning(self, msg):
        if self.debuggerEnabled == True:
            a = msg
            if isinstance(msg, list):
                a = ""
                for i in msg:
                    a += i + " "
            if self.command:
                return(colorama.ansi.Fore.YELLOW + "WARNING: " + a + colorama.ansi.Style.RESET_ALL)
            print(colorama.ansi.Fore.YELLOW + "WARNING: " + a + colorama.ansi.Style.RESET_ALL)
        else:
            return

    def info(self, msg):
        if self.debuggerEnabled == True:
            a = msg
            if isinstance(msg, list):
                a = ""
                for i in msg:
                    a += i + " "
            if self.command:
                return(colorama.ansi.Fore.GREEN + "INFO: " + a + colorama.ansi.Style.RESET_ALL)
            print(colorama.ansi.Fore.GREEN + "INFO: " + a + colorama.ansi.Style.RESET_ALL)
        else:
            return