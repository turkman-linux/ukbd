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
# License

Copyright (C) 2023 Türkmen Linux and contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
