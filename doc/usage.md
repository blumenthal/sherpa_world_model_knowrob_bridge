#RSG - Knowrob bridge Usage

## Overview

## ROSCORE

start a roscore

```
  roscore
```


## UBX

change to the robotscenegraph directory
```
  cd  <pathto>/ubx_robotscenegraph
```

start the interactive console:

```
  start_all()
```
  
  
  
## Bridge

start the sherpa_world_model_knowrob_bridge

```
  roslaunch sherpa_worldmodel_knowrob_bridge sherpa_world_model_knowrob_bridge.launch 
```

## Load World data
Load the needed data into the SWM

### From OSM-File


```
  load_map()
```


### Via Script



```
  cd examples/sherpa/mission_scripts
  python swm.py initialize
  python swm.py load champoluc_map.dcm

```





