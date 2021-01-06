Assignment 5 of CIS*2520 Data Structures!

Purpose: write functions to compose a hash table data type. There are functions to create the table, free the table, get & remove elements, etc.
The hash accuracy function measures how far each item is from it's hashed value. When an item is added to the hashtable, and there is already
data stored at the index the hashing function supplies, it is displaced forward from that index to the next empty space. 
Rehash was written in attempt to improve the hash accuracy. When items are removed it presents an oppurtunity to move items
to improve the hash accuracy. 
The hash table stores data a in void pointer, allowing any data type to be stored there. 
 
*Tests were not written by me*