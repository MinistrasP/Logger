# Logger

Program logs data into a database using sqlite3. Database is stored as myLogger.db at /var/log/

Usage: myLogger option

Where option is:

-h - prints help  
-c - creates a database with a table (Log) if it doesn't already exist  
-i - level data - where level is the level of message (1-INFO,2-WARNING,3-ERROR), and data is the input data  
-p - prints all data from table (Log)  
-d - deletes all data  
-a - engages automatic mode, which writes a level 1 (INFO) message to database every second. Data is a number which starts from 0 and ends with 9, incrementing by 1 each second  

Database table (Log) consists of 5 columns:
1. Auto incrementing ID
2. Date
3. Time
4. Message level (1-INFO,2-WARNING,3-ERROR)
5. Message input data
