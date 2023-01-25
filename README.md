# Railway-Project-Continental-proposal-
The project "Train schedule" is an application that provides or updates in real time information about the train schedule of the respective day 
based on the client-server model. 

The client can ask for information about: train schedule,
departures / arrivals status, 
possible delays in departures / arrivals,
estimates of departures / arrivals,
can send the server information about possible delays in departures / arrivals.

The server processes orders and provides information about: train schedule on that day,
information about departures (delays / estimates) in the next hour at the request of a client, 
information about arrivals (delays / estimates) in the next hour at the request of a client, 
updating the train schedule according to the delay sent by the customer.

I used a TCP (Transmission Control Protocol), because it is an optimized protocol, rather, for accurate delivery than timely delivery of data.
I chose to use a socket for communication between the server and the client because it is a bidirectional communication
Having an application that involves connecting several clients to a server, they will not have to wait for their request to be fulfilled, so I used multithreading.
