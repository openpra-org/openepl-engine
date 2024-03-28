ctmc

//const double STEP_LENGTH = 1e9;// 
const double TICK_DURATION = 1; // 1 sec
const double MAX_RATE = 1e0; // 1 sec

// @ tick-rate = 5e-2, each tick, and each step is about ~10.8 ns
const double TICK_RATE = MAX_RATE; //1e-2; // 100x step rate

// const double e = 2.7182818284;
// const double LN_AF;
// const double THERMAL_ACCELERATION_FACTOR = pow(e, LN_AF);

const double THERMAL_ACCELERATION_FACTOR = 1.0;

// data bit flip-rate
const double base_bit_flips_per_year = 1e-3;
const double zeroed_bbfps = THERMAL_ACCELERATION_FACTOR * base_bit_flips_per_year / (365 * 24 * 60 * 60);
const double base_bit_flips_per_sec = zeroed_bbfps <= 0 ? 0 : zeroed_bbfps ;
//THERMAL_ACCELERATION_FACTOR * base_bit_flips_per_year / (365 * 24 * 60 * 60) 

const double INSTRUCTION_MULTIPLIER = 1e-8;
const double BBFR = base_bit_flips_per_sec * MAX_RATE;

// instruction bit-flip rate


// instruction BFRs
const double BFR = BBFR * 1.00;

const double INS_BFR = BBFR * INSTRUCTION_MULTIPLIER;
const double BFR_LOAD = INS_BFR * 1.149;
const double BFR_STOR = INS_BFR * 3.898; 
const double BFR_FSUB = INS_BFR * 6.862;
const double BFR_FADD = INS_BFR * 6.120;
const double BFR_FMUL = INS_BFR * 11.896;


const int N = 14;

const int FSUB_1 = 1;
const int LOAD_2 = 2;
const int FSUB_3 = 3;
const int FMUL_4 = 4;
const int FMUL_6 = 6;
const int STOR_5 = 5;
const int FADD_7 = 7;
const int LOAD_8 = 8;
const int FMUL_9 = 9;
const int ADD_10 = 10;
const int ADD_13 = 13;
const int STO_11 = 11;
const int MUL_12 = 12;
const int RTN_14 = 14;

