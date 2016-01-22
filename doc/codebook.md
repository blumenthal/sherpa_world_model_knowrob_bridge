# Code book for semantic tags used within SHERPA 

| Key | Value(s) | RSG Support | Knowrob Support | Description |
------|--------|-------------|-----------------|-------------|
| ``osm:node_id`` | any Integer | yes | no | Id used to identtify a OSM *node* |
| ``osm:node_way`` | any Integer | yes | no | Id used to idententify a OSM *way* |
| ``sherpa:agent_name`` | any String | no | yes | Human readable name for a SHARPA robot. E.g. ``donkey`` |
| ``sherpa:observation_type`` | Enum: ``dem``, ``image``, ``point_cloud`` | no | no | Geo tagged perception event as requested by mission. |
| ``sherpa:uri`` | String according to URI nomencalture | no | no | Unique Resource Location of image, point cloud, digital elevation map, etc. |
| ``gis:origin`` | ``utm`` or ``wgs85`` | yes | no | Identifies the reference frame for geosed. |
| ``tf:type`` | ``tf``, ``utm`` or ``wgs85`` | yes | no | Identifies if the Trasform as Cartesian in pose  case of ``tf`` or as a geopose according to the UTM or WGS84 format. |
| ``tf:utm_zone`` | eg. ``39N`` | yes | no | Specifies UTM zone if ``tf:type`` is set to ``utm``. |

