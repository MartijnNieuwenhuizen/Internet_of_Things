# How do you encourage someone to move more often, while that person doesn't want to carry a cellphone all the time?

I came to this idea because of my father. He's a musician/composer who recently opened his own studio. This means he's sitting 10 hours a day with almost no break at all. I tried to get him to use an app like [Human](http://human.co/), but he forgets his phone all the time, so that didn't work.

## What will it fix / help you with?
This will help you to move more ofter while you're working, without using your cell phone, and yes, there are a lot of people who don't want to carry that this around all the time. 

The feedback is given silently, so if you're working in a thing like a studio, it won't mess up your recording. This means all the feedback is given by three RGB LEDs. You can change all the settings via the dashboard, you can also see how you did that day/week.

## What you need
* A URL and hosting (if you don't have this, you can google for a how-to)
* An ESP8266 (available at stores like the [Hackerstore](http://www.hackerstore.nl/))
* 3 RGB led's (also available at the hackerstore)
* A breadboard
* A button or another pressure sensor
* 11 male-male wires
* 4 resistors (brown | black | black | red | brown) 
* 1 USB cable (to connect the ESP to your computer)
* A text editor like [Sublime Text](https://www.sublimetext.com/3)
* An FTP Program like [Filezilla](https://filezilla-project.org/)
* The [Arduino Program](https://www.arduino.cc/en/Main/Software)

## How it works
### What goes to what:
This drawing explains the global process of this project. 

### POST and handle the button status

The ESP for the button requests the button state every second. This will be pushed to the server with a POST Request. The server will check if it receives a POST request. The button state will be written into the *history.json*, *output.txt* and the *data.json*. If you sit, so the button status is true, a script *redOne.php* will be called. After your set time, the code in this file will be run and *led.json* will be written to *ledState: one;*. And the script ledTwo.php will be called. This process is repeated until *redThree.php*. If that script is called, the third led will be set to **RED** and you will need to move!

### GET the led status and set the led's
The ESP for the led's will do a GET request to your server. He will ask for the status of the led, written in *led.json*. The code on the ESP will receive the led.json and will read it. If the ledStatus is *false*, you don't sit and all the LEDs will have a green color. If the ledStatus is *one*, you sit and the set time for the first led is over. This process repeats itself for the coming two leds.

The status of the leds are adjustable in your browser (this update is coming next week).

NOTE: If you use one ESP, this ESP will handle both things.

![Global Setup](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/setup-drawing.jpg "What goes to what")

### The pins of an RGB LED
An RGB LED has for pins. A pin for the ground (the largest) and a pin for each color (red - green - blue). In this picture, you see how the arrangement is set. The longest pin is alway's the pin for the ground.

![RGB LED](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/rgb-led.jpg "RGB LED")

## Setup your board
### The Pressure sensor
A pressure sensor needs a ground and a plus(vin) connection to work. You can read the data with a digital input, I used D7 in this manual.

![Button Setup](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/button-setup.jpg "Button Setup")

![button](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/button.jpg "button")

### The RGB Led's
To set up the RGB LED's, you won't need to connect the blue pin for this project. The ground is alway's connected with a resistor. The color pins go to a Digital port (D1 - D6) in this case. In the picture you will see white wires who connect the green pins, the orange and yellow wires connect the red pins. The drawing gives a better view of this setup.

![RGB LED](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/rgb-setup.jpg "RGB LED")

![leds-one](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/leds-one.jpg "leds-one")

![leds-two](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/blob/master/images/leds-two.jpg "leds-two")

## Installing the software on your board
For this Setup, you could use one OR two ESPs. If you want to use one ESP, upload the code from the folder [code-one-esp](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/tree/master/manual/code-one-esp) to your ESP. If you would like to use two ESP's, that I recommend because one ESP will handle the input data from the pressure sensor and the other gives the feedback. This means that the feedback will be in your sight. Then use the code from the folder [code-two-esps](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/tree/master/manual/code-two-esps). Upload the button.ino to the ESP who handles the button and the rgb.ino the ESP who handles the RGB LED feedback.

NOTE: You will need te fill in a view things. 

* Your routers name
* Your routers password
* Your site's URL

Don't share any passwords/usernames you have put in the fill on GitHub or with anyone else!

## Setup your server
The server is a Node.js server who runs Express. This means you need to have Node.js installed on your computer. If you don't have Node.js installed on your computer check the [Node.js site](https://nodejs.org/en/) for more info.
If you have Node.js download the [server-code](https://github.com/MartijnNieuwenhuizen/Internet_of_Things/tree/master/manual/server-code) file to your mac and open it in your terminal. If it's opened, run the command ```$ npm install```. After All the packages are installed, run ```$ nodemon start```. This will run your server and restart it automatically after an error. 

If you go to [http://localhost:3000/](http://localhost:3000/), you will see the project running and you are ready to use it.

## Usage
The ESP will push and pull its data every 3 seconds. If the server receives data, if will automatically run the matching action and probably return or change a file. 

The site checks every 5 seconds if the data has been changed since the last check. If it's changed, the code will be updated automatically.

## References
To create the Pull request on the ESP, I've used [this tutorial](http://blog.nyl.io/esp8266-led-arduino/), thanks for sharing [Nancy Yi Liang](http://blog.nyl.io/author/nyl/)!

## Tips/Questions
For tips or Questions, you can add create a GitHub issue. If you can improve this manual/code, please make a Pull Request. Thx and good luck.
