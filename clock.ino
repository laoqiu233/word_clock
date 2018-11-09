/*
 * The clock that displays time with words(TM)
 * @ Author: Qiu Dmitri
 * @ Date started: 2018/11/6
 * @ Last Update: 2018/11/6
 * @ Version: 1.1
 * 
 * TODO:
 *  [X] Minutes LEDS.
 *  [X] Real time module.
 *  [X] Startup animation.
 */

#include <iarduino_RTC.h>

void ClearPins(int leds){
    /* Clears all pin modes to input. (or to low)
        0 - Hour leds.
        1 - minute leds.
    */
    switch (leds)
    {
        case 0:
            for (int i = 4; i < 8; i++){
                digitalWrite(i, LOW);
                pinMode(i, INPUT);
            }
            break;
        
        case 1:
            for (int i = 2; i <= 19; i++){
                if (i <= 3 || i >= 11){
                    digitalWrite(i, LOW);
                }
            }

        default:
            break;
    }
}

void LightHours(int Hour){
    /* Lights up a certain LED that shows hours */
    ClearPins(0);
    if (Hour <= 0 || Hour > 12){
        return;
    }
    switch (Hour)
    {   
        case 1:
            // Hour 1
            pinMode(7, OUTPUT);
            pinMode(6, OUTPUT);
            digitalWrite(6, HIGH);
            break;
        
        case 2:
            //Hour 2
            pinMode(7, OUTPUT);
            pinMode(6, OUTPUT);
            digitalWrite(7, HIGH);
            break;

        case 3:
            //Hour 3
            pinMode(5, OUTPUT);
            pinMode(4, OUTPUT);
            digitalWrite(4, HIGH);
            break;

        case 4:
            //Hour 4
            pinMode(5, OUTPUT);
            pinMode(4, OUTPUT);
            digitalWrite(5, HIGH);
            break;

        case 5:
            //Hour 5
            pinMode(7, OUTPUT);
            pinMode(5, OUTPUT);
            digitalWrite(5, HIGH);
            break;

        case 6:
            //Hour 6 
            pinMode(7, OUTPUT);
            pinMode(5, OUTPUT);
            digitalWrite(7, HIGH);
            break;

        case 7:
            //Hour 7
            pinMode(6, OUTPUT);
            pinMode(4, OUTPUT);
            digitalWrite(4, HIGH);
            break;

        case 8:
            //Hour 8
            pinMode(6, OUTPUT);
            pinMode(4, OUTPUT);
            digitalWrite(6, HIGH);
            break;
        
        case 9:
            //Hour 9
            pinMode(6, OUTPUT);
            pinMode(5, OUTPUT);
            digitalWrite(5, HIGH);
            break;

        case 10:
            //Hour 10
            pinMode(6, OUTPUT);
            pinMode(5, OUTPUT);
            digitalWrite(6, HIGH);
            break;

        case 11:
            //Hour 11
            pinMode(7, OUTPUT);
            pinMode(4, OUTPUT);
            digitalWrite(4, HIGH);
            break;

        case 12:
            //Hour 12
            pinMode(7, OUTPUT);
            pinMode(4, OUTPUT);
            digitalWrite(7, HIGH);
            break;

        default:
            break;
    }
}

// Getting time in variables by time.gettime() function.
/* time.hours
 * time.minutes
 * time.seconds
 */

// All the pins.
#define now 14
#define from 3
#define to 2
#define five 19
#define ten 11
#define twenty 18
#define half 17
#define minute 12
#define a 13
#define abs 16
#define almost 15

void almostOrAbs(int minutes, int minutesAbs){
    // Lights up almost or absolute.
    if (minutes == minutesAbs){
        digitalWrite(abs, HIGH);
    }else {
        digitalWrite(almost, HIGH);
    }
}

iarduino_RTC time(RTC_DS1302, 8, 10, 9);

int hour = 0;
int AnimTick = 0;
bool finishAnim = false;

void setup()
{
	Serial.begin(9600);
    //Start the time counting.
    time.begin();
    //Uncomment if you need to set another time.
    //time.settime(0, 26, 17, 9, 11, 18, 5);
    
    //Setting all the pins to output mode.
    for (int i = 2; i <= 19; i++){
        pinMode(i, OUTPUT);
    }
}

