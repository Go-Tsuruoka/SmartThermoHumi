#include <Wire.h>
#include<DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
#define DHTPIN 2 //温湿度センサのデータのポート番号
#define DHTTYPE DHT11
#define INPUT_PIN 8
DHT dht(DHTPIN,DHTTYPE);
int mode=0;
int flag=0;
int vol_pin=1;
void setup(){
    pinMode(INPUT_PIN,INPUT_PULLUP);//スイッチの入力設定
    //LCDの初期化
    lcd.init(); //
    lcd.backlight();
    Serial.begin(9600);
    Serial.println(F("DHT11 test"));
    dht.begin();

}
//気温と湿度を表示する関数
void printtemp(float humid,float temp){
  if(isnan(humid)||isnan(temp)){//データ取得に失敗したときシリアルモニタに表示
    Serial.println(F("failed to read data from DHT11"));
    return;
    }
    //LCDの表示設定，1段目に"humid,temp",二段目に観測データ
    lcd.setCursor(0,0);
    lcd.print("humid ");
    lcd.print("temp");
    lcd.setCursor(0,1);
    lcd.print(humid,1);
    lcd.print("% ");
    lcd.print(temp,1);
    lcd.print("\xdf");
    lcd.print("C");
    //シリアルモニタにも表示(デバッグ用)
  Serial.print(F("Humidity: "));
  Serial.print(humid);
  Serial.print(F("%  Temperature: "));
  Serial.print(temp);
  Serial.println(F("°C "));
  return;
}

//不快指数を計算する関数
float Discomfort_index(float humid,float temp){
  float dindex = 0.81*temp+0.01*humid*(0.99*temp-14.3)+46.3;
  return dindex;
}


void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  //温湿度の取得
  float humid=dht.readHumidity();
  float temp = dht.readTemperature();
  //スイッチの入力の設定，flag関数はスイッチが押されたら1になる(1回ループすると0になる)
    Serial.print(digitalRead(INPUT_PIN));
    if(digitalRead(INPUT_PIN)==0){
      delay(100);
      flag=1;
      mode=mode+1;
      //if(digitalRead(INPUT_PIN)==HIGH)Serial.print("high");
      if(mode>2)mode=0;
      while(digitalRead(INPUT_PIN)==0){
        //delay(100);
      }
      delay(100);
      
    }
    //0の時
    if(mode==0) {
      //modeが変化した場合のみLCDを初期化
      if(flag==1){lcd.init();
      flag=0;}

      printtemp(humid,temp);//温度を表示
      
    }

    //mode1の時
    if(mode==1){
      if(flag==1){lcd.init();
    flag=0;}
       
      int ain = analogRead(vol_pin);//重力センサからの値取得
      
      //入力を書き出す
      Serial.println(ain);//シリアルモニタに表示
      //重量がある一定値以上の時
      if(ain<=300){
        Serial.println("max");
    
      lcd.setCursor(0,0);
      lcd.print("water level");
      lcd.setCursor(0,1);
      lcd.print("max             ");
  }
      //重量が中間の時
      else if(360>ain>300){
        Serial.println("mid");
       
          lcd.setCursor(0,0);
          lcd.print("water level");
          lcd.setCursor(0,1);
          lcd.print("mid             ");
      }
      //重量が一定値以下で殻の時
      else if(ain>390){
        Serial.println("low");
          lcd.setCursor(0,0);
          lcd.print("water level");
          lcd.setCursor(0,1);
          lcd.print("low!,Buy new one");
      }
  delay(100);
}
      //mode2の時
     if(mode==2){
     float d_index=Discomfort_index(humid,temp);
     if(flag==1){lcd.init();
        flag=0;}
          //不快指数を表示
          lcd.setCursor(0,0);
          lcd.print("discom(level)");
          lcd.setCursor(0,1);
          lcd.print(d_index);
          lcd.print(":");
          //不快指数の値に応じてフレグランスの強さのレベルを表示(5段階)
          float vol=max(abs(d_index-65),abs(d_index-70));
          if(vol<=5){
            lcd.print("Very Good,5");
          }
          else if(5<vol and vol<=10){
            lcd.print("Good,4");
          }
          else if(10< vol and  vol<=15){
            lcd.print("Average,3");
          }
          else if(15<vol and vol<=20){
            lcd.print("Not good,2");
          }
          else{
            lcd.print("Bad,1");
          }
        }
    }
   
  
  
    
