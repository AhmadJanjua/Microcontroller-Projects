import serial
import keyboard
import turtle

# create a window and cursor
head = turtle.Turtle()
head.speed(0)
head.shape('square')
head.color("black")
head.goto(0,0)
head.direction = "stop"

# move along the y axis
def move_y(incr):
    y = head.ycor()
    if(incr > 400 and incr < 600):
        incr = 0
    else:
        incr -=  511
        incr /= 50
        
    head.sety(y+ incr)

# move along the x axis
def move_x(incr):
    if(incr > 400 and incr < 600):
        incr = 0
    else:
        incr -=  511
        incr /= 50
    x = head.xcor()
    head.setx(x + incr)
    
def main():
    # establish serial connection
    ser = serial.Serial(port= "COM3", baudrate = 9600, bytesize = 8, timeout =2, stopbits = serial.STOPBITS_ONE)
    
    # default values
    button = ''
    x_axis = False
    
    # infinite loop to run program
    while(True):
        # read a line from serial connection
        line = ser.readline() # reads uint16_t nums as single bytes till \n n stores in string
        micro_input = line.decode("ascii").strip() # convert to python readable string
        
        # check the validity of input
        if(len(micro_input) > 0):
            
            # eliminate input prefix
            micro_input = micro_input[1:]
            
            # if its a number send it to move the cursor
            if( len(micro_input) > 0 and str.isnumeric(micro_input) ):
                micro_input = int(micro_input)
                if(x_axis):
                    move_x(micro_input)
                else:
                    move_y(micro_input)
            # if its a button set the value for button
            else:
                if(len(micro_input)> 0):
                    button = micro_input
                
            # Check if its a button input
            if (button.find('a') != -1):
                # change axis of drawing
                x_axis = not x_axis
                # reset button
                button = ''
            # check if its a c input button
            elif (button.find('c') != -1):
                # reset the program
                head.reset()
                head.clear()
                button = '' 
        print(micro_input)
        # check if escape is pressed and exit the program and close connection
        if(keyboard.is_pressed('esc')):
            break
    ser.close()

if __name__ == "__main__":
    main()