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
void motor_move (int tol,int diff,int term1, int term2, int spd, int x , int y) {
  if ( -1*tol > diff || diff> tol) 
    {  
      if(x>y)//moves toward x
        {
        digitalWrite(term1,HIGH);
        digitalWrite(term2,LOW);
        analogWrite(spd,255);   
        }
       else // moves toward y
        {
        digitalWrite(term1,LOW);
        digitalWrite(term2,HIGH);
        analogWrite(spd,255);
        }
    }
   else 
    {
    //stop
    digitalWrite(term1,LOW);
    digitalWrite(term2,LOW);
    }
}

void loop() 
{
    // put your main code here, to run repeatedly:
   // read from ldr
    int tl = analogRead(topl);
    int tr = analogRead(topr);
    int bl = analogRead(botl);
    int br = analogRead(botr);
    int tol = analogRead(4)/4; //determines  how much of a difference in sunlight the arduino responds to
    int cycletime = analogRead(5); //value adjusted using potentiometer
    //  int spd = anolagRead(7); motor speed setting
    
    // calculate avg voltage readings for top , bottom, left, right
    int avgtop = (tl+tr)/2;
    int avgbot = (bl+br)/2;
    int avgl = (tl+bl)/2;
    int avgr = (tr+br)/2 ;

    int dvert = avgtop - avgbot; // check the diffirence of up and down
    int dhorz = avgl - avgr;// check the diffirence og left and rigt
    // change orientation if difference in averages are outside of tolerance for vertical then horizontal plane
    motor_move(tol,dvert,tilt1,tilt2,ena2,avgtop,avgbot);
    motor_move(tol,dhorz,pan1,pan2,ena1,avgl,avgr);
    delay(cycletime) ; //time allows for motors to move before running again
}
