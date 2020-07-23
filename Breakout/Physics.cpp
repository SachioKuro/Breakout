#include "Physics.hpp"

#include "Game.hpp"

namespace Breakout {
	Physics::Physics() {
	}

	void Physics::CheckMovableCollision(Game* game, std::vector<MovableGameObject*> &objs) {
		for (auto obj : objs) {
			float x = obj->X();
			float y = obj->Y();

			float pg_left = 0;
			float pg_right = game->BoundsW();
			float pg_top = 0;
			float pg_bottom = game->BoundsH();
			bool collision_detected = false;

			// Check against top bounds
			if (obj->IntersectsLine(0, 0, 0, game->BoundsH()) || x < pg_left) {
				float dx = 0;
				float dy = game->BoundsH();
				obj->Collide(dy, -dx);
				collision_detected = true;

				obj->Update(GameObject::Action::hit);
			}
			// Check against right bounds
			else if (obj->IntersectsLine(game->BoundsW(), 0, game->BoundsW(), game->BoundsH()) || x > pg_right) {
				float dx = 0;
				float dy = -game->BoundsH();
				obj->Collide(dy, -dx);
				collision_detected = true;

				obj->Update(GameObject::Action::hit);
			}
			// Check against left bounds
			else if (obj->IntersectsLine(0, 0, game->BoundsW(), 0) || y < pg_top) {
				float dx = game->BoundsW();
				float dy = 0;
				obj->Collide(dy, -dx);
				collision_detected = true;

				obj->Update(GameObject::Action::hit);
			}
			// Check against bottom bounds
			else if (obj->IntersectsLine(0, game->BoundsH(), game->BoundsW(), game->BoundsH()) || y > pg_bottom) {
				float dx = -game->BoundsW();
				float dy = 0;
				obj->Collide(dy, -dx);
				collision_detected = true;

				obj->Update(GameObject::Action::hit_ground);
			}

			obj->CollisionDetected(collision_detected);
		}
	}

	void Physics::CheckMovableCollision(Game* game, std::vector<MovableGameObject*> &objs, GameObject& go) {
		for (auto obj : objs) {
			bool collision_detected = false;

			float x_normal, y_normal;
			if (go.IntersectsWith(obj, &x_normal, &y_normal)) {
				obj->Collide(x_normal, y_normal);
				go.CollisionDetected(true);
				collision_detected = true;

				obj->Update(GameObject::Action::hit);
				go.Update(GameObject::Action::hit);
			}

			obj->CollisionDetected(collision_detected);
		}
	}
	
	void Physics::CheckMovableCollision(Game* game, std::vector<MovableGameObject*> &objs, std::vector<GameObject*> &gos) {
		for (auto& obj : objs) {
			bool collision_detected = false;

			for (auto go : gos) {
				float x_normal, y_normal;
				if (go->IntersectsWith(obj, &x_normal, &y_normal)) {
					obj->Collide(x_normal, y_normal);
					go->CollisionDetected(true);
					collision_detected = true;

					obj->Update(GameObject::Action::hit);
					go->Update(GameObject::Action::hit);
				}
			}

			obj->CollisionDetected(collision_detected);
		}
	}
}