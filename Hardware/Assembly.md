- Chain all modules together (VCC to VCC, GND to GND, DOUT to DIN, CS to CS, CLK to CLK)
- Connect D5 of ESP8266 to CLK on the most right Max7219 module 
- Connect D6 of ESP8266 to DIN on the most right Max7219 module 
- Connect D7 of ESP8266 to CS on the most right Max7219 module
- Connect 5V of ESP8266 to VCC on the most right Max7219 module
- Connect GND of ESP8266 to GND on the most right Max7219 module
- Load software on the ESP8266
- Connect to power source
- The ESP8266 will initially start up as an Access Point with the name "Lichtkrant"
- Connect to the Access point with the name "Lichtkrant" (without a password)
- Browse to 192.168.4.1
  
 ![Wifimanager](https://github.com/rvangelder11/Tube_Clock/assets/90907092/e015b7f6-2212-4e08-b1be-d5a43b859e64)

- Fill in Wifi name and password.
- After success, the clock starts
- The ESP8266 can be mounted on the back of the right MAX7219 module with double sided tape
  
![IMG_0095](https://github.com/rvangelder11/Tube_Clock/assets/90907092/6b8e8c1f-4a8e-44a3-bbfe-8ae082281e5b)

- The whole assembly can be shifted in the perspex tube
- Optionally close the tube on both sides with a 3D printed bracket (dop voor perspex buis v5.stl and dop voor perspex buis_Component1(Mirror) v1.stl)
  
![IMG_0094](https://github.com/rvangelder11/Tube_Clock/assets/90907092/88062fd6-aa1b-408b-a977-7fcb457d2de9)
