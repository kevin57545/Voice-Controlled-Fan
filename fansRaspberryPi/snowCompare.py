
from concurrent.futures import thread
from pickle import GLOBAL
import snowboydecoder
import sys
sys.path.append('/home/pi/.local/lib/python3.9/site-packages/pyaudio')
import serial
import threading
import time

def one_callback():
    print("one")

def two_callback():
    print("two")
    

TimeSensitivity = [0.5,0.5]


TimeModels=["/home/pi/snowboy/examples/snowboytest/7thWind1.pmdl"
,"/home/pi/snowboy/examples/snowboytest/7thWind2.pmdl"]

#關鍵字回應函數陣列

TimeCallbacks = [one_callback,two_callback]

setTimeDetector = snowboydecoder.HotwordDetector(TimeModels, sensitivity=TimeSensitivity, audio_gain=0.1)
print("啟動偵聽器")
setTimeDetector.start(detected_callback=TimeCallbacks, interrupt_check =lambda: False, sleep_time=0.03)
setTimeDetector.terminate()
