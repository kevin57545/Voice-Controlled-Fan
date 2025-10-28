
from pickle import GLOBAL
import snowboydecoder
import sys
sys.path.append('/home/pi/.local/lib/python3.9/site-packages/pyaudio')
import serial
# 設定串口
serial_port = "/dev/ttyUSB0"
serial_baudrate = 9600
serial_timeout = 1
isSettime = False 

# 初始化串口
ser = serial.Serial(serial_port, serial_baudrate, timeout=serial_timeout)


# 定義回應函數
def hello_callback():
    print("你喊了 hello")
    ser.write(str(1).encode())

def close_callback():
    print("你喊了 關閉")
    ser.write(str(9).encode())

def open_callback():
    print("你喊了 開啟")
    ser.write(str(4).encode())

def accelerate_callback():
    print("你喊 accelerate")
    ser.write(str(6).encode())

def accelerate_callback():
    print("你喊 accelerate")
    ser.write(str(6).encode())

def settime_callback():
    global isSettime
    if isSettime == False :
        isSettime = True
        print("你喊 定時")
        ser.write(str(7).encode())

def onehr_callback():
    global isSettime
    if isSettime == True :
        print("你喊 1小時")
        ser.write(str(1).encode())
        isSettime = False

def twohr_callback():
    global isSettime
    if isSettime == True :
        print("你喊 2小時")
        ser.write(str(2).encode())
        isSettime = False

def threehr_callback():
    global isSettime
    if isSettime == True :
        print("你喊 3小時")
        ser.write(str(3).encode())
        isSettime = False

def fourhr_callback():
    global isSettime
    if isSettime == True :
        print("你喊 4小時")
        ser.write(str(4).encode())
        isSettime = False

def fivehr_callback():
    global isSettime
    if isSettime == True :
        print("你喊 5小時")
        ser.write(str(5).encode())
        isSettime = False

def sixhr_callback():
    global isSettime
    if isSettime == True :
        print("你喊 6小時")
        ser.write(str(6).encode())
        isSettime = False

def sevenhr_callback():
    global isSettime
    if isSettime == True :
        print("你喊 7小時")
        ser.write(str(7).encode())
        isSettime = False

def eighthr_callback():
    global isSettime
    if isSettime == True :
        print("你喊 8小時")
        ser.write(str(8).encode())
        isSettime = False

def cancel_settime_callback():
    global isSettime
    print("你喊 不定時")
    if isSettime == True :
        ser.write(str(9).encode())
        isSettime = False
    else :
        ser.write(str(7).encode())
        ser.write(str(9).encode())
    


# 設定敏感度、關鍵字檔案路徑、回應函數
sensitivity = [0.6,0.6,0.6,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5]
models = ["/home/pi/snowboy/examples/snowboytest/hello.pmdl"
, "/home/pi/snowboy/examples/snowboytest/close70.pmdl"
, "/home/pi/snowboy/examples/snowboytest/open50.pmdl"
,"/home/pi/snowboy/examples/snowboytest/accelerate60.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/settime.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/1hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/2hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/3hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/4hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/5hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/6hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/7hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/8hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/settime/cancel_settime.pmdl"
]
callbacks = [hello_callback, close_callback, open_callback,accelerate_callback,
             settime_callback,onehr_callback,twohr_callback,threehr_callback,
             fourhr_callback,fivehr_callback,sixhr_callback,sevenhr_callback,eighthr_callback,cancel_settime_callback]

# 創建偵聽器
detector = snowboydecoder.HotwordDetector(models, sensitivity=sensitivity)

# 開始偵聽
print('請開始說話...')
detector.start(detected_callback=callbacks, interrupt_check= lambda: False, sleep_time=0.03)

# 結束偵聽
detector.terminate()