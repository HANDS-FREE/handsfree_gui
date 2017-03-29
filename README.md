### This is the latest version for HandsFree's Debug GUI(Beta)

#### some attentions:
- 1.this GUI could only be run on the Ubuntu, not support Windows
- 2.this GUI is only a beta verion
- 3.if any bugs found or some advice,please send message to cp_vin@126.com

#### usage:
- 1.make sure your Ubuntu have installed these application:
  - cmake (sudo apt-get install cmake)
  - Boost (http://www.boost.org/)
  - libqt5serialport5 and libqt5serialport5-dev (sudo apt-get install libqt5serialport5*)

- 2.switch to the folder of this project,typing "cmake CMakeList.txt"
- 3.if step 2 get no errors,typing "make"
- 4.after step 3,an executable file called "handsfree_gui_v2" could be found in the directory "./bin"
- 5.run this executable file,and insert the USB serial of Handsfree robot,change the permission of /dev/ttyUSB*

#### By using this GUI , you could:<br/>
- observe some parameters from robot
- sending some commands to robot
- control the by keyboard
- draw some information in the visualization plot (this function will be available in the future)

##### 1.mainwindow<br/>
![](https://github.com/HANDS-FREE/handsfree_gui/blob/master/README/v0.2_mainwindow.png)

##### 2.serial control<br/>
![](https://github.com/HANDS-FREE/handsfree_gui/blob/master/README/v0.2_serial.png)<br/>
*please make sure the serial is opened when using this GUI*

##### 3.odometry information<br/>
![](https://github.com/HANDS-FREE/handsfree_gui/blob/master/README/v0.2_odom.png)<br/>
*show the new odometry data got from robot*

##### 4.mobile control<br/>
![](https://github.com/HANDS-FREE/handsfree_gui/blob/master/README/v0.2_control.png)<br/>
the available key value is:     
- key_up (move foward)      
- key_down (move back)      
- key_left (turn left)      
- key_right (turn right)        
- key_q (to increase the velocity by 20%)       
- key_z (to decrease the velocity by 20%)       
<br/>
**attention:**
before using this function,you must click the mobile control panel to make sure it has got focus ;      
**the original velocity is 0.2m/s**

##### 5.plot<br/>
![](https://github.com/HANDS-FREE/handsfree_gui/blob/master/README/v0.2_plot.png)<br/>

**this funtion is on building , please wait......**