void loop()
{   

    /*  For debugging purposes.
        if (Serial.available() > 0) {
            // read the incoming byte:
            int incomingByte = Serial.parseInt();
            LightHours(incomingByte);
        }
    */

    time.gettime();

    //Serial.print(time.hours);
    //Serial.print(time.minutes);
    //Serial.println(time.seconds);

    //Startup Animation
    if (!finishAnim){
        if (AnimTick >= 0){ digitalWrite(now, HIGH); }
        if (AnimTick >= 5){ digitalWrite(almost, HIGH); }
        if (AnimTick >= 10){ digitalWrite(abs, HIGH); }
        if (AnimTick >= 15){ digitalWrite(half, HIGH); }
        if (AnimTick >= 20){ digitalWrite(twenty, HIGH); }
        if (AnimTick >= 25){ digitalWrite(five, HIGH); }
        if (AnimTick >= 30){ digitalWrite(ten, HIGH); }
        if (AnimTick >= 35){ digitalWrite(minute, HIGH); }
        if (AnimTick >= 40){ digitalWrite(a, HIGH); }
        if (AnimTick >= 45){ digitalWrite(from, HIGH); }
        if (AnimTick >= 50){ digitalWrite(to, HIGH); }
        if (AnimTick >= 55){ 
            LightHours((AnimTick - 50) / 5);
        }
        if ((AnimTick - 50) / 5 >= 13){
            finishAnim = true;
        }
        AnimTick++;
    }else {
        // Time displaying.
        ClearPins(1);
        digitalWrite(now, HIGH);
        //Half hours handling. / Display minutes.
        if (time.minutes < 30){
            hour = time.hours;
            digitalWrite(from, HIGH);
            digitalWrite(minute, HIGH);
            // Zero minutes.
            if (time.minutes == 0){
                digitalWrite(abs, HIGH);
                digitalWrite(from, LOW);
                digitalWrite(minute, LOW);
            // One minute.
            }else if (time.minutes == 1){
                digitalWrite(a, HIGH);
            // Five minutes.
            }else if (time.minutes <= 5){
                almostOrAbs(time.minutes, 5);
                digitalWrite(five, HIGH);
            // Ten minutes.
            }else if (time.minutes <= 10){
                almostOrAbs(time.minutes, 10);
                digitalWrite(ten, HIGH);
            // Twenty minutes.
            }else if (time.minutes <= 20){
                almostOrAbs(time.minutes, 20);
                digitalWrite(twenty, HIGH);
            // Twenty-five minutes.
            }else if (time.minutes <= 25){
                almostOrAbs(time.minutes, 25);
                digitalWrite(twenty, HIGH);
                digitalWrite(five, HIGH);
            // Almost half.
            }else {
                hour = time.hours + 1;
                if (hour > 12){
                    hour -= 12;
                }
                digitalWrite(minute, LOW);
                digitalWrite(half, HIGH);
                digitalWrite(almost, HIGH);
            }
        // Half an hour.
        }else if (time.minutes == 30){
            hour = time.hours + 1;
            if (hour > 12){
                hour -= 12;
            }
            digitalWrite(half, HIGH);
            digitalWrite(abs, HIGH);
        }else if (time.minutes > 30){
            hour = time.hours + 1;
            if (hour > 12){
                hour -= 12;
            }
            digitalWrite(to, HIGH);
            digitalWrite(minute, HIGH);
            // Twenty-five minutes.
            if (60 - time.minutes >= 25){
                almostOrAbs(60 - time.minutes, 25);
                digitalWrite(twenty, HIGH);
                digitalWrite(five, HIGH);
            }else if (60 - time.minutes >= 20){
                almostOrAbs(60 - time.minutes, 20);
                digitalWrite(twenty, HIGH);
            }else if (60 - time.minutes >= 10){
                almostOrAbs(60 - time.minutes, 10);
                digitalWrite(ten, HIGH);
            }else if (60 - time.minutes >= 5){
                almostOrAbs(60 - time.minutes, 5);
                digitalWrite(five, HIGH);
            }else if (60 - time.minutes == 1){
                digitalWrite(a, HIGH);
            }
        }

        // Display hours.
        LightHours(hour);
    }
}

// Writing arduino code is boring as hell, it's 
// just bunch of repeating functions.