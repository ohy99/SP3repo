#include "CollisionManager.h"

#include "CollidableObj.h"
#include "Bricks.h"
#include "Ball.h"
#include "HPArea.h"
#include "TextManager.h"

#include "Graphics.h"
#include "RenderHelper.h"

CollisionManager::CollisionManager() :
	num_partition_x(3),
	num_partition_y(5),
	use_partition(false)
{
	if (use_partition == false)
		return;
	partition_objects = new std::list<CollidableObj*> *[num_partition_y];
	for (unsigned i = 0; i < num_partition_y; ++i)
		partition_objects[i] = new std::list<CollidableObj*>[num_partition_x];

	//width_partition = *GlobalVariables::get()->worldWidth / (float)num_partition_x;
	height_partition = *GlobalVariables::get()->worldHeight * 1.75f / (float)num_partition_y;
	width_partition = *GlobalVariables::get()->worldWidth * 1.2f / (float)num_partition_x;
	//WAITING TO SOFTCODE
	float min_x = -*GlobalVariables::get()->worldWidth * 0.5f * 1.2f;
	float min_y = (-*GlobalVariables::get()->worldHeight * 0.5f) * 1.75f;
	min_partition_point.Set(min_x, min_y);
}
CollisionManager::~CollisionManager() {

	colliders.clear();

	if (use_partition == false)
		return;
	for (unsigned i = 0; i < num_partition_y; ++i) {
		partition_objects[i]->clear();
		//delete partition_objects[i];
	}
	delete[] partition_objects;

}

void CollisionManager::update(double dt)
{
	if (use_partition)
	{
		update_partition(dt);
		return;
	}
	//Reset collision
	for each (auto c in colliders)
		c->collided_at_this_frame = false;
	
	unsigned int active_collision_checks = 0;
	unsigned int number_of_checks = 0;

	for (std::vector<CollidableObj*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		CollidableObj* first = (CollidableObj*)*it;
		//if (first->collision_type == CollidableObj::COLLISION_TYPE::NONE) continue;
		if (first->active == false) continue;
		if (first->is_collidable == false) continue;

		for (std::vector<CollidableObj*>::iterator it2 = it + 1; it2 != colliders.end(); ++it2)
		{
			++number_of_checks;
			CollidableObj* second = (CollidableObj*)*it2;
			//if (second->collision_type == CollidableObj::COLLISION_TYPE::NONE) continue;
			if (second->active == false) continue;
			if (second->is_collidable == false) continue;
			if ((first->collision_type == CollidableObj::COLLISION_TYPE::BRICK || first->collision_type == CollidableObj::COLLISION_TYPE::WALL) &&
				second->collision_type == first->collision_type) continue;
			if ((first->collision_type == CollidableObj::COLLISION_TYPE::HPAREA) &&
				(second->collision_type != CollidableObj::COLLISION_TYPE::BALL) ||
				(second->collision_type == CollidableObj::COLLISION_TYPE::HPAREA) &&
				(first->collision_type != CollidableObj::COLLISION_TYPE::BALL)) continue;

			if (first->collision_type == CollidableObj::COLLISION_TYPE::BRICK ||
				second->collision_type == CollidableObj::COLLISION_TYPE::BRICK ||
				first->collision_type == CollidableObj::COLLISION_TYPE::HPAREA ||
				second->collision_type == CollidableObj::COLLISION_TYPE::HPAREA)
			{
				if (first->collision.isCollide(second->collision) == false)
					continue;
				Bricks* brick = nullptr;
				Ball* ball = nullptr;
				if (first->collision_type == CollidableObj::COLLISION_TYPE::BRICK)
				{
					brick = dynamic_cast<Bricks*>(first);
					ball = dynamic_cast<Ball*>(second);
				}
				else
				{
					brick = dynamic_cast<Bricks*>(second);
					ball = dynamic_cast<Ball*>(first);
				}


				if (brick && ball) {

					++active_collision_checks;
					//if (brick->check_collision(ball) == false)
					//	continue;
						if (ball->collided_at_this_frame == true)
							continue;
						
						//if ball and other are both enemy, dont collide
						if (ball->faction == CollidableObj::FACTION_SIDE::ENEMY &&
							ball->faction == brick->faction)
							continue;
						ball->collision_response(dt, brick);
						brick->collision_response(dt, ball);

					
				}
				else 
				{
					Ball* temp_ball = nullptr;
					HPArea* hp_area = nullptr;
					if (first->collision_type == CollidableObj::COLLISION_TYPE::BALL) {
						temp_ball = dynamic_cast<Ball*>(first);
						hp_area = dynamic_cast<HPArea*>(second);
					}
					else {
						temp_ball = dynamic_cast<Ball*>(second);
						hp_area = dynamic_cast<HPArea*>(first);
					}

					if (hp_area == nullptr || temp_ball == nullptr)
						continue;

					//check hparea
					//if (temp_ball->collided_at_this_frame == true)
					//	continue;

					//temp_ball->collision_response(dt, hp_area);
					hp_area->collision_response(dt, temp_ball);
				}
			}
			else
			{
				CollidableObj* ball = first;
				CollidableObj* other = second;

				if (ball->collision_type != CollidableObj::COLLISION_TYPE::BALL)
				{
					if (other->collision_type != CollidableObj::COLLISION_TYPE::BALL)
						continue;
					ball = (CollidableObj*)*it2;
					other = (CollidableObj*)*it;
				}
				++active_collision_checks;
				if (check_collision(ball, other)) {
					if (ball->collided_at_this_frame == true)
						continue;
					ball->collision_response(dt, other);
					//std::cout << "BAM" << std::endl;
					if (other->collision_type != CollidableObj::COLLISION_TYPE::BALL)
						other->collision_response(dt, ball);
				}
			}
		}
	}

	//std::string text = "Number of brute force collision: " + std::to_string((colliders.size()) * (colliders.size() / 2));
	//TextManager::GetInstance()->add_text(1, text);
	//text = "Number of active collision checks: " + std::to_string(active_collision_checks);
	//TextManager::GetInstance()->add_text(2, text);
	//text = "Number of collision checks: " + std::to_string(number_of_checks);
	//TextManager::GetInstance()->add_text(3, text);
}

