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
}

RsgToKnowrobObserver::~RsgToKnowrobObserver() {

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
	
	LOG(INFO) << "RsgToKnowrobObserver::addNode: A new node with rsg id " << assignedId << "has been added";

	vector<std::string> resultValues;
	if(getValuesFromAttributeList(attributes, "osm:node_id", resultValues)){
		LOG(INFO) << "\t Node represents a OSM node with osm id =  " << resultValues[0];
	}


	return true;
}

bool RsgToKnowrobObserver::addGroup(Id parentId, Id& assignedId,
		vector<Attribute> attributes, bool forcedId) {

	/*
	 * Relevent for creation of semantoc map. Triggered by loading of OSM data.
	 * Mostly eqivalent to addNode.
	 */

	LOG(DEBUG) << "RsgToKnowrobObserver::addGroup: A new node with rsg id " << assignedId << "has been added";

	return true;
}

bool RsgToKnowrobObserver::addTransformNode(Id parentId, Id& assignedId,
		vector<Attribute> attributes,
		IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform,
		TimeStamp timeStamp, bool forcedId) {

	LOG(DEBUG) << "RsgToKnowrobObserver::addTransformNode:";

	/**
	 * {"@worldmodeltype": "RSGUpdate"
	 * ,"node": 
	 * 	{
	 * 	"@graphtype": "Connection",
	 * 	"@semanticContext": "Transform",
	 * 	"attributes": [{"key": "osm:tf","value": "pose"}],
	 * 	"history": [
	 * 		{"stamp": 
	 * 			{"@stamptype": "TimeStampUTCms",
	 * 			"stamp": 1453384154636.7109},
	 * 			"transform": 
	 * 				{"matrix": [[1.0000000000000000,0.0000000000000000,0.0000000000000000,794210.91230174468],[0.0000000000000000,1.0000000000000000,0.0000000000000000,475242.69356737687],[0.0000000000000000,0.0000000000000000,1.0000000000000000,0.0000000000000000],[0.0000000000000000,0.0000000000000000,0.0000000000000000,1.0000000000000000]],
	 * 				 "type": "HomogeneousMatrix44",
	 * 				 "unit": "m"}}
	 * 		],
	 * 	"id": "317628c7-ea7f-4991-b0c3-bfaf9ad1da03"},
	 * 	"operation": "CREATE",
	 * 	"parentId": "e379121f-06c6-4e21-ae9d-ae78ec1986a1"}
	*/
	
	/*
	 * Relevent for creation of semantoc map. Triggered by loading of OSM data.
	 * Potentially triggerd when a new images "snapshot" within a mission
	 * is saved in the DCM.
	 */

	return false;

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

	/*
	 * Possibly relevent for creation of semantic map. Triggered by loading of OSM data.
	 */

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

	LOG(DEBUG) << "RsgToKnowrobObserver::addConnection:";


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

	return true;
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
