import colorama

# Don't look here it's really ugly but it works
class debugger:
    def __init__(self):
       self.debuggerEnabled = True
       colorama.init()

    def fatal(self, msg):
        if self.debuggerEnabled == True:
            return(colorama.ansi.Back.RED + "FATAL: " + msg + colorama.ansi.Style.RESET_ALL)
        else:
            return msg

    def error(self, msg):
        if self.debuggerEnabled == True:
            return(colorama.ansi.Fore.RED + "ERROR: " + msg + colorama.ansi.Style.RESET_ALL)
        else:
            return msg

    def warning(self, msg):
        if self.debuggerEnabled == True:
            return(colorama.ansi.Fore.YELLOW + "WARNING: " + msg + colorama.ansi.Style.RESET_ALL)
        else:
            return msg

    def info(self, msg):
        if self.debuggerEnabled == True:
            return(colorama.ansi.Fore.GREEN + "INFO: " + msg + colorama.ansi.Style.RESET_ALL)
        else:
            return msg