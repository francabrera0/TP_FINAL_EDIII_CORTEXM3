import serial
from tkinter import *
reader = serial.Serial("/dev/ttyUSB0",9600)
characters = "\ bxn'"
scale = 600
weight = 0
tare = 0
level = "0"
maxload = 0.5 

def update():
	global weight
	global tare
	global level
	global maxload

	string=str(reader.readline())
	for c in characters:
		string = string.replace(c,"")
	d = string[0]
	string = string.replace(d,"")
	string = int(string)
	if(d=="W"):
		weight = round(string/scale,1)
		WEIGHT.config(text=(str(weight)+" [Kg]"))
	elif(d=="T"):
		tare = round(string/scale,1)
		TARE.config(text=(str(tare)+" [Kg]"))
	elif(d=="L"):
		level = str(bin(string))
		level = level[2:]

	if (tare!=0):
		neto = round(weight - tare,2)
	else:
		neto = 0
	NETO.config(text=(str(neto)+" [Kg]"))
	
	if(len(level)==4):
		load100.place(x=480,y=260)
		load75.place(x=480,y=306)
		load50.place(x=480,y=350)
		load25.place(x=480,y=397)

	if(len(level)==3):
		load100.place_forget()
		load75.place(x=480,y=306)
		load50.place(x=480,y=350)
		load25.place(x=480,y=397)
	
	if(len(level)==2):
		load100.place_forget()
		load75.place_forget()
		load50.place(x=480,y=350)
		load25.place(x=480,y=397)

	if(len(level)==1):
		if(level=="1"):
			load100.place_forget()
			load75.place_forget()
			load50.place_forget()
			load25.place(x=480,y=397)
		else:
			load100.place_forget()
			load75.place_forget()
			load50.place_forget()
			load25.place_forget()
	
	load = round(neto/maxload*100,2)
	truckLoad.config(text=str(load)+"%")
	
	window.after(100,update)


window = Tk()
window.title('Sistema de carga de camiones')
window.geometry('660x700')

image = PhotoImage(file='truck.png')
Label(window, image=image).place(x=10,y=290)

truckLoad = Label(window,relief="raised", text="0%",background="green")
truckLoad.place(x=230,y=360)


image2 = PhotoImage(file='silo.png')
Label(window, image=image2).place(x=450,y=200)

load25=Label(window,relief="raised", text="         25%         \n",background="red")
load25.place(x=480,y=397)

load50=Label(window,relief="raised", text="         50%         \n",background="orange")
load50.place(x=480,y=350)

load75=Label(window,relief="raised", text="         75%         \n",background="yellow")
load75.place(x=480,y=306)

load100=Label(window,relief="raised", text="        100%        \n",background="green")
load100.place(x=480,y=260)


WEIGHT_t = Label(window,borderwidth=3,relief="raised", text='PESO MEDIDO').place(x=10,y=60)
WEIGHT = Label(window, text = "0")
WEIGHT.place(x=34, y=90)

TARE_t = Label(window,borderwidth=3,relief="raised", text='TARA').place(x=305,y=60)
TARE = Label(window, text = "0")
TARE.place(x=300, y=90)

NETO_t = Label(window,borderwidth=3,relief="raised", text='PESO NETO').place(x=570,y=60)
NETO = Label(window, text = "0")
NETO.place(x=580, y=90)

Button(window, text='Salir', command=window.destroy).place(x=276,y=620)



window.after(2,update)
window.mainloop()

reader.close()
