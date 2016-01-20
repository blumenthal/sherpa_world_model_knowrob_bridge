#include "KnowrobConnection.h"

using namespace std;
using namespace json_prolog;


int KnowrobConnection::init(void){
  
  return 0;
}


void KnowrobConnection::call_nothin()
{
 
  PrologQueryProxy bdgs = pl.query("member(A, [1, 2, 3, 4]), B = ['x', A], C = foo(bar, A, B)");
 
  for(PrologQueryProxy::iterator it=bdgs.begin();
      it != bdgs.end(); it++)
  {
    PrologBindings bdg = *it;
    cout << "Found solution2: " << (bool)(it == bdgs.end()) << endl;
    cout << "A = "<< bdg["A"] << endl;
    cout << "B = " << bdg["B"] << endl;
    cout << "C = " << bdg["C"] << endl;
  }
}

