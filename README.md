# MakitaJukebox
Change the jingle in your makita charger! This project lets your charger play RTTTL ringtones.
The installation diagrams only support the DC18RC charger right now, but the theory is simple:  
Cut the trace that connects the buzzer to the charger's microcontroller and add our own
microcontroller in there, then listen for the charger's beeps and play our jingle instead.
