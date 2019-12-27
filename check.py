import os

def file_get_contents(filename):
  if os.path.exists(filename):
    fp = open(filename, "r")
    content = fp.read()
    fp.close()
    return content

str = file_get_contents("fdfdfd")

def check (way, what):
    for name in way:
        if name == what:
            return 1
    return 0


a = str.split("\n")
ways = []
for way in a:
    ways.append()
for way in a:
    name_arr = way.split(" ")
    res = 0
    for name in name_arr:
        for wayy in a:
            nname_arr = way.split(" ")
            for nname in nname_arr:
