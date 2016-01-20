#ifndef __IAI_RSG_KNOWROB_CONNECTION__
#define __IAI_RSG_KNOWROB_CONNECTION__



#include <string>
#include <iostream>
 
#include <ros/ros.h>
#include <json_prolog/prolog.h>
 
using namespace std;
using namespace json_prolog;

class KnowrobConnection{
  
  public:
    
    int init(void);
    void call_nothin();
    
private:
  Prolog pl;
  
};
  
  

#endif//__IAI_RSG_KNOWROB_CONNECTION__