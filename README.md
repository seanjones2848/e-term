# e-term

Made for a 5.83" waveshare e-paper for use on a raspberry pi with the associated hat.
This is a project intended to get a working terminal on an e-ink screen so I can code in the sunshine.

## setup

Install raspian os on pi

I used the setup and example code from the waveshare [site](https://www.waveshare.com/wiki/5.83inch_e-Paper_HAT_Manual#Working_With_Raspberry_Pi)

Enable SPI on pi (Interface Options -> SPI -> Yes)
```
sudo raspi-config
```

Install BCM2836 lib

```
#Open the Raspberry Pi terminal and run the following command
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.71.tar.gz
tar zxvf bcm2835-1.71.tar.gz
cd bcm2835-1.71/
sudo ./configure && sudo make && sudo make check && sudo make install
# For more information, please refer to the official website: http://www.airspayce.com/mikem/bcm2835/
```

Clone this repo and compile examples and tests for the screen
```
git clone https://github.com/seanjones2848/e-term.git
cd e-term
sudo make clean
sudo make -j4 EPD=epd5in83V2
sudo ./epd
```
