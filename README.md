# The clock that displays time with words.
## Made by Dmitri Qiu.
## Powered by Arduino.

# So what is this project?
Its a little thing that I started about a year ago, and I never got the time to actually work on it until a week ago. So in this week I made this clock and I'm happy with how it actually turned out.

# Where did I got the inspiration for this project?
I saw a video on a channel called Vat19, (here is the original [video](https://www.youtube.com/watch?v=eHMkJWNHNkQ)), and I really liked the minimalistic design and how simple it is. So I thought why don't I make my self a clock like this? I'm broke and can't afford the shipping cost from America to Russia. So I decided to make a Russian version of the clock.

# How does it work?
So the main problem in this project is the pin amount on the Arduino. Because of the weird grammars of the Russian language, this endedup needing about 24 leds to light up every word. Obviously, a single Arduino Uno doesn't have 24 pins to power all of the leds. 

And I solved this problem with multiplexing. Because words that displays one to twelve only need one to light up at the same time. So I can just use multiplex to power 12 leds with 4 pins. And that perfectly solved my problem with the amount of pins, it was just enought to fit all the wires for the leds and the real time module in.

# Photos.
It's so late at night, I'll probably take a picture of the clock tomorrow, I think.