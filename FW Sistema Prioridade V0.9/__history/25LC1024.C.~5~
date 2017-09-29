///////////////////////////////////////////////////////////////////////////
////    //Libraria alterada por Victor Andrade (SPI 2)

/// Library for a MicroChip 93C56 configured for a x8 org           ////
////   Uses hardware SSP unit.                                         ////
////                                                                   ////
////   init_ext_eeprom();    Call before the other functions are used  ////
////                                                                   ////
////   write_ext_eeprom(a, d);  Write the byte d to the address a      ////
////                                                                   ////
////   d = read_ext_eeprom(a);   Read the byte d from the address a    ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2003 Custom Computer Services           ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////


#define EEPROM_SELECT PIN_D7       //Chip Select SPI2
#define EEPROM_DI     PIN_D5
#define EEPROM_DO     PIN_D4
#define EEPROM_CLK    PIN_D6


#define EEPROM_ADDRESS unsigned int32      //Atenção esta memória têm endereço até 24Bits       
#define EEPROM_SIZE    131072              //Espaço da memória


//Verificar se a eeprom está pronta para escrita ou leitura
int1 ext_eeprom_ready(void) 
{ 
 int8 data;

 output_low(EEPROM_SELECT); // CS = 0 
 spi_write2(0x05);             //Lê registo do estado da memória
 data = spi_read2(0);
// fprintf(PORT2,"Data do eeprom ready %X\n\r",data);
 output_high(EEPROM_SELECT); // CS = 1
 delay_ms(2);                //acrescentei
 return(!bit_test(data, 0));    //
}
 

//Escreve dados 8 bits na eeprom SPI

 void write_ext_eeprom(EEPROM_ADDRESS address, BYTE data) 
 { 
 // fprintf(PORT2,"Inicio de Escrita\n\r");
  while(!ext_eeprom_ready());   //
 // fprintf(PORT2,"EEPROM PRONTA\n\r");
  output_low(EEPROM_SELECT);   // CS = 0 
  spi_write2(0x06);             //Habilita escrita em memória WREN
  output_high(EEPROM_SELECT); // CS = 1 
  delay_ms(2);                //Acrescentei 
  output_low(EEPROM_SELECT); // CS = 0
  spi_write2(0x02); //Modo de Escrita
  spi_write2(address >> 16); // Envia os 8bits iniciais mais significativo (dos 24bits)
  spi_write2(address >> 8); // Envia o endereço 8bits intermedio
  spi_write2(address);          // Envia o menos significativo
  spi_write2(data);             //Escreve em memória
  output_high(EEPROM_SELECT);   // CS = 1 
 }



//LEITUTA DA EEPROM

 BYTE read_ext_eeprom(EEPROM_ADDRESS address) 
 { 
 int8 data; 
 //fprintf(PORT2,"Inicio de Leitura\n\r");
 while(!ext_eeprom_ready()); 
 //fprintf(PORT2,"EEPROM PRONTA\n\r");
 output_low(EEPROM_SELECT); // CS =0 
 spi_write2(0x03);           //Modo Leitura
 spi_write2(address >> 16); 
 spi_write2(address >> 8); 
 spi_write2(address);  

 data = spi_read2(0); //Ler dados de 8bits na memória
 output_high(EEPROM_SELECT); // CS = 1 

 return(data); 
 }



