from tkinter import *
import serial

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM1'
ser.open()
print("communication occupée : " + str(ser.is_open))

window = Tk()

window.geometry('500x300')
window.title("Projet elec Groupe 9")


def getNumber():
    result = E1.get()
    if (type(int(result)) == int and int(result) < 99):
        if (int(result) <10):
            result = "0" + result
        print(result)
        ser.write(bytes(result, encoding='utf-8'))
    
L1 = Label(text="Nombre de personne maximum")
L1.pack()

E1 = Entry()
E1.pack()

btn = Button(text ="Changer le seuil", command=getNumber) 
btn.pack(pady = 10)
maxPers = "0"
nombrePers = "0"


L2 = Label(text="Il y a actuellement "+nombrePers +" sur "+maxPers + " personnes" )
L2.place(relx = 0.5, rely = 0.9, anchor = 'center')


def on_closing():
    ser.close()
    print("communication occupée : " + str(ser.is_open))
    window.destroy()


def readSerial():
     
    result = str(ser.read(6))[2:7].split("/")
    
    maxPers = result[0]
    nombrePers = result[1]
    print(result)
    L2.configure(text="Il y a actuellement "+nombrePers +" sur "+maxPers + " personnes")
    L2.update()
    window.after(200, readSerial)
    if (int(nombrePers) >= int(maxPers)) :
        L2.configure(foreground="red")
        L2.update()
    else :
        L2.configure(foreground="green")
        L2.update()

readSerial()  
window.protocol("WM_DELETE_WINDOW", on_closing)
window.mainloop()

