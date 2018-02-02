import RPi.GPIO as GPIO
import time
import MySQLdb
import serial
port=serial.Serial("/dev/ttyS0",9600, timeout=3.0)
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(5, GPIO.OUT)
GPIO.setup(7, GPIO.OUT)


#db = MySQLdb.connect("13.126.221.81","test","test","priyam" )
#cursor = db.cursor()



sql= "select info from status order by id desc limit 1"
sql1= "select infol from statusl order by idl desc limit 1"
sql2= "select infod from statusd order by idd desc limit 1"
sql3= "insert into dht11 (temp) values ('%s')" % \
      ('temperature')
sql4= "insert into dht11 (humidity) values ('%s')" % \
      ('humidity')
while True:
    
    db = MySQLdb.connect("13.126.221.81","test","test","priyam" )
    cursor = db.cursor()
    cursorr = db.cursor()   
    cursorrr = db.cursor()
    
    cursor.execute(sql)
    flag=cursor.fetchone()

    cursorr.execute(sql1)
    flagg=cursorr.fetchone()
    
    cursorrr.execute(sql2)
    flaggg=cursorrr.fetchone()
      
    if flag[0]==1:
        port.write('1')

    else:
        port.write('2')

    if flagg[0]==1:
        port.write('3')

    else:
        port.write('4')

    if flaggg[0]==1:
        port.write('5')
        
        rcv=port.read(3)
        if rcv=="":   
            print "hello"
        else:
            print "hi"

        
    elif flaggg[0]==0:
        port.write('6')
        
        rcv=port.read(3)
        print rcv[0]
            
        
        
            
        
    
        

    db.close()

        
    
       
       
