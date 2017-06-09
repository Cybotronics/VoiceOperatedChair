

String voice;
int
m11 = 5, //Connect LED 1 To Pin #2 
m12 = 6, //Connect LED 2 To Pin #3 
m21 = 7, //Connect LED 3 To Pin #4 
m22 = 8;//Connect LED 4 To Pin #5 
 //Connect LED 5 To Pin #6
const int trigPin = 10;
const int echoPin = 11;
int hrtrate =12;
int buzzer =13;
int LED =3;
long duration;
int distance;

 int count = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(hrtrate, INPUT);
  pinMode(LED, OUTPUT);  
  pinMode(m11, OUTPUT); 
  pinMode(m12, OUTPUT); 
  pinMode(m21, OUTPUT); 
  pinMode(m22, OUTPUT); 
   
}
//-----------------------------------------------------------------------//  
void loop() {
  while (Serial.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable 
  char c = Serial.read(); //Conduct a serial read
  if (c == '#') {break;} //Exit the loop when the # is detected after the word
  voice += c; //Shorthand for voice = voice + c
  }  
  if (voice.length() > 0) {
    Serial.println(voice); 
//-----------------------------------------------------------------------//    
  //----------Control Multiple Pins/ LEDs----------//  
       if(voice == "*forward") 
       {
       digitalWrite(m11,HIGH); 
     digitalWrite(m12, LOW); 
     digitalWrite(m21, HIGH); 
     digitalWrite(m22, LOW);
     delay(2000);
     digitalWrite(m11, LOW); 
     digitalWrite(m12, LOW); 
     digitalWrite(m21, LOW); 
     digitalWrite(m22, LOW);
     
     Serial.println("moving forward"); 
        } 
     else if(voice == "*stop")
     {
     digitalWrite(m11, LOW); 
     digitalWrite(m12, LOW); 
     digitalWrite(m21, LOW); 
     digitalWrite(m22, LOW);
     Serial.println("chair stop"); 
     } 
    else if(voice == "*left")
  {
     digitalWrite(m11, LOW); 
     digitalWrite(m12, HIGH); 
     digitalWrite(m21, HIGH); 
     digitalWrite(m22, LOW);
     delay(500);
     digitalWrite(m11, LOW); 
     digitalWrite(m12, LOW); 
     digitalWrite(m21, LOW); 
     digitalWrite(m22, LOW); 
     Serial.println("moving left"); 
    } 
    else if(voice == "*right")
  {
    digitalWrite(m11, HIGH); 
     digitalWrite(m12, LOW); 
     digitalWrite(m21, LOW); 
     digitalWrite(m22, HIGH);
     delay(500);
     digitalWrite(m11, LOW); 
     digitalWrite(m12, LOW); 
     digitalWrite(m21, LOW); 
     digitalWrite(m22, LOW); 
     Serial.println("moving right"); 
    }
  else if(voice == "*backward")
  {
     digitalWrite(m11, LOW); 
     digitalWrite(m12, HIGH); 
     digitalWrite(m21, LOW); 
     digitalWrite(m22, HIGH);
     delay(2000);
     digitalWrite(m11, LOW); 
     digitalWrite(m12, LOW); 
     digitalWrite(m21, LOW); 
     digitalWrite(m22, LOW); 
     Serial.println("moving backword"); 
    }

  
voice="";}
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
Serial.println(duration);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
if (distance <=20)
{
digitalWrite(buzzer, HIGH);
delay(2000);
digitalWrite(buzzer, LOW);

  
  }
  
  if(digitalRead(hrtrate)>0){               //The heart rate sensor will trigger HIGH when there is a heart beat
    if(!count){                            //Only send data when it first discovers a heart beat - otherwise it will send a high value multiple times
      count=true;                          //By changing the beat variable to true, it stops further transmissions of the high signal
      digitalWrite(LED, HIGH);            //Turn the LED on 
      Serial.println(1023);               //Send the high value to the computer via Serial communication.
    }
  } else {                                //If the reading is LOW, 
    if(count){                             //and if this has just changed from HIGH to LOW (first low reading)
      count=false;                         //change the beat variable to false (to stop multiple transmissions)
      digitalWrite(LED, LOW);             //Turn the LED off.
      Serial.println(0);                  //then send a low value to the computer via Serial communication.
    }
  }


} //Reset the variable after initiating
