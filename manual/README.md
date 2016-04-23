# How do you encurage someone to move more often, while that person doesn't want to carry a cellhone all the time?

I came to this idea because of my father. He's a musician/composer who recently opend his own studio. This means he's sitting 10 hours a day with almost no break at all. I tried to get him to use an app like [Human](http://human.co/), but he forgets his phone all the time, so that didn't work.

## What will it fix / help you with?
This will help you to move more ofter while you're working, without useing your cellphone, and yes, there are a lot of people who dont want to carry that this around all the time. 

The feedback is given silently, so if you're working in a thing like a studio, it won't mess-up your recording. This means all the feedback is given by three RGB Led's. You can change all the settings via the dashboard, you can also see how you did that day/week.

## What you need
* A URL and hosting (if you don't have this, you can google for a how to)
* An ESP8266 (available at stores like the [Hackerstore](http://www.hackerstore.nl/))
* 3 RGB leds (also avalible at the hackerstore)
* A breadboard
* A button or another pressure sensor
* 11 male-male wires
* 4 resistors (brown | black | black | red | brown) 
* 1 USB cable (to connect the ESP to your computer)
* A texteditor like [Sublime Text](https://www.sublimetext.com/3)
* A FTP Program like [Filezilla](https://filezilla-project.org/)
* The [Arduino Program](https://www.arduino.cc/en/Main/Software)

## How it works
### What goes to what:
This drawing explanes the global proces of this project. 

### POST and handle the button status

The ESP for the button requests the button state every second. This will be pushed to the server with a POST Request. The server will check if it receifs a POST request. The button state will be written into the *history.json*, *output.txt* and the *data.json*. If you sit, so the button status is true, a script *redOne.php* will be called. After your set time, the code in this file will be run and *led.json* will be written to *ledState: one;*. And the script ledTwo.php will be called. This proces is repeted until *redThree.php*. If that script is called, the third led will be set to **RED** and you will need to move!

### GET the led status and set the led's
The ESP for the leds will do a GET request to your server. He will ask for the status of the led, writen in *led.json*. The code on the ESP will receife the led.json and wil read it. If the ledStatus is *false*, you don't sit and all the leds wil have a green color. If the ledStatus is *one*, you sit and the set time for the first led is over. This proces repeats itself for the comming two leds.

The status of the leds are adustable in your browser (this update is comming next week).

NOTE: If you uses one ESP, this ESP will handle both things.

![Global Setup](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/setup-drawing.jpg "What goes to what")

### The pins of a RGB LED
A RGB LED has for pins. A pin for the ground (the largest) and a pin for each color (red - green - blue). In this picture you see how the arrangement is set. The longest pin is alway's the pin for the ground.

![RGB LED](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/rgb-led.jpg "RGB LED")

## Setup your board
### The Pressure sensor
A pressure sensor needs a ground and a plus(vin) connection to work. You can read the data with a digital input, I used D7 in this manual.

![Button Setup](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/button-setup.jpg "Button Setup")

![button](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/button.jpg "button")

### The RGB Led's
To set up the RGB LED's, you woun't need to connect the blue pin for this project. The ground is alway's connected with a resistor. The color pins go to a Digital port (D1 - D6) in this case. In the picute you will see white wires who connect the green pins, the orange and yellow wires connect the red pins. The drawing gives a better view of this setup.

![RGB LED](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/rgb-setup.jpg "RGB LED")

![leds-one](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/leds-one.jpg "leds-one")

![leds-two](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/leds-two.jpg "leds-two")

## Installing the software on your board
For this Setup you could use one OR two ESP's. If you want to use one ESP, upload the code from the folder [code-one-esp](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/tree/master/manual/code-one-esp) to your ESP. If you would like to use two ESP's, which I recomand because one ESP will handle the input data from the pressure sensor and the other gives the feedback. This means that the feedback will be in your sight. Than use the code from the folder [code-two-esps](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/tree/master/manual/code-two-esps). Upload the button.ino to the ESP who handles the button and the rgb.ino the the ESP who handles the RGB LED feedback.

NOTE: You will need te fill in a view things. 

* Your routers name
* Your routers password
* Your site's url

Don't share any passwords/usernames you have put in the fill on GitHub or with anyone else!

## Setup your server
For this part you will need a bit of experiance with a FTP program. If you dont have that, ask a friend or Google your question (It ain't that hard.)

1. Go to the root of your url with your ftp Program.
2. Create a folder named 'get-up-stand-up'.
3. Drag the files from [server-code](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/tree/master/manual/server-code) into the 'get-up-stand-up' folder.

Go to: *your_own_url* /get-up-stand-up/index.php
If you see the site, your done here.


## Use It
If your site works and you've set the right data in the arduino code, your good to go. The ESP will transmit every 10sec or-something, so you will see data the minute if everyting is right.

## References
For parts of the code I used [this tutorial](http://blog.nyl.io/esp8266-led-arduino/), thanks for sharing [Nancy Yi Liang](http://blog.nyl.io/author/nyl/)!

## Tips/Questions
For tips or Questions you can add create a GitHub issue. If you can improve this manual/code, please make a Pull Request. Thx and good luck.
