# arduinoPiano
I built a piano using an Arduino Mega 2560. I plan for 20 keys, each with a button ('key') and a resonating speaker. 

The program works by oscillating a set speaker at the frequency for a given input note. Each key and speaker pair is mapped to a specific note. The 'getPeriodForKey' function was provided by https://gist.github.com/codeandmake/1add672bc7957135ac4e212360acbc98#file-gistfile1-txt (all other code is original). The provided function returns the period of a given note in microseconds; a note is played by setting its relative speaker both high and low in one period. I used the micros() function to set 'timers' for each note when its key is played, meaning multiple notes can be played at once. 


