/*
+++++++++++++++++ Programa Sistema de Prioridade  ++++++++++++++++++++++++++++

//////// Program memory: 65532x16  Data RAM: 4096  Stack: 31
//////// I/O: 70   Analog Pins: 16
//////// C Scratch area: 00   ID Location: 0000
//////// Fuses: HS,H4_SW,EC_IO,E4_SW_IO,DEBUG,NODEBUG,XINST,NOXINST,STVREN
//////// Fuses: NOSTVREN,WDT,NOWDT,PROTECT,NOPROTECT,WDT1,WDT2,WDT4,WDT8
//////// Fuses: WDT16,WDT32,WDT64,WDT128,WDT256,WDT512,WDT1024,WDT2048
//////// Fuses: WDT4096,WDT8192,WDT16384,WDT32768,FCMEN,NOFCMEN,IESO,NOIESO
//////// Fuses: CCP2C1,CCP2E7,PRIMARY,INTRC,ECCPE,ECCPH,ETHLED,NOETHLED,WAIT
//////// Fuses: NOWAIT,BW16,BW8,MCU,EMCU12,EMCU16,EMCU20,EASHFT,NOEASHFT
//////// 
// Watch Dog Timer Functions: SETUP_WDT() or SETUP_COUNTERS() (see above)
//                            RESTART_WDT()
SETUP_WDT(WDT_ON)
RESTART_WDT()
//#define WDT_ON        0x100
//#define WDT_OFF       0

*/

#include <18F97J60.h>
#fuses HS,PROTECT,NOETHLED,WDT8192
#use delay(clock=25000000)

#use fast_io(A)
#use fast_io(B)
#use fast_io(D)
#use fast_io(E)                      //Sa�das Rel� 2-9
#use fast_io(F)                      //Entradas anal�gicas e outputs especiais
#use fast_io(H)                      //Entradas DipSwitch
#use fast_io(J)                    //Display LCD+ botoes
 
#use standard_io(C)        //Mosfet,
#use standard_io(G)        //Mosfet, 

#use RS232(UART2, baud=19200, xmit=PIN_G1, rcv=PIN_G2, errors, stream=PORT2,RESTART_WDT)                    

  //RS232
#use I2C(master, sda=PIN_C4, scl=PIN_C3)  //C4 bidi, C3 out


#define LCD_DB4   PIN_J4         //  PIN_J4
#define LCD_DB5   PIN_J5         //  PIN_J5
#define LCD_DB6   PIN_J6         //  PIN_J6
#define LCD_DB7   PIN_J7         //  PIN_J7

#define LCD_RS    PIN_G7         //  PIN_G7
#define LCD_RW    PIN_G6         //  PIN_C0
#define LCD_E     PIN_G5         //  PIN_A5

#define ButtonM   PIN_J3         //  PIN_J3
#define ButtonInc PIN_J0         //  PIN_J2
#define ButtonDec PIN_J1         //  PIN_J0


#define IN1   PIN_B1        //Entrada Digital 0 - 
#define IN2   PIN_B2        //Entrada Digital 1 - 
#define IN3   PIN_D1        //Entrada Digital 2 - 
#define IN4   PIN_D2        //Entrada Digital 3 - 
#define IN5   PIN_D3        //Entrada Digital 4 - 
#define IN6   PIN_B3        //Entrada Digital 5 - 
#define IN7   PIN_B4        //Entrada Digital 6 - 
#define IN8   PIN_B5        //Entrada Digital 7 - 

#define IN9   PIN_A2        //Entrada Digital(Analog) 0 - 
#define IN10  PIN_A5        //Entrada Digital(Analog) 1 - 
#define IN11  PIN_F0        //Entrada Digital(Analog) 2 -   
#define IN12  PIN_F5        //Entrada Digital(Analog) 3 - 
#define IN13  PIN_F4        //Entrada Digital(Analog) 4 - 
#define IN14  PIN_F3        //Entrada Digital(Analog) 5 - 
#define IN15  PIN_F2        //Entrada Digital(Analog) 6 - 
#define IN16  PIN_F1        //Entrada Digital(Analog) 7 - 



/*
#define OUT_SS1   PIN_E2        //Sa�da Rel� 2 - Sem�foro Sa�da Piso -1  (0->RED, 1->GREEN)
#define OUT_SS2   PIN_E3        //Sa�da Rel� 3 - Sem�foro Sa�da Piso -2  (0->RED, 1->GREEN) 
#define OUT_SS3   PIN_E4        //Sa�da Rel� 4 - Sem�foro Sa�da Piso -3  (0->RED, 1->GREEN) 
#define OUT_SE    PIN_E5        //Sa�da Rel� 5 - Sem�foro Entrada Parque (0->RED, 1->GREEN) 
#define OUT_SD    PIN_E6        //Sa�da Rel� 6 - Sem�foro Entrada Piso -3(0->RED, 1->GREEN) 
#define OUT_ME    PIN_E7        //Sa�da Rel� 7 - Sinal Desactiva��o M�quina Entrada(1->OFF) 
#define OUT_MS    PIN_B0        //Sa�da Rel� 8 - Sinal Desactiva��o M�quina Entrada(1->OFF) 
*/





#include <25LC1024.c>
#include <MK41T56.c>
#include <stdlib.h>
#include <flex_lcd.c>


//   ----------------------------------------------------
char description[35]="SW uPLC Continente Bocage - LX\r\n";
char version[20]="Versao V0.8\r\n";
char datasw[15]="25-05-17\r\n";

//   ----------------------------------------------------


int16 TimerI1on=0,TimerI1off=0;    //Timer 5ms
int16 TimerI2on=0,TimerI2off=0;    //Timer 5ms
int16 TimerI3on=0,TimerI3off=0;    //Timer 5ms
int16 TimerI4on=0,TimerI4off=0;    //Timer 5ms
int16 TimerI5on=0,TimerI5off=0;    //Timer 5ms
int16 TimerI6on=0,TimerI6off=0;    //Timer 5ms
int16 TimerI7on=0,TimerI7off=0;    //Timer 5ms
int16 TimerI8on=0,TimerI8off=0;    //Timer 5ms

int16 TimerI9on=0,TimerI9off=0;      //Timer 5ms
int16 TimerI10on=0,TimerI10off=0;    //Timer 5ms
int16 TimerI11on=0,TimerI11off=0;    //Timer 5ms
int16 TimerI12on=0,TimerI12off=0;    //Timer 5ms
int16 TimerI13on=0,TimerI13off=0;    //Timer 5ms
int16 TimerI14on=0,TimerI14off=0;    //Timer 5ms
int16 TimerI15on=0,TimerI15off=0;    //Timer 5ms
int16 TimerI16on=0,TimerI16off=0;    //Timer 5ms




int8 auxI1on=0,auxI1off=0;
int8 auxI2on=0,auxI2off=0;
int8 auxI3on=0,auxI3off=0;
int8 auxI4on=0,auxI4off=0;
int8 auxI5on=0,auxI5off=0;
int8 auxI6on=0,auxI6off=0;
int8 auxI7on=0,auxI7off=0;
int8 auxI8on=0,auxI8off=0;

int8 auxI9on=0,auxI9off=0;
int8 auxI10on=0,auxI10off=0;
int8 auxI11on=0,auxI11off=0;
int8 auxI12on=0,auxI12off=0;
int8 auxI13on=0,auxI13off=0;
int8 auxI14on=0,auxI14off=0;
int8 auxI15on=0,auxI15off=0;
int8 auxI16on=0,auxI16off=0;


int1 ING_I1=0,ING_I2=0,ING_I3=0,ING_I4=0,ING_I5=0,ING_I6=0,ING_I7=0,ING_I8=0;
int1 MEM_I1=0,MEM_I2=0,MEM_I3=0,MEM_I4=0,MEM_I5=0,MEM_I6=0,MEM_I7=0,MEM_I8=0;
int1 ING_I9=0,ING_I10=0,ING_I11=0,ING_I12=0,ING_I13=0,ING_I14=0,ING_I15=0,ING_I16=0;
int1 MEM_I9=0,MEM_I10=0,MEM_I11=0,MEM_I12=0,MEM_I13=0,MEM_I14=0,MEM_I15=0,MEM_I16=0;
int8 data_receive=0;
Unsigned int8 Data_Buffer[7];    //era 6
int8 current_data=0;
int1 Carriage_Return=1;
int1 BufferOK=0;
int1 LinhaComando=0;           //0-> OFF, modo r�dio activo, 1-> ON com linha de comandos



