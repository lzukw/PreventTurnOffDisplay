#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <WinBase.h>


using namespace std;


void printUsageAndExit(int argc, char* argv[])
{
  cerr << "Usage:" << endl;
  cerr << argv[0] << " [ seconds-to-run ]" << endl;
  cerr << endl;
  cerr << "...'seconds-to-run' indicates the time, this program should run." << endl;
  cerr << "   If no value is given for 'seconds-to-run' a default-value of 3600 is " << endl;
  cerr << "   assumed (one hour)." << endl;
  exit(EXIT_FAILURE);
}


int processCmdLineArgs(int argc, char* argv[])
{
  
  int seconds;

  if (argc > 2)
  {
    printUsageAndExit(argc, argv);
  }
  else if (argc == 2)
  {
    seconds = atoi(argv[1]);
    // if the command-line-argument cannot be parsed to an integer, atoi returned 0
    if (seconds <= 0)
    {
      printUsageAndExit(argc, argv);
    }
  }
  else
  {
    // argc == 1
    // default value, because no command-line-argument was given
    seconds = 3600;
  }


  cout << "Program will run for " << seconds << " seconds, and prevent the display from turning off." << endl;
  return seconds;
}



int main(int argc, char* argv[])
{
  // The only command-line-arguments is the number of seconds, this program 
  // should run.
  int secondsToWork = processCmdLineArgs(argc, argv);

  // Move the mouse-pointer to coordinates 0,0 (top left corner of screen).
  BOOL success =   SetCursorPos(0, 0);
  if (!success)
  {
    cerr << "WARNING: could not move mouse-pointer to top-left corner of screen" << endl;
  }

  // This call "sets the thread execution state". With the following flags, this
  // prevents the display from blanking and the system from going into sleep-mode.
  EXECUTION_STATE prevoiusExecutionState = 
          SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED);

  Sleep(secondsToWork * 1000);

  SetThreadExecutionState(prevoiusExecutionState);
}