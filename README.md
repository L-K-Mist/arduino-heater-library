# arduino-heater-library
Easy, heater-based temperature control. Particularly usefull if you want to set and maintain several Heater Objects in your system.  You set the targetTemp and the Heater flashes it's digital pin to reach and maintain that temp.

This is still a work-in-progress, but I think it will be quite usefull for the Arduino community. 
I'm sure there are many enthusiasts who want to read temps for the purpose of reaching and keeping a changeable Target Temperature.

Some credits are due:
  Of course a LOT of google was done to get this far, but Paul Murray's Arduino the Object Way article was where the penny really dropped   for me: http://paulmurraycbr.github.io/ArduinoTheOOWay.html#thespookyway 

  I love his Design Pattern for Arduino of using lots of polymorphic setup and loop functions in his classes. 

  For the State Machine aspects: https://hackingmajenkoblog.wordpress.com/2016/02/01/the-finite-state-machine/ 
