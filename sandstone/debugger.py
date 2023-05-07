from time import sleep
try:
    from include.colorama import colorama
    debug = True
except:
    debug = False
from sandstone import FileRead

# Don't look here it's really ugly but it works
class debugger:
    def __init__(self, command = False):
        self.command = command
        if debug:
            try:
                self.debuggerEnabled = FileRead.File().readFile("data/options.json")["debuggerEnabled"]
            except:
                self.debuggerEnabled = False
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
        if (self.command):
            return "quit"
        quit()

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