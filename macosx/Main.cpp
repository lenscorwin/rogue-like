#include <list>
#include "stdafx.h"

class HeroActor: public PhysicsActor {
public:
	virtual const String	GetClassName(void) {
		return "HeroActor";
	};
	int					touchingGround;
	int					touchingWall;
	int					jumping;
	std::list<b2Body*>	grounds;
	int					orientation;
	int					up;
	bool				canMove;
};

class MouseDebugger: public MouseListener {
public:
	MouseDebugger(void) {
	};
	~MouseDebugger(void) {
	};
	void	MouseDownEvent(Vec2i sc, MouseButtonInput button) {
		Vector2 w;
		w = MathUtil::ScreenToWorld(sc.X, sc.Y);
		std::cout << w.X << ":" << w.Y << std::endl;
	};
};

/*
** Very Important Class: Checks if contact with ground or wall, disabling it if necessary to prevent the clutter
*/

class rContactListener: public b2ContactListener {
public:
	void	BeginContact(b2Contact *contact) {
		HeroActor*		hero = static_cast<HeroActor*>(Actor::GetNamed("Hero"));
		PhysicsActor*	weapon = static_cast<PhysicsActor*>(Actor::GetNamed("Weapon"));
		ActorSet		actor = theTagList.GetObjectsTagged("physics");

		if (hero->GetBody() == contact->GetFixtureA()->GetBody()) {
// 			std::cout << "------------ BEGIN -------------" << std::endl;
// 			std::cout << "X: " << hero->GetBody()->GetWorldCenter().x << ":" << contact->GetFixtureB()->GetBody()->GetWorldCenter().x << std::endl;
// 			std::cout << "Y: " << hero->GetBody()->GetWorldCenter().y << ":" << contact->GetFixtureB()->GetBody()->GetWorldCenter().y << std::endl;
			for (ActorSet::iterator it = actor.begin(); it != actor.end(); it++) {
				if (static_cast<PhysicsActor*>(*it)->GetBody() == contact->GetFixtureB()->GetBody()) {
					//Case ground/wall
					if ((*it)->IsTagged("ground") == true) {
						if (hero->GetBody()->GetWorldCenter().y > contact->GetFixtureB()->GetBody()->GetWorldCenter().y + 1) {
							hero->jumping = 2;
							int		found = 0;
							if (hero->grounds.size() > 0)
								contact->SetEnabled(false);
							for (std::list<b2Body*>::iterator it = hero->grounds.begin(); it != hero->grounds.end(); it++) {
								if ((*it) == contact->GetFixtureB()->GetBody()) {
									found = 1;
									contact->SetEnabled(false);
								}
							}
							if (found == 0) {
								hero->grounds.push_back(contact->GetFixtureB()->GetBody());
//							std::cout << "Ground Touched" << hero->grounds.size() << std::endl;
							}
						}
						//Touching Wall
						else {
							hero->touchingWall++;
							if (hero->touchingWall > 1) {
								contact->SetEnabled(false);
							}
//						std::cout << "Wall Touched" << hero->touchingWall << std::endl;
						}
					}
					//Case ennemy
					else if ((*it)->IsTagged("victim")) {
						hero->canMove = 0;
						theSwitchboard.DeferredBroadcast(new Message("CanMove"), 1.5f);
						hero->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
						if (static_cast<PhysicsActor*>((*it))->GetBody()->GetWorldCenter().x > hero->GetBody()->GetWorldCenter().x)
							hero->ApplyLinearImpulse(Vector2(-20, 20), Vector2(0, 0));
						else
							hero->ApplyLinearImpulse(Vector2(20, 20), Vector2(0, 0));
					}
				}
//			std::cout << "------------- /BEGIN --------- " << std::endl;
			}
		}
		else if  (hero->GetBody() == contact->GetFixtureB()->GetBody()) {
//			std::cout << "Hero in B" << std::endl;
		}
		else if (weapon) {
			if (weapon->GetBody() == contact->GetFixtureB()->GetBody())
				WeaponCollision(contact->GetFixtureA()->GetBody(), weapon);
			else if (weapon->GetBody() == contact->GetFixtureA()->GetBody())
				WeaponCollision(contact->GetFixtureB()->GetBody(), weapon);
		}
	};
	void	WeaponCollision(b2Body *contact, PhysicsActor* weapon) {
		if (weapon->GetBody()->GetWorldCenter().x > contact->GetWorldCenter().x)
			contact->ApplyLinearImpulse(b2Vec2(-20, 20), contact->GetWorldCenter());
		if (weapon->GetBody()->GetWorldCenter().x < contact->GetWorldCenter().x)
			contact->ApplyLinearImpulse(b2Vec2(20, 20), contact->GetWorldCenter());
	}

