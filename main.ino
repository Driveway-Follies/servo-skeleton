#include <Servo.h> 

class Prop{
  
  public:
    void init(int servo_pin, int zero_pin);
    void update(int zero_pin, int full_stop, int min_pull, int max_pull, int min_pause, int max_pause);
    
  private:
    Servo servo;
    int state;
    int revs;
    long pull;
    long push;
    long pause;
    long downspeed;
    long upspeed;
    unsigned long previousMillis;
    unsigned long previousTrigger;
    int debounce;
  
};

void Prop::init(int servo_pin, int zero_pin){
  
    servo.attach(servo_pin);
    pinMode(zero_pin, INPUT_PULLUP);
    state = 0;
    revs = 0;
    pull = random(4, 8);
    push = random(0, 4);
    pause = random(200, 1000);
    downspeed = random(100, 135);
    upspeed = random(45, 80);
    previousMillis = 0;
    previousTrigger = 0;
    debounce = 300;
}
  
void Prop::update(int zero_pin, int full_stop, int min_pull, int max_pull, int min_pause, int max_pause)
      {
      unsigned long currentMillis = millis();
      //Serial.println(spider.previousMillis);
       int zeroed = digitalRead(zero_pin);
       if((currentMillis - previousTrigger) >= debounce){
         if(zeroed == LOW){
           previousTrigger = millis();
           if(state==0){
             revs++;
           }else if (state==2){
             revs--;
           }
         }
       }    
      
      if(state == 0){
         if(revs >= pull){
            pull = random((max_pull-min_pull)/2, max_pull);
            previousMillis = currentMillis;
            state++;
         }
       }else if( state == 2){
         if(revs <= push){
            push = random(min_pull, (max_pull-min_pull)/2);
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
  spider.init(9, 4); 
  lefthand.init(10, 5);
  righthand.init(11, 6);
} 

void loop() 
{ 
    spider.update(4, 88, 0, 16, 200, 1000); //less travel, short movements
    lefthand.update(5, 90, 0, 8, 200, 1000); //more long travels
    righthand.update(6, 88, 0, 8, 200, 1000); //full stop adjusted for motor drift
} 

