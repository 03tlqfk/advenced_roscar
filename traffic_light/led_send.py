import RPi.GPIO as GPIO
import time
import socket

GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.OUT)
GPIO.setup(24, GPIO.OUT)
GPIO.setup(25, GPIO.OUT)

#HOST = '172.30.1.47' #server ip
HOST = '192.168.43.49'
PORT = 8800

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.OUT)
GPIO.setup(24, GPIO.OUT)
GPIO.setup(25, GPIO.OUT)



try:
	while 1:
		GPIO.output(23, True)
		GPIO.output(24, False)
		GPIO.output(25, False)
		msg="stop"
		s.send(msg.encode(encoding='utf_8', errors='strict'))
		data=s.recv(1024)
		time.sleep(20)

		GPIO.output(23, False)
		GPIO.output(24, True)
		GPIO.output(25, False)
		msg="stop"
		s.send(msg.encode(encoding='utf_8', errors='strict'))
		data=s.recv(1024)
		time.sleep(4)

		GPIO.output(23, False)
		GPIO.output(24, False)
		GPIO.output(25, True)
		msg="go"
		s.send(msg.encode(encoding='utf_8', errors='strict'))
		data=s.recv(1024)
		time.sleep(10)
except KeyboardInterrupt:
	print("exit")

finally:
	s.close()
	GPIO.cleanup()
