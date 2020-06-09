This is the template for CMPT 383 projects, providing some basics to get started with various languages in a a consistent environment.

## Demo Code

In `demos/`, you will find several examples of working with message queues. All of the programs start with a comment that indicates the command to run them.

All of the RPC examples do the same basic operation: do a remote procedure call by passing a [JSON](https://en.wikipedia.org/wiki/JSON) string. In each case, the request includes a string; we ask the remote code to calculate its length, and return the result as a JSON response. These should be easily extensible to have whatever information is needed in the request/response messages, and whatever login in between.


### ZeroMQ Demo Code

The `zmq_*` programs are examples of an RPC call using [ZeroMQ](https://zeromq.org/). In each case, the same operation is done: the `zmq_request.*` programs create a request consisting of a single argument (called `"string"`), encode it as JSON, make a ZeroMQ request to localhost port 5555, get the JSON response, decode the JSON, and print the result.

The `zmq_reply.*` programs start a server listening on port 5555. When a request comes in, they decode the JSON, extract the argument (`"string"`), calculate the length of the string, create a response (containing the `"length"`), encode it as JSON, and send it back to the requester.

All of these programs can interact with each other: you can start any of the `zmq_reply.*` programs, and run any of the `zmq_request.*` programs to ask it to calculate a string length.


### RabbitMQ Demo Code

Similarly, the `amqp_*` programs are examples of an RPC call using [RabbitMQ](https://www.rabbitmq.com/) (using its underlying [AMQP](https://en.wikipedia.org/wiki/Advanced_Message_Queuing_Protocol) protocol). All of these require the RabbitMQ server (Ubuntu package `rabbitmq-server`) installed, and assume they can connect with no username/password (which is the default).

The `amqp_client.*` programs create a request consisting of a single argument (called `"string"`), encode it as JSON, make a request through RabbitMQ in the `rpc_queue` queue, get the JSON response, decode the JSON, and print the result.

The `amqp_server.*` programs all listen on the `rpc_queue` queue. When a request comes in, they decode the JSON, extract the argument (`"string"`), calculate the length of the string, create a response (containing the `"length"`), encode it as JSON, and send it back to the requester.

All of these programs can interact with each other: you can start any of the `amqp_server.*` programs, and run any of the `amqp_client.*` programs to ask it to calculate a string length.
