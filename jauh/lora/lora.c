/* Example SPI transfert
 *
 * This sample code is in the public domain.
 */
#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "esp8266.h"
#include <stdio.h>
#include "esp/spi.h"
#include <string.h>

#define REG_VERSION              0x42

/*
 * Possible Data Structure of SPI Transaction
 *
 * [COMMAND]+[ADDRESS]+[DataOUT]+[DUMMYBITS]+[DataIN]
 *
 * [COMMAND]+[ADDRESS]+[DUMMYBITS]+[DataOUT]
 *
 */


void loop(void *pvParameters)
{
    uint32_t time = 0 ; // SPI transmission time
    float avr_time = 0 ; // Average of SPI transmission
    float u = 0 ;

    spi_init(1, SPI_MODE0, SPI_FREQ_DIV_8M, 1, SPI_LITTLE_ENDIAN, false); // init SPI module

	vTaskDelay(1000 / portTICK_PERIOD_MS);
    while(1) {

        time = sdk_system_get_time();
        
        /*
         * Setting Command and Address value can be done using 2 example, like below :
         * 
         * 	
         *  1) The "udon'tsay" way:
         * 			spi_set_command(1,8,0x02);
         * 			spi_set_address(1,8,0x00);
         * 
         *  2) The other way :
         * 			spi_transfer_8(1, 0x02);
         * 			spi_transfer_8(1, 0x00);
		*/
		
		spi_transfer_8(1, 0x02);
        spi_transfer_8(1, 0x00);
        unsigned char name[] = "Aldwin Akbar Hermanudin";
        
	    uint16_t in_buf[sizeof(name)];
		spi_transfer(1, name, in_buf, strlen((char*)name), SPI_8BIT); // len = 4 words * 2 bytes = 8 bytes
        spi_clear_address(1); // remove address
        spi_clear_command(1); // remove command        
		/*  if (version != 0x12) {
			printf("Wrong ID : 0x%x \n", version);
		  }
		  else{
			  printf("True ID : 0x%x \n", version);
		  }*/
	 
	    /*

        spi_set_command(1,1,1) ; // Set one command bit to 1
        spi_set_address(1,4,8) ; // Set 4 address bits to 8
        spi_set_dummy_bits(1,4,false); // Set 4 dummy bit before Dout

        spi_repeat_send_16(1,0xC584,10);  // Send 1 bit command + 4 bits address + 4 bits dummy + 160 bits data

        spi_clear_address(1); // remove address
        spi_clear_command(1); // remove command
        spi_clear_dummy(1); // remove dummy
		*/

        time = sdk_system_get_time() -time ;
        avr_time = ((avr_time * (float)u ) + (float)time)/((float)u+1.0)  ; // compute average
        u++;
        if (u==100) {
            u=0 ;
            printf("Time: %f\n",avr_time);
        }
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}


void user_init(void)
{
    uart_set_baud(0, 115200);
    printf("SDK version:%s\n", sdk_system_get_sdk_version());
    xTaskCreate(loop, "loop", 1024, NULL, 2, NULL);
}

/* Arduino SPISlave
  
  
    SPI Slave Demo Sketch
    Connect the SPI Master device to the following pins on the esp8266:

    GPIO    NodeMCU   Name  |   Uno
  ===================================
     15       D8       SS   |   D10
     13       D7      MOSI  |   D11
     12       D6      MISO  |   D12
     14       D5      SCK   |   D13

    Note: If the ESP is booting at a moment when the SPI Master has the Select line HIGH (deselected)
    the ESP8266 WILL FAIL to boot!
    See SPISlave_SafeMaster example for possible workaround



#include "SPISlave.h"

void setup()
{
    Serial.begin(115200);
    //Serial.setDebugOutput(true);

    // data has been received from the master. Beware that len is always 32
    // and the buffer is autofilled with zeroes if data is less than 32 bytes long
    // It's up to the user to implement protocol for handling data length
    SPISlave.onData([](uint8_t * data, size_t len) {
        String message = String((char *)data);
        Serial.printf("Message: %s\n\r", (char *)data);
    });

    // Setup SPI Slave registers and pins
    SPISlave.begin();
}

void loop() {}
*/
