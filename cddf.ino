/* Carga de Librerias de LCD y otras */
#include <LiquidCrystal.h>

/* Pins de nuestra LCD               */
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

/* Declaracion de Constantes         */
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

/* Valores de los botones de lcd keypad shiel por A0 */
#define btnNONEvalue   1000
#define btnRIGHTvalue  0
#define btnUPvalue     133
#define btnDOWNvalue   310
#define btnLEFTvalue   482
#define btnSELECTvalue 724

#define BACKLIGHTPIN   10    //D10 pin de backlight
#define DELAYADJ      980    // Ajuste del delay

/* Declaracion de Variables          */
int lcd_key       = 0;
int adc_key_in    = 0;

int meses         = 0;
int dias          = 0;
int horas         = 0;
int minutos       = 0;
int segundos      = 0;
int flipflop      = 0;
int incidentes    = 0;

/* Images de bytes                   */
byte pacman[8] = {            //Pacman
  B00000,
  B00000,
  B01110,
  B11011,
  B11100,
  B01110,
  B00000,
  B00000
};

byte fantasma[8] = {         // Fantasma
  B00000,
  B00000,
  B01110,
  B10101,
  B11111,
  B11111,
  B10101,
  B00000
};

byte reloj[8] = {            // Reloj
  B00000,
  B01110,
  B10101,
  B10111,
  B10001,
  B01110,
  B00000,
  B00000
};

byte C[8] = {                //© Copy
  B00000,
  B00000,
  B11100,
  B10000,
  B10000,
  B11100,
  B00000,
  B00000
};

/* SETUP Se ejecuta al inicio 1 vez  */
void setup()   
{
  lcd.begin(16, 2);                  // Inicializamos la LCD

  /* Mensaje de inicio en pantalla     */
  lcd.setCursor(0,0);
  lcd.print("C.d.D.F. Control");
  lcd.setCursor(0,1);
  lcd.print("  de Desastres  ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  de Desastres  "); 
  lcd.setCursor(0,1);
  lcd.print("   Familiares   "); 

  lcd.createChar(0, pacman);         // Generacion de mapas de caracteres
  lcd.createChar(1,fantasma);
  lcd.createChar(2,reloj);
  lcd.createChar(3,C);

  delay(2000);
  lcd.clear();
  
}  // Fin SETUP 


/* LOOP Se ejecuta constantemente    */
void loop()   
{    
    lcd_key = read_LCD_buttons();    // Leeemos si hay algun boton pulsado
    switch (lcd_key)               
    {
     case btnNONE:                  // No hay boton
      {
        lcd.setCursor(0,0);
        lcd.write(byte(2));
        lcd.print(" Sin Desastres  ");
        break;
      }
     case btnSELECT:               // Boton Select -> Muestra el contador de Desastres
      {
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print(String("Desastres: ") + String(incidentes) + String("  "));
        lcd.write(byte(1));
        break;
      }
     case btnRIGHT:                 // Boton Derecha -> Muestra el © Copy
      {
        lcd.setCursor(0,0);
        lcd.print("C.d.D.F. Control");
        lcd.setCursor(0,1);
        lcd.print(" Desastres Fam. ");
        delay(1200);
        lcd.setCursor(0,0);
        lcd.write(byte(3));
        lcd.print("2020 DarkSystem");
        lcd.setCursor(0,1);
        lcd.print("Por ISAAC y POPA");
        break;
      }
     case btnLEFT:                   // Boton Izquierda  -> Incrementa Desastres y reincia contadores
      {
        lcd.setCursor(0,0);
        lcd.print("                ");
        lcd.setCursor(0,0);
        lcd.print("Nuevo Desastre ");
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
      case btnUP:                      // Boton Arriba -> Enciende backlight
      {
        backlightOn();
        break;
      }
      case btnDOWN:                    // Boton Abajo -> Apaga backlight
      {
        backlightOff();
        break;
      }
    }   

    // Incremento de tiempo
    delay(DELAYADJ);
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
        
    // Pintamos el tiempo
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

} // Fin LOOP

/* Lectura de botones pulsados       */
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);        // Lectura del sensor
  // los valores de nuestro lcd keypad shield son: 0, 133, 310, 482, 724
  if ( adc_key_in >  btnNONEvalue )   return btnNONE; 
  if ( adc_key_in == btnRIGHTvalue  ) return btnRIGHT;
  if ( adc_key_in == btnUPvalue )     return btnUP;
  if ( adc_key_in == btnDOWNvalue )   return btnDOWN;
  if ( adc_key_in == btnLEFTvalue )   return btnLEFT;
  if ( adc_key_in == btnSELECTvalue ) return btnSELECT;
  return btnNONE;
}

/* Apagado de retroiluminacion       */
void backlightOff()
{
  digitalWrite(BACKLIGHTPIN, LOW);
  pinMode(BACKLIGHTPIN, OUTPUT);
}

/* Encendido  de retroiluminacion     */
void backlightOn()
{
  digitalWrite(BACKLIGHTPIN, LOW);
  pinMode(BACKLIGHTPIN, INPUT);
}
