# TemperatureComparator
LM35 temperature reading with PIC18F4550.

Reads 2 digit temperature from LM35 (labeled _temp_) and prints to 7seg displays. Compares temperature of the first sensor with two other LM35 (_comp80_ and _comp90_) via analog comparator and lights, respectively, LEDs _alerta_1_ and _alerta_2_ if temperature read is equal to one of the other sensors.
