from Tkinter import *
import time

def create_window():
    window = Toplevel(root)
    w, h = root.winfo_screenwidth(), root.winfo_screenheight()
    canvas = Canvas(window,width=w,height=h)
    canvas.create_text(w/2,h/2,text="this will close after 3 seconds",font="Arial")
    canvas.pack()
    window.overrideredirect(1)
    window.geometry("%dx%d+0+0" % (w, h))
    window.after(3000, lambda: window.destroy())
    
root = Tk()
root.title("3 Second Splash")
root.geometry("250x250")
b = Button(root, text="Launch splash window", command=create_window)
b.place(relx=0.5,rely=0.5,anchor=CENTER)
#b.pack()

root.mainloop()
