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
print("Channels =", info['maxInputChannels'])
