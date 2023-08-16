# Planets
A C++ simulation of Newton's Law of Gravitation.

## Building From Source
### Linux:

#### Step 1: Clone this repository and `cd` into it
```
git clone https://github.com/AzeezDa/Planets.git
cd Planets
```

#### Step 2: Build with CMake
```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```
This step will take a bit of time.

Note: You can use `-DCMAKE_BUILD_TYPE=Debug` (which is the default) instead to add in the debug symbols.

#### Step 3: Done!
You can now use the `Planets` executable to run the Lua universe file. For example if you are inside the `build/` directory:
```
./Planets ../Examples/Twins.lua
```
should display the spinning twin bodies.


### Windows
If you are using WSL, you can follow the Linux steps above. If no window pops up at step 3 then you should make sure that you have installed XLaunch or similar.


## The Universe Through Lua
To make your own *universe*, make a `.lua` file and inside it create a table called `Universe` (case sensitive). You can populate that table with tables that describe the body's mass (as a number), position (as a table), velocity (as a table) or color (as a hexcolor or words). The accepted color words are: `red` ,`green` ,`blue` ,`yellow` ,`magenta` ,`cyan` ,`white` ,`grey` and `orange`

See the [`Examples/`](/Examples) directory for more guidance.

## Configuring the Universe
You can configure the graphical settings of the simulation for each *universe* you create in the Lua file.

In your universe Lua file create a table called `Config` that you can populate with:
- `windowSize = {1080, 720}` - The default size of the created window
- `fpsLimit = 60` - The maximum Frames Per Second for the simulation
- `AALevel = 4` - The Anti-aliasing level for the simulation

The values given above the are the default and if the key for the configuration is not present in the table then those values will be used instead.

See the [`Examples/TwinsWithConfig.lua`](/Examples/TwinsWithConfig.lua) file for more guidance.