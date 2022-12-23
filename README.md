<!-- SUMMARY -->
## Summary

This program implements T9 predictive text, a text input mode developed originally for cell phones and still used for numeric keypads. Each number from 2-9 on the keypad represents three or four letters, the number 0 represents a space, and 1 represents a set of symbols such as { , . ! ? } etc. The numbers from 2-9 represent letters as follows:

2 => ABC
3 => DEF
4 => GHI
5 => JKL
6 => MNO
7 => PQRS
8 => TUV
9 => WXYZ

The program takes a dictionary as an argument, builds the T9 trie using the words in the dictionary, and starts an interactive session. During the session, the user can type numbers and the program outputs the word corresponding to the sequence of numbers entered. Typing a T9 code followed by one or more '#' characters will return any words with the same T9 sequence. 
