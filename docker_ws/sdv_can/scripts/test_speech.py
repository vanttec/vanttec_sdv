import pyaudio
import wave

# Path to the audio file you want to play
audio_file_path = '/home/ws/src/sdv_can/sounds/good_morning_sir.wav'

# Initialize PyAudio
p = pyaudio.PyAudio()

# Open the audio file
wf = wave.open(audio_file_path, 'rb')

# Open a stream with the Bluetooth speaker as the output device
stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
                channels=wf.getnchannels(),
                rate=wf.getframerate(),
                output=True,
                output_device_index=0)

# Read data from the file and play it through the Bluetooth speaker
data = wf.readframes(1024)
while data:
    stream.write(data)
    data = wf.readframes(1024)

# Close the stream and terminate PyAudio
stream.stop_stream()
stream.close()
p.terminate()
