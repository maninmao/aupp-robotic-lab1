void setup() {
  pinMode(16, INPUT);
  pinMode(15, INPUT);
  pinMode(4, INPUT);
  pinMode(2, INPUT);
  Serial.begin(115200);

  //for moving robot
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  ledcSetup(0, 20000, 8);
  ledcAttachPin(33, 0);

  pinMode(32, OUTPUT);
  pinMode(27, OUTPUT);
  ledcSetup(1, 20000, 8);
  ledcAttachPin(14, 1);

  pinMode(21, OUTPUT);
  pinMode(18, OUTPUT);
  ledcSetup(2, 20000, 8);
  ledcAttachPin(05, 2);

  pinMode(23, OUTPUT);
  pinMode(22, OUTPUT);
  ledcSetup(3, 20000, 8);
  ledcAttachPin(19, 3);


  Serial.begin(115200);

  // ADC pins do not need pinMode
  Serial.println("ESP32 Joystick Reading Started");
}



void move_forward(int linear_speed){

  ledcWrite(0, linear_speed);
  ledcWrite(1, linear_speed);
  ledcWrite(2, linear_speed);
  ledcWrite(3, linear_speed);

  //M1
  digitalWrite(26, LOW);
  digitalWrite(25, HIGH);

  //M2
  digitalWrite(27, LOW);
  digitalWrite(32, HIGH);

  //M3
  digitalWrite(18, HIGH);
  digitalWrite(21, LOW);

  //M4
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
}

void move_backward(int linear_speed){
  ledcWrite(0, linear_speed);
  ledcWrite(1, linear_speed);
  ledcWrite(2, linear_speed);
  ledcWrite(3, linear_speed);

  //M1
  digitalWrite(26, HIGH);
  digitalWrite(25, LOW);

  //M2
  digitalWrite(27, HIGH);
  digitalWrite(32, LOW);

  //M3
  digitalWrite(18, LOW);
  digitalWrite(21, HIGH);

  //M4
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
}

void move_left(int rotation_speed){
  ledcWrite(0, rotation_speed);
  ledcWrite(1, rotation_speed);
  ledcWrite(2, 0);
  ledcWrite(3, 0);

  //M1
  digitalWrite(26, LOW);
  digitalWrite(25, HIGH);

  //M2
  digitalWrite(27, LOW);
  digitalWrite(32, HIGH);

 //M3
  digitalWrite(18, LOW);
  digitalWrite(21, HIGH);

  //M4
  digitalWrite(22, LOW);
  digitalWrite(23, HIGH);
}

void move_right(int rotation_speed){
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, rotation_speed);
  ledcWrite(3, rotation_speed);

  //M1
  digitalWrite(26, HIGH);
  digitalWrite(25, LOW);

  //M2
  digitalWrite(27, HIGH);
  digitalWrite(32, LOW);

  //M3
  digitalWrite(18, HIGH);
  digitalWrite(21, LOW);

  //M4
  digitalWrite(22, HIGH);
  digitalWrite(23, LOW);
}

void stop(){
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
}



const int joyX = 34;
const int joyY = 35;

int xValue = 0;
int yValue = 0;


  int linear_speed = 10;
  int rotation_speed = 10;
  bool lastButtonUp = HIGH;
  bool lastButtonDown = HIGH;
  bool lastButtonRight = HIGH;
  bool lastButtonLeft = HIGH;

void loop(){
  xValue = analogRead(joyX);  // 0 - 4095
  yValue = analogRead(joyY);  // 0 - 4095
  int button_up = digitalRead(16);
  int button_down = digitalRead(15);
  int button_right = digitalRead(4);
  int button_left = digitalRead(2);

  if (button_up == LOW && lastButtonUp == HIGH){
    linear_speed += 12;
    Serial.print("Linear: ");
    Serial.println(linear_speed);
  }

  else if (button_down == LOW && lastButtonDown == HIGH){
    linear_speed -=12;
    Serial.print("Linear: ");
    Serial.println(linear_speed);
    }

  else if (button_right == LOW && lastButtonRight == HIGH){
    rotation_speed +=12;
    Serial.print("Rotation: ");
    Serial.println(rotation_speed);
  }

  else if (button_left == LOW && lastButtonLeft == HIGH){
    rotation_speed -=12;
    Serial.print("Rotation: ");
    Serial.println(rotation_speed);
  }

  // limit the speed to only 100 to prevent the board from getting smoked
  linear_speed = constrain(linear_speed, 0, 100);
  rotation_speed = constrain(rotation_speed, 0, 100);

  lastButtonUp = button_up;
  lastButtonDown = button_down;
  lastButtonRight = button_right;
  lastButtonLeft = button_left;


  if (yValue <= 1700 && yValue >= 0){
    move_forward(linear_speed);}

  else if (yValue <= 4095 && yValue >= 2200){
    move_backward(linear_speed);
    }

  else if (xValue <= 1700 && xValue >= 0){
    move_right(rotation_speed);
    }
  
  else if (xValue <= 4095 && xValue >= 2200){
    move_left(rotation_speed);
    }

  else{
    stop();}

}
