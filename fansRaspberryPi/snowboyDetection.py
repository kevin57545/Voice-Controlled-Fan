
from concurrent.futures import thread
from pickle import GLOBAL
import snowboydecoder
import sys
sys.path.append('/home/pi/.local/lib/python3.9/site-packages/pyaudio')
import serial
import threading
import time

#--------------------------------------------------------------與Arduino的串口通訊-------------------------------------------------------------------
# 設定串口
serial_port = "/dev/ttyUSB0"
serial_baudrate = 115200
serial_timeout = 1
# 初始化串口
ser = serial.Serial(serial_port, serial_baudrate, timeout=serial_timeout)

#傳送數字給arduino的函式,number為此次要傳遞的數字
def passNumber(number):
    try:
        # Attempt to write data to the serial port
        ser.write(str(number).encode())

    except serial.SerialException as e:
        # Handle serial port exceptions
        print(f"Serial port exception: {e}")
    except Exception as e:
        # Handle other exceptions
        print(f"Exception occurred: {e}")

mutex = 0
#用於同步處理之software solution
def mywait():  #只能用於停止主thread
    global mutex
    while(mutex <= 0):
        pass
    mutex = mutex - 1 

def myset():
    global mutex
    mutex = mutex + 1

#---------------------------------------------------------------------------------------------------------------------------------------------------

#--------------------------------------------------------------偵聽器相關宣告----------------------------------------------------------------
# 定義偵聽器偵測到關鍵字後執行的回應函數
# 注意,hello_callback()、setspeed_callback()、setspeed_callback()都會呼叫event.wait()使主thread等待,以免繼續不必要的偵測
def hello_callback():
    print("你喊了 小北小北")
    passNumber(1)
    mywait()

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
    mywait()

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
    mywait()

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
    passNumber(10)
    
def garbage_callback():
    print("偵測中...")
    

# 設定敏感度
HelloSensitivity = [0.5]
FunctionSensitivity = [0.49,0.5,0.5,0.62,0.64,0.64,0.53,0.6,0.51,0.53,0.62,0.7]
WindSensitivity = [0.4,0.45,0.37,0.52,0.5,0.5,0.412,0.381,0.5,0.41,0.555,0.57]
TimeSensitivity = [0.528,0.472,0.576,0.53,0.4,0.465,0.623,0.407]
# 關鍵字檔案路徑
HelloModels = ["/home/pi/snowboy/examples/snowboytest/PMDL/Xiaobei.pmdl"]
FunctionModels = ["/home/pi/snowboy/examples/snowboytest/PMDL/Close.pmdl"
, "/home/pi/snowboy/examples/snowboytest/PMDL/open50.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Accelerate.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/StartOSC.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/StopOSC.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/SleepWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/NaturalWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/NormalWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/SetSpeed.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/SetTime.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Cancel_SetTime.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Garbage.pmdl"
]
WindModels=["/home/pi/snowboy/examples/snowboytest/PMDL/Wind/1stWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/2ndWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/3rdWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/4thWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/5thWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/6thWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/7thWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/8thWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/9thWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/10thWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/11thWind.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Wind/12thWind.pmdl"]
TimeModels=["/home/pi/snowboy/examples/snowboytest/PMDL/Hour/1hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Hour/2hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Hour/3hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Hour/4hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Hour/5hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Hour/6hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Hour/7hr.pmdl"
,"/home/pi/snowboy/examples/snowboytest/PMDL/Hour/8hr.pmdl"]

#關鍵字回應函數陣列
HelloCallbacks = [hello_callback]
FunctionCallbacks = [close_callback, open_callback, accelerate_callback, 
startOSC_callback, stopOSC_callback, sleepwind_callback, naturalwind_callback, normalwind_callback,
setspeed_callback,settime_callback,cancel_settime_callback,garbage_callback]
WindCallbacks = [one_callback, two_callback, three_callback, four_callback, five_callback, six_callback,
seven_callback, eight_callback, nine_callback, ten_callback, eleven_callback, twelve_callback]
TimeCallbacks = [onehr_callback,twohr_callback,threehr_callback,
fourhr_callback,fivehr_callback,sixhr_callback,sevenhr_callback,eighthr_callback]


#每個偵聽器的interrupt變數
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
#-------------------------------------------------------------------------------------------------------------------------------------------------


#--------------------------------------------------------偵聽Arduino的data_receive_thread----------------------------------------------------------

