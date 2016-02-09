/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
der GNU General Public License, wie von der Free Software Foundation,
Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
veröffentlichten Version, weiterverbreiten und/oder modifizieren.

Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
Siehe die GNU General Public License für weitere Details.

Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>.
*/

/*
  Simple-Lamp-Switch for Attiny85 / Arduino
  Tested on Digispark-Board
*/


// lower and upper barriers for ADC signal. Those have to be carefully adjusted to your hardware
#define LOWER_BARRIER 67
#define UPPER_BARRIER 157
#define HOLD_TIME     350
#define NUMBER_OF_COUNTS 0b11

// 
uint16_t sensor_analog; // store ADC value in this variable
uint8_t counter;        // counter stores current mode (50%, 100%, off and so forth)


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(1, OUTPUT); //LED on Model A   // depends on your specific hardware
  pinMode(0, OUTPUT); //LED on Model B   // depends on your specific hardware
  pinMode(3, INPUT);  //Analog input for sensor
  sensor_analog = 0;  
  counter       = 0;
}

// the loop routine runs over and over again forever:
void loop() {
  sensor_analog = ( analogRead(3)>>2 )&(0xFF);
//  analogWrite(1, sensor_analog);
//  analogWrite(0, sensor_analog);
  
//  delay(1000);
  
//  counter = (counter+1)&(NUMBER_OF_COUNTS);
  
//  delay(1000);
  
  if(sensor_analog > UPPER_BARRIER)
  {
    delay(HOLD_TIME);
    sensor_analog = ( analogRead(3)>>2 )&(0xFF);
   
    if(sensor_analog > UPPER_BARRIER)
    {
      counter = (counter+1)&(NUMBER_OF_COUNTS);
    }
    /* else
    {
      uint8_t inner_counter = 0;
      while( (sensor_analog > LOWER_BARRIER)&&(inner_counter<200) )  
        sensor_analog = ( analogRead(3)>>2 )&(0xFF);
        if(sensor_analog > UPPER_BARRIER)
        {
          counter = (counter+1)&(NUMBER_OF_COUNTS);
        }
        inner_counter++;
    }*/
    
  }
  
  switch(counter){
    case 0:
      analogWrite(0,0);
      analogWrite(1,0);
      break;
    case 1:
      analogWrite(0,255);
      analogWrite(1,255);
      break;
    case 2:
      analogWrite(0,175);
      analogWrite(1,175);    
      break;
    case 3:
      analogWrite(0,90);
      analogWrite(1,90);    
      break;
    default:
      break;  
  }
  
}
