# freefish
An ascii fishtank for the linux terminal. I am very new to C++, but my code shouldn't be awful.

# using freefish
Place the executable where you like and create the freefish folders and resources mentioned later in this readme. Then, run freefish with the following arguments to produce the desired result.

--help    -h  Displays a help menu similar to this.
--list    -l  lists avaliable fish and tanks. This simply uses ls in the directories /usr/share/freefish/fish and usr/share/freefish/background so it is actually rather limited as of now.
--speed   -s  Sets the legnth of each frame in microseconds.
--tank    -t  Uses single following argument as fishtank file by loading the background and foreground from their respecitve directories.
--fish    -f  uses following arguments not beginning with a '-' as fish to spawn in the tank. Typing a fish multiple times will load it multiple times. The fish typed first will always be rendered on top of the fish typed after.

# compiling freefish
Freefish must be compiled in C++ 11 or later. A codebocks project file is included which may be of use if you want to compile freefish in an IDE.

# file structure
The executable can be ran from anywhere, but you can place it in /usr/bin if you please

Freefish looks for files in four folders
for fish /usr/share/freefish/fish
for flipped fish /usr/share/freefish/flip
for backgrounds /usr/share/freefish/background
for foreground /usr/share/freefish/background

I'd recomend not putting a file extention after the resource files, but if you do you will have to include that in your argument

# file formatting

Files are simply uniform text with color codes. A new line signals a new line of the resource while an empty line signifies a new frame.

The following could be read as a fish or part of a tank that is two charcters tall, three charcters wide, and each frame changes from a block of 'x's to 'o's to 'z's 
  xxx
  xxx

  ooo
  ooo

  zzz
  zzz
Color codes can be places in like so and everything following that color code will be that color until another code is used. The following would make the resource cycle from a block of green 'x's to yellow 'o's to red 'z's

# resource creation
You can use your favorite text editor or you can use the zlib liscensed program created by my brother. It is very nifty, but as of right now has no error handling.
