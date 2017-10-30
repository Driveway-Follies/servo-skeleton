#include <Servo.h> 

class Prop{
  
  public:
    void init(int pin);
    void update(int full_stop);
    
  private:
    Servo servo;
    int state;
    long time;
    long pause;
    long downspeed;
    long upspeed;
    unsigned long previousMillis;
  
};

void Prop::init(int pin){
  
    servo.attach(pin);
    state = 0;
    time = random(1000, 5000);
    pause = random(200, 1000);
    downspeed = random(100, 135);
    upspeed = random(45, 80);
    previousMillis = 0;
    
}
  
void Prop::update(int full_stop)
      {
      unsigned long currentMillis = millis();
      //Serial.println(spider.previousMillis);
       
       if(state == 0 || state == 2){
         if((currentMillis - previousMillis) >= time){
            previousMillis = currentMillis;
            time = random(1000, 5000);
            state++;
         }
       }else if(state == 1 || state == 3){
          if((currentMillis - previousMillis) >= pause){
            previousMillis = currentMillis;
            pause = random(200, 1000);
            state++;
         }
       }
       
      switch(state){
        case 0:
          servo.write(135);
          break;
        case 1:
          servo.write(90);
          break;
        case 2:
          servo.write(45);
          break;
        case 3:
          servo.write(90);
          break;
        case 4:
          state = 0;
          break;
        default:
          Serial.println("broken");
        break;
      }
}

Prop spider;
Prop lefthand;
Prop righthand;

void setup() 
{ 
  Serial.begin(9600);
  spider.init(9);
  lefthand.init(10);
  righthand.init(11);
} 

void loop() 
{ 
    spider.update(90);
    lefthand.update(90);
    righthand.update(88);
} 

