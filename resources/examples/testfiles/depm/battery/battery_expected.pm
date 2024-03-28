dtmc
const int Battery = 0;
const int Device = 1;
const int Generator = 2;
const int OK = 10;
const int NO_POWER = 11;
const int HAS_POWER = 12;
const int FAIL = 13;


formula Battery_Low = (bLoad < 3);
formula Generator_Down = (gState1 = FAIL);
formula Failure = (bPower = NO_POWER);

module control_flow
	cf:  init Generator;
	[Battery] (cf = Battery) -> 1 : (cf' = Device);
	[Device] (cf = Device) -> 1 : (cf' = Generator);
	[Generator] (cf = Generator) -> 1 : (cf' = Battery);
endmodule

module error_propagation
	gState1:  init OK;
	gPower:  init HAS_POWER;
	bPower:  init HAS_POWER;
	bLoad:  init 5;
	[Battery] ((gPower = HAS_POWER) & (bLoad < 9)) -> 1 : (bPower' = HAS_POWER) & (bLoad' = (bLoad + 1));
	[Battery] ((gPower = HAS_POWER) & (bLoad = 9)) -> 1 : (bPower' = HAS_POWER) & (bLoad' = bLoad);
	[Battery] ((gPower = NO_POWER) & (bLoad > 0)) -> 1 : (bPower' = HAS_POWER) & (bLoad' = (bLoad - 1));
	[Battery] ((gPower = NO_POWER) & (bLoad = 0)) -> 1 : (bPower' = NO_POWER) & (bLoad' = bLoad);
	[Generator] (gState1 = OK) -> 99/100 : (gState1' = OK) & (gPower' = HAS_POWER) + 1/100 : (gState1' = FAIL) & (gPower' = NO_POWER);
	[Generator] (gState1 = FAIL) -> 1 : (gState1' = FAIL) & (gPower' = NO_POWER);
endmodule

rewards "time"
	(cf = Battery): 1;
	(cf = Device): 1;
	(cf = Generator): 1;
endrewards