	void	EndContact(b2Contact *contact) {
		HeroActor	*hero = static_cast<HeroActor*>(Actor::GetNamed("Hero"));
		ActorSet	actor = theTagList.GetObjectsTagged("physics");

		if (hero->GetBody() == contact->GetFixtureA()->GetBody()) {
// 			std::cout << "------------ END -------------" << std::endl;
// 			std::cout << "X: " << hero->GetBody()->GetWorldCenter().x << ":" << contact->GetFixtureB()->GetBody()->GetWorldCenter().x << std::endl;
// 			std::cout << "Y: " << hero->GetBody()->GetWorldCenter().y << ":" << contact->GetFixtureB()->GetBody()->GetWorldCenter().y << std::endl;
			for (ActorSet::iterator it = actor.begin(); it != actor.end(); it++) {
				if (static_cast<PhysicsActor*>(*it)->GetBody() == contact->GetFixtureB()->GetBody()) {
					//if contactB == ground - TODO
					if (hero->GetBody()->GetWorldCenter().y > contact->GetFixtureB()->GetBody()->GetWorldCenter().y + 1 && hero->grounds.size() >= 1) {
						//Leaving the ground
						hero->grounds.remove(contact->GetFixtureB()->GetBody());
						if (hero->grounds.size() == 0) {
							hero->jumping--;
						}
//						std::cout << "Leaving ground: " << hero->grounds.size() << std::endl;
					}
					else if (hero->touchingWall > 0) {
						hero->touchingWall--;
//						std::cout << "Leaving wall:" << hero->touchingWall << std::endl;
					}
				}
			}
//			std::cout << "-------------- /END ----------" << std::endl;
		}
	};
};


class GroundActor: public PhysicsActor {
public:
	virtual const String	GetClassName() {
		return "GroundActor";
	}
};


class Hero: public GameManager {

public:
	Hero(void) {

		this->p1 = new HeroActor();
 		this->p1->SetPosition(-3.0f, 5.0f);
		this->p1->SetColor(0,0,0);
		this->p1->orientation = 1;
		this->p1->SetSize(1);
		this->p1->SetDrawShape(ADS_Square);
		this->p1->SetName("Hero");
		this->p1->SetShapeType(PhysicsActor::SHAPETYPE_HERO);
		this->p1->SetDensity(1.0f);
		this->p1->SetFriction(1.0f);
		this->p1->SetRestitution(0.0f);
		this->p1->SetFixedRotation(true);
		this->p1->canMove = true;
		this->p1->Tag("hero");

		this->p1->InitPhysics();
		theWorld.Add(this->p1);

		this->victim = new PhysicsActor();
 		this->victim->SetPosition(7.0f, 5.0f);
		this->victim->SetColor(0,1,0);
		this->victim->SetSize(1);
		this->victim->SetDrawShape(ADS_Square);
		this->victim->SetName("Victim");
		this->victim->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
		this->victim->SetDensity(1.0f);
		this->victim->SetFriction(1.0f);
		this->victim->SetRestitution(0.0f);
		this->victim->SetFixedRotation(true);
		this->victim->Tag("victim, physics");

		this->victim->InitPhysics();
		theWorld.Add(this->victim);


		for (int i = -13; i <= 13; i++) {
			this->floor.push_back(new GroundActor());
		}

		int i = -13;
		for (std::list<GroundActor*>::iterator it = this->floor.begin(); it != this->floor.end(); it++) {
			if (i > 13)
				(*it)->SetPosition(5, 8 - i);
			else
				(*it)->SetPosition(i, -10);
			(*it)->SetDrawShape(ADS_Square);
			(*it)->SetSize(1);
			(*it)->SetDensity(0.0f);
			(*it)->SetColor(1, 0, 0);
			(*it)->Tag("ground, Physics");
			(*it)->SetFriction(1.0f);
			(*it)->SetName("Ground");
			(*it)->SetRestitution(0.0f);
			(*it)->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
			(*it)->InitPhysics();
			i++;
			theWorld.Add(*it);
		}

		theSwitchboard.SubscribeTo(this, "Jump");
		theSwitchboard.SubscribeTo(this, "ForPressed");
		theSwitchboard.SubscribeTo(this, "BackPressed");
		theSwitchboard.SubscribeTo(this, "UpPressed");
		theSwitchboard.SubscribeTo(this, "DownPressed");
		theSwitchboard.SubscribeTo(this, "DownReleased");
		theSwitchboard.SubscribeTo(this, "UpReleased");
		theSwitchboard.SubscribeTo(this, "ForReleased");
		theSwitchboard.SubscribeTo(this, "BackReleased");
		theSwitchboard.SubscribeTo(this, "Smash");
		theSwitchboard.SubscribeTo(this, "Attack");
		theSwitchboard.SubscribeTo(this, "CanMove");
		theSwitchboard.SubscribeTo(this, "CollisionStartWithHero");
		theSwitchboard.SubscribeTo(this, "CollisionEndWithHero");
		theSwitchboard.SubscribeTo(this, "CollisionStartWithWeapon");
		theSwitchboard.SubscribeTo(this, "CollisionStartWithVictim");
		theSwitchboard.SubscribeTo(this, "CollisionStart:Hero.Victim");
		theSwitchboard.SubscribeTo(this, "DeleteWeapon");
	};

