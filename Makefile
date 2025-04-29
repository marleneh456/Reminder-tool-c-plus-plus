reminder.exe: reminder.cpp
	g++ -o reminder.exe reminder.cpp

clean:
	del reminder.exe