int8 count_TimerA=0;
int8 count_TimerB=0; // Contador p/Timer dos Pulsos
int8 count_TimerC=0;
int8 count_TimerD=0;
int8 count_TimerE=0;

int8 TIMER_A=0;
int8 TIMER_B=0;             // Timer p/Pulsos
int8 TIMER_C=0;             // Timer p/Pulsos
int8 TIMER_D=0;             // Timer p/Pulsos
int8 TIMER_E=0;             // Timer p/Pulsos


int8 TIMER_G12=0;          //timer limpeza G1 -> G2
int8 TIMER_G13=0;          //timer limpeza G1 -> G3

int1 SIGNAL_BLINK=0;



Unsigned int8 Tempos[25];

int8 EstadoG1=0;  //0: Verde, 1:Vermelho
int8 EstadoG2=0;  //0: Verde, 1:Vermelho
int8 EstadoG3=0;  //0: Verde, 1:Vermelho

int8 step=0;

int1 debug=0,debugInputs=0;
int1 flagEstadoME=0,flagEstadoMS=0;  //1-> M�quina Ativada
int1 flag_maqAtiva=0,flag_maqSaidaAtiva=0;
int1 flagBlockI13=0;

#INT_RDA2
void trata_INT_RDA2()
{
  data_receive=fgetc(PORT2);
  if(data_receive=='#' && Carriage_Return)  //� o '#'  ---Associar um timeout
    {
     //TimeOut=0;
     //count_TimerA=0;
     current_data=0;
     Data_Buffer[current_data]=data_receive;
     current_data++;
     Carriage_Return=0;
     BufferOK=0; 
    }
  else  
    {
     if(!Carriage_Return)
       {
        if(current_data==6 || data_receive==13)           //  || Timeout    
          {Data_Buffer[current_data]=data_receive;
           Carriage_Return=1;
           current_data=0;
           bufferOK=1;
           if(data_receive!=13)     //erro
              bufferOK=0;
          }
        else
          {Data_Buffer[current_data]=data_receive;
           current_data++;
          }
       }
    }
}





#INT_RTCC
void trata_t0()             //Entra aqui a cada 5ms
{
count_TimerA++;
count_TimerB++;
count_TimerC++;
count_TimerD++;
count_TimerE++;


TimerI1on++;    //Timer 5ms
TimerI1off++;   //Timer 5ms
TimerI2on++;    //Timer 5ms
TimerI2off++;   //Timer 5ms
TimerI3on++;    //Timer 5ms
TimerI3off++;   //Timer 5ms
TimerI4on++;    //Timer 5ms
TimerI4off++;   //Timer 5ms
TimerI5on++;    //Timer 5ms
TimerI5off++;   //Timer 5ms
TimerI6on++;    //Timer 5ms
TimerI6off++;   //Timer 5ms
TimerI7on++;    //Timer 5ms
TimerI7off++;   //Timer 5ms
TimerI8on++;    //Timer 5ms
TimerI8off++;   //Timer 5ms


TimerI9on++;    //Timer 5ms
TimerI9off++;   //Timer 5ms
TimerI10on++;    //Timer 5ms
TimerI10off++;   //Timer 5ms
TimerI11on++;    //Timer 5ms
TimerI11off++;   //Timer 5ms
TimerI12on++;    //Timer 5ms
TimerI12off++;   //Timer 5ms
TimerI13on++;    //Timer 5ms
TimerI13off++;   //Timer 5ms
TimerI14on++;    //Timer 5ms
TimerI14off++;   //Timer 5ms
TimerI15on++;    //Timer 5ms
TimerI15off++;   //Timer 5ms
TimerI16on++;    //Timer 5ms
TimerI16off++;   //Timer 5ms




if(count_timerA<=100)
   SIGNAL_BLINK=1;
else
  {
   SIGNAL_BLINK=0;
   if(count_timerA>=200)   //1 segundo
     {
      count_timerA=0;
      if(TIMER_A<255)
         TIMER_A++;
     if(TIMER_G12>0)
        TIMER_G12--;
     if(TIMER_G13>0)
        TIMER_G13--;   
     }
  }  
     
if(count_timerB>=200)   //1 segundo
     {
      count_timerB=0;
      if(TIMER_B<255)
         TIMER_B++;
     }    
if(count_timerC>=200)   //1 segundo
     {
      count_timerC=0;
      if(TIMER_C<255)
         TIMER_C++;
     }  
if(count_timerD>=200)   //1 segundo
     {
      count_timerD=0;
      if(TIMER_D<255)
         TIMER_D++;
     }
if(count_timerE>=200)   //1 segundo
     {
      count_timerE=0;
      if(TIMER_E<255)
         TIMER_E++;
     }



set_timer0(34286);

}



void delay_seg(int8 time)
{
 int i;
 RESTART_WDT();
 for(i=0;i<time;i++)
    delay_ms(1000);

}


void ImprimeMSGRS232(int1 msg) //0:Erro, 1:OK
{
if(!msg)
  {
   fputc('#',PORT2); //STX
   fputc('E',PORT2); //ERRO
   fputc('R',PORT2); //
   fputc(13,PORT2);
  }
else
  {
   fputc('#',PORT2); //STX
   fputc('O',PORT2); 
   fputc('K',PORT2);
   fputc(13,PORT2);
  }
}


void trata_msgAtoI(unsigned int32 i_ee,int8 i_temp,int16 max)   //m�x 199
{
int16 aux=0;
int16 MSB=0,LSB=0;

if((Data_Buffer[2]>='0' && Data_Buffer[2]<='2') && (Data_Buffer[3]>='0' && Data_Buffer[3]<='9') && 

(Data_Buffer[4]>='0' && Data_Buffer[4]<='9') && (Data_Buffer[5]==13))   //s�o 3 digitos
  {
   MSB=Data_Buffer[2]-48;
   MSB=MSB*100;
   LSB=Data_Buffer[3]-48;
   LSB=LSB*10;
   MSB=MSB+LSB;
   LSB=Data_Buffer[4]-48;
   aux=MSB+LSB;
   if(aux<=max)
     {Tempos[i_temp]=(int8) aux;
      write_ext_eeprom(i_ee, Tempos[i_temp]);
      ImprimeMSGRS232(1);          //OK 
     }
   else
      ImprimeMSGRS232(0);          //ERRO
  }
else
  {
   if((Data_Buffer[2]>='0' && Data_Buffer[2]<='9') && (Data_Buffer[3]>='0' && Data_Buffer[3]<='9') && 

(Data_Buffer[4]==13))   //s�o dois digitos
     {
      MSB=Data_Buffer[2]-48;
      MSB=MSB*10;
      LSB=Data_Buffer[3]-48;
      aux=MSB+LSB;
      if(aux<=max)
        {Tempos[i_temp]=(int8) aux;
         write_ext_eeprom(i_ee, Tempos[i_temp]);
         ImprimeMSGRS232(1);          //OK 
        }
      else
        ImprimeMSGRS232(0);          //ERRO
     }
   else
     {
      if((Data_Buffer[2]>='0' && Data_Buffer[2]<='9') && (Data_Buffer[3]==13))   //� 1 d�gito
        {
         LSB=Data_Buffer[2]-48;
         aux=LSB;
         if(aux<=LSB)
           {Tempos[i_temp]=(int8) aux;
            write_ext_eeprom(i_ee, Tempos[i_temp]);
            ImprimeMSGRS232(1);          //OK                   
           }
         else
           ImprimeMSGRS232(0);
        }
      else
        ImprimeMSGRS232(0);
      }
   }
}


