
from pickle import GLOBAL
import snowboydecoder
import sys
sys.path.append('/home/pi/.local/lib/python3.9/site-packages/pyaudio')
import serial
import threading
import time
# 設定串口
serial_port = "/dev/ttyUSB0"
serial_baudrate = 9600
serial_timeout = 1
# 初始化串口
ser = serial.Serial(serial_port, serial_baudrate, timeout=serial_timeout)

import pyaudio

# 獲取系統中的音訊輸入設備列表
p = pyaudio.PyAudio()
# 遍历所有音频设备，查找特定名称的麦克风
desired_microphone_name = "Yeti Nano: USB Audio (hw:3,0)"
input_device_index = None

for i in range(p.get_device_count()):
    info = p.get_device_info_by_index(i)
    print(f"Device {i}: {info['name']}")
    if info['name'] == desired_microphone_name:
        input_device_index = i
        break

if input_device_index is not None:
    # 使用找到的麦克风设备
    stream = p.open(input_device_index=input_device_index, format=pyaudio.paInt16, channels=1, rate=44100, input=True)
    # 进行后续操作
else:
    print(f"找不到名称为'{desired_microphone_name}'的麦克风设备")

def passNumber(number):
    try:
        # Attempt to write data to the serial port
        ser.write(str(number).encode())

    except serial.SerialException as e:
        # Handle serial port exceptions
        print(f"Serial port exception: {e}")
    except serial.SerialTimeoutException as e:
        # Handle serial port timeout exceptions
        print(f"Serial port timeout exception: {e}")
    except Exception as e:
        # Handle other exceptions
        print(f"Exception occurred: {e}")

# 定義回應函數
def hello_callback():
    print("你喊了 hello")
    passNumber(1)

def close_callback():
    print("你喊了 關閉")
    passNumber(9)

def open_callback():
    print("你喊了 開啟")
    passNumber(4)

def accelerate_callback():
    print("你喊了 加速")
    passNumber(6)

def startOSC_callback():
    print("你喊 開始擺頭")
    passNumber(5)

def stopOSC_callback():
    print("你喊 停止擺頭")
    passNumber(5)

def sleepwind_callback():
    print("你喊 睡眠風")
    passNumber(13)

def naturalwind_callback():
    print("你喊 自然風")
    passNumber(12)

def normalwind_callback():
    print("你喊 一般模式")
    passNumber(11)

def setspeed_callback():
    print("你喊 設定風量")
    passNumber(3)

def one_callback():
    print("你喊 1")
    passNumber(1)

def two_callback():
    print("你喊 2")
    passNumber(2)

def three_callback():
    print("你喊 3")
    passNumber(3)

def four_callback():
    print("你喊 4")
    passNumber(4)

def five_callback():
    print("你喊 5")
    passNumber(5)

def six_callback():
    print("你喊 6")
    passNumber(6)

def seven_callback():
    print("你喊 7")
    passNumber(7)

def eight_callback():
    print("你喊 8")
    passNumber(8)

def nine_callback():
    print("你喊 9")
    passNumber(9)

def ten_callback():
    print("你喊 10")
    passNumber(10)

def eleven_callback():
    print("你喊 11")
    passNumber(11)

def twelve_callback():
    print("你喊 12")
    passNumber(12)

def settime_callback():
    print("你喊 定時")
    passNumber(7)
    

def onehr_callback():
    print("你喊 1小時")
    passNumber(1)

def twohr_callback():
    print("你喊 2小時")
    passNumber(2)

def threehr_callback():
    print("你喊 3小時")
    passNumber(3)

def fourhr_callback():
    print("你喊 4小時")
    passNumber(4)

def fivehr_callback():
    print("你喊 5小時")
    passNumber(5)

def sixhr_callback():
    print("你喊 6小時")
    passNumber(6)

def sevenhr_callback():
    print("你喊 7小時")
    passNumber(7)

def eighthr_callback():
    print("你喊 8小時")
    passNumber(8)

def cancel_settime_callback():
    print("你喊 不定時")
    passNumber(7)
    passNumber(9)
    

# 設定敏感度
HelloSensitivity = [0.6]
FunctionSensitivity = [0.7,0.7,0.6,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8]
WindSensitivity = [0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8]
TimeSensitivity = [0.8,0.8,0.8,0.8,0.8,0.8,0.8,0.8]

# 關鍵字檔案路徑
HelloModels = ["/home/pi/snowboy/examples/snowboytest/pmdlFile/hello.pmdl"]
FunctionModels = ["/home/pi/snowboy/examples/snowboytest/pmdlFile/close70.pmdl"
, "/home/pi/snowboy/examples/snowboytest/pmdlFile/open50.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/accelerate60.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/StartOSC_10.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/StopOSC_10.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/SleepWind_10.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/NaturalWind_10.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/NormalWind_10.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/SetSpeed_10.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/settime.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/cancel_settime.pmdl"
]
WindModels=["/home/pi/snowboy/examples/snowboytest/pmdlFile/One_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Two_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Three_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Four_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Five_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Six_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Seven_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Eight_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Nine_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Ten_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Eleven_5.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/Twelve_5.pmdl"]
TimeModels=["/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/1hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/2hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/3hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/4hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/5hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/6hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/7hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/pmdlFile/settime/8hr.pmdl"]

