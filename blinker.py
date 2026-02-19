import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)  # Use BCM pin numbering
GPIO.setwarnings(False)  # Disable warnings

# Set up GPIO pin 18 as an output pin
GPIO.setup(18, GPIO.OUT)

try:
    # Run the blinking 10 times
    for _ in range(10):
        print("LED on")
        # Turn the LED on
        GPIO.output(18, GPIO.HIGH)
        time.sleep(1)  # Wait for 1 second

        print("LED off")
        # Turn the LED off
        GPIO.output(18, GPIO.LOW)
        time.sleep(1)  # Wait for 1 second

except KeyboardInterrupt:
    print("Program interrupted, cleaning up GPIO.")
    GPIO.cleanup()  # Clean up GPIO settings when the script is stopped

