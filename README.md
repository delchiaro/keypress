# keypress
With this command line application you can simulate an input from your keyboard in windows environments (win 2000 and later).<br />
You can simulate the pressure of every character in the keyboard, and probably also the special vendor keys.
<br/>
For characters list, execute 'keypress ls' or seee this page : https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx)
<br />
<br />
Usage: keypress [OPTIONS]<br />
<br />
Options:<br />
time       [MILLIS] -  t [MILLIS]  - Specify a sleep time in milliseconds before the key pressing<br />
hex        [HEX]    -  h [HEX]     - HEX will be processed as a hex number and converted following the special table<br />
win-code   [STRING] -  w [STRING]  - STRING will be processed as a string and converted following the special table<br />
list-specials       -  ls          - Show the list of special characters<br />

<br />
<br />
<br />
example:
- keypress w VK_ESCAPE t 100
- keypress w VK_VOLUME_MUTE
- keypress w VK_BROWSE_BACK
- keypress w VK_MEDIA_NEXT_TRACK
- keypress w VK_PLAY
- keypress w VK_ZOOM


