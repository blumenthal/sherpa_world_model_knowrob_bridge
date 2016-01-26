# Code book for semantic tags used within SHERPA 

This *code book* is a Work-In-Progress document for the SHERPA relevat semantic tags.
These tags can originate from different contexts like GIS, Open Street Map, or application sppecific SHERPA tags.
The different domains are denoted here as *semantic context*s.
In order to better seperate *semantic context*s tags have a prefix to indecate a namespace seperated by a ``:``.

Currently there are the following contexts:

 * ``osm`` for Open Street Map data
 * ``gis`` for GIS related data like coordinate reference frames
 * ``tf`` for ``Transform`` related data
 * ``sherpa`` for application specific data like detected humans.

In general scene related tags should comply with the tags for [Open Street Map](http://wiki.openstreetmap.org/wiki/Map_Features) data plus the added prefix ``osm:``.
E.g. ``highway=path`` turns into ``osm:highway=path``. Some examples are listed in the below table as well.  

| Key | Value(s) | RSG Primitives | Knowrob Support | Description |
------|--------|-------------|-----------------|-------------|
| ``osm:highway`` | ``path`` | ``Connection`` | tbd | Example for a generic [path](http://wiki.openstreetmap.org/wiki/Tag:highway%3Dpath) tag from OSM. |
| ``osm:waterway`` | ``river`` | ``Connection`` | tbd | Example for a [river](http://wiki.openstreetmap.org/wiki/Tag:waterway%3Driver) tag from OSM. |
| ``osm:building`` | ``house`` | tbd | tbd | Example for a [house](http://wiki.openstreetmap.org/wiki/Tag:building%3Dhouse) tag from OSM. |
| ``osm:natural`` | ``wood`` | tbd | tbd | Example for a [wood](http://wiki.openstreetmap.org/wiki/Tag:natural%3Dwood) tag from OSM. |
| ``osm:natural`` | ``peak`` | tbd | tbd | Example for the [peak](http://wiki.openstreetmap.org/wiki/Tag:natural%3Dpeak) of a mountain tag from OSM. |
| ``osm:building`` | ``house`` | tbd | tbd | Example for a [house](http://wiki.openstreetmap.org/wiki/Tag:building%3Dhouse) tag from OSM. |
| ``osm:node_id`` | any Integer | ``Node`` | tbd | Id used to identtify a OSM *node*. Added to common tags within OSM |
| ``osm:node_way`` | any Integer | ``Connection`` | tbd | Id used to idententify a OSM *way*. Added to common tags within OSM  |
| ``sherpa:agent_name`` | any String | ``Node`` | yes | Human readable name for a SHARPA robot. E.g. ``donkey`` |
| ``sherpa:observation_type`` | Enum: ``dem``, ``image``, ``point_cloud`` | ``Node`` | tbd | Geo tagged perception event as requested by mission. |
| ``sherpa:uri`` | String according to URI specification | ``Node`` | tbd | Unique Resource Location of image, point cloud, digital elevation map, etc. |
| ``sherpa:origin`` | ``initial`` | tbd | tbd | Start frame for a robot. Typically used for local odometry |
| ``gis:origin`` | ``utm`` or ``wgs85`` | ``Node`` | tbd | Identifies the reference frame for geoses. |
| ``tf:type`` | ``tf``, ``utm`` or ``wgs85`` | ``Transform`` | tbd | Identifies if the Transform as Cartesian in pose  case of ``tf`` or as a geopose according to the UTM or WGS84 format. |
| ``tf:utm_zone`` | eg. ``39N`` | tbd | tbd | Specifies UTM zone if ``tf:type`` is set to ``utm``. |

