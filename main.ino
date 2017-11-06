#include <Servo.h> 

class Prop{
  
  public:
    void init(int pin);
    void update(int full_stop, int min_pull, int max_pull, int min_pause, int max_pause);
    
  private:
    Servo servo;
    int state;
    long pull;
    long pause;
    long downspeed;
    long upspeed;
    unsigned long previousMillis;
  
};

void Prop::init(int pin){
  
    servo.attach(pin);
    state = 0;
    pull = random(1000, 5000);
    pause = random(200, 1000);
    downspeed = random(100, 135);
    upspeed = random(45, 80);
    previousMillis = 0;
    
}
  
void Prop::update(int full_stop, int min_pull, int max_pull, int min_pause, int max_pause)
      {
      unsigned long currentMillis = millis();
      //Serial.println(spider.previousMillis);
       
       if(state == 0){
         if((currentMillis - previousMillis) >= pull){
            previousMillis = currentMillis;
            pull = random(min_pull, max_pull);
            state++;
         }
       }else if( state == 2){
         if((currentMillis - previousMillis) >= pull){
            previousMillis = currentMillis;
            state++;
         }
       }else if(state == 1 || state == 3){
          if((currentMillis - previousMillis) >= pause){
            previousMillis = currentMillis;
            pause = random(min_pause, max_pause);
            state++;
         }
       }
       
      switch(state){
        case 0:
          servo.write(135);
          break;
        case 1:
          servo.write(full_stop);
          break;
        case 2:
          servo.write(45);
          break;
        case 3:
          servo.write(full_stop);
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
    spider.update(88, 500, 4000, 200, 1000); //less travel, short movements
    lefthand.update(90, 5000, 6500, 200, 1000); //more long travels
    righthand.update(88, 3000, 6500, 200, 1000); //full stop adjusted for motor drift
} 

