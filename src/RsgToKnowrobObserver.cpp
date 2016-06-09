/******************************************************************************
 * BRICS_3D - 3D Perception and Modeling Library
 * Copyright (c) 2015, KU Leuven
 *
 * Authors: Sebastian Blumenthal
 *          Benjamin  Brieber
 *
 *
 * This software is published under a dual-license: GNU Lesser General Public
 * License LGPL 2.1 and Modified BSD license. The dual-license implies that
 * users of this code may choose which terms they prefer.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License LGPL and the BSD license for
 * more details.
 *
 ******************************************************************************/

#include "RsgToKnowrobObserver.h"
#include <brics_3d/core/Logger.h>


using brics_3d::Logger;

namespace brics_3d {
namespace rsg {

RsgToKnowrobObserver::RsgToKnowrobObserver(WorldModel* wm) : wm(wm) {
	// init menbers here
  kb_con = new KnowrobConnection();
}

RsgToKnowrobObserver::~RsgToKnowrobObserver() {

  delete kb_con;
}

bool RsgToKnowrobObserver::addNode(Id parentId, Id& assignedId,
		vector<Attribute> attributes, bool forcedId) {

	/*
	 * Relevent for creation of semantic map. Triggered by loading of OSM data.
	 * Potentially triggerd when a new images "snapshot" within a mission
	 * is saved in the DCM.
	 */
	
	//rsg_parent_id
	//rsg_assigned_id
	
	
	/*
	 * 
	 * {
	 * "@worldmodeltype": "RSGUpdate" //
	 * "node": 
	 * 	{
	 * 	"@graphtype": "Node",//"Connection"
	 * 	"attributes": 
	 * 		[{"key": "osm:node_id","value": 360484115}],
	 * 	"id": "00000000-0000-0000-0000-0000157c8d13"},
	 * 	"operation": "CREATE",
	 * 	"parentId": "3ea6ce2c-7a8a-485b-9eb7-2cd57c8a24bf"
	 * 	}
	 */
	Attribute att;
	
	Id iddd;
	
	//iddd.
	LOG(ERROR) << "RsgToKnowrobObserver::addNode: A new node with rsg id " << assignedId << "has been added";

	vector<std::string> resultValues;
	if(getValuesFromAttributeList(attributes, "osm:node_id", resultValues)){
        RSG_Node node;
        node.attrs = attributes;
		LOG(ERROR) << "\t Node represents a OSM node with osm id =  " << resultValues[0];
        if(poseNodes.count( parentId) != 0){
            kb_con->createNode(parentId.toString(), attrNodes[assignedId],poseNodes[parentId]);
            //LOG(ERROR) << "Query"<< query;
            
        }
	}else if (getValuesFromAttributeList(attributes, "sherpa:rescue_victim_id", resultValues)){
		LOG(ERROR) << "\t Node represents a VICTIM node with osm id =  " << resultValues[0];

	}
	return true;
}

bool RsgToKnowrobObserver::addGroup(Id parentId, Id& assignedId,
		vector<Attribute> attributes, bool forcedId) {

	/*
	 * Relevent for creation of semantoc map. Triggered by loading of OSM data.
	 * Mostly eqivalent to addNode.
	 */
    vector<std::string> resultValues;
    if(getValuesFromAttributeList(attributes, "osm:node_id", resultValues)){
        RSG_Node node;
        node.attrs = attributes;
        attrNodes[assignedId] = node;
        LOG(ERROR) << "\t Warning GROUP represents a OSM node with osm id =  " << resultValues[0];
    }
	LOG(ERROR) << "RsgToKnowrobObserver::addGroup: A new node with rsg id " << assignedId << "has been added";

	return true;
}

bool RsgToKnowrobObserver::addTransformNode(Id parentId, Id& assignedId,
		vector<Attribute> attributes,
		IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform,
		TimeStamp timeStamp, bool forcedId) {

	LOG(ERROR) << "RsgToKnowrobObserver::addTransformNode:";
    //double x,y,z,roll,pitch,yaw;
    const double* ts = transform->getRawData();
    double x = ts[12];
    double y = ts[13];
    double z = ts[14];
    RSG_GeoPoint point;
    point.longitude =x;
    point.latitude =y;
    point.altitude =z;
    
    poseNodes[assignedId] = point;
    
    //HomogeneousMatrix44::matrixToXyzRollPitchYaw(transform,x,y,z,roll,pitch,yaw);
    //kb_con->createNode(parentId, x,y,z);

	return true;

}

bool RsgToKnowrobObserver::addUncertainTransformNode(Id parentId,
		Id& assignedId, vector<Attribute> attributes,
		IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform,
		ITransformUncertainty::ITransformUncertaintyPtr uncertainty,
		TimeStamp timeStamp, bool forcedId) {

	return true;
}


bool RsgToKnowrobObserver::addGeometricNode(Id parentId, Id& assignedId,
		vector<Attribute> attributes, Shape::ShapePtr shape,
		TimeStamp timeStamp, bool forcedId) {

    //FIXME is this used or do we use the sam construct as for connections
    LOG(ERROR) << "RsgToKnowrobObserver::addGeometricNode:";

	return true;
}

bool RsgToKnowrobObserver::addRemoteRootNode(Id rootId, vector<Attribute> attributes) {

	return true;
}

bool RsgToKnowrobObserver::addConnection(Id parentId, Id& assignedId, vector<Attribute> attributes, vector<Id> sourceIds, vector<Id> targetIds, TimeStamp start, TimeStamp end, bool forcedId) {

	/*
	 * Relevent for creation of semantic map. Triggered by loading of OSM data.
	 * This is used for osm "ways".
	 * 
	 * 
	 *  {"@worldmodeltype": "RSGUpdate","node": {"@graphtype": "Node","attributes": [{"key": "osm:way_id","value": 4012537},{"key": "osm:highway","value": "tertiary"},{"key": "osm:junction","value": "roundabout"},{"key": "osm:maxspeed","value": 50},{"key": "osm:name","value": "Rathausallee"},{"key": "osm:source:maxspeed","value": "DE:urban"}],"id": "00000000-0000-0000-0000-0000003d39f9"},"operation": "CREATE","parentId": "e379121f-06c6-4e21-ae9d-ae78ec1986a1"}
	 */

    vector<std::string> resultValues;
    if(getValuesFromAttributeList(attributes, "osm:way_id", resultValues)){
        LOG(ERROR) << "RsgToKnowrobObserver::";
        
        for(vector<Id>::iterator it=targetIds.begin();
            it != targetIds.end(); it++) {
            if (! attrNodes.count(*it)>0){
                LOG(ERROR) << "connection node not found";
                
            }
                LOG(ERROR) << "connection node found";
            
        }

        /**
        RSG_Node node;
        node.attrs = attributes;
        LOG(ERROR) << "\t Node represents a OSM node with osm id =  " << resultValues[0];
        if(poseNodes.count( parentId) != 0){
            std::string query = kb_con->createNode(parentId.toString(), attrNodes[id],poseNodes[parentId]);
            LOG(ERROR) << "Query"<< query;
            
        }
        */
    }


	return true;
}

bool RsgToKnowrobObserver::setNodeAttributes(Id id,
		vector<Attribute> newAttributes, TimeStamp timeStamp ) {

	/*
	 * Pecepetion event w.r.t to a changed attribute
	 * goes here...
	 */

	return true;
}

bool RsgToKnowrobObserver::setTransform(Id id,
		IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform,
		TimeStamp timeStamp) {

	/*
	 * Pecepetion event w.r.t to a changed pose goes here...
	 */
    LOG(ERROR) << "RsgToKnowrobObserver::setTransform FIXME not used now but fix meeee:";
    //FIXME is this used?
	return false;
}

bool RsgToKnowrobObserver::setUncertainTransform(Id id,
		IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform,
		ITransformUncertainty::ITransformUncertaintyPtr uncertainty,
		TimeStamp timeStamp) {

	return true;
}

bool RsgToKnowrobObserver::deleteNode(Id id) {

	return true;
}

bool RsgToKnowrobObserver::addParent(Id id, Id parentId) {
    if(attrNodes.count( id) != 0 && poseNodes.count( parentId) != 0){
        kb_con->createNode(parentId.toString(), attrNodes[id],poseNodes[parentId]);
        return true;
    }
        LOG(ERROR) << "NO VALID Parent child relation:";

    return false;
}

bool RsgToKnowrobObserver::removeParent(Id id, Id parentId) {

	return true;
}
void RsgToKnowrobObserver::setKnowrobConnection(KnowrobConnection* kb)
{

	kb_con = kb;//
}

} /* namespace rsg */
} /* namespace brics_3d */

/* EOF */
