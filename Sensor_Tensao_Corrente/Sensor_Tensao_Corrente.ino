//------Sensor de Corrente------
const int analogIn_corrente = A1;
// Valor é igual 100 miliVolts
int mVperAmp = 100; 
int RawValue = 0;
int count = 0;
float maximo = 0;
double Voltage = 0;
double Amps = 0;
int ACSoffset = 2500;
float erro_corrente = 0.25;
//------------------------------//

//------Sensor de Tensao------
const int analogIn_tensao = A0;
float tensao = 0;
float erro = 2;
//Valor de calibragem da tensão
float form = 0.1495; 
//------------------------------//

//Variavel que recebe valor da potencia.
float potencia = 0;
//Contador de leitura
int aux = 0;


void setup() {
  Serial.begin (9600);
}

void loop() {

  tensao = analogRead(analogIn_tensao);
  tensao = (tensao - erro)*form;
  RawValue = analogRead(analogIn_corrente);
  Voltage = (RawValue / 1024.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp)- erro_corrente;

  //Corrente Negativas Convertidas
  if (Amps < 0){
   Amps = Amps * -1;
  }

  //Corrente maior
  if (maximo < Amps){
   maximo = Amps;
  }
  
  //Correnção de Corrente
  Amps = Amps - erro_corrente;

  //Filtro
  if(Amps < 0.3 * maximo){
    Amps = 0;
  }  
  
  //Cálculo de Potência
  potencia = Amps*tensao;
 
  Serial.print(aux++);
  Serial.print("     Corrente: ");
  Serial.print(Amps);
  Serial.print("  Tensao: ");
  Serial.print(tensao);
  Serial.print("   Potencia: ");
  Serial.println(potencia);
  delay(500);
}
