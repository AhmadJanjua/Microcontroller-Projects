import serial
import keyboard
import turtle

#cursor.
head = turtle.Turtle()
head.speed(0)
head.shape('square')
head.color("black")
head.goto(0,0)
head.direction = "stop"


def move_y(incr):
    y = head.ycor()
    if(incr > 400 and incr < 600):
        incr = 0
    else:
        incr -=  511
        incr /= 50
        
    head.sety(y+ incr)
    
def move_x(incr):
    if(incr > 400 and incr < 600):
        incr = 0
    else:
        incr -=  511
        incr /= 50
    x = head.xcor()
    head.setx(x + incr)
    
def main():
    ser = serial.Serial(port= "COM3", baudrate = 9600, bytesize = 8, timeout =2, stopbits = serial.STOPBITS_ONE)
    
    button = ''
    x_axis = False
    
    while(True):
        line = ser.readline() # reads uint16_t nums as single bytes till \n n stores in string
        micro_input = line.decode("ascii").strip()
        
        if(len(micro_input) > 0):
            
            micro_input = micro_input[1:]
            
            if( len(micro_input) > 0 and str.isnumeric(micro_input) ):
                micro_input = int(micro_input)
                if(x_axis):
                    move_x(micro_input)
                else:
                    move_y(micro_input)
            else:
                if(len(micro_input)> 0):
                    button = micro_input
                
            if (button.find('a') != -1):
                x_axis = not x_axis
                button = ''
            elif (button.find('c') != -1):
                head.reset()
                head.clear()
                
        
        print(micro_input)
                  
        if(keyboard.is_pressed('esc')):
            break

if __name__ == "__main__":
    main()