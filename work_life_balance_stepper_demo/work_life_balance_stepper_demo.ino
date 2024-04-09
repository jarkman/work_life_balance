
#include <AccelStepper.h>


// runs on a Nano 

// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::FULL4WIRE, 2,4,3,5); // note middle two pins are swapped to work with 28BYJ-48 
                                                            // wire arduino pin D2 to driver board IN1, and so on
                                                            

// using 28BYj-48 motors from http://www.ebay.co.uk/itm/131410728499

#define STEPS_PER_REV (4096.0/2.0) // these motore come in two different gear rations, 
                              // see http://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno/ 
                              // and http://forum.arduino.cc/index.php?topic=71964.15

#define MAX_SPEED 350 // 800 is a sensible limit on 5v motor supply, 300 is a sensible limit on 3v.
#define MAX_ACCELERATION 400 // 1600 on 5v, 400 on 3v

#define NUM_BALLS 16.0 // must match pulley

float target = 0.0;

void setup()
{  

  stepper.setMaxSpeed(MAX_SPEED); // 800 is a sensible limit on 5v motor supply, 300 is a sensible limit on 3v.
  stepper.setAcceleration(MAX_ACCELERATION); // 1600 on 5v
  
  target = -20;

}

void loop()
{

  stepper.run(); // must call this often to keep the stepper library working

  if( ! stepper.isRunning())
  {
    target = -target;
    go(target);
  }
  
}

float stepsForDistance( float balls ) // dinstance in balls
{
  return balls * STEPS_PER_REV / NUM_BALLS;
}



void go( float balls )
{
  float steps = stepsForDistance( balls );
  stepper.setCurrentPosition(0);
  
  stepper.move(steps);
  
  
}




