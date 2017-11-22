#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "lora/lora.h"
#include "task.h"

inline void delay(int ms){
	vTaskDelay(ms/portTICK_PERIOD_MS);
}

uint32_t counter = 0;
void loop(void *pvParameters){
	while(1) {
		delay(1000);
		/*
	 // try to parse packet
		int packetSize = lora_parse_packet(0);
		if (packetSize) {
			// received a packet
			printf("Received packet '");

				// read packet
			while (lora_available()) {
				printf("%c",(char)lora_read());
			}

				// print RSSI of packet
			printf("' with RSSI ");
			printf("%d\n",lora_packet_rssi());
		}
		*/
	  /*
	  char counter_string[32];	  
	  sprintf(counter_string, "%d", counter++);
	  
	  lora_begin_packet_default();
	  lora_write_string("| 1 : ");
	  lora_write_string(counter_string);
	  
	  lora_write_string(" | 2 : ");
	  lora_write_string(counter_string);
	  
	  lora_write_string(" | 3 : ");
	  lora_write_string(counter_string);
	  
	  lora_write_string(" | 4 : ");
	  lora_write_string(counter_string);
	  
	  lora_write_string(" | 5 : ");
	  lora_write_string(counter_string);
	  lora_end_packet();
	  //delay(1000);
	  */
	  
    }
}

void onReceive(int packetSize) {
 
			// received a packet
	printf("Received packet '");


	for (int i = 0; i < packetSize; i++) {
		printf("%c",(char)lora_read());
	}
				// print RSSI of packet
	printf("' with RSSI ");
	printf("%d\n",lora_packet_rssi());
}

void user_init(void)
{
    uart_set_baud(0, 115200);
    
    
    lora_set_pins(15, DEFAULT_RESET_PIN, DEFAULT_IRQ_PIN);
    if (!lora_begin(915E6)) {
		printf("Starting LoRa failed!");
		while (1);
	}
	
	lora_set_coding_rate_4(8);
	lora_set_spreading_factor(11);
	lora_set_signal_bandwidth(41.7E3);
	lora_set_tx_power_pa_boost(17);
	//lora_enable_crc();
	
	  // register the receive callback
	lora_on_receive(onReceive);

  // put the radio into receive mode
	lora_receive(0);
   
    printf("SDK version:%s\n", sdk_system_get_sdk_version());
    xTaskCreate(loop, "loop", 1024, NULL, 2, NULL);
}
