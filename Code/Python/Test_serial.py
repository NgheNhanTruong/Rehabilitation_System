import serial
import time

arduino = serial.Serial(port = 'COM3', timeout=0)
time.sleep(2)

while True:

    print ("Enter '1' to turn 'on' the LED and '2' to turn LED 'off'")
    received_data = arduino.readline().decode().strip()
    var = str(input())
    print ("You Entered :", var)

    if(var == '1'):
        arduino.write(str.encode('abc'))
        print("LED turned on")
        time.sleep(1)

    if(var == '2'):
        arduino.write(str.encode('xyz'))
        print("LED turned off")

    # Kiểm tra nếu tín hiệu là "xyz" thì in ra màn hình
    # if received_data == 'x':
    print(received_data)