<h1 align="center">Minitalk</h1>
<p align="center"><i><b>A bit better than smoke</b></i><p>

This is a simple client-server project demonstrating inter-process communication using signals in C. The server and client communicate by sending signals to each other to encode and decode messages.

## Server (`server.c`)

### Key Points:

- **Signal Handling Function (`handlemessage`):**
  - Accumulates bits received from the client.
  - Decodes bits into characters and prints the characters when a complete character is received.
  - Sends acknowledgment signals back to the client.