bool CollisionManager::check_collision(CollidableObj* ball, CollidableObj* other)
{
	if (ball->collision_type == CollidableObj::COLLISION_TYPE::BALL && 
		other->collision_type == CollidableObj::COLLISION_TYPE::BALL)
	{
		float distSquared = (ball->pos - other->pos).LengthSquared();
		float combinedRadius = ball->scale.x + other->scale.x;

		//Practical 4, Exercise 13: improve collision detection algorithm
		if (distSquared <= combinedRadius * combinedRadius)
		{
			Vector3 relative_position = ball->pos - other->pos;
			Vector3 relative_velocity = ball->vel - other->vel;
			if (relative_velocity.Dot(relative_position) < 0)
				return true;
			else
				return false;
		}
	}
	else if (ball->collision_type == CollidableObj::COLLISION_TYPE::BALL &&
		other->collision_type == CollidableObj::COLLISION_TYPE::WALL)
	{
		Vector3 ball_to_wall = other->pos - ball->pos;
		Vector3 normal_perpendicular = other->normal.Cross(Vector3(0, 0, 1)).Normalize();
		Vector3 relative_position = ball->pos - other->pos;
		Vector3 N = other->normal;
		
		if (relative_position.Dot(N) > 0)
			N = -N;
		return (ball->vel.Dot(N) > 0 && abs(ball_to_wall.Dot(N)) < ball->scale.x + other->scale.y * 0.5f &&
			abs(ball_to_wall.Dot(normal_perpendicular)) < ball->scale.x + other->scale.x * 0.5f);
	}
	if (ball->collision_type == CollidableObj::COLLISION_TYPE::BALL && 
		other->collision_type == CollidableObj::COLLISION_TYPE::PILLAR)
	{
		Vector3 normal = (other->pos - ball->pos).Normalize();

		return ball->vel.Dot(normal) > 0 && (other->pos - ball->pos).LengthSquared() < (ball->scale.x + other->scale.x) * (ball->scale.x + other->scale.x);
	}
	return false;
}


