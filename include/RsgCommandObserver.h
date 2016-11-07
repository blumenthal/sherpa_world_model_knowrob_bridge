/******************************************************************************
 * BRICS_3D - 3D Perception and Modeling Library
 * Copyright (c) 2015, KU Leuven
 * FIXME based on....
 * Author: Benjamin Brieber
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

#ifndef __RSG_COMMAND_OBSERVER_H__
#define __RSG_COMMAND_OBSERVER_H__

/* RSG related headers */
#include <brics_3d/worldModel/sceneGraph/ISceneGraphUpdateObserver.h>
#include <brics_3d/worldModel/sceneGraph/Attribute.h>
#include <brics_3d/util/Timer.h>

/* ROS TF related headers */
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include "std_msgs/Empty.h"

#include "SceneGraphTypeCasts.h"


namespace brics_3d {
namespace rsg {

class RsgCommandObserver : public ISceneGraphUpdateObserver {
public:
RsgCommandObserver(WorldModel* wm);
	virtual ~RsgCommandObserver();

	
	bool addNode(Id parentId, Id& assignedId, vector<Attribute> attributes, bool forcedId = false);
	bool addGroup(Id parentId, Id& assignedId, vector<Attribute> attributes, bool forcedId = false);
	bool addTransformNode(Id parentId, Id& assignedId, vector<Attribute> attributes, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform, TimeStamp timeStamp, bool forcedId = false);
	bool addUncertainTransformNode(Id parentId, Id& assignedId, vector<Attribute> attributes, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform, ITransformUncertainty::ITransformUncertaintyPtr uncertainty, TimeStamp timeStamp, bool forcedId = false);
	bool addGeometricNode(Id parentId, Id& assignedId, vector<Attribute> attributes, Shape::ShapePtr shape, TimeStamp timeStamp, bool forcedId = false);
	bool addRemoteRootNode(Id rootId, vector<Attribute> attributes);
	bool addConnection(Id parentId, Id& assignedId, vector<Attribute> attributes, vector<Id> sourceIds, vector<Id> targetIds, TimeStamp start, TimeStamp end, bool forcedId = false);
	bool setNodeAttributes(Id id, vector<Attribute> newAttributes, TimeStamp timeStamp = TimeStamp(0));
	bool setTransform(Id id, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform, TimeStamp timeStamp);
	bool setUncertainTransform(Id id, IHomogeneousMatrix44::IHomogeneousMatrix44Ptr transform, ITransformUncertainty::ITransformUncertaintyPtr uncertainty, TimeStamp timeStamp);
	bool deleteNode(Id id);
	bool addParent(Id id, Id parentId);
	bool removeParent(Id id, Id parentId);
    
private:
    
    WorldModel* wm;
    
    ros::Publisher commandPub;
    ros::Publisher interpretedCommandPub;
    
    std_msgs::Empty msg;

};

} /* namespace rsg */
} /* namespace brics_3d */

#endif /* __RSG_COMMAND_OBSERVER_H__ */

/* EOF */
