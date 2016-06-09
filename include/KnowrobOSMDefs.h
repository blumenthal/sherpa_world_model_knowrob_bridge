/******************************************************************************
 * Sherpa RSG KNOWROB Bridge
 * Copyright (c) 2016, IAI Bremen
 *
 * Authors: Benjamin  Brieber
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

#ifndef __IAI_KNOWROB_OSM_DEFS__
#define __IAI_KNOWROB_OSM_DEFS__

#include "string"
#include "list"
#include "vector"
#include <brics_3d/worldModel/sceneGraph/TimeStamp.h>
#include <brics_3d/worldModel/sceneGraph/Attribute.h>
#include <brics_3d/worldModel/sceneGraph/Id.h>


using namespace std;



struct RSG_Attribute{
    string key;
    string value;    
};


struct RSG_Node{
    vector<brics_3d::rsg::Attribute> attrs;
    brics_3d::rsg::TimeStamp timeStamp;
};

struct RSG_GeoPoint{
  float longitude;
  float latitude;
  float altitude;
    
};


struct RSG_TfPoint{
  float x;
  float y;
  float z;
    
};

struct RSG_GeoNode{
    RSG_Node node;
   RSG_GeoPoint location;
  
} ;


struct RSG_TfNode{
    RSG_Node node;
   RSG_TfPoint location;
} ;


struct RSG_PathNode{
    RSG_Node node;
  std::list<RSG_Node> nodes;
} ;

struct RSG_Way{
    RSG_Node node;
    vector<brics_3d::rsg::Id> nodes;
} ;

struct RSG_PolyNode{
  RSG_Node node;
  std::list<RSG_Node> nodes;
} ;

#endif //__IAI_KNOWROB_OSM_DEFS__