from Tkinter import *

master = Tk()

fonts=["Arial","Helvetica","Times"]
curr = 0


def onClick(event):
    global curr
    curr = (curr+1)%3
    canvas.itemconfig(t1,font=fonts[curr])

canvas = Canvas(master,width=250,height=250)


canvas.bind("<Button-1>", onClick)

t1=canvas.create_text(125,125,text="this is text",font=fonts[curr])

canvas.pack()

mainloop()
