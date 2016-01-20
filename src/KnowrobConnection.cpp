#include "KnowrobConnection.h"
#include "ros/ros.h"
#include <ros/console.h>

using namespace std;
using namespace json_prolog;


int KnowrobConnection::init(void){
  while(!ros::service::waitForService("json_prolog/query", 1000))
  {
    ROS_WARN_ONCE("json_prolog does not seem to run.");
    ROS_WARN_ONCE("... Retrying");
  }
  ROS_INFO("json_prolog connected.");
  return 0;
}


void KnowrobConnection::onSherpaEvent(const sherpa_world_model_knowrob_bridge_msgs::SherpaEvent::ConstPtr& msg){
}

void KnowrobConnection::call_nothin()
{
 
  PrologQueryProxy bdgs = pl.query("add_sherpa_object_perception('asdasdasd', A)");
 
  for(PrologQueryProxy::iterator it=bdgs.begin();
      it != bdgs.end(); it++)
  {
    PrologBindings bdg = *it;
    cout << "Found solution2: " << (bool)(it == bdgs.end()) << endl;
    cout << "A = "<< bdg["A"] << endl;
  }
}