void CollisionManager::update_partition(double dt)
{
	//check all obj and see if they are in the right partition
	for (unsigned int i = 0; i < num_partition_y; ++i) {
		for (unsigned int j = 0; j < num_partition_x; ++j) {

			for (std::list<CollidableObj*>::iterator itobj = partition_objects[i][j].begin();
				itobj != partition_objects[i][j].end(); ++itobj)
			{
				if ((*itobj)->active == false)
					continue;

				int current_index = i * num_partition_x + j;

				(*itobj)->collided_at_this_frame = false;//reset
				if (check_if_object_in_right_parition(*itobj, i, j) == false)
				{
					CollidableObj* reputobj = *itobj;
					std::list<CollidableObj*>::iterator wad = itobj;
					std::advance(wad, 1);
					if (wad != partition_objects[i][j].end())
						itobj = partition_objects[i][j].erase(itobj);
					else
					{
						partition_objects[i][j].pop_back();
						add_collider_obj(reputobj);
						break;
					}
					add_collider_obj(reputobj);
				}
			}
		}
	}

	unsigned int active_collision_checks = 0;
	unsigned int number_of_checks = 0;

	//do collision checks in each partition
	for (unsigned int i = 0; i < num_partition_y; ++i) {
		for (unsigned int j = 0; j < num_partition_x; ++j) {
			for (std::list< CollidableObj* >::iterator itobj = partition_objects[i][j].begin();
				itobj != partition_objects[i][j].end(); ++itobj) {

				CollidableObj* first = (CollidableObj*)*itobj;
				//if (first->collision_type == CollidableObj::COLLISION_TYPE::NONE) continue;
				if (first->active == false) continue;
				if (first->is_collidable == false) continue;

				//std::list< CollidableObj* >::iterator it2 = itobj;
				//if (it2 != partition_objects[i][j].end())
				//	std::advance(it2, 1);

				//int right_index, up_index, num_checks;
				//get_surrounding_partition_check_info(*itobj, right_index, up_index, num_checks, i, j);

				//int check_index_y = Math::Min(i, i + up_index);
				//int	check_index_x = Math::Min(j, j + right_index);
				//int check_index_y = i;
				//int	check_index_x = j;

				check_surrounding_partitions(dt, first);


			//	if (collision_checked)//check once only
			//		break;

			}


		}

	}

	std::string text = "Number of brute force collision: " + std::to_string((colliders.size()) * (colliders.size() / 2));
	TextManager::GetInstance()->add_text(1, text);
	text = "Number of active collision checks: " + std::to_string(active_collision_checks);
	TextManager::GetInstance()->add_text(2, text);
	text = "Number of collision checks: " + std::to_string(number_of_checks);
	TextManager::GetInstance()->add_text(3, text);
}

bool CollisionManager::check_if_object_in_right_parition(CollidableObj* obj, int iy, int jx)
{
	if (iy * height_partition < obj->pos.y + min_partition_point.y && obj->pos.y + min_partition_point.y< (iy + 1) * height_partition)
	{
		if (jx * width_partition < obj->pos.x + min_partition_point.x && obj->pos.x + min_partition_point.x < (jx + 1) * width_partition)
		{
			//in the right place
			return true;
		}
	}

	//in the wrong place
	return false;
}

bool CollisionManager::check_if_point_in_right_parition(Vector3 point, int iy, int jx) {

	if (iy * height_partition < point.y + min_partition_point.y && point.y + min_partition_point.y< (iy + 1) * height_partition)
	{
		if (jx * width_partition < point.x + min_partition_point.x && point.x + min_partition_point.x < (jx + 1) * width_partition)
		{
			//in the right place
			return true;
		}
	}

	//in the wrong place
	return false;
}

int CollisionManager::get_index_of_partition(CollidableObj* obj)
{
	return 0;
}

void CollisionManager::add_collider_obj(CollidableObj* c) {
	if (use_partition == false) {
		colliders.push_back(c);
		return;
	}
	int index_y = (c->pos.y - min_partition_point.y) / height_partition;
	int index_x = (c->pos.x - min_partition_point.x) / width_partition;
	index_y = Math::Clamp(index_y, 0, num_partition_y - 1);
	index_x = Math::Clamp(index_x, 0, num_partition_x - 1);

	partition_objects[index_y][index_x].push_front(c);
}

void CollisionManager::get_surrounding_partition_check_info(CollidableObj* obj, int& right, 
	int& up, int& checks, int i, int j)
{
	right = 0;
	up = 0;

	if (check_if_point_in_right_parition(obj->pos - obj->scale.x, i, j) == false) {
		//check if left if out of its own partition
		right = -1;
	}
	else if (check_if_point_in_right_parition(obj->pos + obj->scale.x, i, j) == false) {
		//check if right is out of its own partition
		right = 1;
	}
	
	if (check_if_point_in_right_parition(obj->pos - obj->scale.y, i, j) == false) {
		//check if down if out of its own partition
		up = -1;
	}
	else if (check_if_point_in_right_parition(obj->pos + obj->scale.y, i, j) == false) {
		//check if up is out of its own partition
		up = 1;
	}

	checks = 4;
	if (right == 0 && up == 0)
		checks = 1;//mid
	else if (right == 1 && up == 0)
		checks = 2;//middle and right
	else if (right == 0 && up == 1)
		checks = 2;//middle and up
}


void CollisionManager::render_partition_lines()
{
	if (use_partition == false)
		return;
	MS& ms = Graphics::getInstance()->modelStack;

	static Mesh* redline = EntityBase::getInstance()->getEntity("REDLINE");
	static Mesh* greenline = EntityBase::getInstance()->getEntity("GREENLINE");
	static Mesh* blueline = EntityBase::getInstance()->getEntity("BLUELINE");
	
	for (int i = 0; i <= num_partition_y; ++i)
	{
		ms.PushMatrix();
		ms.Translate(0, min_partition_point.y + i * height_partition, 0);
		ms.Scale(100, 100, 100);
		RenderHelper::RenderMesh(redline, false);
		ms.PopMatrix();

	}

	for (int j = 0; j <= num_partition_x; ++j)
	{
		ms.PushMatrix();
		ms.Translate(min_partition_point.x + j * width_partition, 0, 0);
		ms.Scale(100, 100, 100);
		ms.Rotate(90, 0, 0, 1);
		RenderHelper::RenderMesh(greenline, false);
		ms.PopMatrix();
	}
}


