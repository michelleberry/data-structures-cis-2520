Assignment 6 of CIS*2520 Data Structures!

*util.c, util.h, and hashfn.c and hashfn.h were provided by the instructor - not written by me*

First, you are meant to run buildidx on name.basics.kv, title.basics.kv, and title.principals.kv to generate
.khs and .vhs versions of these files. The file .khs contains a hashed key, of which the value is the index
that the key is stored in in the matching .kv file. The .vhs file is the same thing but the value is hashed. 

Using these files, I wrote key2val and val2key. You can use these programs to search for a key when you know the
value of something, which in this case the values were movie titles or actor names. 

Then, bacon1.c is meant to be like "1 degree of kevin bacon" game. If you name an actor, it will print out a movie
that they have acted in with Kevin Bacon. 

actors.c will print out all the actors in the cast when given a movie title. 

*disclaimer*
The organization of this assignment is poor but had to be done that way because of assignment restrictions. 
I was not allowed to have extra files to hold my key2val/val2key/etc. functions but had to copy/paste them into each file. 
I am aware that this is bad practice and would not do it given the choice. 

Name: Michelle Berry
SN: 1082031 