#此函式為data_receive_thread做的事,接收arduino訊號並更換成相應的偵聽器
def receive_and_print_data():#1:啟動Hello偵聽器 2:啟動Function偵聽器 3:啟動setWind偵聽器 4:啟動setTime偵聽器
    global isSettime
    global isSetWind
    global FunctionInterrupt
    global HelloInterrupt
    global mode
    global event
    while True:#不斷接收arduino訊息
        try:
            data = ser.readline().decode('utf-8')  # 解碼從Arduino收到的字串訊息
            data = data.strip()  # 去除結尾的換行符號
            num = int(data)
            if num in [1, 2, 3, 4]:#如果接收到的資料為合法數字,也代表hello_callback()、setspeed_callback()、setspeed_callback()其一已執行,將主thread暫停
                if num == 1:
                    #print("啟動Hello偵聽器")
                    HelloInterrupt = True
                    isSettime = False
                    isSetWind = False
                    FunctionInterrupt = True
                    myset()                     #讓主thread繼續執行,使原本的偵聽器關閉
                    mode = 1
                    HelloInterrupt = False      #告訴主thread新偵聽器可被打開
                elif num == 2:
                    #print("啟動Function偵聽器")
                    FunctionInterrupt = True
                    isSettime = False
                    isSetWind = False
                    HelloInterrupt = True
                    myset()                 #讓主thread繼續執行,使原本的偵聽器關閉
                    mode = 2
                    FunctionInterrupt = False   #告訴主thread新偵聽器可被打開
                elif num == 3:
                    #print("啟動setWind偵聽器")
                    isSetWind = False
                    isSettime = False
                    HelloInterrupt = True
                    FunctionInterrupt = True
                    myset()                 #讓主thread繼續執行,使原本的偵聽器關閉
                    mode = 3                   
                    isSetWind = True            #告訴主thread新偵聽器可被打開(因為是新偵聽器所以主thread還沒來的及關也沒關係)
                elif num == 4:
                    #print("啟動setTime偵聽器")
                    isSettime = False
                    HelloInterrupt = True
                    FunctionInterrupt = True
                    isSetWind = False
                    myset()                     #讓主thread繼續執行,使原本的偵聽器關閉
                    mode = 4
                    isSettime = True            #告訴主thread新偵聽器可被打開
                myset()                     #讓主thread繼續執行,繼而變成新的偵聽器

        except UnicodeDecodeError as e:
            # Handle decoding error, e.g., print the raw data
            print(f"UnicodeDecodeError: {e}")
        except ValueError:
            if data == "":
                pass        # 沒傳訊息就跳過
            else:
                print(data) # 若為arduino非數字訊息(即為monitor資訊),輸出


# 偵測Arduino訊息的thread(data_receive_thread)啟動
data_receive_thread = threading.Thread(target=receive_and_print_data)
data_receive_thread.start()

#-------------------------------------------------------------------------------------------------------------------------------------------------


#----------------------------------------------------------主thread宣告完所有東西後在做的事----------------------------------------------------------

# 創建一個事件對象以完成所有thread間的互斥控制
event = threading.Event()

#以下為主thread主要執行內容,由data_receive_thread回傳之mode決定接下來要打開哪個偵聽器
mode = 0
while True :
    
    if mode == 1 :
        # 創建Hello偵聽器
        HelloDetector = snowboydecoder.HotwordDetector(HelloModels, sensitivity = HelloSensitivity, audio_gain=1)
        print("啟動Hello偵聽器")
        HelloDetector.start(detected_callback=HelloCallbacks, interrupt_check = Hello_interrupt_check , sleep_time=0.03)
        HelloDetector.terminate()
        mywait()   #等待data_receive_thread將mode設定完成
    elif mode == 2 :
        # 創建Function偵聽器
        FunctionDetector = snowboydecoder.HotwordDetector(FunctionModels, sensitivity=FunctionSensitivity, audio_gain=1)
        print("啟動Function偵聽器")
        FunctionDetector.start(detected_callback=FunctionCallbacks, interrupt_check = Function_interrupt_check, sleep_time=0.03)
        FunctionDetector.terminate()
        mywait()   #等待data_receive_thread將mode設定完成
    elif mode == 3 :
        # 創建setWind偵聽器
        setWindDetector = snowboydecoder.HotwordDetector(WindModels, sensitivity=WindSensitivity, audio_gain=1)
        print("啟動setWind偵聽器")
        setWindDetector.start(detected_callback=WindCallbacks, interrupt_check = Wind_interrupt_check, sleep_time=0.03)
        setWindDetector.terminate()
        mywait()   #等待data_receive_thread將mode設定完成
    elif mode == 4 :
        # 創建setTime偵聽器
        setTimeDetector = snowboydecoder.HotwordDetector(TimeModels, sensitivity=TimeSensitivity, audio_gain=1)
        print("啟動setTime偵聽器")
        setTimeDetector.start(detected_callback=TimeCallbacks, interrupt_check = Time_interrupt_check, sleep_time=0.03)
        setTimeDetector.terminate()
        mywait()   #等待data_receive_thread將mode設定完成
#---------------------------------------------------------------------------------------------------------------------------------------------------
 
