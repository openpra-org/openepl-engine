dtmc
const int Receiver = 0;
const int Processor = 1;
const int Channel_3 = 2;
const int Channel_2 = 3;
const int Channel_1 = 4;
const int Transmitter = 5;
const int Sensor = 6;
const int ok = 0;
const int error = 1;


formula QuorumLost = ((CONSENSUS != ok) & (RECEIVED_SAMPLE = error));
formula TransmissionFault = (SAMPLE != RECEIVED_SAMPLE);

module control_flow
	cf:  init Sensor;
	[Receiver] ((cf = Receiver) & (CONSENSUS = error)) -> 1 : (cf' = Receiver);
	[Receiver] ((cf = Receiver) & (CONSENSUS = ok)) -> 1 : (cf' = Processor);
	[Processor] (cf = Processor) -> 1 : (cf' = Sensor);
	[Channel_3] (cf = Channel_3) -> 1 : (cf' = Receiver);
	[Channel_2] (cf = Channel_2) -> 1 : (cf' = Receiver);
	[Channel_1] (cf = Channel_1) -> 1 : (cf' = Receiver);
	[Transmitter] (cf = Transmitter) -> 1 : (cf' = Channel_1);
	[Transmitter] (cf = Transmitter) -> 1 : (cf' = Channel_2);
	[Transmitter] (cf = Transmitter) -> 1 : (cf' = Channel_3);
	[Sensor] (cf = Sensor) -> 1 : (cf' = Transmitter);
endmodule

module error_propagation
	CONSENSUS:  init error;
	RECEIVED_SAMPLE:  init error;
	RECEIVED_3:  init error;
	RECEIVED_2:  init error;
	RECEIVED_1:  init error;
	REPLICA_3:  init error;
	REPLICA_2:  init error;
	REPLICA_1:  init error;
	SAMPLE:  init error;
	[Receiver] (((RECEIVED_1 != ok) | (RECEIVED_2 != ok)) | (RECEIVED_3 != ok)) -> 1 : (CONSENSUS' = error) & (RECEIVED_SAMPLE' = error);
	[Receiver] (((RECEIVED_1 = ok) & (RECEIVED_2 = ok)) & (RECEIVED_3 = ok)) -> 1 : (CONSENSUS' = ok) & (RECEIVED_SAMPLE' = ok);
	[Channel_3] (REPLICA_3 != ok) -> 99/100 : (RECEIVED_3' = error) + (1 - 99/100) : (RECEIVED_3' = ok);
	[Channel_3] (REPLICA_3 = ok) -> 99999/100000 : (RECEIVED_3' = ok) + (1 - 99999/100000) : (RECEIVED_3' = error);
	[Channel_2] (REPLICA_2 != ok) -> 1 : (RECEIVED_2' = error);
	[Channel_2] (REPLICA_2 = ok) -> 1 : (RECEIVED_2' = ok);
	[Channel_1] (REPLICA_1 != ok) -> 1 : (RECEIVED_1' = error);
	[Channel_1] (REPLICA_1 = ok) -> 1 : (RECEIVED_1' = ok);
	[Transmitter] (SAMPLE != ok) -> 1 : (REPLICA_3' = error) & (REPLICA_2' = error) & (REPLICA_1' = error);
	[Transmitter] (SAMPLE = ok) -> 1 : (REPLICA_3' = ok) & (REPLICA_2' = ok) & (REPLICA_1' = ok);
	[Sensor] true -> 1 : (SAMPLE' = ok);
endmodule

rewards "time"
	(cf = Receiver): 1;
	(cf = Processor): 1;
	(cf = Channel_3): 1;
	(cf = Channel_2): 1;
	(cf = Channel_1): 1;
	(cf = Transmitter): 1;
	(cf = Sensor): 1;
endrewards


