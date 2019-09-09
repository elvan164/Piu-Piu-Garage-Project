#include "Arduino.h"

class IR_Comms

{
	public:
	IR_Comms(int gunID, int teamID);
	int encrypt();
	int* decrypt (int recvCode);


	private:
	int teamID, gunID, dmgType, dmgVal;
};
