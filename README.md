ofxHuez
====
![ofxHuez](http://25.media.tumblr.com/5d72808c0b6c93392f2e0f17613b58e2/tumblr_myvjgeBmz61rtc945o1_1280.png)

Addons
====
* ofxBMath(own thing)
* ofxVJKinect(own thing)
* ofxKinect
* ofxBeatTracking
* ofxTrueTypeFontUC

plese refer to this URL  
[ofxAddons](http://ofxaddons.com/)

Environment
====
* OSX 10.6 and the later
* SDK 10.6 only
* Xcode 4.x
* openFrameworks v007  

Tutorial
====

###Kinet Setup Side
Please Refer to some Entries about running ofxKinect and connecting to OSX on Google.  

###Ruby Side  
At first, edit the ./bin/tweet_to_txt.rb file.   
e.g.(about twitter developing acount's some informations and path_to_txt)  
if you completely input the informations.  
then, you run

`cd ./bin`  
`ruby tweet_to_txt.rb`  

You'll get tweet from twitter and export tweet txt file to ./bin directory.  

###OpenFrameworks Side in Xcode
Open The Xcode Project File and Set up Xcode. e.g.(importing some addons and SDK 10.6)  
Edit 'path_to_txt'  
Finally Build and Run.


