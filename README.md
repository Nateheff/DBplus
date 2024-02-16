# DB+ - SQL RDBMS All in C++
DB+ is a lite SQL Relational Database Management System (RDBMS) which is written STRICTLY in C++. Also, DB+ uses only B+ Trees for data indexing in files.
This repository holds the exhaustive source code of DB+. 
## How to use:
### First Time:
- Copy repo
- Run bin.exe
- Enter Command: CREATE DATABASE <DATABASE_NAME> to create first database name
- You are now connected to that database
- Enter any supported SQL query (using support keywords listed below)
### Returning
- Enter the database you would like to work in this session
- You are now connected to that database
- Enter any supported SQL query (using supported keywords listed below)

## Supported SQL keywords
- CREATE
- DROP
- DELETE
- SELECT
- INSERT
- UPDATE
- Associated keywords (ex. table/database for CREATE)
## Supported Data Types
- INT
- VARCHAR
- BOOL
- CHAR
- SHORT
- FLOAT
## Example
- CREATE DATABASE example_db
- CREATE TABLE table1 ( int a, float b, short c, bool d, char e, varchar f )
- INSERT INTO table1 ( 1, 1.1, 2, 0, a, welcome to my repo! )
- SELECT * FROM table1 WHERE a = 1
- *prints row*
- DELETE * FROM table1
- DROP TABLE table1
