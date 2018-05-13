from Tkinter import *
import time

master = Tk()
master.title("Clock")
master.geometry("150x100")

time1=''
clock = Label(master, font=("Arial", 20))
clock.pack(fill=BOTH,expand=1)
#clock.place(relx=0.5,rely=0.5,anchor=CENTER) <- does same as above

def tick():
    global time1
    time2 = time.strftime('%I:%M:%S')
    if (time1 != time2):
        time1 = time2
        clock.config(text=time1)
    clock.after(200,tick) #updates after 200ms

tick()
mainloop()
