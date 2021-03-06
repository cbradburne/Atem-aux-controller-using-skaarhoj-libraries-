#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>

// MAC address and IP address for this *particular* Ethernet Shield!
// MAC address is printed on the shield
// IP address is an available address you choose on your subnet where the switcher is also present:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xE8, 0xE9 };    // <= arudino mac
IPAddress ip(192, 168, 0, 55);        // <= arudino ip
IPAddress switcherIp(192, 168, 0, 50);     // <= SETUP!  IP address of the ATEM Switcher

// Include ATEM library and make an instance:
#include <ATEMbase.h>
#include <ATEMuni.h>

ATEMuni AtemSwitcher;

int buttonPC = 0;//numbers correlate to pins on board
bool PCread = true;

int buttonCam2 = 1;//numbers correlate to pins on board
bool Cam2read = true;

int buttonPGM = 2;//numbers correlate to pins on board
bool PGMread = true;

void setup() { 

  // Set up pins for input
  pinMode(buttonPC,   INPUT_PULLUP);//pc       aux 1
  pinMode(buttonCam2, INPUT_PULLUP);//cam2     aux 1
  pinMode(buttonPGM,  INPUT_PULLUP);//PGM      aux 1

  delay(1000); //allows ethernet too boot up
  
  // Start the Ethernet, Serial (debugging) and UDP:
  Ethernet.begin(mac,ip);

  //starts serial debugger
  Serial.begin(9600);  

  // Initialize a connection to the switcher:
  AtemSwitcher.begin(switcherIp);
  AtemSwitcher.serialOutput(0x80);
  AtemSwitcher.connect();
}

void loop() {
  // On ATEM 1M/E: Black (0), 1 (1), 2 (2), 3 (3), 4 (4), 5 (5), 6 (6), 7 (7), 8 (8), Bars (9), Color1 (10), Color 2 (11), Media 1 (12), Media 1 Key (13), Media 2 (14), Media 2 Key (15), Program (16), Preview (17), Clean1 (18), Clean 2 (19)

  AtemSwitcher.runLoop();
    
  //switches aux 1 to PC
  if(!digitalRead(buttonPC)){
    AtemSwitcher.setAuxSourceInput(0,1);
    Serial.println("aux 2 has been switched to pc");
  }
  
  //switches aux 1 to Cam2 
  if(!digitalRead(buttonCam2)){
    AtemSwitcher.setAuxSourceInput(0,3);
  }

  //switches aux 1 to PGM
  if(!digitalRead(buttonPGM)){
    AtemSwitcher.setAuxSourceInput(0,16);
  }
}
