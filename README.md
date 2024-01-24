# minitalk
The goal of this project is to create two executables: a server and a client.<br>
The client will send information (a string) to the server using UNIX signals.<br>
The server must correctly receive and interpret this information, then display it.<br>

### Mandatory

- Produce `server` & `client` executables
- `client` must communicate a string passed as a parameter to `server` *(referenced by its process ID)* which then displays it
- Use `SIGUSR1` & `SIGUSR2` signals **ONLY**

### Bonus

- Add reception acknowledgement system
- Support Unicode characters
