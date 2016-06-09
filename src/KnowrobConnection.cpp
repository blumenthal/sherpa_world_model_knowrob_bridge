#include "KnowrobConnection.h"
#include "ros/ros.h"
#include <ros/console.h>

#include <iostream>
#include <iomanip>
#include <string>

#include "string"
#include "boost/format.hpp"

#include <brics_3d/core/Logger.h>


using brics_3d::Logger;

using namespace std;
using namespace json_prolog;



//FIXME add the attributes

//std::string REFERENCE_STRING = "set_reference_point({}, {},0.0 )";
std::string PATH_STRING = "generate_rsg_path_perception('%s','%s','%s',[],_)";
std::string POLY_STRING = "generate_rsg_poly_perception('%s',[],_)";


std::string POINTSET_STRING = "generate_rsg_poly_perception('%s','%s','%s',[],_)";
std::string NODE_STRING =  "generate_rsg_point_perception('%s',[%s, %s],[['type','osm:node'],['describes','WayPoint']],_)";
std::string TF_NODE_STRING =  "generate_rsg_point_perception('%s',[%s, %s,%s],[['type','osm:node_id'],['describes','WayPoint']],_)";
std::string CONNECTION_STRING = "rdf_has(Node1, 'http://knowrob.org/kb/knowrob.owl#withRSG-ID' , literal(type(xsd:string,'%s'))),\
    rdf_has(Node2, 'http://knowrob.org/kb/knowrob.owl#withRSG-ID' , literal(type(xsd:string,'%s'))),\
    create_rsg_connection_node('%s','%s',Node1,Node2,[['type','osm:way_id'],['road_id','1']],C1)";
    


std::string KnowrobConnection::createPath(std::string id,string firstId,string lastId){
    boost::format fmt = boost::format(PATH_STRING) % id % firstId % lastId; 
    return fmt.str();
}



std::string KnowrobConnection::createPoly(string id){
    boost::format fmt = boost::format(POLY_STRING) % id ; 
    return fmt.str();
}
void KnowrobConnection::createNode(string id,RSG_Node nodes, RSG_GeoPoint point){
    boost::format fmt = boost::format(NODE_STRING) % id % point.longitude % point.latitude; 
//    return fmt.str();
    assertQuery(fmt.str());
}



void KnowrobConnection::createWay(std::string id,RSG_Way way){
    brics_3d::rsg::Id start = way.nodes.front();
    brics_3d::rsg::Id end =  way.nodes.back();
    
    boost::format fmt = boost::format(PATH_STRING) % id % start.toString()% end.toString(); 
    assertQuery(fmt.str());
    int i=0;

        std::string con_id;
   //std::string ;
    for(vector<brics_3d::rsg::Id>::iterator it=way.nodes.begin();
            it != way.nodes.end(); it++) {
        
        std::ostringstream stm ;
        stm << id << "_"<<i ;
        con_id =stm.str();
        fmt = boost::format(CONNECTION_STRING) % con_id% id % it->toString() % boost::next(it)->toString(); 
        i++;
        assertQuery(fmt.str()); 
    }
        
    
    
    ///return fmt.str();
    
   //boost::format fmt = boost::format(CONNECTION_STRING) % id % point.longitude % point.latitude; 
    
}
std::string KnowrobConnection::createTransformNode(string id,float longitude,float latitude){
    boost::format fmt = boost::format(NODE_STRING) % id % longitude % latitude; 
    return fmt.str();
}


/*
std::string KnowrobConnection::createTfTransformNode(string id,float x,float y, float z){
    boost::format fmt = boost::format(TF_NODE_STRING) % id % x % y % z; 
    return fmt.str();
}
*/
std::string KnowrobConnection::createConnection(string id, string PathId,string Node1, string Node2){
    boost::format fmt = boost::format(CONNECTION_STRING) % id % PathId % Node1 % Node2; 
    return fmt.str();
}

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
      it != bdgs.end(); it++){
    PrologBindings bdg = *it;
    cout << "Found solution2: " << (bool)(it == bdgs.end()) << endl;
    cout << "A = "<< bdg["A"] << endl;
  }
}


void KnowrobConnection::onAssertNode(const sherpa_world_model_knowrob_bridge_msgs::SherpaEvent::ConstPtr& msg){
  
  
}

void KnowrobConnection::onAssertConnection(const sherpa_world_model_knowrob_bridge_msgs::SherpaEvent::ConstPtr& msg){
}

void KnowrobConnection::onAsserWay(const sherpa_world_model_knowrob_bridge_msgs::SherpaEvent::ConstPtr& msg){
}


void KnowrobConnection::setReferencePoint(float lat, float lon, float alt){
  std::stringstream query;
  query << "set_reference_point("<<lat<<", "<<lon<<", "<<alt<<" )";
  PrologQueryProxy bdgs = pl.query(query.str());
 
  for(PrologQueryProxy::iterator it=bdgs.begin();
      it != bdgs.end(); it++)
  {
    PrologBindings bdg = *it;
    cout << "Generating Reference Point: " << (bool)(it == bdgs.end()) << endl;
  }
}


void KnowrobConnection::assertQuery(std::string query){
    PrologQueryProxy bdgs  = pl.query(query);
    
  for(PrologQueryProxy::iterator it=bdgs.begin();
      it != bdgs.end(); it++)
  {
    PrologBindings bdg = *it;
  }
    
}