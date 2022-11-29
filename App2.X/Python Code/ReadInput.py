import serial
import keyboard

def main():
    ser = serial.Serial(port= "COM3", baudrate = 9600, bytesize = 8, timeout =2, stopbits = serial.STOPBITS_ONE)
    button = ''
    num = ''
    while(True):
        line =ser.readline() # reads uint16_t nums as single bytes till \n n stores in string
        info = line.decode("ascii").strip().lstrip()
        info = info[1:]
        
        if(len(info) > 0 and info[0] != 'b'):
            num = int(info)
            
        else:
            button = info
            
        print(num)
        if(keyboard.is_pressed('esc')):
            break

if __name__ == "__main__":
    main()