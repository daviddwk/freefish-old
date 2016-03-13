# freefish
A free ASCII fish tank for the Linux terminal under the GPLv3. I am very new to C++, but my code shouldn't be awful.

# installing freefish
First, simply run `make` in the cloned freefish directory. This will create an executable file `freefish` in the directly. You can place and run the executable from anywhere. If you wish to always have it at your disposal you can copy the executable to `/usr/bin` so you may run freefish by typing freefish into your shell at any time.

If you wish to manually compile, make sure you are compiling freefish in C++11 or later.

Next, you must set up the proper series of folders with properly formatted resources in them. These folders are currently hardcoded to be in `/usr/share/freefish`, but you can easily modify this before compiling if you wish to have a different directory. The folders and file formatting are explained below, but if you wish to use my sample resources you can start using freefish right off of the bat. Just copy the contents of the sample folder into `/usr/share/freefish`.

# using freefish
Place the executable where you like and create the freefish folders and resources mentioned later in this readme. Then, run freefish with the following arguments to produce the desired result.

```
--help    -h  Displays a help menu similar to this.

--list    -l  lists available fish and tanks. This simply uses ls in the
              directories /usr/share/freefish/fish and
              usr/share/freefish/background so it is actually rather limited as
              of now.

--speed   -s  Sets the length of each frame in microseconds.

--tank    -t  Uses single following argument as fishtank file by loading the
              background and foreground from their respective directories.

--fish    -f  uses following arguments not beginning with a '-' as fish to
              spawn in the tank. Typing a fish multiple times will load it
              multiple times. The fish typed first will always be rendered on
              top of the fish typed after.
```

# file structure
The executable can be ran from anywhere, but you can place it in `/usr/bin` if you please.

Freefish looks for files in four folders:

* for fish `/usr/share/freefish/fish`
* for flipped fish `/usr/share/freefish/flip`
* for backgrounds `/usr/share/freefish/background`
* for foreground `/usr/share/freefish/foreground`

When loading a fish, freefish looks for a file of that name in the folders fish and flip, so it is important to format them correctly. Loading tanks works similarly where the background of the tank is in the background folder, and the foreground of the tank is in the foreground folder.

I'd recommend not putting a file extension after the resource files, but if you do you will have to include the file extension in your argument.

# file formatting
Resources are to be made of lines of uniform length and with frames of a uniform number of lines. Each line is separated by a return and each frame is separated by an empty line. Color codes can also be used in these files and will not be counted as a character, but two or more color codes should never be used in a row. Color codes are to be formatted as such `^[[94m` where the initial `^[` is an escape character.

The fish and flip files for any type of fish must have the same number of frames, number of lines per frame, and number of characters for character per frame. The foreground and background files for a tank must have the same number of lines per frame and the same number of character per line, but do not need to have the same number of frames.

If this is confusing take a look at the resources in the sample folder, or use the program mentioned below.

When rendering, the foreground has first priority, the fish have second, and the background has third. Spaces are transparent, so only the background's spaces will be rendered. If a foreground has spaces what is behind it will be rendered and if a fish has spaces, the same will happen.

# file creation
You can use your favorite text editor or you can use [asciieditor][], which was created by my brother. It is very nifty, but as of right now, it has no error handling. It is under the zlib license.i

If you make any resourse files feel free to make a commit. If there is a better program to create these files than plese send me a message.
[asciieditor]: https://github.com/daviddwk/asciieditor
