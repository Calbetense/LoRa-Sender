# LoRa-Sender

This project takes samples from some sensors and send the averaged info to another [LoRa-Reciver](https://github.com/Calbetense/LoRa-Reciver) who acts as Gateway. 

The sensors are:

* Temperature: ds18b20 - Digital temperature sensor that uses OneWire as comunnication protocol. Documentation: [Atlas Scientific DO](https://atlas-scientific.com/kits/gravity-analog-do-kit/) ![ds18b20](https://www.ardutech.com/wp-content/uploads/2019/10/24.-DS18B20-1.jpg) {width=30%}
* Disolved Oxygen: From _Atlas Scientific_. Analog sensor. Needs calibration and converts the units from %Sat to mg/L. ![DO_sensor](https://cdn.shopify.com/s/files/1/1386/3791/products/atlas-scientific-water-quality-gravity-analog-dissolved-oxygen-kit-atlas-scientific-14468538695767_large.jpg?v=1596851961)
* ORP: From _Atlas Scientific_. Analog sensor. Needs calibration. Documentation: [Atlas Scientific ORP](https://atlas-scientific.com/kits/gravity-analog-orp-kit/){width=30%}

![ORP_Sensor](https://cdn.shopify.com/s/files/1/1386/3791/products/atlas-scientific-water-quality-gravity-analog-orp-kit-atlas-scientific-14468509040727_large.jpg?v=1596850638){width=30%}
