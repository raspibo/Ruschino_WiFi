int en12=9;
int en34=10;
int dir12=4;
int dir34=5;
int board=1;
int out_bridge_n=0;
int s_speed_sx=0;
int s_speed_dx=0;
boolean direction_sx=0;
boolean direction_dx=0;

void motor_drive(int out_bridge, boolean dir, int speed) {
  if (speed < 30) {
    speed = 0;
  }
  if (out_bridge == 34) {
    digitalWrite(dir34, dir);
    analogWrite(en34, speed);  
  } 
  else if (out_bridge == 12) {
    digitalWrite(dir12, dir);
    analogWrite(en12, speed);
  }  
}  

void setup() {
  Serial.begin(9600); 
  pinMode(en12, OUTPUT);
  pinMode(dir12, OUTPUT);
  pinMode(en34, OUTPUT);
  pinMode(dir34, OUTPUT); 
  Serial.println("READY");
}
 
void loop() {
  while (Serial.available() > 0) {
    s_speed_sx = Serial.parseInt();
    s_speed_dx = Serial.parseInt();    
    if (Serial.read() == '*') {
      if (s_speed_sx<0) {
        direction_sx = 0;
      } else {
        direction_sx = 1;
      }
      if (s_speed_dx<0) {
        direction_dx = 1;
      } else {
        direction_dx = 0;
      }
      motor_drive(34,direction_sx,abs(s_speed_sx));
      motor_drive(12,direction_dx,abs(s_speed_dx));
    }
  }
}


