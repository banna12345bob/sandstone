import sandstone

def sayHello():
    print("[PYTHON] Hello from python!")
    sandstone.cppFunc()
    print("[PYTHON] Calling c++ classes test")
    return sandstone.version().checkVersion("../sandstone/version.json")

def add(a, b):
    return a + b