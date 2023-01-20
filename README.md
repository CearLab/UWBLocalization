# uwbAcquisition
Low-level software for UWB acquisition

Install stlink to flash the EVB1000 to 2.1 firmware version, here you can find the .deb file: 
https://github.com/stlink-org/stlink/releases

Run stlink-gui.ui

You can find the 2.1 firmware version here, in old_firmware folder:
https://github.com/fabrizioromanelli/EVB1000-firmware.git

Now you can see the exadecimal id code of the board on the screen.

Add the id code to uwb_slave_ids in main.cc in this repo:
https://github.com/fabrizioromanelli/uwbAcquisition.git

and upgrade the NODENUMBER in the previous line.

Connect one of the board (no matter if it is a tag or an anchor)

Check if /dev/ttyACM0 is correctly initializated 

Now if you run ./install.sh /dev/ttyACM0 you can find the acquisition in UWBReadings.dat