void trata_buffer(){
unsigned int8 data=0;
BYTE year, mth, date, dow, hr, min, sec;



delay_ms(10);


switch(Data_Buffer[1]){
      case '#':if(Data_Buffer[2]=='#' && Data_Buffer[3]==13)
                 {
                  if(!LinhaComando)
                    {LinhaComando=1;
                     fprintf(PORT2,"Modo Linha de Comandos Activado\n\r");
                    }
                  else
                    {
                     LinhaComando=0;
                     fprintf(PORT2,"Modo Linha de Comandos Desactivado\n\r");
                    }            
                 }
               break;
      case 'A':if(LinhaComando)
                  trata_msgAtoI(0,0,150);  //Tempo A [seg]
               break;
      case 'B':if(LinhaComando)
                  trata_msgAtoI(1,1,250);  //Tempo B [seg]
               break;
      case 'C':if(LinhaComando)
                  trata_msgAtoI(2,2,25);   //Tempo C [seg]
               break;
      case 'D':if(LinhaComando)
                  trata_msgAtoI(3,3,150);  //Tempo D [seg]
               break;
      case 'E':if(LinhaComando)
                  trata_msgAtoI(4,4,250);  //Tempo E [seg]
               break;
      case 'F':if(LinhaComando)
                  trata_msgAtoI(5,5,25);   //Tempo F [seg]
               break;
      case 'G':if(LinhaComando)
                  trata_msgAtoI(6,6,150);  //Tempo G [seg]
               break;         
      case 'H':if(LinhaComando)
                  trata_msgAtoI(7,7,250);  //Tempo H [seg]
               break;            
      case 'I':if(LinhaComando)
                  trata_msgAtoI(8,8,25);   //Tempo I [seg]
               break;           
      case 'J':if(LinhaComando)
                  trata_msgAtoI(9,9,120);   //Tempo J [seg]
               break;        
      case 'K':if(LinhaComando)
                  trata_msgAtoI(10,10,120);   //Tempo K [seg]
               break;        
      case 'L':if(LinhaComando)
                  trata_msgAtoI(11,11,120);   //Tempo L [seg]
               break;    
      case 'M':if(LinhaComando)
                  trata_msgAtoI(12,12,120);   //Tempo M [seg]
               break;         
      case 'N':if(LinhaComando)
                  trata_msgAtoI(13,13,120);   //Tempo N [seg]
               break;        
      case 'O':if(LinhaComando)
                  trata_msgAtoI(14,14,120);   //Tempo O [seg]
               break;        
      case 'P':if(LinhaComando)
                  trata_msgAtoI(15,15,255);   //Tempo P [seg]
               break;            
      case 'Q':
               break;                       
      case 'R':if(LinhaComando)
                  reset_cpu(); 
               break;     
      case 'S':if(LinhaComando)
                 if(Data_Buffer[2]=='W' && Data_Buffer[3]==13)             //Mostra dados contidos na EEPROM
                    {                                                                                         
                     data = read_ext_eeprom(0);
                     fprintf(PORT2,"Tempo Verde m�nimo G1[seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(1);
                     fprintf(PORT2,"Tempo Verde m�ximo G1[seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(2);
                     fprintf(PORT2,"Tempo Incremento G1[seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(3);
                     fprintf(PORT2,"Tempo Verde m�nimo G2[seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(4);
                     fprintf(PORT2,"Tempo Verde m�ximo G2 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(5);
                     fprintf(PORT2,"Tempo Incremento G2 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(6);
                     fprintf(PORT2,"Tempo Verde m�nimo G3 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(7);
                     fprintf(PORT2,"Tempo Verde m�ximo G3 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(8);
                     fprintf(PORT2,"Tempo Incremento G3 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(9);
                     fprintf(PORT2,"Tempo Percurso G1 -> G2 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(10);
                     fprintf(PORT2,"Tempo Percurso G2 -> G1 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(11);
                     fprintf(PORT2,"Tempo Percurso G1 -> G3 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(12);
                     fprintf(PORT2,"Tempo Percurso G3 -> G1 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(13);
                     fprintf(PORT2,"Tempo Percurso G2 -> G3 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(14);
                     fprintf(PORT2,"Tempo Percurso G3 -> G2 [seg]=%u\n\r",data);
                     delay_ms(2);
                     data = read_ext_eeprom(15);
                     fprintf(PORT2,"Timeout Desbloqueio=%u\n\r",data);
                     delay_ms(2);
                     if(!debug)
                        fprintf(PORT2,"Debug=Desabilitado\n\r");
                     else
                        fprintf(PORT2,"Debug=Habilitado\n\r"); 
                    if(!debugInputs)
                        fprintf(PORT2,"Debug Inputs=Desabilitado\n\r");
                     else
                        fprintf(PORT2,"Debug Inputs=Habilitado\n\r"); 
                    }
               break;
      case 'V':if(LinhaComando)
                  if(Data_Buffer[2]=='S' && Data_Buffer[3]==13) 
                    {
                     fprintf(PORT2,"%s",description);
                     fprintf(PORT2,"%s",version);
                     fprintf(PORT2,"%s",datasw);
                    }
               break;
      case 'a':if(LinhaComando)
                 {if(Data_Buffer[2]=='0' && Data_Buffer[3]==13)
                     debug=0;
                  else
                    if(Data_Buffer[2]=='1' && Data_Buffer[3]==13)
                      debug=1;
                 }
               break; 
       case 'b':if(LinhaComando)
                  {if(Data_Buffer[2]=='0' && Data_Buffer[3]==13)
                      debugInputs=0;
                   else
                     if(Data_Buffer[2]=='1' && Data_Buffer[3]==13)
                       debugInputs=1;
                  }
                break;                     
       case 'c': // set data
               //mk41t56_set_date_time(BYTE year, BYTE mth, BYTE date, BYTE dow, BYTE hr, BYTE min, BYTE sec);
                                                                         //sec: 0-59
                                                                         //  min: 0-59
                                                                         //  hour:0-23
                                                                         //  dayOfWeek:01-07
                                                                         //  date:01-31
                                                                         //  moth:01-12
                                                                         // year: 0-99
               if(LinhaComando)
                  if(Data_Buffer[2]==13)
                    mk41t56_set_date_time(17,4,25,2,18,30,00);
               break;
      case 'd'://Read data
               //mk41t56_get_date(BYTE &year, BYTE &mth ,BYTE &date, BYTE &dow);
               if(LinhaComando)
                  if(Data_Buffer[2]==13)
                     {
                      mk41t56_get_date(year, mth ,date, dow);
                      fprintf(PORT2,"YEAR=%u\n\r",year);
                      fprintf(PORT2,"MONTH=%u\n\r",mth);
                      fprintf(PORT2,"Date=%u\n\r",date);
                      fprintf(PORT2,"DayOfWeek=%u\n\r",dow);
                     }
               break;         
      case 'e'://Read time
               //mk41t56_get_time(BYTE &hr, BYTE &min, BYTE &sec)
               if(LinhaComando)
                  if(Data_Buffer[2]==13)
                     {
                      mk41t56_get_time(hr, min, sec);
                      fprintf(PORT2,"HOUR=%u\n\r",hr);
                      fprintf(PORT2,"MINUTE=%u\n\r",min);
                      fprintf(PORT2,"SECOND=%u\n\r",sec);
                     }
               break;       

           //default:ImprimeMSGRS232(0);
           //        break; 
        }
}





/*

Outputs
Porto A ->RA1 -> LED Ambar (Ethernet)
          RA0 -> LED Verde (Ethernet)

Porto B -> RB0 -> Rel� 8

Porto C -> RC6 -> TX UART1 RS485
           RC5 -> Rel� 9
           RC3 -> SCL I2C
           RC1 -> LED Verde CPU     (0V ON)
           RC0 -> LED Vermelho CPU  (0V ON)

Porto D -> RD7 -> /CS (Chip Select) SPI
           RD6 -> SCK
           RD4 -> SDO SPI
           RD0 -> Ilumina��o Display

Porto E -> RE7 -> Rel� 7  //No manual estava mal
           RE6 -> Rel� 6
           RE5 -> Rel� 5  // Definir como OUT2
           RE4 -> Rel� 4  // Definir OUT1
           RE3 -> Rel� 3
           RE2 -> Rel� 2
           RE1 -> Rel� 0
           RE0 -> Rel� 1

Porto F -> RF7 -> SEND UART 1 RS485
           RF6 -> RTS UART 2

Porto G -> RG4 -> Mosfet 0
           RG3 -> Mosfet 1
           RC2 -> Mosfet 2
           RG1 -> TX UART2 RS232
           RG0 -> Mosfet 3


        
      

Inputs

Porto A -> RA5 -> Anal�gica A1
           RA4 -> CTS UART2 RS232
           RA3 -> Input digital, anal�gica ou com 3.3V/Vref
           RA2 -> Anal�gica A0
           

Porto B -> RB5 -> Optoacoplador 7 (0V signal ON)
           RB4 -> Optoacoplador 6 (0V signal ON)
           RB3 -> Optoacoplador 5 (0V signal ON)
           RB2 -> Optoacoplador 1 (0V signal ON)
           RB1 -> Optoacoplador 0 (0V signal ON) 

Porto C -> RC7 -> RX UART1 RS485

Porto D -> RD5 -> SDI SPI
           RD3 -> Optoacoplador 4 (0V signal ON)
           RD2 -> Optoacoplador 3 (0V signal ON)
           RD1 -> Optoacoplador 2 (0V signal ON)

Porto F -> RF5 -> Anal�gica A3
           RF4 -> Anal�gica A4
           RF3 -> Anal�gica A5
           RF2 -> Anal�gica A6
           RF1 -> Anal�gica A7
           RF0 -> Anal�gica A2

Porto H -> RH7 -> SW1 Inputs Dip Switch
           RH6 -> SW2 Inputs Dip Switch
           RH5 -> SW3 Inputs Dip Switch
           RH4 -> SW4 Inputs Dip Switch
           RH3 -> SW5 Inputs Dip Switch
           RH2 -> SW6 Inputs Dip Switch
           RH1 -> SW7 Inputs Dip Switch
           RH0 -> SW8 Inputs Dip Switch

Porto G -> RG2 -> RX UART2 RS232


Bidireccionais (Display, Mem+orias, etc)
Porto B -> RB7 -> PGC
           RB6 -> PGC

Porto C -> RC4 -> SDA I2C

Porto G -> RG7 -> Display RS
           RG6 -> Display R/W
           RG5 -> Display E


Porto J -> RJ7 -> Display DB7
           RJ6 -> Display DB6
           RJ5 -> Display DB5
           RJ4 -> Display DB4
           RJ3 -> Display DB3
           RJ2 -> Display DB2
           RJ1 -> Display DB1
           RJ0 -> Display DB0
           

*/



void LER_ENTRADAS()
{

//Leitura Espiras Simples
 RESTART_WDT();

 //Entradas digitais
switch(auxI1on){
      case 0:if(!input(IN1))
               {
                TimerI1on=0;
                auxI1on=1;
               }
             break;  
      case 1:if(TimerI1on<10)          //50ms
               {if(input(IN1))
                  {auxI1on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI1on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I1)
                  fprintf(PORT2,"Input 1 -> ON\n\r");
                ING_I1=1;         //Espira de Entrada Ocupada
                MEM_I1=1;
                auxI1on=0;         
               }
             break;
         }
 
switch(auxI1off){
      case 0:if(input(IN1))
               {
                TimerI1off=0;
                auxI1off=1;
               }
             break;  
      case 1:if(TimerI1off<10)          //50ms
               {if(!input(IN1))
                  {auxI1off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI1off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I1)
                  fprintf(PORT2,"Input 1 -> OFF\n\r");
                ING_I1=0;         //Espira de Entrada Ocupada
                auxI1off=0;         
               }
             break;
         }

switch(auxI2on){
      case 0:if(!input(IN2))
               {
                TimerI2on=0;
                auxI2on=1;
               }
             break;  
      case 1:if(TimerI2on<10)          //50ms
               {if(input(IN2))
                  {auxI2on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI2on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I2)
                  fprintf(PORT2,"Input 2-> ON\n\r");
                ING_I2=1;         //Espira de Entrada Ocupada
                MEM_I2=1;     
                auxI2on=0;         
               }
             break;
         }
 
switch(auxI2off){
      case 0:if(input(IN2))
               {
                TimerI2off=0;
                auxI2off=1;
               }
             break;  
      case 1:if(TimerI2off<10)          //50ms
               {if(!input(IN2))
                  {auxI2off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI2off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I2)
                  fprintf(PORT2,"Input 2-> OFF\n\r");
                ING_I2=0;         //Espira de Entrada Ocupada
                auxI2off=0;         
               }
             break;
         }


switch(auxI3on){
      case 0:if(!input(IN3))
               {
                TimerI3on=0;
                auxI3on=1;
               }
             break;  
      case 1:if(TimerI3on<10)          //50ms
               {if(input(IN3))
                  {auxI3on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI3on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I3)
                  fprintf(PORT2,"Input 3-> ON\n\r");
                ING_I3=1;         //Espira de Entrada Ocupada
                MEM_I3=1;
                auxI3on=0;         
               }
             break;
         }
 
switch(auxI3off){
      case 0:if(input(IN3))
               {
                TimerI3off=0;
                auxI3off=1;
               }
             break;  
      case 1:if(TimerI3off<10)          //50ms
               {if(!input(IN3))
                  {auxI3off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI3off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I3)
                  fprintf(PORT2,"Input 3-> OFF\n\r");
                ING_I3=0;         //Espira de Entrada Ocupada              
                auxI3off=0;         
               }
             break;
         }


switch(auxI4on){
      case 0:if(!input(IN4))
               {
                TimerI4on=0;
                auxI4on=1;
               }
             break;  
      case 1:if(TimerI4on<10)          //50ms
               {if(input(IN4))
                  {auxI4on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI4on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I4)
                  fprintf(PORT2,"Input 4-> ON\n\r");
                ING_I4=1;         //Espira de Entrada Ocupada
                MEM_I4=1;   
                auxI4on=0;         
               }
             break;
         }
 
switch(auxI4off){
      case 0:if(input(IN4))
               {
                TimerI4off=0;
                auxI4off=1;
               }
             break;  
      case 1:if(TimerI4off<10)          //50ms
               {if(!input(IN4))
                  {auxI4off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI4off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I4)
                  fprintf(PORT2,"Input 4-> OFF\n\r");
                ING_I4=0;         //Espira de Entrada Ocupada
                auxI4off=0;
               }
             break;
         }


switch(auxI5on){
      case 0:if(!input(IN5))
               {
                TimerI5on=0;
                auxI5on=1;
               }
             break;  
      case 1:if(TimerI5on<10)          //50ms
               {if(input(IN5))
                  {auxI5on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI5on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I5)
                  fprintf(PORT2,"Input 5-> ON\n\r");
                ING_I5=1;         //Espira de Entrada Ocupada
                MEM_I5=1;
                auxI5on=0;
               }
             break;
         }
 
switch(auxI5off){
      case 0:if(input(IN5))
               {
                TimerI5off=0;
                auxI5off=1;
               }
             break;  
      case 1:if(TimerI5off<10)          //50ms
               {if(!input(IN5))
                  {auxI5off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI5off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I5)
                  fprintf(PORT2,"Input 5-> OFF\n\r");
                ING_I5=0;         //Espira de Entrada Ocupada
                auxI5off=0;         
                
               }
             break;
         }


switch(auxI6on){
      case 0:if(!input(IN6))
               {
                TimerI6on=0;
                auxI6on=1;
               }
             break;  
      case 1:if(TimerI6on<10)          //50ms
               {if(input(IN6))
                  {auxI6on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI6on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I6)
                  fprintf(PORT2,"Input 6-> ON\n\r");
                ING_I6=1;         //Espira de Entrada Ocupada
                MEM_I6=1;
                auxI6on=0; 
               }
             break;
         }
 
switch(auxI6off){
      case 0:if(input(IN6))
               {
                TimerI6off=0;
                auxI6off=1;
               }
             break;  
      case 1:if(TimerI6off<10)          //50ms
               {if(!input(IN6))
                  {auxI6off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI6off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I6)
                  fprintf(PORT2,"Input 6-> OFF\n\r");
                ING_I6=0;         //Espira de Entrada Ocupada
                auxI6off=0;  
               }
             break;
         }


switch(auxI7on){
      case 0:if(!input(IN7))
               {
                TimerI7on=0;
                auxI7on=1;
               }
             break;  
      case 1:if(TimerI7on<10)          //50ms
               {if(input(IN7))
                  {auxI7on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI7on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I7)
                  fprintf(PORT2,"Input 7-> ON\n\r");
                ING_I7=1;         //Espira de Entrada Ocupada
                MEM_I7=1;
                auxI7on=0;
               }
             break;
         }
 
switch(auxI7off){
      case 0:if(input(IN7))
               {
                TimerI7off=0;
                auxI7off=1;
               }
             break;  
      case 1:if(TimerI7off<10)          //50ms
               {if(!input(IN7))
                  {auxI7off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI7off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I7)
                  fprintf(PORT2,"Input 7-> OFF\n\r");
                ING_I7=0;         //Espira de Entrada Ocupada
                auxI7off=0;    
               }
             break;
         }


switch(auxI8on){
      case 0:if(!input(IN8))
               {
                TimerI8on=0;
                auxI8on=1;
               }
             break;  
      case 1:if(TimerI8on<10)          //50ms
               {if(input(IN8))
                  {auxI8on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI8on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I8)
                  fprintf(PORT2,"Input 8-> ON\n\r");
                ING_I8=1;         //Espira de Entrada Ocupada
                MEM_I8=1;
                auxI8on=0;         
               }
             break;
         }
 
switch(auxI8off){
      case 0:if(input(IN8))
               {
                TimerI8off=0;
                auxI8off=1;
               }
             break;  
      case 1:if(TimerI8off<10)          //50ms
               {if(!input(IN8))
                  {auxI8off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI8off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I8)
                  fprintf(PORT2,"Input 8-> OFF\n\r");
                ING_I8=0;         //Espira de Entrada Ocupada
                auxI8off=0;         
               }
             break;
         }


switch(auxI9on){
      case 0:if(input(IN9))
               {
                TimerI9on=0;
                auxI9on=1;
               }
             break;  
      case 1:if(TimerI9on<10)          //50ms
               {if(!input(IN9))
                  {auxI9on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI9on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I9)
                  fprintf(PORT2,"Input 9-> ON\n\r");
                ING_I9=1;         //Espira de Entrada Ocupada
                MEM_I9=1;
                auxI9on=0;         
               }
             break;
         }
 
switch(auxI9off){
      case 0:if(!input(IN9))
               {
                TimerI9off=0;
                auxI9off=1;
               }
             break;  
      case 1:if(TimerI9off<10)          //50ms
               {if(input(IN9))
                  {auxI9off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI9off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I9)
                  fprintf(PORT2,"Input 9-> OFF\n\r");
                ING_I9=0;         //Espira de Entrada Ocupada
                auxI9off=0;         
               }
             break;
         }
 switch(auxI10on){
      case 0:if(input(IN10))
               {
                TimerI10on=0;
                auxI10on=1;
               }
             break;  
      case 1:if(TimerI10on<10)          //50ms
               {if(!input(IN10))
                  {auxI10on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI10on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I10)
                  fprintf(PORT2,"Input 10-> ON\n\r");
                ING_I10=1;         //Espira de Entrada Ocupada
                MEM_I10=1;
                auxI10on=0;         
               }
             break;
         }        
switch(auxI10off){
      case 0:if(!input(IN10))
               {
                TimerI10off=0;
                auxI10off=1;
               }
             break;  
      case 1:if(TimerI10off<10)          //50ms
               {if(input(IN10))
                  {auxI10off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI10off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I10)
                  fprintf(PORT2,"Input 10-> OFF\n\r");
                ING_I10=0;         //Espira de Entrada Ocupada
                auxI10off=0;         
               }
             break;
         }
   
 switch(auxI11on){
      case 0:if(input(IN11))
               {
                TimerI11on=0;
                auxI11on=1;
               }
             break;  
      case 1:if(TimerI11on<10)          //50ms
               {if(!input(IN11))
                  {auxI11on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI11on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I11)
                  fprintf(PORT2,"Input 11-> ON\n\r");  
                ING_I11=1;         //Espira de Entrada Ocupada
                MEM_I11=1;
                auxI11on=0;         
               }
             break;
         }           
switch(auxI11off){
      case 0:if(!input(IN11))
               {
                TimerI11off=0;
                auxI11off=1;
               }
             break;  
      case 1:if(TimerI11off<10)          //50ms
               {if(input(IN11))
                  {auxI11off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI11off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I11)
                  fprintf(PORT2,"Input 11-> OFF\n\r");  
                ING_I11=0;         //Espira de Entrada Ocupada
                auxI11off=0;         
               }
             break;
         }
switch(auxI12on){
      case 0:if(input(IN12))
               {
                TimerI12on=0;
                auxI12on=1;
               }
             break;  
      case 1:if(TimerI12on<10)          //50ms
               {if(!input(IN12))
                  {auxI12on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI12on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I12)
                  fprintf(PORT2,"Input 12-> ON\n\r");  
                ING_I12=1;         //Espira de Entrada Ocupada
                MEM_I12=1;
                auxI12on=0;         
               }
             break;
         }          
         
switch(auxI12off){
      case 0:if(!input(IN12))
               {
                TimerI12off=0;
                auxI12off=1;
               }
             break;  
      case 1:if(TimerI12off<10)          //50ms
               {if(input(IN12))
                  {auxI12off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI12off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I12)
                  fprintf(PORT2,"Input 12-> OFF\n\r");  
                ING_I12=0;         //Espira de Entrada Ocupada
                auxI12off=0;         
               }
             break;
         }
switch(auxI13on){
      case 0:if(input(IN13))
               {
                TimerI13on=0;
                auxI13on=1;
               }
             break;  
      case 1:if(TimerI13on<10)          //50ms
               {if(!input(IN13))
                  {auxI13on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI13on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I13)
                  fprintf(PORT2,"Input 13-> ON\n\r");  
                ING_I13=1;         //Espira de Entrada Ocupada
                MEM_I13=1;
                auxI13on=0;         
               }
             break;
         }          
switch(auxI13off){
      case 0:if(!input(IN13))
               {
                TimerI13off=0;
                auxI13off=1;
               }
             break;  
      case 1:if(TimerI13off<10)          //50ms
               {if(input(IN13))
                  {auxI13off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI13off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I13)
                  fprintf(PORT2,"Input 13-> OFF\n\r");  
                ING_I13=0;         //Espira de Entrada Ocupada
                auxI13off=0;         
               }
             break;
         }
switch(auxI14on){
      case 0:if(input(IN14))
               {
                TimerI14on=0;
                auxI14on=1;
               }
             break;  
      case 1:if(TimerI14on<10)          //50ms
               {if(!input(IN14))
                  {auxI14on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI14on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I14)
                  fprintf(PORT2,"Input 14-> ON\n\r");  
                ING_I14=1;         //Espira de Entrada Ocupada
                MEM_I14=1;
                auxI14on=0;         
               }
             break;
         }          
switch(auxI14off){
      case 0:if(!input(IN14))
               {
                TimerI14off=0;
                auxI14off=1;
               }
             break;  
      case 1:if(TimerI14off<10)          //50ms
               {if(input(IN14))
                  {auxI14off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI14off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I14)
                  fprintf(PORT2,"Input 14-> OFF\n\r");  
                ING_I14=0;         //Espira de Entrada Ocupada
                auxI14off=0;         
               }
             break;
         }
switch(auxI15on){
      case 0:if(input(IN15))
               {
                TimerI15on=0;
                auxI15on=1;
               }
             break;  
      case 1:if(TimerI15on<10)          //50ms
               {if(!input(IN15))
                  {auxI15on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI15on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I15)
                  fprintf(PORT2,"Input 15-> ON\n\r");  
                ING_I15=1;         //Espira de Entrada Ocupada
                MEM_I15=1;
                auxI15on=0;         
               }
             break;
         }          
switch(auxI15off){
      case 0:if(!input(IN15))
               {
                TimerI15off=0;
                auxI15off=1;
               }
             break;  
      case 1:if(TimerI15off<10)          //50ms
               {if(input(IN15))
                  {auxI15off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI15off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I15)
                  fprintf(PORT2,"Input 15-> OFF\n\r");  
                ING_I15=0;         //Espira de Entrada Ocupada
                auxI15off=0;         
               }
             break;
         }
switch(auxI16on){
      case 0:if(input(IN16))
               {
                TimerI16on=0;
                auxI16on=1;
               }
             break;  
      case 1:if(TimerI16on<10)          //50ms
               {if(!input(IN16))
                  {auxI16on=0;          //Se houve um pico ou foi um sinal falso
                   TimerI16on=0;      
                  }            
               }
             else
               {if(debugInputs && !ING_I16)
                  fprintf(PORT2,"Input 16-> ON\n\r");  
                ING_I16=1;         //Espira de Entrada Ocupada
                MEM_I16=1;
                auxI16on=0;         
               }
             break;
         }          
switch(auxI16off){
      case 0:if(!input(IN16))
               {
                TimerI16off=0;
                auxI16off=1;
               }
             break;  
      case 1:if(TimerI16off<10)          //50ms
               {if(input(IN16))
                  {auxI16off=0;          //Se houve um pico ou foi um sinal falso
                   TimerI16off=0;      
                  }            
               }
             else
               {if(debugInputs && ING_I16)
                  fprintf(PORT2,"Input 16-> OFF\n\r");  
                ING_I16=0;         //Espira de Entrada Ocupada
                auxI16off=0;         
               }
             break;
         }         


}

#define OUT_G1_EV   PIN_E1       //Sa�da Rel� 2 - Sem�foro Sa�da Piso 0   (0->RED, 1->GREEN)
#define OUT_G2_EV   PIN_E0       //Sa�da Rel� 2 - Sem�foro Sa�da Piso -1  (0->RED, 1->GREEN)
#define OUT_G3_E    PIN_E2       //Sa�da Rel� 2 - Sem�foro Sa�da Piso -2  (0->OFF, 1->RED)
#define OUT_G3_V    PIN_E3       //Sa�da Rel� 2 - Sem�foro Sa�da Piso -2  (0->OFF, 1->GREEN)
#define OUT1        PIN_E4       //Sa�da Rel� 4 - Sinal Inibi��o Leitor ME
#define OUT2        PIN_E5       //Sa�da Rel� 5 - Sinal Inibi��o Leitor MS
#define OUT3        PIN_E6       //Sa�da Rel� 6 - Sinal Abrir Port�o P0 (Entrada)
#define OUT4        PIN_E7       //Sinal Rel� 7 - Sinal Abrir Port�o P-1 (Residentes)   
#define OUT5        PIN_B0       //Sinal Rel� 8 - Sinal Abrir Barreira P0 
#define OUT6        PIN_C5       //Sinal Rel� 9 - Sinal Abrir Barreira P-1 (Auxiliar)



//0: Verde, 1: Vermelho, 2:Mant�m
void EstadoGrupos(int8 G1, int8 G2, int8 G3)
{

switch(G1){
     
      case 0:output_low(OUT_G1_EV);
              //M�quina de entrada ativada enquanto Grupo 1 Aberto.              
             flagEstadoME=1;
             EstadoG1=0;              // Verde
             break;  
      
      case 1:output_high(OUT_G1_EV);
             //M�quina de fechada enquanto Grupo 1 Aberto.
             flagEstadoME=0;
             EstadoG1=1;             // Vermelho
             break;
          }      

switch(G2){
      case 0:output_low(OUT_G2_EV);
             flagEstadoMS=1;
             EstadoG2=0;              // Verde
             break;  
      case 1:output_high(OUT_G2_EV);
             flagEstadoMS=0;
             EstadoG2=1;             // Vermelho
             break;
          }

switch(G3){
      case 0:output_high(OUT_G3_E);        //RED OFF
             output_low(OUT_G3_V);       //Green ON  
             EstadoG3=0;              // Verde
             break;  
      case 1:output_low(OUT_G3_E);        //RED ON
             output_high(OUT_G3_V);        //Green OFF  
             EstadoG3=1;             // Vermelho
             break;
          }
}





void main(void) {
int1 id0,id1,id2,id3,id4,id5,id6,id7,ia0,ia1,ia2,ia3,ia4,ia5,ia6,ia7,ia8;
int8 i=0;
int8 auxTime=0;
int8 cleartime=0;
int8 TIMER_A_OLD=0;

int1 aux1=0,aux2=0,aux3=0,aux4=0,aux5=0,aux6=0,aux7=0,aux8=0;
int1 aux9=0,aux10=0,aux11=0,aux12=0,aux13=0,aux14=0,aux15=0,aux16=0;

int1 auxNotRES=0,auxRES=0,auxINTERFON=0,blockENT=0;
int1 aux_P_RES=0,aux_B_ENT=0,auxNotRESBarAux=0,BarAuxFim=0;

int1 ABRE_BARR_ENT=0,ABRE_BARR_AUX=0,ABRE_P_ENT=0,ABRE_P_RES=0;
int1 PULSO_1=0,PULSO_2=0,PULSO_3=0,PULSO_4=0;

int1 auxCheck_in=0;   //((flag para indicar que ouve pedido na ME
int1 auxBO_open=0;

SET_TRIS_A(0b00111100);
SET_TRIS_B(0b00111110);

SET_TRIS_D(0b00101110);
SET_TRIS_E(0b00000000); //Coloca o pinos E0~E7 com outputs Rel� ON-> Output 0
SET_TRIS_F(0b00111111); //Coloca o pinos F0~F5 Anal�gicas, F6 e F7 special outputs
SET_TRIS_H(0b11111111); //Coloca o pinos H0~H7 com inputs  SW ON-> Input 0
SET_TRIS_J(0b00001111); //Set Tris do display
SETUP_ADC(ADC_OFF);
setup_adc_ports(NO_ANALOGS);
SETUP_WDT(WDT_ON);
RESTART_WDT();
SETUP_TIMER_0(RTCC_INTERNAL|RTCC_DIV_1);  //timer0 16bits
SET_TIMER0(34286);
enable_interrupts(INT_RTCC);               // Habilito Interrupci�n RTCC
enable_interrupts(INT_RDA2);               // Habilito Interrupciones RS232
enable_interrupts(global);                 // Habilito Interrupciones
SET_TIMER0(34286);


output_high(PIN_C0);
output_low(PIN_C1);

output_low(PIN_F7);                        //SEND RS485

setup_spi2(SPI_MASTER | SPI_L_TO_H |SPI_XMIT_L_TO_H | SPI_CLK_DIV_16);
output_high(EEPROM_SELECT); 


RESTART_WDT();
//numLSB=read_ext_eeprom(type);
//write_ext_eeprom(type,numLSB); //Escreve o n� de Parques



//------------------------Start

//OUTPUT_E(0b11111111);
output_high(PIN_C5);
output_high(PIN_B0);

OUTPUT_E(0b11111011);
delay_seg(1);
RESTART_WDT();

output_high(PIN_G4);
output_high(PIN_G3);
output_high(PIN_G0);
output_high(PIN_C2);
RESTART_WDT();
delay_ms(1000);
RESTART_WDT();
output_low(PIN_G4);
output_low(PIN_G3);
output_low(PIN_G0);
output_low(PIN_C2);

fprintf(PORT2,"Inicio de Funcionamento OK\n\r");

OUTPUT_E(0b11111011);


ia0=0;
ia1=0;
ia2=0;
ia3=0;
ia4=0;
ia5=0;
ia6=0;
ia7=0;
ia8=0;

// Testes  -- LOAD TIMES FROM EEPROM

for(i=0;i<25;i++)
  {
   Tempos[i] = read_ext_eeprom(i);
   delay_ms(2);
  }

delay_seg(1);

//

TIMER_A_OLD = TIMER_A;

EstadoGrupos(0,1,1); //0: Verde, 1:VErmelho,2:Mant�m  //Inicializa��o sem�foros


RESTART_WDT();
while(true)
{

  if(BufferOK)  //Faz soma de checksum
    {
     delay_ms(50);
     trata_buffer();
     BufferOK=0;
    } 


  //--------------------PROGRAM----------------------------------- 
 LER_ENTRADAS();
 RESTART_WDT();

 if(TIMER_A_OLD != TIMER_A)
   {
   if(debug)
      fprintf(PORT2,"STEP=%u\n\r",step);
   TIMER_A_OLD=TIMER_A;
   }                                                                                                                                                                                   

 // ACESSOS 
 if(ING_I1 && ING_I8  && !auxINTERFON && flagEstadoME)      // Detec��o Residentes com leitor ativo
   { 
     flagBlockI13=1;
     auxINTERFON=1;
     if(debug)
       fprintf(PORT2,"Interfonia - Noite. Abrir Barreira, Port�o P0 e Portao RES.");
     ABRE_P_ENT=1;
     ABRE_BARR_ENT=1;
     ABRE_P_RES=1;
     auxCheck_in=1;
   }
 else
   if(!ING_I1 && auxINTERFON)
     {
      TIMER_G13=Tempos[11];
      if(debug)
        fprintf(PORT2,"Vou carregar o TimerG13");
      auxINTERFON=0;
      auxBO_open=0;
      auxCheck_in=0;
      flagBlockI13=0;
     } 
 //ACESSO N�O RESIDENTES
 if(ING_I1 && ING_I13 && !auxNotRES && flagEstadoME && !flagBlockI13)      // Detec��o N�o residentes com leitor ativo
   { 
      auxNotRES=1;
      auxNotRESBarAux=1;
      if(debug)
        fprintf(PORT2,"N Residente. Abrir Barreiras.");
      ABRE_P_ENT=1;  
      ABRE_BARR_AUX=1;
      auxCheck_in=1;
      //ABRE_P_ENT=1;
   }
 else
 if(!ING_I1 && auxNotRES)
     {
      if(debug)
         fprintf(PORT2,"Carregar TimerG12");
      TIMER_G12=Tempos[9];
      auxNotRES=0;
      auxBO_open=0;
     }
 // ACESSO RESIDENTES
 if(ING_I1 && ING_I12 && !auxRES && flagEstadoME)      // Detec��o Residentes com leitor ativo
   { auxRES=1;
     if(debug)
       fprintf(PORT2,"Residente. Abrir Barreira e Portao RES.");
     ABRE_P_ENT=1;
     ABRE_P_RES=1;
     auxCheck_in=1;
   }
 else
   if(!ING_I1 && auxRES)
     {
      TIMER_G13=Tempos[11];
      if(debug)
        fprintf(PORT2,"Vou carregar o TimerG13");
      auxRES=0;
      auxBO_open=0;
      auxCheck_in=0;
     } 
 
/*if(ING_I1 && ING_I9 && !auxBO_open && !auxCheck_in && flagEstadoME)         //Barreira Aberta
   auxBO_open=1;
else
  if(!ING_I1 && ING_I9 && !auxCheck_in && auxBO_open) 
    {
     fprintf(PORT2,"Parque Offline. Barreiras Abertas. Carregar Timers");
     TIMER_G13=Tempos[11];
     TIMER_G12=Tempos[11];
     auxBO_open=0;
     ABRE_P_RES=1;
     ABRE_BARR_AUX=1;
    }
 */
 
 // ESPIRA DE SAIDA -2
if(ING_I1 && flagEstadoME && !flag_maqAtiva)
 {
    output_low(OUT1);
    flag_maqAtiva=1;
  }
 if(!ING_I1 && flag_maqAtiva)  //if(!ING_I1 && flagEstadoME==0)
 {
   output_high(OUT1);
   flag_maqAtiva=0;
 }
 if(ING_I2 && flagEstadoMS && !flag_maqSaidaAtiva)  //if(ING_I1 && flagEstadoME==1)
 {
   output_low(OUT2);
   flag_maqSaidaAtiva=1;
 }
 
if(!ING_I2 && flag_maqSaidaAtiva)  //if(ING_I1 && flagEstadoME==1)
 {   
   output_high(OUT2);
   flag_maqSaidaAtiva=0;
 }
 
if(ING_I7 && !aux_P_RES)
  {
   ABRE_P_RES=1;
   aux_P_RES=1;
  }
if(!ING_I7)
    aux_P_RES=0;
 // ESPIRA DE SAIDA -1
if(ING_I5 && !aux_B_ENT)
  {
   ABRE_BARR_ENT=1;
   ABRE_P_ENT=1;
   aux_B_ENT=1;
  }
if(!ING_I5)
  aux_B_ENT=0;
 //ESPIRA MEIO CAMINHO SENTIDO DESCENDENTE - ABRIR BARREIRA AUXILIAR.
 
if(ING_I4 && auxNotRESBarAux && !BarAuxFim)
{
ABRE_BARR_AUX=1;
BarAuxFim=1;
}
if(!ING_I4 && BarAuxFim)
{
auxNotRESBarAux=0;
BarAuxFim=0;
} 


 switch(step){
        case 0:if(TIMER_A>=Tempos[0]-Tempos[2])      //Verde m�nimo G1
                  {MEM_I1=0;
                   step=1;
                   auxTime=Tempos[0]-Tempos[2];
                   TIMER_A=0;
                  }
               break;
        case 1:if(TIMER_A>=Tempos[2]) 
                 {
                  auxTime=auxTime+Tempos[2];
                  if((auxTime>Tempos[1] || !MEM_I1) && (MEM_I2 || MEM_I3))  //
                    {
                     if(MEM_I2)
                        step=2;
                else
                       {step=5;
                        cleartime=0;
                  //  cleartime=Tempos[11];        // Tempo limpeza G1->G3
                       }
                     TIMER_A=0;
                     EstadoGrupos(1,1,1);          //0: Verde, 1:VErmelho,3:Mant�m        //ALLRED
                     blockENT=0;
                    }
                  else
                    {TIMER_A=0;
                     MEM_I1=0;
                    }
                 }   
               break;   
        case 2:if(TIMER_A<5 && ING_I1) 
                 {  
                  blockENT=1;
                   //M�quina de entrada ativada no tempo extra.
                  flagEstadoME=1;
                  if(debug)
                    fprintf(PORT2,"Chamada I1, Bloqueei");
                 }
               if(!ING_I1 && TIMER_A>=5 && blockENT) // if(!ING_I1 && TIMER_A>=5 && blockENT)
                 {    
                  blockENT=0;
                  flagEstadoME=0;
                  if(debug)
                     fprintf(PORT2,"Chamada I1 Saiu, Desloqueei");             
                  }   
               if(TIMER_G12==0 && TIMER_G13==0 && !ING_I11 && !blockENT && TIMER_A>=5 || TIMER_A>=Tempos[15])                //limpeza G1->G2  //TIMER_A>=Tempos[9]
                 {step=3;
                  TIMER_A=0;
                  EstadoGrupos(1,0,1);             //0: Verde, 1:VErmelho,3:Mant�m           //G2 Verde
                 }
               break;
        case 3:if(TIMER_A>=Tempos[3]-Tempos[5])      //Verde m�nimo G2
                  {
                   MEM_I2=0;
                   step=4;
                   auxTime=Tempos[3]-Tempos[5];
                   TIMER_A=0;
                  }
               break;                     
        case 4:if(TIMER_A>=Tempos[5]) 
                 {
                  auxTime=auxTime+Tempos[5];
                  if((auxTime>Tempos[4] || !MEM_I2))
                    {
                     if(MEM_I3)                     
                       {step=5;
                        cleartime=Tempos[13]; // Tempo limpeza G2->G3
                       }
                     else
                       {step=8;
                        cleartime=Tempos[10];  //Tempo limpeza G2->G1 (Subida)
                       } 
                     
                     TIMER_A=0;
                     EstadoGrupos(1,1,1); //0: Verde, 1:VErmelho,3:Mant�m        //ALLRED
                    }
                  else
                    {TIMER_A=0;
                     MEM_I2=0;  
                    }
                 }
               break;
        case 5:if(TIMER_A<5 && ING_I1) //N�o � MEM_I1? N�O EST� A ENTRAR NA CONDI��O if(TIMER_A<5 && ING_I1)
                 {  
                  blockENT=1;
                  flagEstadoME=1;
                  if(debug)
                    fprintf(PORT2,"Chamada I1, Bloqueei");
                 }
               if(!ING_I1 && TIMER_A>=5 && blockENT) // if(!ING_I1 && TIMER_A>=5 && blockENT)
                 {    
                  blockENT=0;
                  flagEstadoME=0;
                  if(debug)
                    fprintf(PORT2,"Chamada I1 Saiu, Desloqueei");
                 }  
          /*     if(TIMER_A>=cleartime)                //Sentido G1->G3  (vai ser 0)
                 {step=6;
                  TIMER_A=0;
                  EstadoGrupos(1,1,0);             //0: Verde, 1:VErmelho,3:Mant�m           //G2 Verde
                 }*/
             if(TIMER_G13==0 && !blockENT && TIMER_A>=5 && TIMER_A>=cleartime || TIMER_A>=Tempos[15])                //limpeza G1->G3  //TIMER_A>=Tempos[9]
                 {step=6;
                  TIMER_A=0;
                  EstadoGrupos(1,1,0);             //0: Verde, 1:VErmelho,3:Mant�m           //G2 Verde
                 } 
               break;              
        case 6:if(TIMER_A>=Tempos[6]-Tempos[8])      //Verde m�nimo G3
                  {
                   MEM_I3=0;
                   step=7;
                   auxTime=Tempos[6]-Tempos[8];
                   TIMER_A=0;
                  }
               break;                
        case 7:if(TIMER_A>=Tempos[8]) 
                 {
                  auxTime=auxTime+Tempos[8];
                  if((auxTime>Tempos[7] || !MEM_I3))
                    {
                     step=8;
                     cleartime=Tempos[12];  //Tempo limpeza G3->G1 (Subida)
                     TIMER_A=0;
                     EstadoGrupos(1,1,1); //0: Verde, 1:VErmelho,3:Mant�m        //ALLRED
                    }
                  else
                    {TIMER_A=0;
                     MEM_I3=0;  
                    }
                 }
               break;                               
        case 8:if(TIMER_A>=cleartime)    //Sentido Sa�da p/ entrada
                 {step=0;
                  TIMER_A=0;
                  EstadoGrupos(0,1,1); //0: Verde, 1:VErmelho,3:Mant�m   //G2 Verde
                 }
               break;        
        }

//Pulsos para Barreiras
if(ABRE_BARR_ENT)
  {
   if(debug)
     fprintf(PORT2,"Pulso barreira de entrada");
   PULSO_1=1;
   output_low(OUT5); //PULSO ON Instante 0 ms; Abro Barreira de Entrada
   TIMER_B=0;
   count_timerB=0;
   ABRE_BARR_ENT=0;
  }
if(PULSO_1 && TIMER_B>1)
  { 
    output_high(OUT5);  //PULSO OFF Instante 1000 ms
    PULSO_1=0;
  }
  
if(ABRE_BARR_AUX)
  {
   if(debug)
     fprintf(PORT2,"Pulso barreira auxiliar.");
   PULSO_2=1;
   output_low(OUT6); //PULSO ON Instante 0 ms; Abro Barreira Auxiliar
   TIMER_C=0;
   count_timerC=0;
   ABRE_BARR_AUX=0;
  }
if(PULSO_2 && TIMER_C>1)
  { output_high(OUT6);  //PULSO OFF Instante 1000 ms
    PULSO_2=0;
  }
 //Pulsos para abrir Port�es
if(ABRE_P_ENT)
  {
   if(debug)
     fprintf(PORT2,"Pulso portao ent.");
   PULSO_3=1;
   output_low(OUT3); //PULSO ON Instante 0 ms; Abro Portao Entrada
   TIMER_D=0;
   count_timerD=0;
   ABRE_P_ENT=0;
  }
if(PULSO_3 && TIMER_D>1)
  { output_high(OUT3);  //PULSO OFF Instante 1000 ms
    PULSO_3=0;
  }
 
if(ABRE_P_RES)
  {
   if(debug)
     fprintf(PORT2,"Pulso portao res.");
   PULSO_4=1;
   output_low(OUT4); //PULSO ON Instante 0 ms;  Abro Portao Residentes
   TIMER_E=0;
   count_timerE=0;
   ABRE_P_RES=0;
  }
if(PULSO_4 && TIMER_E>1)
  { output_high(OUT4);  //PULSO OFF Instante 1000 ms
    PULSO_4=0;
  }
  
// TEstes inputs
/*
 if(ING_I1 && !aux1)
   {fprintf(PORT2,"I1 ON\n\r");
    aux1=1;
   }
if(!ING_I1 && aux1)
  {fprintf(PORT2,"I1 OFF\n\r");
   aux1=0;
   }
 
if(ING_I2 && !aux2)
   {fprintf(PORT2,"I2 ON\n\r");
    aux2=1;
   }
if(!ING_I2 && aux2)
  {fprintf(PORT2,"I2 OFF\n\r");
   aux2=0;
   }

if(ING_I3 && !aux3)
   {fprintf(PORT2,"I3 ON\n\r");
    aux3=1;
   }
if(!ING_I3 && aux3)
  {fprintf(PORT2,"I3 OFF\n\r");
   aux3=0;
   }

if(ING_I4 && !aux4)
   {fprintf(PORT2,"I4 ON\n\r");
    aux4=1;
   }
   
if(!ING_I4 && aux4)
  {fprintf(PORT2,"I4 OFF\n\r");
   aux4=0;
   }

if(ING_I5 && !aux5)
   {fprintf(PORT2,"I5 ON\n\r");
    aux5=1;
   }
if(!ING_I5 && aux5)
  {fprintf(PORT2,"I5 OFF\n\r");
   aux5=0;
   }

if(ING_I6 && !aux6)
   {fprintf(PORT2,"I6 ON\n\r");
    aux6=1;
   }
if(!ING_I6 && aux6)
  {fprintf(PORT2,"I6 OFF\n\r");
   aux6=0;
   }

if(ING_I7 && !aux7)
   {fprintf(PORT2,"I7 ON\n\r");
    aux7=1;
   }
if(!ING_I7 && aux7)
  {fprintf(PORT2,"I7 OFF\n\r");
   aux7=0;
   }

if(ING_I8 && !aux8)
   {fprintf(PORT2,"I8 ON\n\r");
    aux8=1;
   }
if(!ING_I8 && aux8)
  {fprintf(PORT2,"I8 OFF\n\r");
   aux8=0;
   }

if(ING_I9 && !aux9)
   {fprintf(PORT2,"I9 ON\n\r");
    aux9=1;
   }
if(!ING_I9 && aux9)
  {fprintf(PORT2,"I9 OFF\n\r");
   aux9=0;
   }

if(ING_I10 && !aux10)
   {fprintf(PORT2,"I10 ON\n\r");
    aux10=1;
   }
if(!ING_I10 && aux10)
  {fprintf(PORT2,"I10 OFF\n\r");
   aux10=0;
   }

if(ING_I11 && !aux11)
   {fprintf(PORT2,"I11 ON\n\r");
    aux11=1;
   }
if(!ING_I11 && aux11)
  {fprintf(PORT2,"I11 OFF\n\r");
   aux11=0;
   }

if(ING_I12 && !aux12)
   {fprintf(PORT2,"I12 ON\n\r");
    aux12=1;
   }
if(!ING_I12 && aux12)
  {fprintf(PORT2,"I12 OFF\n\r");
   aux12=0;
   }

if(ING_I13 && !aux13)
   {fprintf(PORT2,"I13 ON\n\r");
    aux13=1;
   }
if(!ING_I13 && aux13)
  {fprintf(PORT2,"I13 OFF\n\r");
   aux13=0;
   }

if(ING_I14 && !aux14)
   {fprintf(PORT2,"I14 ON\n\r");
    aux14=1;
   }
if(!ING_I14 && aux14)
  {fprintf(PORT2,"I14 OFF\n\r");
   aux14=0;
   }

if(ING_I15 && !aux15)
   {fprintf(PORT2,"I15 ON\n\r");
    aux15=1;
   }
if(!ING_I15 && aux15)
  {fprintf(PORT2,"I15 OFF\n\r");
   aux15=0;
   }

if(ING_I16 && !aux16)
   {fprintf(PORT2,"I16 ON\n\r");
    aux16=1;
   }
if(!ING_I16 && aux16)
  {fprintf(PORT2,"I16 OFF\n\r");
   aux16=0;
   }  
           
*/            
 
 
/* 
OUTPUT_E(0b11111101); //Activa rele 0
fprintf(PORT2,"RELE 0 -> ON\n\r");
delay_seg(2);

OUTPUT_E(0b11111100);  //Activa rele 0,1
fprintf(PORT2,"RELE 0,1 -> ON\n\r");
delay_seg(2);

OUTPUT_E(0b11111000); //Activa rele 0,1,2
fprintf(PORT2,"RELE 0,1,2 -> ON\n\r");
delay_seg(2);

OUTPUT_E(0b11110000);  //Activa rele 0,1,2,3
fprintf(PORT2,"RELE 0,1,2,3 -> ON\n\r");
delay_seg(2);

OUTPUT_E(0b11100000); //Activa rele 0,1,2,3,4
fprintf(PORT2,"RELE 0,1,2,3,4 -> ON\n\r");
delay_seg(2);

OUTPUT_E(0b11000000);  //Activa rele 0,1,2,3,4,5
fprintf(PORT2,"RELE 0,1,2,3,4,5 -> ON\n\r");
delay_seg(2);

OUTPUT_E(0b10000000); //Activa rele 0,1,2,3,4,5,6
fprintf(PORT2,"RELE 0,1,2,3,4,5,6 -> ON\n\r");
delay_seg(2);

OUTPUT_E(0b00000000); //Activa rele 0,1,2,3,4,5,6,7
fprintf(PORT2,"RELE 0,1,2,3,4,5,6,7 -> ON\n\r");
delay_seg(2);

output_low(PIN_B0);  //activa rel� 8  //Activa rele 0,1,2,3,4,5,6,7,8
fprintf(PORT2,"RELE 0,1,2,3,4,5,6,7,8 -> ON\n\r");
delay_seg(2);

output_low(PIN_C5);  //Activa rel� 7   //Activa rele 0,1,2,3,4,5,6,7,8,9
fprintf(PORT2,"RELE 0,1,2,3,4,5,6,7,8, -> ON\n\r");
delay_seg(2);

OUTPUT_E(0b11111111);                   //Desliga rele 0,1,2,3,4,5,6,7
output_High(PIN_C5);  //Desliga rel� 9
output_High(PIN_B0);  //Desliga rel� 8
fprintf(PORT2,"Desliga Tudo -> ON\n\r");
delay_seg(4);

*/

}//fim while(true) 1


}//fim main






