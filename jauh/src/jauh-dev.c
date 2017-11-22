#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "lora_wrapper/lora_wrapper.h"

#include <string.h>

#include <espressif/esp_common.h>
#include <esp/uart.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <dhcpserver.h>

#include <lwip/api.h>

#include <paho_mqtt_c/MQTTESP8266.h>
#include <paho_mqtt_c/MQTTClient.h>

#define AP_SSID "esp-open-rtos AP"
#define AP_PSK "esp-open-rtos"

 
/* You can use http://test.mosquitto.org/ to test mqtt_client instead
 * of setting up your own MQTT server */
#define MQTT_HOST ("172.16.0.2")
#define MQTT_PORT 1883

#define MQTT_USER NULL
#define MQTT_PASS NULL

QueueHandle_t publish_queue; 
char lora_msg_buffer[254];

void print_with_rssi(char * input){
	
	// received a packet
	printf("Received packet'");

	printf("%s", input);
				
	printf("' with RSSI ");
	printf("%d\n",LoRa.packet_rssi());
	
}


inline void delay(int ms){
	vTaskDelay(ms/portTICK_PERIOD_MS);
}

static void  topic_received(mqtt_message_data_t *md)
{
    int i;
    mqtt_message_t *message = md->message;
    printf("Received: ");
    for( i = 0; i < md->topic->lenstring.len; ++i)
        printf("%c", md->topic->lenstring.data[ i ]);

    printf(" = ");
    for( i = 0; i < (int)message->payloadlen; ++i)
        printf("%c", ((char *)(message->payload))[i]);

    printf("\r\n");
    	  
	LoRa.begin_packet_default();
	for( i = 0; i < (int)message->payloadlen; ++i)
        LoRa.write_default(((char *)(message->payload))[i]);
	LoRa.end_packet();
	LoRa.receive(0);
}

static const char *  get_my_id(void)
{
    // Use MAC address for Station as unique ID
    static char my_id[13];
    static bool my_id_done = false;
    int8_t i;
    uint8_t x;
    if (my_id_done)
        return my_id;
    if (!sdk_wifi_get_macaddr(STATION_IF, (uint8_t *)my_id))
        return NULL;
    for (i = 5; i >= 0; --i)
    {
        x = my_id[i] & 0x0F;
        if (x > 9) x += 7;
        my_id[i * 2 + 1] = x + '0';
        x = my_id[i] >> 4;
        if (x > 9) x += 7;
        my_id[i * 2] = x + '0';
    }
    my_id[12] = '\0';
    my_id_done = true;
    return my_id;
}

static void  mqtt_task(void *pvParameters)
{
    int ret         = 0;
    struct mqtt_network network;
    mqtt_client_t client   = mqtt_client_default;
    char mqtt_client_id[20];
    uint8_t mqtt_buf[100];
    uint8_t mqtt_readbuf[100];
    mqtt_packet_connect_data_t data = mqtt_packet_connect_data_initializer;

    mqtt_network_new( &network );
    memset(mqtt_client_id, 0, sizeof(mqtt_client_id));
    strcpy(mqtt_client_id, "ESP-");
    strcat(mqtt_client_id, get_my_id());

    while(1) {
		
        printf("%s: started\n\r", __func__);
        printf("%s: (Re)connecting to MQTT server %s ... ",__func__,
               MQTT_HOST);
        ret = mqtt_network_connect(&network, MQTT_HOST, MQTT_PORT);
        if( ret ){
            printf("error: %d\n\r", ret);
            taskYIELD();
            continue;
        }
        printf("done\n\r");
        mqtt_client_new(&client, &network, 5000, mqtt_buf, 100,
                      mqtt_readbuf, 100);

        data.willFlag       = 0;
        data.MQTTVersion    = 3;
        data.clientID.cstring   = mqtt_client_id;
        data.username.cstring   = MQTT_USER;
        data.password.cstring   = MQTT_PASS;
        data.keepAliveInterval  = 10;
        data.cleansession   = 0;
        printf("Send MQTT connect ... ");
        ret = mqtt_connect(&client, &data);
        if(ret){
            printf("error: %d\n\r", ret);
            mqtt_network_disconnect(&network);
            taskYIELD();
            continue;
        }
        printf("done\r\n");
        mqtt_subscribe(&client, "/tlora", MQTT_QOS1, topic_received);
        xQueueReset(publish_queue);

        while(1){
			
            int packetSize = 0;
            while(xQueueReceive(publish_queue, &packetSize, 0) == pdTRUE){
				
				print_with_rssi(lora_msg_buffer);
				
                mqtt_message_t message;
                message.payload = lora_msg_buffer;
                message.payloadlen = packetSize;
                message.dup = 0;
                message.qos = MQTT_QOS1;
                message.retained = 0;
                ret = mqtt_publish(&client, "/flora", &message);
                if (ret != MQTT_SUCCESS ){
                    printf("error while publishing message: %d\n", ret );
                    break;
                }
            }

            ret = mqtt_yield(&client, 1000);
            if (ret == MQTT_DISCONNECTED)
                break;
        }
        printf("Connection dropped, request restart\n\r");
        mqtt_network_disconnect(&network);
        taskYIELD();
    }
}

void onReceive(int packetSize) {
	
	for (int i = 0; i < packetSize; i++) {
		lora_msg_buffer[i] = (char)LoRa.read();
	}
	lora_msg_buffer[packetSize] = '\0';
	
	if (xQueueSendToBackFromISR(publish_queue, &packetSize, 0) == pdFALSE){
		printf("Publish queue overflow.\r\n");
	}	
}

void user_init(void)
{
    uart_set_baud(0, 115200);
    
    if (!LoRa.begin(915E6)) {
		printf("Starting LoRa failed!");
		while (1);
	}
	
	LoRa.set_coding_rate_4(8);
	LoRa.set_spreading_factor(11);
	LoRa.set_signal_bandwidth(125E3);
	LoRa.set_tx_power_pa_boost(17);
	// register the receive callback
	LoRa.on_receive(onReceive);

	// put the radio into receive mode
	LoRa.receive(0);
	
	char wifi_ssid[21];  
    memset(wifi_ssid, 0, sizeof(wifi_ssid));
    strcpy(wifi_ssid, "JAUH-");
    strcat(wifi_ssid, get_my_id());

	printf("SDK version:%s\n", sdk_system_get_sdk_version());

    sdk_wifi_set_opmode(SOFTAP_MODE);
    struct ip_info ap_ip;
    IP4_ADDR(&ap_ip.ip, 172, 16, 0, 1);
    IP4_ADDR(&ap_ip.gw, 0, 0, 0, 0);
    IP4_ADDR(&ap_ip.netmask, 255, 255, 0, 0);
    sdk_wifi_set_ip_info(1, &ap_ip);

    struct sdk_softap_config ap_config = { .ssid_hidden = 0, .channel = 3, .authmode = AUTH_OPEN, .max_connection = 3, .beacon_interval = 100, };
    
    strcpy((char*) ap_config.ssid,wifi_ssid);
	ap_config.ssid_len = strlen(wifi_ssid);
    
    sdk_wifi_softap_set_config(&ap_config);
	
    ip_addr_t first_client_ip;
    IP4_ADDR(&first_client_ip, 172, 16, 0, 2);
    dhcpserver_start(&first_client_ip, 4);
    
    publish_queue = xQueueCreate(3, sizeof(int));   
    xTaskCreate(&mqtt_task, "mqtt_task", 2048, NULL, 2, NULL);
}
