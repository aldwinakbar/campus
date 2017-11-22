#ifndef DRIVER_LORA_WRAPPER_H_
#define DRIVER_LORA_WRAPPER_H_

#include "lora/lora.h"

typedef struct {
	
	int (*begin)(long);
	void (*end)();

	int (*begin_packet)(int);
	int (*begin_packet_default)();
	int (*end_packet)();

	int (*parse_packet)(int );
	int (*packet_rssi)();
	float (*packet_snr)();

	size_t (*write)(const uint8_t *, size_t );
	size_t (*write_default)(uint8_t );
	size_t (*write_string)(char * );

	int (*available)();
	int (*read)();
	int (*peek)();


	void (*on_receive)(void(*callback)(int));

	void (*receive)(int);
	void (*receive_default)();
	void (*idle)();
	void (*sleep)();

	void (*set_tx_power)(int,int);
	void (*set_tx_power_pa_boost)(int);
	void (*set_frequency)(long);
	void (*set_spreading_factor)(int);
	void (*set_signal_bandwidth)(long);
	void (*set_coding_rate_4)(int);
	void (*set_preamble_length)(long);
	void (*set_sync_word)(int);
	void (*enable_crc)();
	void (*disable_crc)();
	uint8_t (*random)();
	
} LoRaWrapper;


LoRaWrapper LoRa;

#endif
