dtmc
const int Sensor = 0;
const int Transmitter = 1;
const int Channel_1 = 2;
const int Channel_2 = 3;
const int Channel_3 = 4;
const int Processor = 5;
const int Receiver = 6;
const int ok = 0;
const int error = 1;


formula TransmissionFault = (SAMPLE != RECEIVED_SAMPLE);

module control_flow
	cf:  init Sensor;
	[Sensor] (cf = Sensor) -> 1 : (cf' = Transmitter);
	[Transmitter] (cf = Transmitter) -> 1 : (cf' = Channel_1);
	[Transmitter] (cf = Transmitter) -> 1 : (cf' = Channel_2);
	[Transmitter] (cf = Transmitter) -> 1 : (cf' = Channel_3);
	[Channel_1] (cf = Channel_1) -> 1 : (cf' = Receiver);
	[Channel_2] (cf = Channel_2) -> 1 : (cf' = Receiver);
	[Channel_3] (cf = Channel_3) -> 1 : (cf' = Receiver);
	[Processor] (cf = Processor) -> 1 : (cf' = Sensor);
	[Receiver] ((cf = Receiver) & (CONSENSUS = ok)) -> 1 : (cf' = Processor);
	[Receiver] ((cf = Receiver) & (CONSENSUS = error)) -> 1 : (cf' = Receiver);
endmodule

module error_propagation
	SAMPLE:  init ok;
	REPLICA_1:  init ok;
	REPLICA_2:  init ok;
	REPLICA_3:  init ok;
	RECEIVED_1:  init ok;
	RECEIVED_2:  init ok;
	RECEIVED_3:  init ok;
	RECEIVED_SAMPLE:  init ok;
	CONSENSUS:  init ok;
	[Sensor] true -> 1 : (SAMPLE' = ok);
	[Transmitter] (SAMPLE = ok) -> 1 : (REPLICA_1' = ok) & (REPLICA_2' = ok) & (REPLICA_3' = ok);
	[Transmitter] (SAMPLE != ok) -> 1 : (REPLICA_1' = error) & (REPLICA_2' = error) & (REPLICA_3' = error);
	[Channel_1] (REPLICA_1 = ok) -> 1 : (RECEIVED_1' = ok);
	[Channel_1] (REPLICA_1 != ok) -> 1 : (RECEIVED_1' = error);
	[Channel_2] (REPLICA_2 = ok) -> 1 : (RECEIVED_2' = ok);
	[Channel_2] (REPLICA_2 != ok) -> 1 : (RECEIVED_2' = error);
	[Channel_3] (REPLICA_3 = ok) -> 99999/100000 : (RECEIVED_3' = ok) + (1 - 99999/100000) : (RECEIVED_3' = error);
	[Channel_3] (REPLICA_3 != ok) -> 99/100 : (RECEIVED_3' = error) + (1 - 99/100) : (RECEIVED_3' = ok);
	[Receiver] (((RECEIVED_1 = ok) & (RECEIVED_2 = ok)) & (RECEIVED_3 = ok)) -> 1 : (RECEIVED_SAMPLE' = ok) & (CONSENSUS' = ok);
	[Receiver] (((RECEIVED_1 != ok) | (RECEIVED_2 != ok)) | (RECEIVED_3 != ok)) -> 1 : (RECEIVED_SAMPLE' = error) & (CONSENSUS' = error);
endmodule


