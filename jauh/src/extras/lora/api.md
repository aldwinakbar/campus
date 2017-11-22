# LoRa API

## Include Library

```c
#include "lora/lora.h"
```

## Setup

### Begin

Initialize the library with the specified frequency.

```c
lora_begin(frequency);
```
 * `frequency` - frequency in Hz (`433E6`, `866E6`, `915E6`)

Returns `1` on success, `0` on failure.

### Set pins

Override the default `NSS`, `NRESET`, and `DIO0` pins used by the library. **Must** be called before `lora_begin()`.

```c
lora_set_pins(ss, reset, dio0);
```
 * `ss` - new slave select pin to use, defaults to `10`
 * `reset` - new reset pin to use, defaults to `9`
 * `dio0` - new DIO0 pin to use, defaults to `2`.  **Must** be interrupt capable via [attachInterrupt(...)](https://www.arduino.cc/en/Reference/AttachInterrupt).

This call is optional and only needs to be used if you need to change the default pins used.

### Set SPI Frequency

Override the default SPI frequency of 10 MHz used by the library. **Must** be called before `LoRa.begin()`.

```c
lora_set_spi_frequency(frequency);
```
 * `frequency` - new SPI frequency to use, defaults to `8E6`

This call is optional and only needs to be used if you need to change the default SPI frequency used. Some logic level converters cannot support high speeds such as 8 MHz, so a lower SPI frequency can be selected with `LoRa.setSPIFrequency(frequency)`.

## Sending data

### Begin packet

Start the sequence of sending a packet.

```c
lora_begin_packet_default();

lora_begin_packet(implicitHeader);
```

 * `implicitHeader` - (optional) `true` enables implicit header mode, `false` enables explicit header mode (default)

Returns `1` on success, `0` on failure.

### Writing

Write data to the packet. Each packet can contain up to 255 bytes.

```c
lora_write(buffer, size);

lora_write_default(byte);

lora_write_string(input);
```
* `byte` - single byte to write to packet
* `input` - a null-terminated string

or

* `buffer` - data to write to packet
* `size` - size of data to write

Returns the number of bytes written.

### End packet

End the sequence of sending a packet.

```c
lora_end_packet()
```

Returns `1` on success, `0` on failure.

## Receiving data

### Parsing packet

Check if a packet has been received.

```c
int packetSize = lora_parse_packet(0);

int packetSize = lora_parse_packet(size);
```

 * `size` - (optional) if `> 0` implicit header mode is enabled with the expected a packet of `size` bytes, default mode is explicit header mode


Returns the packet size in bytes or `0` if no packet was received.

### Continuous receive mode

#### Register callback

Register a callback function for when a packet is received.

```c
lora_on_receive(onReceive);

void onReceive(int packetSize) {
 // ...
}
```

 * `onReceive` - function to call when a packet is received.

#### Receive mode

Puts the radio in continuous receive mode.

```c
lora_receive_default();

lora_receive(int size);
```

 * `size` - (optional) if `> 0` implicit header mode is enabled with the expected a packet of `size` bytes, default mode is explicit header mode

The `onReceive` callback will be called when a packet is received.

### Packet RSSI

```c
int rssi = lora_packet_rssi();
```

Returns the RSSI of the received packet.

### Packet SNR

```c
float snr = lora_packet_snr();
```

Returns the estimated SNR of the received packet in dB.

### Available

```c
int availableBytes = lora_available()
```

Returns number of bytes available for reading.

### Peeking

Peek at the next byte in the packet.

```c
byte b = lora_peek();
```

Returns the next byte in the packet or `-1` if no bytes are available.

### Reading

Read the next byte from the packet.

```c
byte b = lora_read();
```

Returns the next byte in the packet or `-1` if no bytes are available.

**Note:** Other Arduino [`Stream` API's](https://www.arduino.cc/en/Reference/Stream) can also be used to read data from the packet

## Other radio modes

### Idle mode

Put the radio in idle (standby) mode.

```c
lora_idle();
```

### Sleep mode

Put the radio in sleep mode.

```c
lora_sleep();
```

## Radio parameters

### TX Power

Change the TX power of the radio.

```c
lora_set_tx_power_pa_boost(txPower);

lora_set_tx_power(txPower, outputPin);
```
 * `txPower` - TX power in dB, defaults to `17`
 * `outputPin` - (optional) PA output pin, supported values are `PA_OUTPUT_RFO_PIN` and `PA_OUTPUT_PA_BOOST_PIN`, defaults to `PA_OUTPUT_PA_BOOST_PIN`.

Supported values are between `2` and `17` for `PA_OUTPUT_PA_BOOST_PIN`, `0` and `14` for `PA_OUTPUT_RFO_PIN`.

Most modules have the PA output pin connected to PA BOOST,

### Frequency

Change the frequency of the radio.

```c
lora_set_frequency(frequency);
```
 * `frequency` - frequency in Hz (`433E6`, `866E6`, `915E6`)

### Spreading Factor

Change the spreading factor of the radio.

```c
lora_set_spreading_factor(spreadingFactor);
```
 * `spreadingFactor` - spreading factor, defaults to `7`

Supported values are between `6` and `12`. If a spreading factor of `6` is set, implicit header mode must be used to transmit and receive packets.

### Signal Bandwidth

Change the signal bandwidth of the radio.

```c
lora_set_signal_bandwidth(signalBandwidth);
```

 * `signalBandwidth` - signal bandwidth in Hz, defaults to `125E3`.

Supported values are `7.8E3`, `10.4E3`, `15.6E3`, `20.8E3`, `31.25E3`, `41.7E3`, `62.5E3`, `125E3`, and `250E3`.

### Coding Rate

Change the coding rate of the radio.

```c
lora_set_coding_rate_4(codingRateDenominator);
```

 * `codingRateDenominator` - denominator of the coding rate, defaults to `5`

Supported values are between `5` and `8`, these correspond to coding rates of `4/5` and `4/8`. The coding rate numerator is fixed at `4`.

### Preamble Length

Change the preamble length of the radio.

```c
lora_set_preamble_length(preambleLength);
```

 * `preambleLength` - preamble length in symbols, defaults to `8`

Supported values are between `6` and `65535`.

### Sync Word

Change the sync word of the radio.

```c
lora_set_sync_word(syncWord);
```

 * `syncWord` - byte value to use as the sync word, defaults to `0x34`

### CRC

Enable or disable CRC usage, by default a CRC is not used.

```c
lora_enable_crc();

lora_disable_crc();
```

## Other functions

### Random

Generate a random byte, based on the Wideband RSSI measurement.

```
byte b = lora_random();
```

Returns random byte.
