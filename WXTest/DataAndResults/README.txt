First, input the path to your DataAndResults folder. The input must be in the following format: D:/DataAndResults/
After pressing enter, if the path is in correct format, a file HELLO.txt will generate in the folder and you're ready to go.

LOG EVENTS
	Input only integers in one column in the competition order. The file must be named "EventList.txt". After that's done, click >Log events<.
	1 - deadlift
	2 - sand sack
	3 - farmers walk
	4 - truck pull
	5 - viking press

REGISTER EVENTS
	If you have completed the log, click >Register events<.
	
LOG COMPETITORS
	Input competitors in three columns in the prepared "CompetitorList.txt" file. Names must not have spaces.
	Nationalities must be denoted with country codes in caps. Check that all columns are separated by tabs. Click >Log competitors<.
	
REGISTER COMPETITORS
	If you have completed the log of the competitors, click >Register competitors<.

LOG EVENT RESULTS
	For the first event, log the order of the competitors manually in the prepared excel file.
	For each event, you need to know whick columns to fill (weight, distance, ...). Consult someone about the rules if needed.
	Copy the table (without header) in "e1.txt" file. Check that all columns are separated with tabs. Click >Log eventname results<.
	For the next events, the number 1 in file will be replaced by the sequence number of the event.
	
CALCULATE EVENT
	If you have completed the log for the event, click >Calculate eventname<. Some files will be generated:
	"e#_eventname_result.txt" will give order and points for the event.
	"e#_eventname_order.txt" will give starting order for the next event (except after the last event).
	This order can be copied to excell to easily log the next result.
	"Standing after # events.txt" will give all points and overall standing after an event.
	All these can be copied in excel file to be edited.

