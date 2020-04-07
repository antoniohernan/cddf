/*-----( Import needed libraries )-----*/
#include <LiquidCrystal.h>

/*-----( Declare objects )-----*/
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //These are the pins used on this shield

/*-----( Declare Constants )-----*/
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

/*-----( Declare Variables )-----*/
int lcd_key       = 0;
int adc_key_in0   = 0;

int meses = 0;
int dias = 0;
int horas = 0;
int minutos = 0;
int segundos = 0;
int flipflop = 0;
int incidentes = 0;

// Imagen de Pacman
byte pacman[8] = {
  B00000,
  B00000,
  B01110,
  B11011,
  B11100,
  B01110,
  B00000,
  B00000
};

// Imagen Fantasma
byte fantasma[8] = {
  B00000,
  B00000,
  B01110,
  B10101,
  B11111,
  B11111,
  B10101,
  B00000
};

byte reloj[8] = {
  B00000,
  B01110,
  B10101,
  B10111,
  B10001,
  B01110,
  B00000,
  B00000
};

byte C[8] = {
  B00000,
  B00000,
  B11100,
  B10000,
  B10000,
  B11100,
  B00000,
  B00000
};

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  lcd.begin(16, 2);              // start the lcd object
  //Print Initial Messages
  lcd.setCursor(0,0);
  lcd.print("S.D.C.A. Sistema");
  lcd.setCursor(0,1);
  lcd.print("Ctrl Accidentes");
  lcd.createChar(0, pacman);
  lcd.createChar(1,fantasma);
  lcd.createChar(2,reloj);
  lcd.createChar(3,C);

  delay(2000);
  lcd.clear();
  
}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{    
    lcd_key = read_LCD_buttons(); 
    switch (lcd_key)               
    {
     case btnNONE:
      {
        lcd.setCursor(0,0);
        lcd.write(byte(2));
        lcd.print(" Sin Accidentes ");
        break;
      }
     case btnSELECT:
      {
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print(String("Incidentes: ") + String(incidentes) + String(" "));
        lcd.write(byte(1));
        break;
      }
     case btnRIGHT:
      {
        lcd.setCursor(0,0);
        lcd.print("S.D.C.A. Sistema");
        lcd.setCursor(0,1);
        lcd.print("Ctrl Accidentes");
        delay(1200);
        lcd.setCursor(0,0);
        lcd.write(byte(3));
        lcd.print("2020 DarkSystem");
        lcd.setCursor(0,1);
        lcd.print("Por ISAAC y POPA");
        break;
      }
     case btnUP:
      {
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("Nuevo Accidente");
        lcd.write(byte(1));
        incidentes++;
        meses = 0;
        dias = 0;
        horas = 0;
        minutos = 0;
        segundos = 0;
        delay(3000);
        break;
      }
    }   
    
    delay(1000);
    segundos++;
  
    if(segundos >= 60){ 
      segundos = 0;
      minutos++;
    }
    if(minutos == 60){ 
      minutos = 0;
      horas++;
    }

    if(horas == 24){ 
      horas = 0;
      dias++;
    }

    if(dias == 30){ 
      dias = 0;
      meses++;
    }
        
    //Print Time
    lcd.setCursor(0,1);
    
    if(meses < 10){
      lcd.print("0");
    }
    lcd.print(meses);
    lcd.print(":");

    lcd.setCursor(3,1);
    if(dias < 10){
      lcd.print("0");
    }
    lcd.print(dias);
    lcd.print(":");

    lcd.setCursor(6,1);
    if(horas < 10){
      lcd.print("0");
    }
    lcd.print(horas);
    lcd.print(":");
    
    lcd.setCursor(9,1);
    if(minutos < 10){
      lcd.print("0");
    }
    lcd.print(minutos);
    lcd.print(":");
    
    lcd.setCursor(12,1);
    if(segundos < 10){
      lcd.print("0");
    }
    lcd.print(segundos);
    lcd.print(":");
    
    lcd.setCursor(15,1);
    if (flipflop < 1){
      lcd.write(" ");
      flipflop=1;
    }
    else {
      lcd.write(byte(0));
      flipflop=0;
    }

}/* --(end main loop )-- */


//get which button is pressed
int read_LCD_buttons()
{
  adc_key_in0 = analogRead(0);      // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in0 > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in0 == 0  )  return btnRIGHT;
  if (adc_key_in0 == 133)  return btnUP;
  if (adc_key_in0 == 310)  return btnDOWN;
  if (adc_key_in0 == 482)  return btnLEFT;
  if (adc_key_in0 == 724)  return btnSELECT;
  return btnNONE;  // when all others fail, return this...
}
