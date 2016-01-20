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


#ifndef __IAI_ISHERPA_EVENT_OBSERVER__
#define __IAI_ISHERPA_EVENT_OBSERVER__

#include "sherpa_world_model_knowrob_bridge_msgs/SherpaEvent.h"

class ISherpaEventObserver {
  public: virtual void onSherpaEvent(const sherpa_world_model_knowrob_bridge_msgs::SherpaEvent::ConstPtr& msg) = 0;
};
  
  

#endif//___IAI_ISHERPA_EVENT_OBSERVER__