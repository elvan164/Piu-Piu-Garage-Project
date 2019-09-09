#include "Arduino.h"
#include "IR_Comms.h"

//int gunID, teamID;

	IR_Comms::IR_Comms(int gunID, int teamID) {

	//int gunIdentity[2] = {0, 0}; //1st value of array = team 1, 2, 2nd value of array = gun 1, 2, 3...

	this->gunID = gunID;
	this->teamID = teamID;

	}


	int IR_Comms::encrypt() {

		int sentCode = 0x0000;

 		sentCode += teamID << 12; // put team code in 13 - 16 hex place	 
	  	sentCode += gunID << 8;  // put gun code in 9 - 12 hex place

	  	return sentCode;
	}


	int* IR_Comms::decrypt (int recvCode) {

		int shotInfo[4];
		shotInfo[3] = (recvCode & 0xF000) >> 12;
		shotInfo[2] = (recvCode & 0x0F00) >> 8;
		shotInfo[1] = (recvCode & 0x00F0) >> 4;
		shotInfo[0] = (recvCode & 0x000F);
		Serial.println(shotInfo[3], HEX);
		Serial.println(shotInfo[2], HEX);
		Serial.println(shotInfo[1], HEX);
		Serial.println(shotInfo[0], HEX);


		int* shotInfoPointer;

		shotInfoPointer = shotInfo;

		return shotInfoPointer;
	}


