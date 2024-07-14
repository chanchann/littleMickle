WebSocket++ includes two major object types. The `endpoint` and the `connection`


The connection stores information specific to each WebSocket session.

Note: Once a connection is launched, there is no link between the endpoint and the connection. All default settings are copied into the new connection by the endpoint. Changing default settings on an endpoint will only affect future connections.

Connections do not maintain a link back to their associated endpoint. Endpoints do not maintain a list of outstanding connections. If your application needs to iterate over all connections it will need to maintain a list of them itself.


## Terminology: Endpoint Config

WebSocket++ endpoints have `a group of settings` that may be configured at `compile time` via the config template parameter. 

A config is a struct that contains types and static constants that are used to produce an endpoint with specific properties. Depending on which config is being used the endpoint will have different methods available and may have additional third party dependencies.

The endpoint role takes a template parameter called config that is used to configure the behavior of endpoint at compile time. 

For this example we are going to use a default config provided by the library called asio_client, provided by <websocketpp/config/asio_no_tls_client.hpp>. 

This is a client config that uses boost::asio to provide network transport and does not support TLS based security.

Combine a config with an endpoint role to produce a fully configured endpoint.

```cpp
typedef websocketpp::client<websocketpp::config::asio_client> client
```

Create endpoint wrapper object that handles initialization and setting up the `background thread`.

In `perpetual mode` the endpoint's processing loop will not exit automatically when it has no connections

This is important because we want this endpoint to remain active while our application is running and process requests for new WebSocket connections on demand as we need them. 

## Opening WebSocket connections

Adds two new commands to utility_client. The ability to open a new connection and the ability to `view information about a previously opened connection`. 

Every connection that gets opened will be `assigned an integer connection id` that the user of the program can use to interact with that connection.

- New Connection Metadata Object

In order to track information about each connection a connection_metadata object is defined. 

This object stores the `numeric connection id` and `a number of fields` that will be filled in as the connection is processed. 

Initially this includes the `state of the connection (opening, open, failed, closed, etc)`, the `original URI` connected to, an `identifying value` from the server, and a `description of the reason for connection failure/closure`.

The websocket_endpoint object has gained some new data members and methods. 

It now tracks a mapping between connection IDs and their associated metadata as well as the next sequential ID number to hand out. 

## The connect method

The connect() method `initiates a new connection`. The get_metadata method retrieves metadata given an ID.

A new WebSocket connection is initiated via a three step process. 

1. A connection request is created by endpoint::get_connection(uri). 

2. the connection request is configured.

3. the connection request is submitted back to the endpoint via endpoint::connect() which adds it to the queue of new connections to make.

WebSocket++ keeps track of connection related resources using a reference counted shared pointer. The type of this pointer is endpoint::connection_ptr. 

A connection_ptr allows direct access to information about the connection and allows changing connection settings. 

Because of this direct access and their internal resource management role within the library it is not safe for end applications to use connection_ptr except in the specific circumstances.

- When is it safe to use connection_ptr?

1. After endpoint::get_connection(...) and before endpoint::connect(): get_connection returns a connection_ptr. It is safe to use this pointer to configure your new connection. Once you submit the connection to connect you may no longer use the connection_ptr and should discard it immediately for optimal memory management.

2. During a handler: WebSocket++ allows you to register hooks / callbacks / event handlers for specific events that happen during a connection's lifetime. During the invocation of one of these handlers the library guarantees that it is safe to use a connection_ptr for the connection associated with the currently running handler.

## connection_hdl

Because of the `limited thread safety` of the connection_ptr the library also provides a `more flexible connection identifier`, the connection_hdl. 

The connection_hdl has type websocketpp::connection_hdl and it is defined in <websocketpp/common/connection_hdl.hpp>. 

Note that unlike connection_ptr this is `not dependent on the type or config of the endpoint`. Code that simply stores or transmits connection_hdl but does not use them can include only the header above and can treat its hdls like values.

Connection handles `are not used directly`. They are used by endpoint methods to identify the target of the desired action. For example, the endpoint method that sends a new message will `take as a parameter the hdl of the connection to send the message to`.

- When is it safe to use connection_hdl? 

connection_hdls may be used at any time from any thread. They may be copied and stored in containers. Deleting a hdl will not affect the connection in any way. 

Handles may be upgraded to a connection_ptr during a handler call by using endpoint::get_con_from_hdl(). The resulting connection_ptr is safe to use for the duration of that handler invocation.

- connection_hdl FAQs

connection_hdls are guaranteed to be unique within a program. 

Multiple endpoints in a single program will always create connections with unique handles.

Using a connection_hdl with a different endpoint than the one that created its associated connection will result in undefined behavior.

Using a connection_hdl whose associated connection has been closed or deleted is safe. The endpoint will return a specific error saying the operation couldn't be completed because the associated connection doesn't exist. [TODO: more here? link to a connection_hdl FAQ elsewhere?]

websocket_endpoint::connect() begins by calling endpoint::get_connection() using a uri passed as a parameter. Additionally, an error output value is passed to capture any errors that might occur during. If an error does occur an error notice is printed along with a descriptive message and the -1 / 'invalid' value is returned as the new ID.

