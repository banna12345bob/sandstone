from time import sleep
import colorama
import FileRead

# Don't look here it's really ugly but it works
class debugger:
    def __init__(self):
        if FileRead.File().readFile("options.json")["debuggerEnabled"] == "True":
            self.debuggerEnabled = True
        else:
            self.debuggerEnabled = False
        colorama.init()

    def fatal(self, msg):
        if self.debuggerEnabled == True:
            a = ""
            for i in msg:
                a += i + " "
            print(colorama.ansi.Back.RED + "FATAL: " + a + colorama.ansi.Style.RESET_ALL)
            sleep(5)
            quit()
        else:
            return

    def error(self, msg):
        if self.debuggerEnabled == True:
            a = ""
            for i in msg:
                a += i + " "
            print(colorama.ansi.Fore.RED + "ERROR: " + a + colorama.ansi.Style.RESET_ALL)
        else:
            return

    def warning(self, msg):
        if self.debuggerEnabled == True:
            a = ""
            for i in msg:
                a += i + " "
            print(colorama.ansi.Fore.YELLOW + "WARNING: " + a + colorama.ansi.Style.RESET_ALL)
        else:
            return

    def info(self, msg):
        if self.debuggerEnabled == True:
            a = ""
            for i in msg:
                a += i + " "
            print(colorama.ansi.Fore.GREEN + "INFO: " + a + colorama.ansi.Style.RESET_ALL)
        else:
            return