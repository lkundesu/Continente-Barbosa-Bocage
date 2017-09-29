
#ifndef scl
   //definição dos pinos de comunicação
   #define scl pin_b1  //pino clock
   #define sda pin_b0  //pino dados
   #define EEPROM_SIZE 32768  //tamanho em bytes da memoria eeprom
#endif

#define activa_scl   output_float(scl);  //liga o pino SCL
#define desliga_scl  output_low(scl);  //Desliga o pino SCL
#define activa_sda   output_float(sda);  //liga o pino SDA
#define desliga_sda  output_low(sda);  //Desliga o pino SDA

void I2c_start(void)
//Colocar o barramento na condição start
{
  desliga_scl;  //Coloca a linha de clock em nível 0
  activa_sda;   //Coloca a linha de dados em alta impedancia(1)
  activa_scl;   //coloca a linha de clock em alta impedancia
  desliga_sda;  //coloca a linha de dados em nível 0
  desliga_scl;  //Coloca a linha de clock em nível 0

}

void I2c_stop(void)
//Coloca o barramento na condição stop
{
 desliga_scl;  //coloca a linha de clock a nível 0
 desliga_sda;  //coloca a linha de dados em nível 0
 activa_scl;   //Coloca a linha de clock em alta impedancia (1)
 activa_sda;   //Coloca a linha de dados em alta impedancia (1)
}

void I2c_ack()
//Coloca sinal de reconhecimento (ack) no barramento
{
   desliga_sda;
   activa_scl;
   desliga_scl;
   activa_sda;
}

 void I2c_nack()
 //  coloca sinal de não reconhecimento (nack) no barramento
{
  activa_sda;
  activa_scl;
  desliga_scl;
}

boolean i2c_le_ack()
//efectua a leitura do sinal de ack/nack
{
boolean estado;
activa_sda;
activa_scl;
estado = input(sda);
desliga_scl;
return estado;
}
