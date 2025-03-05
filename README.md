# AudioViz1.0

<img width="803" alt="Screenshot 2025-03-05 at 5 26 04 PM" src="https://github.com/user-attachments/assets/ae4b84ea-b805-4ff7-948d-651260fa67c3" />

Install dependencies:

### Port Audio (Audio Sampling)
- Linux: ```sudo apt-get install libasound-dev```
- Mac: ```brew install portaudio```


### GLFW (OpenGL windowing)
- Linux: ```sudo apt install libglfw3-dev```
- Mac: ```brew install glfw```


### GLEW (OpenGL extensions)
- Linux: ```sudo apt install libglew-dev```
- Mac: ```brew install glew```

<br/><br/>
Audio is sampled from the default input device, which is configured in your operating system's settings. Typically this is set to the internal microphone in the device, but can be configured to any source that has an input channel.

For troubleshooting and to get a list of available audio interfaces, ```list_devices``` has been included:
```
Outsidesman$ g++ list_devices.cpp -o list_devices -L/opt/homebrew/lib -lportaudio -I/opt/homebrew/include && ./list_devices 
Available audio devices:
Device 0: U2790B (Max input channels: 0, Max output channels: 2)
Device 1: Matthew's iPhone Microphone (Max input channels: 1, Max output channels: 0)
Device 2: BlackHole 2ch (Max input channels: 2, Max output channels: 2)
Device 3: External Headphones (Max input channels: 0, Max output channels: 2)
Device 4: MacBook Pro Microphone (Max input channels: 1, Max output channels: 0)
Device 5: MacBook Pro Speakers (Max input channels: 0, Max output channels: 2)
Device 6: Multi-Output Device (Max input channels: 0, Max output channels: 2)
Device 7: Multi-Output Device 2 (Max input channels: 0, Max output channels: 2)
```

To run the application:
```
make run
```
Edit ```Makefile``` to match your dependency install location.

The visualization cycles through 16 color palette gradients (found in ```palettes.h```).

To skip to a palette, press 0-9 or a-f.

From left to right, the four sliders control:
- Waveform redness
- Waveform amplitude
- Waveform point size
- Amplitude indicator magnitude
