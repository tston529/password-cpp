# password-cpp
Writes stdin to the terminal as a string of asterisks.

usage:
```c++
#include "password.hpp"

...

std::string pass = password::read_password();

```

To-do: 
[x] Handle backspaces/carriage returns
[ ] Handle arrow keys
    [ ] L/R - back and forth
        [ ] Windows
        [ ] 'Nix
    [ ] U/D - Ignored
        [ ] Windows
        [ ] 'Nix
[ ] std::string is not secure, want to switch to char buffer