## error handling: exceptions vs error_code

WebSocket++ uses the error code system defined by the C++11 <system_error> library. It can optionally fall back to a similar system provided by the Boost libraries. All user facing endpoint methods that can fail take an error_code in an output parameter and store the error that occured there before returning. An empty/default constructed value is returned in the case of success.

Exception throwing varients All user facing endpoint methods that take and use an error_code parameter have a version that throws an exception instead. These methods are identical in function and signature except for the lack of the final ec parameter. The type of the exception thrown is websocketpp::exception. This type derives from std::exception so it can be caught by catch blocks grabbing generic std::exceptions. The websocketpp::exception::code() method may be used to extract the machine readable error_code value from an exception.

For clarity about error handling the utility_client example uses exclusively the exception free varients of these methods. Your application may choose to use either.

## Registering handlers

Handlers can be registered at the `endpoint level` and at the `connection level`. Endpoint handlers are copied into new connections as they are created. `Changing an endpoint handler will affect only future connections`. Handlers registered at the connection level will be bound to that specific connection only.

The signature of handler binding methods is the same for endpoints and connections. 

The format is: set_*_handler(...). Where * is the name of the handler.

`set_open_handler(...)` will set the handler to be called when a new connection is open. 

`set_fail_handler(...)` will set the handler to be called when a connection fails to connect.

All handlers `take one argument`, a callable type that can be converted to a std::function with the correct count and type of arguments. You can pass free functions, functors, and Lambdas with matching argument lists as handlers. 

```
Enter Command: connect not a websocket uri
> Connect initialization error: invalid uri
Enter Command: show 0
> Unknown connection id 0
Enter Command: connect ws://echo.websocket.org
> Created connection with id 0
Enter Command: show 0
> URI: ws://echo.websocket.org
> Status: Open
> Remote Server: Kaazing Gateway
> Error/close reason: N/A
Enter Command: connect ws://wikipedia.org
> Created connection with id 1
Enter Command: show 1
> URI: ws://wikipedia.org
> Status: Failed
> Remote Server: Apache
> Error/close reason: Invalid HTTP status.
```

## Closing connections

Adds a command that allows you to close a WebSocket connection and adjusts the quit command so that it cleanly closes all outstanding connections before quitting.

## WebSocket close codes & reasons

During the close handler call WebSocket++ connections offer the following methods for accessing close handshake information:

connection::get_remote_close_code(): Get the close code as reported by the remote endpoint

connection::get_remote_close_reason(): Get the close reason as reported by the remote endpoint

connection::get_local_close_code(): Get the close code that this endpoint sent.

connection::get_local_close_reason(): Get the close reason that this endpoint sent.

connection::get_ec(): Get a more detailed/specific WebSocket++ error_code indicating what library error (if any) ultimately resulted in the connection closure.

```cpp
m_endpoint.close(metadata_it->second->get_hdl(), code, "", ec);
```

endpoint::close is a `thread safe` method that is used to `asynchronously dispatch a close signal to the connection` with the given handle. When the operation is complete the connection's close handler will be triggered.

```cpp
Enter Command: connect ws://localhost:9002
> Created connection with id 0
Enter Command: close 0 1001 example message
Enter Command: show 0
> URI: ws://localhost:9002
> Status: Closed
> Remote Server: WebSocket++/0.4.0
> Error/close reason: close code: 1001 (Going away), close reason:  example message
Enter Command: connect ws://localhost:9002
> Created connection with id 1
Enter Command: close 1 1006
> Error initiating close: Invalid close code used
Enter Command: quit
> Closing connection 1
```

## Sending and receiving messages

- WebSocket message types (opcodes)

WebSocket messages have types indicated by their opcode. The protocol currently specifies two different opcodes for data messages, text and binary.

Text messages represent UTF8 text and will be validated as such. Binary messages represent raw binary bytes and are passed through directly with no validation.

WebSocket++ provides the values websocketpp::frame::opcode::text and websocketpp::frame::opcode::binary that can be used to direct how outgoing messages should be sent and to check how incoming messages are formatted.

- Sending Messages

Messages are sent using endpoint::send. This is a `thread safe` method that may be called from anywhere to queue a message for sending on the specified connection. There are three send overloads for use with different scenarios.

Each method takes a connection_hdl to indicate which connection to send the message on as well as a frame::opcode::value to indicate which opcode to label the message as. All overloads are also available with an exception free varient that fills in a a status/error code instead of throwing.

The first overload, connection_hdl hdl, std::string const & payload, frame::opcode::value op, takes a std::string. The string contents are copied into an internal buffer and can be safely modified after calling send.

The second overload, connection_hdl hdl, void const * payload, size_t len, frame::opcode::value op, takes a void * buffer and length. The buffer contents are copied and can be safely modified after calling send.

The third overload, connection_hdl hdl, message_ptr msg, takes a WebSocket++ message_ptr. This overload allows a message to be constructed in place before the call to send. It also may allow a single message buffer to be sent multiple times, including to multiple connections, without copying. Whether or not this actually happens depends on other factors such as whether compression is enabled. The contents of the message buffer may not be safely modified after being sent.