#回應函數
HelloCallbacks = [hello_callback]
FunctionCallbacks = [close_callback, open_callback, accelerate_callback, 
startOSC_callback, stopOSC_callback, sleepwind_callback, naturalwind_callback, normalwind_callback,
setspeed_callback,settime_callback,cancel_settime_callback]
WindCallbacks = [one_callback, two_callback, three_callback, four_callback, five_callback, six_callback,
seven_callback, eight_callback, nine_callback, ten_callback, eleven_callback, twelve_callback]
TimeCallbacks = [onehr_callback,twohr_callback,threehr_callback,
fourhr_callback,fivehr_callback,sixhr_callback,sevenhr_callback,eighthr_callback]

def receive_and_print_data():#1:啟動Hello偵聽器 2:啟動Function偵聽器 3:啟動setWind偵聽器 4:啟動setTime偵聽器
    global isSettime
    global isSetWind
    global FunctionInterrupt
    global HelloInterrupt
    global mode
    global event
    while True:
        try:
            data = ser.readline().decode('utf-8')  # 从串口接收数据并解码为字符串
            data = data.strip()  # 去除末尾的换行符
            num = int(data)
            if num == 1:
                print("啟動Hello偵聽器")
                HelloInterrupt = True
                isSettime = False
                isSetWind = False
                FunctionInterrupt = True
                HelloInterrupt = False
                mode = 1
            elif num == 2:
                print("啟動Function偵聽器")
                FunctionInterrupt = True
                isSettime = False
                isSetWind = False
                HelloInterrupt = True
                FunctionInterrupt = False
                mode = 2
            elif num == 3:
                print("啟動setWind偵聽器")
                isSetWind = False
                isSettime = False
                HelloInterrupt = True
                FunctionInterrupt = True
                isSetWind = True
                mode = 3
            elif num == 4:
                print("啟動setTime偵聽器")
                isSettime = False
                HelloInterrupt = True
                FunctionInterrupt = True
                isSetWind = False
                isSettime = True
                mode = 4
            event.set()
        except UnicodeDecodeError as e:
            # Handle decoding error, e.g., print the raw data
            print(f"UnicodeDecodeError: {e}")
        except ValueError:
            if data == "":
                pass
            else:
                print(data) # 忽略非数字

# 偵測Aduino訊息的thread啟動
data_receive_thread = threading.Thread(target=receive_and_print_data)
data_receive_thread.start()


#interrupt變數
FunctionInterrupt = True
def Function_interrupt_check():
    global FunctionInterrupt
    return FunctionInterrupt
isSetWind = False
def Wind_interrupt_check():
    global isSetWind
    return not isSetWind
isSettime = False 
def Time_interrupt_check():
    global isSettime
    return not isSettime
HelloInterrupt = False#一開始先打開
def Hello_interrupt_check():
    global HelloInterrupt
    return HelloInterrupt

# 創建一個事件對象
event = threading.Event()

#由thread回傳之mode決定接下來要打開哪個偵聽器
mode = 0
while True :
    print(mode)
    if mode == 1 :
        # 創建Hello偵聽器
        HelloDetector = snowboydecoder.HotwordDetector(HelloModels, sensitivity = HelloSensitivity)
        print("啟動Hello偵聽器")
        HelloDetector.start(detected_callback=HelloCallbacks, interrupt_check = Hello_interrupt_check , sleep_time=0.03)
        event.wait()
        HelloDetector.terminate()
    elif mode == 2 :
        # 創建Function偵聽器
        FunctionDetector = snowboydecoder.HotwordDetector(FunctionModels, sensitivity=FunctionSensitivity)
        print("啟動Function偵聽器")
        FunctionDetector.start(detected_callback=FunctionCallbacks, interrupt_check = Function_interrupt_check, sleep_time=0.03)
        event.wait()
        FunctionDetector.terminate()
    elif mode == 3 :
        # 創建setWind偵聽器
        setWindDetector = snowboydecoder.HotwordDetector(WindModels, sensitivity=WindSensitivity)
        print("啟動setWind偵聽器")
        setWindDetector.start(detected_callback=WindCallbacks, interrupt_check = Wind_interrupt_check, sleep_time=0.03)
        event.wait()
        setWindDetector.terminate()
    elif mode == 4 :
        # 創建setTime偵聽器
        setTimeDetector = snowboydecoder.HotwordDetector(TimeModels, sensitivity=TimeSensitivity)
        print("啟動setTime偵聽器")
        setTimeDetector.start(detected_callback=TimeCallbacks, interrupt_check = Time_interrupt_check, sleep_time=0.03)
        event.wait()
        setTimeDetector.terminate()
        
 