import os

def file_get_contents(filename):
  if os.path.exists(filename):
    fp = open(filename, "r")
    content = fp.read()
    fp.close()
    return content

str = file_get_contents("fdfdfd")

def check (way, what):
    for i in range(0, len(way)):
        if way[i] == what:
          print(what)
          return 1
    return 0


a = str.split("\n")
ways = []
for way in a:
    ways.append(way.split(" "))

f = 0
for i in range(0, len(ways)):
    for j in range(0, len(ways[i])):
      for k in range(0, len(ways)):
        if k != i and len(ways[i][j]) > 2 and not ways[i][j] == ways[i][-1]:
          f += check(ways[k], ways[i][j])
print(f) 
      
