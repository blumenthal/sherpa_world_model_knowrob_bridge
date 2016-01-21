# Code book for semantic tags used within SHERPA 

| Key | Value(s) | RSG Support | Knowrob Support | Description |
------|--------|-------------|-----------------|-------------|
| ``osm:node_id`` | any Integer | yes | no | Id used to identtify a OSM *node* |
| ``osm:node_way`` | any Integer | yes | no | Id used to idententify a OSM *way* |
| ``sherpa:agent_name`` | any String | no | yes | Human readable name for a SHARPA robot. E.g. ``donkey`` |
| ``sherpa:observation_type`` | Enum: ``dem``, ``image``, ``point_cloud`` | no | no | Geo tagged perception event as requested by mission. |
| ``sherpa:uri`` | String according to URI nomencalture | no | no | Unique Resource Location of image, point cloud, digital elevation map, etc. |
