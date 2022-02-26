import serial 

#connecting to the arduino port (the closer port on a MacBook Pro). User might need to change the first parameter.
ser = serial.Serial('/dev/cu.usbmodem14101', baudrate = 9600, timeout = 1)

#setting speed from user input
speed = int(input("RPM (100-2900): "))
if speed > 2900: 
    speed = 2900 
    print("Centrifuge can handle a maximum speed of 2900")
if speed < 0: 
    print("Don't break our centrifuge!") 
    speed = 0

#setting duration of spin time from user input
duration = input("Time (minutes:seconds): ")
minsec = duration.split(":")
time = int(minsec[0])*60 + int(minsec[1])
if time < 0:
    print("Time must be a positive number in the centrifuge's reality")
    time = 0


#formatting user input into byte format to be sent to arduino
def formatData(speed, time): 
    sendingRPM = 's' + str(speed) +'n'
    sendingTime = 't' + str(time)
    data = sendingRPM + sendingTime
    ser.write(bytes(data, 'utf-8'))

formatData(speed, time)
#reads arduino serial to user's terminal to confirm functionality
def readArduino():
    arduinoData = ser.readline().decode('ascii')
    return arduinoData

while(1): 
    print(readArduino())


