# Code book for semantic tags used within SHERPA 

This *code book* is a Work-In-Progress document for the SHERPA relevat semantic tags.
These tags can originate from different contexts like GIS, Open Street Map, or application sppecific SHERPA tags.
The different domains are denoted here as *Semantic Context*s.
In order to better seperate *Semantic Context*s tags have a prefix to indecate a namespace seperated by a ``:``.

Currently there are the following contexts:

 * ``osm`` for Open Street Map data
 * ``gis`` for GIS related data like coordinate reference frames
 * ``tf`` for ``Transform`` related data
 * ``sherpa`` for application specific data like detected humans
 * ``rsg``	for Robot Scene Graph related tags
 * ``tst``	for Task Specifiacation Trees (TST) as used by the LKU delegation framework
 * ``kb``	for Knowrob related tags
 * ``geo``	for geometry

In general scene related tags should comply with the tags for [Open Street Map](http://wiki.openstreetmap.org/wiki/Map_Features) data plus the added prefix ``osm:``.
E.g. ``highway=path`` turns into ``osm:highway=path``. Some examples are listed in the below table.  

| Key | Value(s) | RSG Primitives | Knowrob Support | Description |
------|--------|-------------|-----------------|-------------|
| ``osm:highway`` | ``path`` | ``Connection`` | tbd | Example for a generic [path](http://wiki.openstreetmap.org/wiki/Tag:highway%3Dpath) tag from OSM. |
| ``osm:waterway`` | ``river`` | ``Connection`` | tbd | Example for a [river](http://wiki.openstreetmap.org/wiki/Tag:waterway%3Driver) tag from OSM. |
| ``osm:building`` | ``house`` | tbd | tbd | Example for a [house](http://wiki.openstreetmap.org/wiki/Tag:building%3Dhouse) tag from OSM. |
| ``osm:natural`` | ``wood`` | tbd | tbd | Example for a [wood](http://wiki.openstreetmap.org/wiki/Tag:natural%3Dwood) tag from OSM. |
| ``osm:natural`` | ``peak`` | tbd | tbd | Example for the [peak](http://wiki.openstreetmap.org/wiki/Tag:natural%3Dpeak) of a mountain tag from OSM. |
| ``osm:building`` | ``house`` | tbd | tbd | Example for a [house](http://wiki.openstreetmap.org/wiki/Tag:building%3Dhouse) tag from OSM. |
| ``osm:node_id`` | any Integer | ``Node`` | yes | Id used to identtify a OSM *node*. Added to common tags within OSM |
| ``osm:node_way`` | any Integer | ``Connection`` | yes | Id used to idententify a OSM *way*. Added to common tags within OSM  |
| ``geo:area`` | ``polygon`` | ``Connection`` | yes | The set of Nodes must be indicated as targetIds. The first and the last Node ID must be the same. |
| ``sherpa:agent_name`` | any String | ``Node`` | yes | Human readable name for a SHARPA robot. E.g. ``donkey`` |
| ``sherpa:observation_type`` | Enum: ``dem``, ``image``, ``point_cloud``, ``victim``, ``artva``, ``battery`` | ``Node`` | tbd | Geo tagged perception event as requested by mission. |
| ``sherpa:uri`` | String according to URI specification | ``Node`` | tbd | Unique Resource Location of image, point cloud, digital elevation map, etc. Conventaion is: ``<MediatorUUID>:<path_to_file>`` |
| ``sherpa:image_height`` | positive Integer  | ``Node`` | tbd | Optional inidication on height of image. Can be use for geotiff  (DEM) files as well. |
| ``sherpa:image_width`` | positive Integer  | ``Node`` | tbd | Optional inidication on width of image. Can be use for geotiff  (DEM) files as well. |
| ``sherpa:author`` | String for the author e.g. ``donkey0``  | ``Node`` | tbd | Optional inidication who made the image |
| ``sherpa:stamp`` | Miliseconds since epoch  | ``Node`` | tbd | Optional inidication when the image was take. |
| ``sherpa:origin`` | ``initial`` | ``Node`` | yes | Start frame for a robot. Typically used for local odometry |
| ``sherpa:artva_signal0`` ... ``sherpa:artva_signal3`` | ``0``-``100`` | ``Node`` | tbd | A single *ARTVA* measurement, stored as Node. Its geoposes is represented as a Transform. Cf. below. |
| ``sherpa:battery_voltage`` | Real | ``Node`` | tbd | A single battery voltage measurement, stored as Node. Might be used with a single Node by just overriding the value. Should be a child of the agent. |
| ``sherpa:battery_status`` | ``HIGH``, ``MID``, ``LOW`` | ``Node`` | tbd | A single battery status measurement, stored as Node. Might be used with a single Node by just overriding the value. Should be a child of the agent. |
| ``gis:origin`` | ``utm`` or ``wgs84`` | ``Node`` | tbd | Identifies the reference frame for geoses. |
| ``tf:type`` | ``tf``, ``utm`` or ``wgs84`` | ``Transform`` | tbd | Identifies if the Transform as Cartesian pose in case of ``tf`` or as a geopose according to the UTM or WGS84 format. |
| ``tf:utm_zone`` | eg. ``39N`` | tbd | tbd | Specifies UTM zone if ``tf:type`` is set to ``utm``. |
| ``tst:envtst`` | A TST model wrapped in a  "sherpa_msgs" meta model  | ``Node`` | no | Specifies a complete TST that is valid for a mission. |
| ``tst:ennodeupdate`` | A TST update wrapped in a  "sherpa_msgs" meta model  | ``Node`` | no | Specifies an update for TST node. |
| ``kb:iri`` | IRI for knowrob classes and instances   | ``Node,Connection,Group`` | yes | Reference to corresponding knowrob instance |
| ``kb:node_id`` | any Integer | ``Node`` | yes | Id used to identtify a OSM like *node* inserted by knowrob. The node can contain additional OSM data  |
| ``kb:way_id`` |any Integer | ``Connection`` | yes | Id used to idententify a OSM like *way* inserted by knowrob. The node can contain additional OSM data  |
| ``kb:map_id`` |any Integer | ``Group`` | yes | Id used to idententify a OSM like virtual *maps* inserted by knowrob. The node might be deleted if it is not needed anymore  |




