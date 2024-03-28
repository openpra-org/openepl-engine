dtmc
const int Generator = 0;
const int Device = 1;
const int Battery = 2;
const int OK = 10;
const int NO_POWER = 11;
const int HAS_POWER = 12;
const int FAIL = 13;


formula Device_Failure = (dState1 = FAIL);
formula Battery_Failure = (bPower = NO_POWER);
formula Generator_Down = (gState1 = FAIL);
formula Battery_Low = (bLoad < 3);

module control_flow
	cf:  init Generator;
	[Generator] (cf = Generator) -> 1 : (cf' = Battery);
	[Device] (cf = Device) -> 1 : (cf' = Generator);
	[Battery] (cf = Battery) -> 1 : (cf' = Device);
endmodule

module error_propagation
	bLoad:  init 5;
	bPower:  init NO_POWER;
	gPower:  init NO_POWER;
	gState1:  init FAIL;
	dState1:  init FAIL;
	[Generator] (gState1 = FAIL) -> 1 : (gPower' = NO_POWER) & (gState1' = FAIL);
	[Generator] (gState1 = OK) -> 99/100 : (gPower' = HAS_POWER) & (gState1' = OK) + 1/100 : (gPower' = NO_POWER) & (gState1' = FAIL);
	[Device] (dState1 = FAIL) -> 1 : (dState1' = FAIL);
	[Device] (dState1 = OK) -> 999/1000 : (dState1' = OK) + 1/1000 : (dState1' = FAIL);
	[Battery] ((gPower = HAS_POWER) & (bLoad < 9)) -> 1 : (bLoad' = (bLoad + 1)) & (bPower' = HAS_POWER);
	[Battery] ((gPower = HAS_POWER) & (bLoad = 9)) -> 1 : (bLoad' = bLoad) & (bPower' = HAS_POWER);
	[Battery] ((gPower = NO_POWER) & (bLoad = 0)) -> 1 : (bLoad' = bLoad) & (bPower' = NO_POWER);
	[Battery] ((gPower = NO_POWER) & (bLoad > 0)) -> 1 : (bLoad' = (bLoad - 1)) & (bPower' = HAS_POWER);
endmodule

rewards "time"
	(cf = Generator): 1;
	(cf = Device): 1;
	(cf = Battery): 1;
endrewards


