import font
import hid

class display:
    def __init__(self, width, height):
        self.w = width
        self.h = height
        self.buf = [0]*(width*height/8)
        self.x =0
        self.y =0
        self.page = [0]*(width*height/8/32)
    def inc_cur(self, x, y):
        if x:
            self.x = self.x + x
            if self.x == 22:
                self.x = 0
                self.y = self.y + 1
        if y:
            self.y = self.y + y
            self.x = 0
            if self.y == 4:
                self.y = 0
        
    def write(self, arg):
        for i in arg:
            if i == '\n':
                self.inc_cur(0,1)
            else:
                cur = self.y * 128 + self.x * 6
                self.buf[cur:cur+6]=font.get(ord(i))
                self.inc_cur(1,0)

    def data(self):
        return self.buf

    def clear(self):
        self.buf = [0]*(self.w*self.h/8)
        self.x = 0
        self.y = 0
    
    def rectangle(self, x, y, length):
        cur = y * 128 + x
        self.buf[cur:cur+length] = [0x7e]*length
    
