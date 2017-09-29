/////////////////////////////////////////////////////////////////////////
////                           max7312.c                             ////
////           Library for Maxim's 20/28 Port IO Expander            ////
////                                                                 ////
//// This library provides the following functions:                  ////
////                                                                 ////
//// max7313_init(device) - Initializes Max7300, and all ports set   ////
////                        to input with internall pull-up resistor ////
////                                                                 ////
//// int1 = input_pin_ext(device, pin) - Returns the logic level of  ////
////                                     pin, where pin can be 4     ////
////                                     through 31                  ////
////                                                                 ////
//// int32 = input_ext(device) - Returns an int32 which is a bitmap  ////
////                     of all logic levels read on all ports.      ////
////                     Bit0 of the returned value is Port0 on the  ////
////                     Max7300, Bit31 of the returned value is     ////
////                     Port31.                                     ////
////                                                                 ////
//// output_ext(device, data) - Sets the output latch of the         ////
////                            Max7300 to data, which is an int32   ////
////                            bit map of all ports.  Bit0 of data  ////
////                            is Port0, Bit31 of data is Port31.   ////
////                                                                 ////
//// set_tris_ext(device, pin, tris, pullup) -                       ////
////          Configures the specified pin to be input or output.    ////
////          Pin can range from 4 through 31 to specify which pin,  ////
////          set tris to 1 to specify input, 0 for output.  Set     ////
////          pullup to 1 to specify to enable pull-up resistors,    ////
////          clear to disable pull-up resistors.                    ////
////          If you wish to change several ports at once it would   ////
////          be more effecient to use max7300_write() to write to   ////
////          the control registers directly.                        ////
////                                                                 ////
//// output_high_ext(device, pin) - Sets the output latch of         ////
////                                specified pin to high            ////
////                                                                 ////
//// output_low_ext(device, pin) - Sets the output latch of          ////
////                               specified pin to low              ////
////                                                                 ////
//// output_pin_ext(device, pin, level) -                            ////
////         Sets the output latch of specified pin to level         ////
////                                                                 ////
//// int8 = max7300_read(device, address) - Reads and returns the    ////
////                                 value in the control register   ////
////                                 specified by address            ////
////                                                                 ////
//// max7300_write(device, address, data) - Writes data to the       ////
////                    control register as specified by address     ////
////                                                                 ////
//// In all functions, device is the I2C address of the Max7300 you  ////
//// wish to talk to, to seperate individual Max7300's on the bus.   ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2003 Custom Computer Services         ////
//// This source code may only be used by licensed users of the CCS  ////
//// C compiler.  This source code may only be distributed to other  ////
//// licensed users of the CCS C compiler.  No other use,            ////
//// reproduction or distribution is permitted without written       ////
//// permission.  Derivative programs created using this software    ////
//// in object code form are not restricted in any way.              ////
/////////////////////////////////////////////////////////////////////////


#ifndef MAX7312_CLK
   #define MAX7312_CLK  PIN_B1
   #define MAX7312_DATA PIN_B0
#endif

#use I2C(master, sda=MAX7312_DATA, scl=MAX7312_CLK)

//prototypes
int8 max7312_read(int device, int address);  //reads 7312 control register
void max7312_write(int device, int address, int data);   //writes 7312 control register

void max7312_init_output(int device) { //Alterei esta função
   output_float(MAX7312_CLK);
   output_float(MAX7312_DATA);

   max7312_write(device,0x06,0x00);  //configura porto 1 como saída
   max7312_write(device,0x07,0x00);  //configura porto 2 como saída                                             -->Nota: Alterei Aqui


   max7312_write(device,0x02,0x00); //Coloca o porto 1 como saída(Mudar para 0x00 onde está o 0xFF)
   max7312_write(device,0x03,0x00); //Coloca o porto 2 como saída(Mudar para 0x00 onde está o 0xFF)             -->Nota: Alterei Aqui
}

void max7312_init_input(int device) { //Alterei esta função
   output_float(MAX7312_CLK);
   output_float(MAX7312_DATA);

   max7312_write(device,0x06,0x11);  //configura porto 1 como entrada  ------------->Verificar se não é FF

}

/*
int1 input_pin_ext(int device, int pin) {
   return(max7300_read(device,pin+0x20) & 0x01);
}

*/
/*
int32 input_ext(int device) {
   int a;   //4-11
   int b;   //12-19
   int c;   //20-27
   int d;   //28-31
   int32 ret;


   a=max7300_read(device, 0x44);
   b=max7300_read(device, 0x4C);
   c=max7300_read(device, 0x54);
   d=max7300_read(device, 0x5C);

   ret=make32(d,c,b,a); //bit 0 is port 4
   ret=ret << 4;   //bit 0 is port 0
   ret &= 0xFFFFFFF0;   //p0-p4 are junk

   return(ret);
}
*/
/*
void output_ext(int device, int32 data) {
   int a;   //4-11
   int b;   //12-19
   int c;   //20-27
   int d;   //28-31

   data=data >> 4;

   a=make8(data,0);
   b=make8(data,1);
   c=make8(data,2);
   d=make8(data,3);
   max7300_write(device,0x44,a);
   max7300_write(device,0x4C,b);
   max7300_write(device,0x54,c);
   max7300_write(device,0x5C,d);
}
*/
/*
void set_tris_ext(int device, int pin, int1 tris, int1 pullup) {
   int addy, data, mod;
   if ((pin >= 4)&&(pin <= 31)) {
       addy=0x08 + (pin / 4);
       mod=(pin%4) * 2;
       data=max7300_read(device,addy);
       if (!tris)
       {
         bit_set(data,mod);
         bit_clear(data,mod+1);
       }
       else {
           bit_set(data,mod+1);
           if (pullup) {
              bit_set(data,mod);
           }
           else {
              bit_clear(data,mod);
           }
       }
       max7300_write(device,addy,data);
   }
}
*/
/*
void output_high_ext(int device, int pin) {
   max7300_write(device, pin + 0x20, 1);
}
*/
/*
void output_low_ext(int device, int pin) {
   max7300_write(device, pin + 0x20, 0);
}
*/
/*
void output_pin_ext(int device, int pin, int1 level) {
   max7300_write(device, pin + 0x20, level);
}
*/

/*
int8 max7300_read(int device, int address) {
   BYTE data;

   i2c_start();
   i2c_write(device); //endereço do escravo
   i2c_write(address);  //endereço de memoria
   i2c_start();
   i2c_write(device | 1);
   data=i2c_read(0);         //Colocar i2c_read(1), 1 significa com ack
   i2c_stop();
   return(data);
}
*/

int8 max7312_read(int device, int commandByte) {
   BYTE data;

   i2c_start();
   i2c_write(device);       //endereço do escravo
   i2c_write(commandByte);  //commando de entrada
   i2c_start();
   i2c_write(commandByte | 1);//escreve endereço com read=1
   data=i2c_read(0);         //sem ack pq vai parar a seguir
   i2c_stop();
   return(data);
}

void max7312_write(int device, int address, int data) {
   i2c_start();
   i2c_write(device);
   i2c_write(address);
   i2c_write(data);
   i2c_stop();
}
