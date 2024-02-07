# MakitaJukebox
Change the jingle in your makita charger! This project lets your charger play RTTTL ringtones.
The installation diagrams only support the DC18RC charger right now, but the theory is simple:  
Cut the trace that connects the buzzer to the charger's microcontroller and add our own
microcontroller in there, then listen for the charger's beeps and play our jingle instead.
The arduino monitors the leds on the charger to detect whether the charging is just starting
or is totally complete and plays a short or long jingle depending on which charge state it
detects.  
You can use any arduino for this. I used a pro mini for its small size and low power consumption
but a pro micro, nano, or any other 5v! tollerant microcontroller will do.  

# Demo
[![AAAAAAAAA](https://img.youtube.com/vi/VoyhR_ulGIQ/0.jpg)](https://www.youtube.com/watch?v=VoyhR_ulGIQ)

# DC18RC
<img src="https://github.com/Real-Time-Kodi/MakitaJukebox/blob/bf120546cb7fedda6acbc5d6aee3256074883976/DC18RC_Diagram_front.jpg" />  
Cut or desolder the link labeled JW7 on the front of the pcb. This connects the charger's microcontroller
to the transistor that drives the buzzer.
<img src="https://github.com/Real-Time-Kodi/MakitaJukebox/blob/bf120546cb7fedda6acbc5d6aee3256074883976/DC18RC_Diagram_back.jpg" />  
Two sided tape the arduino to the pcb and make the connections according to the diagram. It should look
something like this:
<img src="https://github.com/Real-Time-Kodi/MakitaJukebox/blob/bf120546cb7fedda6acbc5d6aee3256074883976/Installed.jpg" />  
Note that the led detection pins are soldered to the microcontroller side of the resistors. This is important
to get a good signal.  

**Some arduinos' reset buttons are too tall and will come into contact with the case when the
charger is reassembled. Cut tall reset buttons off with your snips!**

# Song customization
Any RTTTL ringtone can be used by pasting it into the jingle and jingle_short variables. The
sketch ships with "Buddy Holly" by weezer and the tetris theme by default. The idea is to play
a shortened song when the charging starts and a longer version when the charging is done.
