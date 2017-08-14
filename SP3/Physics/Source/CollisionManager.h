#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <list>
//#include "CollidableObj.h"
class CollidableObj;
#include "Vector3.h"

class CollisionManager : public Singleton<CollisionManager>
{
	friend Singleton;

	std::vector<CollidableObj*> colliders;

	bool check_collision(CollidableObj* ball, CollidableObj* other);
	const bool use_partition;
	//spatial partition
	const int num_partition_x, num_partition_y;
	float width_partition, height_partition;
	Vector3 min_partition_point;
	std::list< CollidableObj* > **partition_objects;
	void update_partition(double dt);
	void check_surrounding_partitions(double dt, CollidableObj* obj);
	bool check_if_object_in_right_parition(CollidableObj* obj, int i, int j);
	bool check_if_point_in_right_parition(Vector3 p, int i, int j);
	void get_index_from_point(Vector3 p, int &x, int &y);
	int get_index_of_partition(CollidableObj* obj);
	void get_surrounding_partition_check_info(CollidableObj* obj, int& right, int& up, int& checks, int i, int j);
public:
	void update(double dt);

	void add_collider_obj(CollidableObj* c);

	void render_partition_lines();

protected:
	CollisionManager();
	virtual ~CollisionManager();
};

#endif // !COLLISION_MANAGER_H