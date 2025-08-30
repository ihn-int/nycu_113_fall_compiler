# hw2 report

|Field|Value|
|-:|:-|
|Name|陳均凱|
|ID|11155001|

## How much time did you spend on this project

> e.g. 2 hours.

I spent roughly 15 hours on this project, but the number isn't very precise.

## Project overview

> Please describe the structure of your code and the ideas behind your implementation in an organized way. \
> The point is to show us how you deal with the problems. It is not necessary to write a lot of words or paste all of your code here. 

The implementation consists of two parts: declarations and rules. Two parts have the same order of the information provided by syntactic definitions.

Basically, just follow the information provided and everything will be done. There are only some details that need attention, such as associativity and priorities of the operators.

All symbols are represented in uppercase letters, and there are some naming conventions to indicate the meaning of the symbols:

- Prefix "NT_" means this symbol is a non-terminal symbol.
- Prefix "KW_" means this symbol is a terminal symbol and is a keyword.
    - The parser is modified first, so the tokens are different from the scanner.
- Suffix "_OPT" means this symbol may be an empty string.
- Suffix "_LIST" means this symbol consists of one or more idnetical symbols.
- Most other content is named according to the information provided.

In addtion, some additional non-terminal symbols are used to simplify the grammer.

## What is the hardest you think in this project

> Not required, but bonus point may be given.

Debbuging is a hard part. Since there is no information of the program, it's difficult to know the status of it when itr encounters a mistake.

I really should learn how to use gdb.

## Feedback to T.A.s

> Not required, but bonus point may be given.

It has nothing to do with the homework itself, but I suggest that the filename of the test cases could include the file extension, so that Windows could recognize it and open it with the corresponding editor.