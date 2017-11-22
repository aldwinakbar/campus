#include "lora_wrapper.h"

LoRaWrapper LoRa = {
	
	.begin = &lora_begin,
	.end = &lora_end,
	.begin_packet = &lora_begin_packet,
	.begin_packet = &lora_begin_packet,
	.begin_packet_default = &lora_begin_packet_default,
	.end_packet = &lora_end_packet,

	.parse_packet = &lora_parse_packet,
	.packet_rssi = &lora_packet_rssi,
	.packet_snr = &lora_packet_snr,
	
	
	.write = &lora_write,
	.write_default = &lora_write_default,
	.write_string = &lora_write_string,

	.available = &lora_available,
	.read = &lora_read,
	.peek = &lora_peek,

	.on_receive = &lora_on_receive,

	.receive = &lora_receive,
	.receive_default = &lora_receive_default,
	.idle = &lora_idle,
	.sleep = &lora_sleep,

	.set_tx_power = &lora_set_tx_power,
	.set_tx_power_pa_boost = &lora_set_tx_power_pa_boost,
	.set_frequency = &lora_set_frequency,
	.set_spreading_factor = &lora_set_spreading_factor,
	.set_signal_bandwidth = &lora_set_signal_bandwidth,
	.set_coding_rate_4 = &lora_set_coding_rate_4,
	.set_preamble_length = &lora_set_preamble_length,
	.set_sync_word = &lora_set_sync_word,
	.enable_crc = &lora_enable_crc,
	.disable_crc = &lora_disable_crc,
	.random = &lora_random
};



