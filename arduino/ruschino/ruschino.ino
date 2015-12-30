String comando;
int en12=9;
int en34=10;
int dir12=4;
int dir34=5;
int board=1;
int out_bridge_n=0;
int incomingByte = 0;
int s_speed_sx=0;
int s_speed_dx=0;
boolean direction_sx=0;
boolean direction_dx=0;
boolean enable_sx=0; //non utilizzato
boolean enable_dx=0; //non utilizzato
  int command_name;
  int position;
  char cmd;

// Calculate based on max input size expected for one command
#define INPUT_SIZE 30

void motor_drive(int out_bridge, boolean dir, int speed) {

  if (out_bridge == 34) {
    //Serial.print(" Motor34 ");
    digitalWrite(dir34, dir);
    analogWrite(en34, speed);  
  } 
  else if (out_bridge == 12) {
    digitalWrite(dir12, dir);
    analogWrite(en12, speed);
  }  
}  

void setup() {
  Serial.begin(115200); 
  pinMode(en12, OUTPUT);
  pinMode(dir12, OUTPUT);
  pinMode(en34, OUTPUT);
  pinMode(dir34, OUTPUT); 
  Serial.println("Start");
}

void loop() {

  if (Serial.available() > 0) {

    char input[INPUT_SIZE + 1];
    byte size = Serial.readBytes(input, INPUT_SIZE);
    input[size] = 0;

    char* command = strtok(input, "&");
    while (command != 0)
    {
      char* command_value = strchr(command, '=');
      if (command_value != 0)
      {
        *command_value = 0;
        command_name = command[0];
        ++command_value;
        position = atoi(command_value);
      }
      command = strtok(0, "&");


      switch(command_name) {
      case 'l':
        s_speed_sx=position;
        break;
      case 'R':
        s_speed_dx=position;
        break;  
      case 'D':
        direction_dx=position;
        break;
      case 'd':
        direction_sx=position;
        break;  
      case 'E':
        enable_dx=position;
        break;
      case 'e':
        enable_sx=position;
        break;  

      }  
    }
   motor_drive(34,direction_sx,s_speed_sx);
   motor_drive(12,direction_dx,s_speed_dx); 
  }
}




