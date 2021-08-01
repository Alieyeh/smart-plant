  #include <LiquidCrystal.h>
  #include <SoftwareSerial.h>
  
  // bluetooth  
  SoftwareSerial EEBlue(10, 11); 
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

  byte humidity_sensor_vcc = 6;
  const int sensor_light = 0; // A0
  float value_light;
  const int sensor_temp = 5; // A5
  float value_temp;
  const int sensor_water = 1; // A1
  int value_water;

  int temp_limit_low = 15;
  int temp_limit_high = 35;
  int light_limit_low = 20;
  int light_limit_high = 50;
  int water_limit_low = 10;
  int water_limit_high = 30;

  void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    pinMode(sensor_temp, INPUT);
    pinMode(sensor_light, INPUT);
    pinMode(sensor_water, INPUT);
    pinMode(humidity_sensor_vcc, OUTPUT);
    digitalWrite(humidity_sensor_vcc, LOW);
    Serial.begin(9600);
  } 
  
  void loop() {
  
      if (EEBlue.available()){
        String data = EEBlue.readStringUntil('.');
        temp_limit_low = data.toInt();
        data = EEBlue.readStringUntil('.');
        temp_limit_high = data.toInt();
      
        data = EEBlue.readStringUntil('.');
        water_limit_low = data.toInt();
        data = EEBlue.readStringUntil('.');
        water_limit_high = data.toInt();

        data = EEBlue.readStringUntil('.');
        light_limit_low = data.toInt();
        data = EEBlue.readStringUntil('.');
        light_limit_high = data.toInt();
      
    }

        // temp
        value_temp = analogRead(sensor_temp);
        // convert to mV
        float mv = (value_temp / 1024.0) * 5000;
        // convert to Centigrade
        value_temp = mv / 10;
        String temp = String(value_temp);
        
        // light
        value_light = analogRead(sensor_light);
        String light = String(value_light);
 
        // water
        digitalWrite(humidity_sensor_vcc, HIGH);
        // wait for a second
        delay(500);

        value_water = analogRead(sensor_water);
        String water = String(value_water);
        
        value_water = analogRead(sensor_water);
        digitalWrite(humidity_sensor_vcc, LOW);
 
        int bad = 0;
        
        if (value_temp < temp_limit_low){
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print(temp);
          lcd.print("c ");
          lcd.print("*-* ");
          lcd.setCursor(0, 1);
          lcd.print("Freezing...help!");
          EEBlue.write("Freezing...help!!! *-*");
          delay(1500);
          bad = 1;
        }
          
        if (value_temp > temp_limit_high){
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print(temp);
          lcd.print("c ");
          lcd.print("~o_o~ ");
          lcd.setCursor(0, 1);
          lcd.print("Its hot...help!");
          EEBlue.write("Is it just me or is it getting realllly hot in here ~o _ o~");
          delay(1500);
          bad = 1;
        }
          
        if (value_light < light_limit_low) {
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print(light);
          lcd.print(" -_- ");
          lcd.setCursor(0, 1);
          lcd.print("Its dark...help!");
          EEBlue.write("Spare some sunlight pls -_-");
          delay(1500);               
          bad = 1;
        }
          
        if (value_light > light_limit_high) {
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print(light);
          lcd.print(" x_x ");
          lcd.setCursor(0, 1);
          lcd.print("I'm going blind!");
          EEBlue.write("I'm going blind!!! x-x");
          delay(1500);              
          bad = 1;
        }
          
        if (value_water < water_limit_low) {  
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print(water);
          lcd.print(" o_o ");
          lcd.setCursor(0, 1);
          lcd.print("I'm thirsty");
          EEBlue.write("When will this drought come to an end o-o");
          delay(1500);                 
          bad = 1;
        }
          
        if (value_water > water_limit_high) {  
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print(water);
          lcd.print(" T_T ");
          lcd.setCursor(0, 1);
          lcd.print("I'm drowning");
          EEBlue.write("I'm drowning T-T");
          delay(1500);               
          bad = 1;
        }
          
        if(bad == 0){
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print("^_^ ");
          lcd.setCursor(0, 1);
          lcd.print("It's all good");
          EEBlue.write("It's all good:)");
          delay(1500);
        }
} 
