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

#include "RsgCommandObserver.h"
#include <brics_3d/core/Logger.h>


using brics_3d::Logger;

namespace brics_3d {
namespace rsg {

bool RsgCommandObserver::setNodeAttributes(Id id,
		vector<Attribute> newAttributes, TimeStamp timeStamp ) {

    vector<std::string> resultValues;
    if(getValuesFromAttributeList(newAttributes, "sherpa:command", resultValues)){
        LOG(ERROR) << "Received command";
        commandPub.publish(msg);
        
    }
    if(getValuesFromAttributeList(newAttributes, "sherpa:command_interpetation_success", resultValues)){
        LOG(ERROR) << "Received interpreted command";
        interpretedCommandPub.publish(msg);
        
        
    }

	return true;
}










bool RsgCommandObserver::addNode(Id parentId, Id& assignedId,
		vector<Attribute> attributes, bool forcedId) {

	vector<std::string> resultValues;
    if(getValuesFromAttributeList(attributes, "sherpa:command", resultValues)){
        LOG(ERROR) << "Received command";
        commandPub.publish(msg);
        
    }
    if(getValuesFromAttributeList(attributes, "sherpa:command_interpetation_success", resultValues)){
        LOG(ERROR) << "Received interpreted command";
        interpretedCommandPub.publish(msg);
        
        
    }
	return true;
}




RsgCommandObserver::RsgCommandObserver(WorldModel* wm) : wm(wm) {
	
    ros::NodeHandle n;
    commandPub = n.advertise<std_msgs::Empty>("commandPing", 1000);
    interpretedCommandPub = n.advertise<std_msgs::Empty>("interpretedCommandPing", 1000);
}

RsgCommandObserver::~RsgCommandObserver() {
}

bool RsgCommandObserver::addGroup(Id parentId, Id& assignedId,
		vector<Attribute> attributes, bool forcedId) {
	return true;
}

bool RsgCommandObserver::addTransformNode(Id parentId, Id& assignedId,
		vector<Attribute> attributes,
		IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform,
		TimeStamp timeStamp, bool forcedId) {

	return true;

}

bool RsgCommandObserver::addUncertainTransformNode(Id parentId,
		Id& assignedId, vector<Attribute> attributes,
		IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform,
		ITransformUncertainty::ITransformUncertaintyPtr uncertainty,
		TimeStamp timeStamp, bool forcedId) {

	return true;
}


bool RsgCommandObserver::addGeometricNode(Id parentId, Id& assignedId,
		vector<Attribute> attributes, Shape::ShapePtr shape,
		TimeStamp timeStamp, bool forcedId) {

	return true;
}

bool RsgCommandObserver::addRemoteRootNode(Id rootId, vector<Attribute> attributes) {

	return true;
}

bool RsgCommandObserver::addConnection(Id parentId, Id& assignedId, vector<Attribute> attributes, vector<Id> sourceIds, vector<Id> targetIds, TimeStamp start, TimeStamp end, bool forcedId) {
	return true;
}


bool RsgCommandObserver::setTransform(Id id,
		IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform,
		TimeStamp timeStamp) {
	return true;
}

bool RsgCommandObserver::setUncertainTransform(Id id,
		IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform,
		ITransformUncertainty::ITransformUncertaintyPtr uncertainty,
		TimeStamp timeStamp) {

	return true;
}

bool RsgCommandObserver::deleteNode(Id id) {
	return true;
}

bool RsgCommandObserver::addParent(Id id, Id parentId) {
    return true;
}

bool RsgCommandObserver::removeParent(Id id, Id parentId) {
    return true;
}
} /* namespace rsg */
} /* namespace brics_3d */

/* EOF */