module program_counter

	pc: [1..N] init 1;

	// sensor input
	PROCESS_VAR : bool init false;

	// reset every loop
      //  PID : bool init false;
	PID: bool init false;
	CURRENT_ERROR : bool init false;
	CURRENT_INTEGRAL : bool init false;
        DELTA_ERROR : bool init false;

	// persistent
        PREV_ERROR : bool init false;
        INTEGRAL : bool init false;

	//pc_jump:[1..N-1] init 1;

	[tick] (true) -> BFR : (PROCESS_VAR'=true);

        //[tick] (pc <= N | pc >= 1) -> tick_rate: (pc'=(pc <= N) ? (pc + 1) : pc_jump); //& (tock'=!tock);
	
        // fsub_1
	[tick] (pc = FSUB_1) -> (PROCESS_VAR ? MAX_RATE : BFR_FSUB) : (CURRENT_ERROR'=true) + TICK_RATE: (pc'=LOAD_2);
 
        // load_2
        [tick] (pc = LOAD_2) -> (PREV_ERROR ? MAX_RATE : BFR_LOAD) : (PREV_ERROR'=true) + TICK_RATE: (pc'=FSUB_3);

	// fsub_3
        [tick] (pc = FSUB_3) -> ((PREV_ERROR | CURRENT_ERROR) ? MAX_RATE : BFR_FSUB) : (DELTA_ERROR'=true) + TICK_RATE: (pc'=FMUL_4);

	// fmul_4
        [tick] (pc = FMUL_4) -> (DELTA_ERROR ? MAX_RATE : BFR_FMUL): (PID'=true) + TICK_RATE: (pc'=STOR_5);
 
        // store_5
        [tick] (pc = STOR_5) -> (CURRENT_ERROR ? MAX_RATE : BFR_STOR) : (PREV_ERROR'=true) + TICK_RATE: (pc'=FMUL_6);

	// fmul_6
        [tick] (pc = FMUL_6) -> (CURRENT_ERROR ? MAX_RATE : BFR_FMUL) : (PID'=true) + TICK_RATE: (pc' = FADD_7);

	// fadd_7
        [tick] (pc = FADD_7) & !PID -> BFR_FADD : (PID'=true) + TICK_RATE: (pc' = LOAD_8);

        // load_8
        [tick] (pc = LOAD_8) & !INTEGRAL -> BFR_LOAD : (INTEGRAL'=true) + TICK_RATE: (pc' = FMUL_9);

	// fmul_9
        [tick] (pc = FMUL_9) -> (CURRENT_ERROR ? MAX_RATE : BFR_FMUL) : (CURRENT_INTEGRAL'=true) + TICK_RATE: (pc' = ADD_10);

	// fadd_10
        [tick] (pc = ADD_10) -> (CURRENT_INTEGRAL ? MAX_RATE : BFR_FADD) : (INTEGRAL'=true) + TICK_RATE: (pc' = STO_11);

	// store_11
        [tick] (pc = STO_11) -> (INTEGRAL ? MAX_RATE : BFR_STOR) : (INTEGRAL'=true) + TICK_RATE: (pc' = MUL_12);

	// fmul_12
        [tick] (pc = MUL_12) -> (INTEGRAL ? MAX_RATE : BFR_FMUL) : (PID'=true) + TICK_RATE: (pc' = ADD_13);

	// fadd_13
        [tick] (pc = ADD_13) & !PID -> BFR_FADD : (PID'=true) + TICK_RATE: (pc' = RTN_14);

	// rtn_14
        [tick] (pc = RTN_14) -> MAX_RATE :(PID'=false) & (CURRENT_ERROR'=false) & (DELTA_ERROR'=false) & (CURRENT_INTEGRAL'=false) & (PROCESS_VAR'=false)
			      + NOMINAL_BRANCH_RATE : (pc' = FSUB_1)
			      + FAULTED_BRANCH_RATE : (pc' = LOAD_2)
			      + FAULTED_BRANCH_RATE : (pc' = FSUB_3)
			      + FAULTED_BRANCH_RATE : (pc' = FMUL_4)
			      + FAULTED_BRANCH_RATE : (pc' = STOR_5)
			      + FAULTED_BRANCH_RATE : (pc' = FMUL_6)
			      + FAULTED_BRANCH_RATE : (pc' = FADD_7)
			      + FAULTED_BRANCH_RATE : (pc' = LOAD_8)
			      + FAULTED_BRANCH_RATE : (pc' = FMUL_9)
			      + FAULTED_BRANCH_RATE : (pc' = ADD_10)
			      + FAULTED_BRANCH_RATE : (pc' = STO_11)
			      + FAULTED_BRANCH_RATE : (pc' = MUL_12)
			      + FAULTED_BRANCH_RATE : (pc' = ADD_13);
endmodule

formula FAULTED_BRANCH_RATE = (BRANCHING_FAULT ? MAX_RATE/13 : 0);

formula NOMINAL_BRANCH_RATE = (BRANCHING_FAULT ? MAX_RATE : MAX_RATE);

formula BITFLIP = PROCESS_VAR;

formula INPUT_ERROR = (pc = FSUB_1) & PROCESS_VAR;

formula OUTPUT_ERROR = PID;

formula OUTPUT_ERROR_ONLY = PID & !BITFLIP;

formula IO_ERROR = INPUT_ERROR | OUTPUT_ERROR;

formula PERSISTENT_ERROR = (PREV_ERROR | INTEGRAL);

formula FAULT = (CURRENT_ERROR | DELTA_ERROR | CURRENT_INTEGRAL);

formula INTERNAL_FAULT = !BITFLIP & FAULT;

formula BRANCHING_FAULT = (CURRENT_ERROR | DELTA_ERROR | CURRENT_INTEGRAL);

formula NOMINAL = !OUTPUT_ERROR & !PERSISTENT_ERROR & !FAULT & !BRANCHING_FAULT;

rewards "NOMINAL"
	NOMINAL : 1;
endrewards

rewards "BITFLIP"
	BITFLIP : 1;
endrewards

rewards "INPUT_ERROR"
	INPUT_ERROR : 1;
endrewards

rewards "OUTPUT_ERROR"
	OUTPUT_ERROR : 1;
endrewards

rewards "OUTPUT_ERROR_ONLY"
	OUTPUT_ERROR_ONLY : 1;
endrewards

rewards "IO_ERROR"
	IO_ERROR : 1;
endrewards

rewards "PERSISTENT_ERROR"
	PERSISTENT_ERROR : 1;
endrewards

rewards "FAULT"
	FAULT : 1;
endrewards

rewards "INTERNAL_FAULT"
	INTERNAL_FAULT : 1;
endrewards

rewards "BRANCHING_FAULT"
	BRANCHING_FAULT : 1;
endrewards
