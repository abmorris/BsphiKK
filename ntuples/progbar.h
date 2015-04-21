#include <time.h>
#include <iostream>
#include <iomanip>
void progbar(Int_t ievent, Int_t nevents, Int_t barwidth=80)
{
  Int_t perc = (Int_t)(100*ievent/nevents)+1;
  cout << "\r [";
  for (Int_t ibar = 0; ibar < (perc*barwidth)/100; ibar++)
    cout << "#";
  for (Int_t ibar = (perc*barwidth)/100; ibar < barwidth; ibar++)
    cout << "-";
  cout << "] " << perc << "% " << flush;
}
void timestamp(const Int_t t0)
{
  Int_t t1 = time(0);
  cout << (t1-t0)/60 << ":" << setw(2) << setfill('0') << (t1-t0)%60 << flush;
}