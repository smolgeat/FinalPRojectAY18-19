
/* 
 Improvements controll speed via potentiometer
 control update frequency vs potentiometer
 use functions for movement
*/
// For l298LN driver connections
int pan1 = 5;
int pan2 = 6;
int ena1 =7;
int tilt1 = 4;
int tilt2 = 3;
int ena2 = 2;
// for ldr
int topl = 0;
int topr = 1;
int botl = 2;
int botr = 3;

void setup() {
  // put your setup code here, to run once:

  pinMode(pan1,OUTPUT);
  pinMode(pan2,OUTPUT);
  pinMode(ena1,OUTPUT);
  pinMode(tilt1,OUTPUT);
  pinMode(tilt2,OUTPUT);
  pinMode(ena2,OUTPUT);

}

void loop() 
{
    // put your main code here, to run repeatedly:
   // read from ldr
    int tl = analogRead(topl);
    int tr = analogRead(topr);
    int bl = analogRead(botl);
    int br = analogRead(botr);
    int tol = analogRead(5)/4; //toleranc eallows for  relatively even sunlight across 4 quadrants
     int cycletime = analogRead(6); //time arduino waits
    //  int spd = anolagRead(7); motor speed setting
    
    // get avg voltage readings
    int avgtop = (tl+tr)/2;
    int avgbot = (bl+br)/2;
    int avgl = (tl+bl)/2;
    int avgr = (tr+br)/2 ;

    int dvert = avgtop - avgbot; // check the diffirence of up and down
    int dhorz = avgl - avgr;// check the diffirence og left and rigt
    // change orientation if difference in averages are outside of tolerance for vertical plane
  if ( -1*tol > dvert || dvert> tol) 
    {  
      if(avgtop>avgbot)//top has more average lightmove upwards
    {
       digitalWrite(tilt1,HIGH);
       digitalWrite(tilt2,LOW);
       analogWrite(ena2,255);   
       }
       else // bot has more move downwards
       {
        digitalWrite(tilt1,LOW);
       digitalWrite(tilt2,HIGH);
       analogWrite(ena2,255);
        }
    }
    else 
    {
      //stop
      digitalWrite(tilt1,LOW);
      digitalWrite(tilt2,LOW);
      }
    if ( -1*tol > dhorz|| dhorz> tol) //check for difference in horizontal plane
    {  
      if(avgtop>avgbot)//left has more average lightmove left
    {
       digitalWrite(pan1,HIGH);
       digitalWrite(pan2,LOW);
       analogWrite(ena1,255);   
       }
       else // right has more move right
       {
        digitalWrite(pan1,LOW);
       digitalWrite(pan2,HIGH);
       analogWrite(ena1,255);
        }
    }
       else 
    {
      //stop
      digitalWrite(pan1,LOW);
      digitalWrite(pan2,LOW);
      }

    
    delay(cycletime) ; //waits for x seconds
}
