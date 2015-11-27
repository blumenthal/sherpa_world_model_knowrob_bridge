#RSG - Knowrob bridge design

## Overview

![Overview](rsg_knowrob_bridge_overview.png)

## Modules

### Knowrob

* has *semantic map* with triples
  * Object
  * Transform
  * Perception Event 
 
### Knowrob Bridgre

* Used *Observer* Software Pattern to send triples to semantic map whenever a RSG update arrives (JSON).
  * Has a configurable *filter* policy
* Recieves Perception Events and 
  * inserts a Perception Event into semantic map
  * inserts a geoloclized Node to represent the Prerception Event.  

### SHERPA World model

* Same as described [here](https://github.com/blumenthal/ubx_robotscenegraph) 
* loads OSM map