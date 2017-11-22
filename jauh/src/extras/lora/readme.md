# Arduino LoRa

An [Arduino](http://arduino.cc/) library for sending and receiving data using [LoRa](https://www.lora-alliance.org/) radios.

## Compatible Hardware

 * [Semtech SX1276/77/78/79](http://www.semtech.com/apps/product.php?pn=SX1276) based boards including:
   * [Dragino Lora Shield](http://www.dragino.com/products/module/item/102-lora-shield.html)
   * [HopeRF](http://www.hoperf.com/rf_transceiver/lora/) [RFM95W](http://www.hoperf.com/rf_transceiver/lora/RFM95W.html), [RFM96W](http://www.hoperf.com/rf_transceiver/lora/RFM96W.html), and [RFM98W](http://www.hoperf.com/rf_transceiver/lora/RFM98W.html)
   * [Modtronix](http://modtronix.com/) [inAir4](http://modtronix.com/inair4.html), [inAir9](http://modtronix.com/inair9.html), and [inAir9B](http://modtronix.com/inair9b.html)

### Semtech SX1276/77/78/79 wiring

| Semtech SX1276/77/78/79 | ESP8266 |
| :---------------------: | :------:|
| VCC | 3.3V |
| GND | GND |
| SCK | SCK |
| MISO | MISO |
| MOSI | MOSI |
| NSS | CS |
| NRESET | 16 |
| DIO0 | 5 |


`NSS`, `NRESET`, and `DIO0` pins can be changed by using `lora_set_pins(ss, reset, dio0)`. `DIO0` pin is optional, it is only needed for receive callback mode. If `DIO0` pin is used, it **must** be interrupt capable via [`attachInterrupt(...)`](https://www.arduino.cc/en/Reference/AttachInterrupt).

## API

See [API.md](API.md).

## Examples

See [examples](examples) folder.

## License

This libary is [licensed](LICENSE) under the [MIT Licence](http://en.wikipedia.org/wiki/MIT_License).