	~Hero(void) {
	};

	void	ReceiveMessage(Message *m) {
		if (m->GetMessageName() == "Jump" && this->p1->jumping > 0) {
			if (this->p1->canMove == 1) {
				this->p1->ApplyLinearImpulse(Vector2(0.0f, 30.0f), Vector2(0.0f, 0.0f));
				if (p1->grounds.size() == 0)
					p1->jumping--;
			}
		}

		if (m->GetMessageName() == "Smash") {
			if (this->p1->canMove == 1)
				this->p1->ApplyLinearImpulse(Vector2(0.0f, -1000.0f), Vector2(0.0f, 0.0f));
		}

		if (m->GetMessageName() == "Attack") {
			this->weapon = new PhysicsActor();
			this->weapon->SetPosition(this->p1->GetBody()->GetWorldCenter().x + this->p1->orientation, this->p1->GetBody()->GetWorldCenter().y +this->p1->up);
			this->weapon->SetColor(0,0,1);
			this->weapon->SetSize(1);
			this->weapon->SetDrawShape(ADS_Square);
			this->weapon->SetName("Weapon");
			this->weapon->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
			this->weapon->SetDensity(0.0f);
			this->weapon->SetFriction(1.0f);
			this->weapon->SetRestitution(0.3f);
			this->weapon->SetFixedRotation(true);
			this->weapon->Tag("weapon");
			this->weapon->SetIsSensor(true);
			this->weapon->InitPhysics();
			theWorld.Add(this->weapon);
		}

		if (m->GetMessageName() == "DeleteWeapon") {
			if (this->weapon) {
				theWorld.Remove(this->weapon);
				delete this->weapon;
			}
		}

		if (m->GetMessageName() == "CollisionStart:Hero.Ground") {
		}

		else if (m->GetMessageName() == "ForPressed" || m->GetMessageName() == "ForReleased") {
			this->p1->orientation = 1;
			this->p1->up = 0;
			if (this->p1->canMove == true) {
				MoveForward();
			}
		}
		else if (m->GetMessageName() == "BackPressed" || m->GetMessageName() == "BackReleased") {
			this->p1->orientation = -1;
			this->p1->up = 0;
			if (this->p1->canMove == true) {
				MoveBackward();
			}
		}
		else if (m->GetMessageName() == "UpPressed" || m->GetMessageName() == "UpReleased") {
			this->p1->orientation = 0;
			this->p1->up = 1;
		}
		else if (m->GetMessageName() == "DownPressed" || m->GetMessageName() == "DownReleased") {
			this->p1->orientation = 0;
			this->p1->up = -1;
		}

		else if (m->GetMessageName() == "CanMove")
			this->p1->canMove = 1;
	};

 	void	MoveForward(void) {
 		if (this->p1->GetBody()->GetLinearVelocity().x < 10) {
 			this->p1->ApplyLinearImpulse(Vector2(10.0f, 0.0f), Vector2(0.0f, 0.0f));
		}
 	};

 	void	MoveBackward(void) {
 		if (this->p1->GetBody()->GetLinearVelocity().x > -10) {
 			this->p1->ApplyLinearImpulse(Vector2(-10.0f, 0.0f), Vector2(0.0f, 0.0f));
		}
 	};

private:
	std::list<GroundActor*> floor;
	HeroActor		*p1;
	PhysicsActor	*weapon;
	PhysicsActor	*map;
	PhysicsActor	*victim;
};

int main(int argc, char* argv[])
{
	theWorld.Initialize(1920, 1024, "La soeur de ryad", false, false, false);
	theWorld.Add(new GridActor(), -1);

	theWorld.SetupPhysics(Vector2(0, -80));
	theWorld.SetSideBlockers(true, 0.7f);

	rContactListener cListen;
	theWorld.GetPhysicsWorld().SetContactListener(&cListen);

	Hero salut;



	b2Vec2 v1(-14, -9.6f);
	b2Vec2 v2(4, -9.6f);
	b2EdgeShape edge;
	edge.Set(v1, v2);
	MouseDebugger debug;
	theWorld.StartGame();


	theWorld.Destroy();
	return 0;
}
