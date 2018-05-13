# w1tk.py   python using Tkinter, see web for documentation
from Tkinter import *
root=Tk()
root.title('w1tk.py  click to exit')

def mouseB1press(event): # left
  sys.exit()

c=Canvas(root, width=200, height=100, bg='white')
c.create_line( 50, 50,150, 50,fill='black')
c.create_line(150, 50,150, 75,fill='black')
c.create_line(150, 75, 50, 75,fill='black')
c.create_line( 50, 75, 50, 50,fill='black')
c.create_text(100,30, text='click here to exit', fill='black')
c.bind('<ButtonPress-1>'  , mouseB1press)

c.pack()
root.mainloop()
