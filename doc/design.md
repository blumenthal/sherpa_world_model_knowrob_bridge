#RSG - Knowrob bridge design

## Overview

![Overview](rsg_knowrob_bridge_overview.png)

The Knowrob component is connected to the SHERPA World Model (SWM) through (i) the **Knowrob Mediator** to 
transform primitives according to the Robot Scene Graph (RSG) data model into assertions that are
added to the knowledgebase of Knowrob and 
(ii) a **query** channel that allows to retrieve information about the world at any given point in time.

### Knowrob Mediator

The mediator component is a central element that serves three purposes: (a) it translates RSG Updates into assertions in the Knowrob knowledgebase, (b) it handles incoming **Sherpa Events** that are relevant for a SHERPA mission by adding them to the SWM and the Knowrob knowledgebase, and (c) it handles external Knowrob queries by sending them to a local Knowrob component or, if no local Knowrob component is present, forwards it to another animal.

(a) Whenever a for Knowrob relevant part of the SHERPA world model is changed an update is sent from the SWM to the mediator. This update, encoded as JSON message, is sent to the mediator as a ROS message. The mediator utilizes
an [Observer](../src//RsgToKnowrobObserver.cpp) Software Pattern to trigger the creation of a new assertion for Prolog as used by Knowrob. 
The [JSON Prolog](https://github.com/knowrob/knowrob/tree/master/json_prolog) interface transmits the assertions. 
An extension of the ontology for RSG specific entities for the knowledgebase comprises TODO. 
The related Prolog and OWL files can be found in the [knowrob_rsg](https://github.com/bbrieber/knowrob_rsg) 
repository.
The primary use case is the **creation** of the semantic map at start up. In particular when it is populated with data originating
from Open Street Map (OSM), which is loaded by the SWM by the [``osmloder``](https://github.com/blumenthal/brics_3d_function_blocks/tree/master/osmloader) 
module. 

(b) The second responsibility of the mediator is to handle incoming [**Sherpa Events**](https://github.com/blumenthal/sherpa_world_model_knowrob_bridge_msgs/blob/master/msg/SherpaEvent.msg).
 SHERPA Events can for example be the detection of a human, the insertion of a geo-localized image as requested by a "perception on demand" task, or a task/TST related event.
The effect of such an event is always the same: a new object for the RSG and a new assertion for Knowrob is created with:
* the geopose **where** the event has happened,
* the time stamp **when** it has happened,
* a categorization on **what** has happened and 
* further attributes (key-value tags) describing the details of the event.
The set of agreed attributes is summarized in a [code book](codebook.md). 
Please note, the mediator provides the events to Knowrob and SWN at the same time to foster testability, i.e., Knowrob can be tested without the SWM and vice versa. 

(c) The knowrob mediator also allows querying the database from external software components/agents. This allows the same interface for components independent of a local Knowrob component being present. Components can send Knowrob queries as JSON encoded messages to the mediator. The mediator knows if a local Knowrob component is present or not. If one is present, it will send the query there. Otherwise, it will forward the query to the communication mediator, which will send it to all other Sherpa animals. The animals with a Knowrob component will then resolve the query and send the result back. Only the first returned result will be taken into account. The later ones will be ignored and termination signals for these query interfaces are sent.

![Architecture](sherpa_arhitecture.png)


### Queries from Knowrob to SWM

In order to obtain information from the SWM, Knowrob can issues queries. These queries are send on demand and are used to gain access to information that has not been explicitly modeled in knowrob. It uses 
the [JSON RSG Query API](https://github.com/blumenthal/ubx_robotscenegraph/tree/master/examples/json_api). 
A typical querie requests pose infomation of an object at a given point in time. Here the SWM serves as an episodic 
memory to improve the reasoning capabilities of Knowrob.
The technical realization uses the Java to Prolog capabilities in Knowrob to issua a **JSON Query** via a ZMQ communication channel to the SWM.
A response immediatly follows by returning a **JSON RSG Reply** . Note that queries can only be posed about objects that have been added as assertion by the mediator beforehand. 


## Launching the system

### Sherpa World Model
```
  cd <path_to_ubx_robotscenegraph>
  ./run_sherpa_world_model.sh
  start_all()
```

### Knowrob with mediator
```
  roslaunch sherpa_world_model_knowrob_bridge sherpa_world_model_knowrob_bridge.launch 
```


---

## Modules

### Knowrob

* Same as described [here](https://github.com/bbrieber/knowrob_rsg)
* has *semantic map* with triples	
  * Object
  * Transform
  * Perception Event 
 
### Knowrob Mediator

* Module can be found in **this** repository
* Used *Observer* Software Pattern to send triples to semantic map whenever a RSG update arrives (JSON).
  * Has a configurable *filter* policy
* Recieves Perception Events and 
  * Inserts a Perception Event into semantic map
  * Inserts a geoloclized Node to represent the Prerception Event.  

* TODO
  * [x] Add Perception Event ROS message description a.k.a. **Sherpa Event**
  * [ ] Add semantic map updates within observer 
  * [ ] Add filter
  * [ ] Add handling of Perception Event Messages
  * [x] Add code book for semantic tags

### SHERPA World model

* Same as described [here](https://github.com/blumenthal/ubx_robotscenegraph) 
* Loads OSM map
