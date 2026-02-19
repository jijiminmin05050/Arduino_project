mport time
import RPi.GPIO as GPIO
import tkinter as tk

# Set up GPIO
GPIO.setmode(GPIO.BCM)  # Use Broadcom pin numbering
GPIO.setwarnings(False)


# Set up the GPIO pins for the LEDs
GPIO.setup(17, GPIO.OUT)  # Red LED
GPIO.setup(27, GPIO.OUT)  # Orange LED
GPIO.setup(22, GPIO.OUT)  # Blue LED

# Function to turn on the corresponding LED and turn off the others
def led_on(led_color):
    # Turn off all LEDs first
    GPIO.output(17, GPIO.LOW)  # Red
    GPIO.output(27, GPIO.LOW)  # Orange
    GPIO.output(22, GPIO.LOW)  # Blue

    # Turn on the selected LED
    if led_color == "Red":
        GPIO.output(17, GPIO.HIGH)
    elif led_color == "Orange":
        GPIO.output(27, GPIO.HIGH)
    elif led_color == "Blue":
        GPIO.output(22, GPIO.HIGH)

# Function to exit the program and clean up GPIO
def exit_program():
    GPIO.cleanup()  # Reset all GPIO pins
    root.quit()  # Close the Tkinter window

# Create the main Tkinter window
root = tk.Tk()
root.title("LED Control")

# Create radio buttons for controlling LEDs
red_button = tk.Radiobutton(root, text="Red LED", value="Red", command=lambda: led_on("Red"))
green_button = tk.Radiobutton(root, text="Orange LED", value="Orange", command=lambda: led_on("Orange"))
blue_button = tk.Radiobutton(root, text="Blue LED", value="Blue", command=lambda: led_on("Blue"))

# Pack the radio buttons into the window
red_button.pack()
orange_button.pack()
blue_button.pack()

# Create an exit button
exit_button = tk.Button(root, text="Exit", command=exit_program)
exit_button.pack()

# Run the Tkinter event loop
root.mainloop()
