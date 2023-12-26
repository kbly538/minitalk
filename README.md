<h1 align="center">Minitalk</h1>
<p align="center"><i><b>A bit better than smoke</b></i><p>

 <p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/kbly538/minitalk?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/badge/total_lines-178-green" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/kbly538/minitalk?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/kbly538/minitalk?color=green" />
</p>

---

This is a simple client-server project demonstrating inter-process communication using signals in C. The server and client communicate by sending signals to each other to encode and decode messages.

## Server

### Key Points:

- **Signal Handling Function (`handlemessage`):**
  - Accumulates bits received from the client.
  - Decodes bits into characters and prints the characters when a complete character is received.
  - Sends acknowledgment signals back to the client.

## Client

### Key Points:

- **Command-Line Argument Verification (`args_verifier`):**
  - Verifies the correctness of command-line arguments.
  - Checks for a valid PID and the presence of a message. Abcense of a valid pid means there is an ongoing job.

- **Sending Message Bits to Server (`send_message`):**
  - Sends bits of the message to the server using signals.
  - Moves to the next character when all bits are sent.

- **Acknowledgment Signal Handling (`acknowledge`):**
  - Handles acknowledgment signals from the server.
  - Exits the client when a complete message is acknowledged.

## Example:

1. **Run the server:**

   ```bash
   make
   ./server
2. **In another terminal run the client with server PID which will be printed in the server's terminal:**
   ```bash
   ./client [server_PID] "Hello, Server!"
   ```