void CollisionManager::get_index_from_point(Vector3 p, int &x, int &y)
{
	x = (p.x - min_partition_point.x) / width_partition;
	y = (p.y - min_partition_point.y) / height_partition;

	x = Math::Clamp(x, 0, num_partition_x - 1);
	y = Math::Clamp(y, 0, num_partition_y - 1);
}

void CollisionManager::check_surrounding_partitions(double dt, CollidableObj* obj)
{
	int min_check_x = 0, min_check_y = 0;
	int max_check_x = 0, max_check_y = 0;
	if (obj->collision_type == CollidableObj::COLLISION_TYPE::WALL) {
		int a = 0;
	}
	get_index_from_point(obj->pos - obj->scale, min_check_x, min_check_y);
	get_index_from_point(obj->pos + obj->scale, max_check_x, max_check_y);


	bool collision_checked = false;
	for (int check_index_y = min_check_y; check_index_y <= max_check_y && !collision_checked; ++check_index_y)
	{
		for (int check_index_x = min_check_x; check_index_x <= max_check_x && !collision_checked; ++check_index_x)
		{
			for (std::list<CollidableObj*>::iterator it2 = partition_objects[check_index_y][check_index_x].begin(); it2 != partition_objects[check_index_y][check_index_x].end(); ++it2)
			{

				//++number_of_checks;
				CollidableObj* second = (CollidableObj*)*it2;
				//if (second->collision_type == CollidableObj::COLLISION_TYPE::NONE) continue;
				if (second->active == false) continue;
				if (second->is_collidable == false) continue;

				if ((obj->collision_type == CollidableObj::COLLISION_TYPE::NONE || obj->collision_type == CollidableObj::COLLISION_TYPE::WALL) &&
					second->collision_type == obj->collision_type) continue;

				if (obj == second) continue;
					//got struct collision
				if (obj->collision.isCollide((*it2)->collision) == false)
				{
					continue;
				}
				else
				{
					Bricks* brick = nullptr;
					Ball* ball = nullptr;
					if (obj->collision_type == CollidableObj::COLLISION_TYPE::NONE)
					{
						brick = dynamic_cast<Bricks*>(obj);
						ball = dynamic_cast<Ball*>(*it2);
					}
					else
					{
						brick = dynamic_cast<Bricks*>(*it2);
						ball = dynamic_cast<Ball*>(obj);
					}


					if (brick && ball) {
						//++active_collision_checks;

						if (brick->check_collision(ball)) {
							if (ball->collided_at_this_frame == true)
								continue;

							//if ball and other are both enemy, dont collide
							if (ball->faction == CollidableObj::FACTION_SIDE::ENEMY &&
								ball->faction == brick->faction)
								continue;
							ball->collision_response(dt, brick);
							brick->collision_response(dt, ball);
							//if (second->collision_type == CollidableObj::COLLISION_TYPE::BALL)
							//	collision_checked = true;
							//break;
						}
					}
					else
					{
						CollidableObj* temp_ball = obj;
						CollidableObj* other = second;
						if (obj->collision_type != CollidableObj::COLLISION_TYPE::BALL) {
							if (second->collision_type != CollidableObj::COLLISION_TYPE::BALL)
								continue;
							temp_ball = second;
							other = obj;
						}
						if (check_collision(temp_ball, other))
						{
							if (temp_ball->collided_at_this_frame == true)
								continue;
							if (temp_ball->faction == CollidableObj::FACTION_SIDE::ENEMY &&
								temp_ball->faction == other->faction)
								continue;
							temp_ball->collision_response(dt, other);
							other->collision_response(dt, temp_ball);
						}

				
					}
				}

			}// !CHECK PARTITION LIST
		}// !CHECK RIGHT SIDE
	}// !CHECK UP SIDE
}

//else
//{
//	CollidableObj* ball = first;
//	CollidableObj* other = second;
//
//	if (ball->collision_type != CollidableObj::COLLISION_TYPE::BALL)
//	{
//		if (other->collision_type != CollidableObj::COLLISION_TYPE::BALL)
//			continue;
//		ball = (CollidableObj*)*it2;
//		other = (CollidableObj*)*itobj;
//	}
//	++active_collision_checks;
//	if (check_collision(ball, other)) {
//		ball->collision_response(dt, other);
//
//		if (other->collision_type != CollidableObj::COLLISION_TYPE::BALL)
//			other->collision_response(dt, ball);
//
//		collision_checked = true;
//		break;
//	}
//}