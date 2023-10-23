# Uinput keyboard library

## Building:
run `make` for build library and service

## Usage:
1. Run service as root
2. write client
3. Compile your client and run

## Language binding:
python
```python
import libukbd
...
libukbd.event(code,status)
libukbd.press(code)
libukbd.send(code)
libukbd.release(code)
```
C / C++
```C
#include <libukbd.h>
...
void ukbd_event(int code, int status);
void ukbd_press(int code);
void ukbd_send(int code);
void ukbd_release(int code);
```
Vala
```C++
// Compile with --pkg libukbd
...
void ukbd.event(int code, int status);
void ukbd.press(int code);
void ukbd.send(int code);
void ukbd.release(int code);
```
