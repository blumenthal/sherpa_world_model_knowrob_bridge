#RSG - Knowrob bridge design

## Overview

![Overview](rsg_knowrob_bridge_overview.png)

## Modules

### Knowrob

* Same as described [here](https://github.com/bbrieber/knowrob_rsg)
* has *semantic map* with triples	
  * Object
  * Transform
  * Perception Event 
 
### Knowrob Bridge

* Module can be found in **this** repository
* Used *Observer* Software Pattern to send triples to semantic map whenever a RSG update arrives (JSON).
  * Has a configurable *filter* policy
* Recieves Perception Events and 
  * Inserts a Perception Event into semantic map
  * Inserts a geoloclized Node to represent the Prerception Event.  

* TODO
  * [ ] Add Perception Event ROS message description
  * [ ] Add semantic map updates within observer 
  * [ ] Add filter
  * [ ] Add handling of Perception Event Messages

### SHERPA World model

* Same as described [here](https://github.com/blumenthal/ubx_robotscenegraph) 
* Loads OSM map