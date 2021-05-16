#include <main.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LED_GREEN PIN_C0
#define LED_RED PIN_C3
#define HORLOGE_AFFICHAGE 25

#define ENTREE PIN_B1
#define SORTIE PIN_B2
#use rs232 (baud=9600, xmit=pin_C6,rcv=pin_C7)

int number = 0;
int max_Pers = 3 ;
char buffer[3];
boolean flag = 0;
#int_RDA
void  RDA_isr(void) {
      flag = 1;
      buffer[0] = getch();
      buffer[1] = getch();
   
}

int affichage(int nombre){
   int unite = nombre % 10;
   int dizaine = nombre / 10 ;
   int sortiez = 0 ;
   if(nombre < 10){
    output_d(nombre);
   }
   else{
      sortiez = unite + dizaine*16;
      output_d(sortiez);
    
   }
}

void maximum(){

   if(number >= max_pers){
      output_toggle(LED_RED);
      output_low(LED_GREEN);
   }
   else {
      
      output_high(LED_GREEN);
      output_low(LED_RED);
   }
}


void main() {

   
   setup_low_volt_detect(FALSE);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   setup_timer_1( T1_INTERNAL | T1_DIV_BY_1  );
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_oscillator(False);
   set_tris_d(0);
   
   enable_interrupts(INT_RDA); 
   enable_interrupts(GLOBAL);
   output_high(PIN_C0);
   output_low(PIN_C3);
    

    while(TRUE){
        
        if(input(ENTREE) == 1 && input(SORTIE) ==0 && number < 95){
            number += 1 ;
            delay_ms(1000);
            affichage(number);
        }

        else if(input(SORTIE) ==1 && input(ENTREE) ==0 && number > 0){
            number -= 1 ;
            affichage(number);
            delay_ms(1000);
        }
              
        affichage(number);
        maximum();
        delay_ms(100);
        
        char number_str[10];
        char max_Pers_str[10];
        char slash[10] = "/";
        if (max_pers < 10){
            sprintf(max_Pers_str, "0%d", max_Pers);
            
            if (number < 10){
               sprintf(number_str, "0%d", number);
             
            }
            else{
               sprintf(number_str, "%d", number);
            }
        }
        
        else {
        sprintf(max_Pers_str, "%d", max_Pers);
           if (number < 10){
               sprintf(number_str, "0%d", number);
               
               }
            else{
               sprintf(number_str, "%d", number);
            }
        }
        strcat(max_Pers_str, slash);
        strcat(max_Pers_str, number_str);
        printf("%s ",max_Pers_str);

       if (flag==1){
            flag = 0;
            max_Pers = atoi(buffer);

            
        }
    }

}
