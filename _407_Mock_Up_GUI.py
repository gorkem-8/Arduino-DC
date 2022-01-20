
from tkinter import *
import serial
import time
arduino = serial.Serial(port='COM5',baudrate=115200,timeout=.1)

gui = Tk()
gui.title("407 Mock-Up ")
gui.geometry("600x400")


def start():
    print("Motor Started")
    a = var.get()
    a =str(a)
    print(a)
    arduino.write(bytes('!'+a,'utf-8'))
    time.sleep(0.05)

def stop():
    print("Motor Stopped")
    arduino.write(bytes('!0','utf-8'))
    time.sleep(0.05)

        

left=Label(text="SELECT AN OPERATION MODE",font=("Arial",15))
left.pack()
left.place(x=150,y=50)

var = IntVar()
button1 = Radiobutton(gui,text="LONG DISTANCE MODE",font=("Arial",10),variable = var,value=30)
button2 = Radiobutton(gui,text="SHORT DISTANCE MODE",font=("Arial",10),variable = var,value=60)
button1.pack()
button1.place(x=100,y=100)
button2.pack()
button2.place(x=350,y=100)

buttonStart = Button(gui,text="START",bg="green",height=5,width=20,command=lambda:start())
buttonStart.pack()
buttonStart.place(x=100,y=200)
buttonStop = Button(gui,text="STOP",bg="red",height=5,width=20,command=lambda:stop())
buttonStop.pack()
buttonStop.place(x=350,y=200)



gui.mainloop()
