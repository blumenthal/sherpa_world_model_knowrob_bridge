/******************************************************************************
* BRICS_3D - 3D Perception and Modeling Library
* Copyright (c) 2014, KU Leuven
*
* Author: Sebastian Blumenthal
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


#include <iostream>
#include <fstream>

/* ROS includes */
#include <ros/ros.h>
//#include <tf/tf.h>
//#include <tf/transform_listener.h> //@deprecated
//#include <tf/transform_broadcaster.h> //@deprecated
//#include <tf2_bullet/tf2_bullet/tf2_bullet.h> // package.xml does not resolve this correctly
//#include <LinearMath/btTransform.h>
//#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
//#include <tf2_ros/buffer.h>
//#include <tf2_ros/transform_listener.h>
//#include <tf2_ros/transform_broadcaster.h>
#include <std_msgs/ByteMultiArray.h> // update channel for world model

/* BRICS_3D includes */
#include <brics_3d/worldModel/WorldModel.h>
#include <brics_3d/worldModel/sceneGraph/DotVisualizer.h>
#include <brics_3d/worldModel/sceneGraph/SceneGraphFacade.h>
#include <brics_3d/worldModel/sceneGraph/HDF5UpdateSerializer.h>
#include <brics_3d/worldModel/sceneGraph/HDF5UpdateDeserializer.h>
#include <brics_3d/worldModel/sceneGraph/JSONSerializer.h>
#include <brics_3d/worldModel/sceneGraph/JSONDeserializer.h>
#include <brics_3d/worldModel/sceneGraph/OutdatedDataIdAwareDeleter.h>
#include <brics_3d/worldModel/sceneGraph/SceneGraphToUpdatesTraverser.h>
#include <brics_3d/worldModel/sceneGraph/FrequencyAwareUpdateFilter.h>
#include <brics_3d/core/Logger.h>
#include <brics_3d/core/HomogeneousMatrix44.h>

/* RSG <-> ROS bindings*/
#include "RsgRosBridge.h"

/* RSG <-> Knowrob bindings */
#include "RsgToKnowrobObserver.h"
#include "KnowrobConnection.h"

#include <vector>
#include "ISherpaEventObserver.h"


/* Optional visialization via OSG. This has to be enabled via a CMake option */
#ifdef ENABLE_OSG
	#include <brics_3d/worldModel/sceneGraph/OSGVisualizer.h>
#endif

#define SHERPA_EVENT_TOPIC_NAME "sherpa_event"

using brics_3d::Logger;
using namespace brics_3d::rsg;

std::vector<class ISherpaEventObserver*> sherpaEventObservers;

void onSherpaEvent(const sherpa_world_model_knowrob_bridge_msgs::SherpaEvent::ConstPtr& msg){
  for(int i=0; i < sherpaEventObservers.size(); i++){
    sherpaEventObservers[i]->onSherpaEvent(msg);
  }
}


int main(int argc, char **argv)
{

	/* Initialize ROS framework */
	ros::init(argc, argv, "world_model_knowrob_bridge");
	ros::NodeHandle node;

	/* parameters */
	bool enableDotVisualizer;

	node.param("enable_dot_visualizer", enableDotVisualizer, false);

	/* Define logger level for world model */
	brics_3d::Logger::setMinLoglevel(brics_3d::Logger::LOGDEBUG);
	brics_3d::Logger::setLogfile("world_model_tf_bridge.log");

	/* Create an empty world model */
	brics_3d::WorldModel* wm = new brics_3d::WorldModel();
	vector<Attribute> rootNodeAttributes;
	rootNodeAttributes.push_back(Attribute("name", "rsg_kb_bridge")); // the name tag is for debugging
	wm->scene.setNodeAttributes(wm->getRootNodeId(), rootNodeAttributes);

	/* Attach additional debug output to the world model */
	brics_3d::rsg::DotVisualizer structureVisualizer(&wm->scene);
	if (enableDotVisualizer) {
		LOG(INFO) << "DotVisualizer is enabled.";
		wm->scene.attachUpdateObserver(&structureVisualizer);
	}

	/* Connect input port to world model */
//	brics_3d::rsg::HDF5UpdateDeserializer* inDeserializer = new brics_3d::rsg::HDF5UpdateDeserializer(wm);
//	RsgRosInputBridge* inBridge = new RsgRosInputBridge(inDeserializer, node, "world_model/update_stream");
	brics_3d::rsg::JSONDeserializer* inDeserializer = new brics_3d::rsg::JSONDeserializer(wm);
	RsgRosInputBridge* inBridge = new RsgRosInputBridge(inDeserializer, node, "world_model/json/updates");

	/* Attach the outout filter + port */
//	RsgRosOutputBridge* outBridge = new RsgRosOutputBridge(node, "world_model/update_stream_tf_bridge");
//	HDF5UpdateSerializer* outSerializer = new HDF5UpdateSerializer(outBridge);
	RsgRosOutputBridge* outBridge = new RsgRosOutputBridge(node, "world_model/json/knowrob_updates");
	JSONSerializer* outSerializer = new JSONSerializer(outBridge);

	outSerializer->setStoreMessageBackupsOnFileSystem(false);
	FrequencyAwareUpdateFilter* frequencyFilter = new FrequencyAwareUpdateFilter();
	frequencyFilter->setMaxTransformUpdateFrequency(1/*Hz*/);
	/* chaines up ubserver: wm -> frequencyFilter -> outSerializer */
	wm->scene.attachUpdateObserver(frequencyFilter);
	frequencyFilter->attachUpdateObserver(outSerializer);


#ifdef ENABLE_OSG
	//Visualization tool for world model
	brics_3d::rsg::OSGVisualizer* wmObserver = new brics_3d::rsg::OSGVisualizer(); // can segfault
	brics_3d::rsg::VisualizationConfiguration osgConfig;
	osgConfig.visualizeIds = false;
	wmObserver->setConfig(osgConfig);
	wm->scene.attachUpdateObserver(wmObserver); // enable visualization
	wm->scene.advertiseRootNode(); 				// required by visualizer
#endif

//#ifdef ENABLE_KNOWROB
	/* Model to model transform of RSG udates to
	 * assertions(?) for the semantic map reperesentaion as used within Knowrob */
	RsgToKnowrobObserver rsgToKr(wm);
	//wm->scene.attachUpdateObserver(&rsgToKr); // unfiltered version
	/* Application specific fileter for the SHERPA scenaio: (TDB) */
	frequencyFilter->attachUpdateObserver(&rsgToKr);
	
	KnowrobConnection kb_con;
	kb_con.init();
	rsgToKr.setKnowrobConnection(&kb_con);
	sherpaEventObservers.push_back(&kb_con);
	ros::Subscriber sub = node.subscribe(SHERPA_EVENT_TOPIC_NAME, 1000, onSherpaEvent);
	kb_con.call_nothin();
//#endif
	LOG(INFO) << "Ready.";

	/* Let the node loop and process messages. */
	ros::MultiThreadedSpinner spinner(2);
	wm->scene.advertiseRootNode();

	spinner.spin();

	/* Clean up */
	delete wm;

	return 0;
}



/* EOF */
