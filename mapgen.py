import sys
import random

class Map:
    height = 0
    width = 0
    step = 0
    padding = 0
    arr = []

    def __init__ (self, height, width, size):
        self.height = height
        self.width = width
        self.padding = (int)(size / 10)
        self.step = (int) ((size - self.padding * 2)/(height if height > width else width))

    def calc (self):
        arr = []
        for i in range (0, self.height):
            arr.append([])
            for j in range (0, self.width):
                arr[i].append(dict())
                arr[i][j]['name'] = str(i) + '|' + str(j)
                arr[i][j]['coordinate'] = [self.step * j + self.padding, self.step * i + self.padding]

        self.arr = arr

    def link (self):
        for i in range(0, len(self.arr)):
            for j in range(0, len(self.arr[i])):
                self.arr[i][j]['links'] = []
                if i + 1 < len(self.arr) and random.randint(0, 3):
                    self.arr[i][j]['links'].append(self.arr[i][j]['name'] + '-' + self.arr[i + 1][j]['name'])
                if j + 1 < len(self.arr[i]) and random.randint(0, 3):
                    self.arr[i][j]['links'].append(self.arr[i][j]['name'] + '-' + self.arr[i][j + 1]['name'])

    def print_ants(self, ants):
        print(str(ants))

    def print_room (self):
        for i in self.arr:
            for room in i:
                if room['name'] == self.arr[0][0]['name']:
                    print('##start')
                if room['name'] == self.arr[self.height - 1][self.width - 1]['name']:
                    print('##end')
                print(room['name'] +  " " + str(room['coordinate'][0]) + " " + str(room['coordinate'][1]))

    def print_links (self):
        for i in self.arr:
            for room in i:
                for link in room['links']:
                    print(link)

    def common (self):
        self.calc()
        self.link()
        self.print_ants(sys.argv[4])
        self.print_room()
        self.print_links()

class Check:
    def help (self):
        print("usage: " + sys.argv[0] + " [int height] [int width] [int size] [int ants]")

    def run (self):
        if len(sys.argv) != 5:
            return 0
        for arg in sys.argv:
            if arg == sys.argv[0]:
                continue
            try:
                if int(arg) <= 0:
                    return 0
            except ValueError:
                return 0
        return 1
        

checker = Check();
if not checker.run():
    checker.help()
    exit()

map = Map(int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3]))
map.common()
