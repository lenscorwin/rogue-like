#include <list>
#include "stdafx.h"

class HeroActor: public PhysicsActor {
public:
	virtual const String	GetClassName() {
		return "HeroActor";
	}
	int				touchingGround;
	int				touchingWall;
	int				jumping;
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
		ActorSet		actor = theTagList.GetObjectsTagged("actor");

		if (hero->GetBody() == contact->GetFixtureA()->GetBody()) {
			std::cout << "------------ BEGIN -------------" << std::endl;
			std::cout << "X: " << hero->GetBody()->GetWorldCenter().x << ":" << contact->GetFixtureB()->GetBody()->GetWorldCenter().x << std::endl;
			std::cout << "Y: " << hero->GetBody()->GetWorldCenter().y << ":" << contact->GetFixtureB()->GetBody()->GetWorldCenter().y << std::endl;
			for (ActorSet::iterator it = actor.begin(); it != actor.end(); it++) {
				if (static_cast<PhysicsActor*>(*it)->GetBody() == contact->GetFixtureB()->GetBody()) {
					//Touching ground
					if (hero->GetBody()->GetWorldCenter().y > contact->GetFixtureB()->GetBody()->GetWorldCenter().y + 1 &&
						(hero->GetBody()->GetWorldCenter().x > contact->GetFixtureB()->GetBody()->GetWorldCenter().x + 1.05 ||
						 hero->GetBody()->GetWorldCenter().x > contact->GetFixtureB()->GetBody()->GetWorldCenter().x - 1.05)) {
						hero->touchingGround++;
						hero->jumping = 2;
						if (hero->touchingGround > 1) {
							contact->SetEnabled(false);
						}
						std::cout << "Ground Touched" << ": " << hero->touchingGround << std::endl;
					}
					//Touching Wall
					else if (hero->GetBody()->GetWorldCenter().y < contact->GetFixtureB()->GetBody()->GetWorldCenter().y + 1) {
						hero->touchingWall++;
//						if (hero->touchingWall > 1) {
//							contact->SetEnabled(false);
//						}
						std::cout << "Wall Touched" << ": " << hero->touchingWall << std::endl;
					}
					else
						std::cout << "Contact ignored" << std::endl;
				}
			}
			std::cout << "------------- /BEGIN --------- " << std::endl;
		}
		else if  (hero->GetBody() == contact->GetFixtureB()->GetBody())
			std::cout << "Hero in B" << std::endl;
	};

	void	EndContact(b2Contact *contact) {
		HeroActor	*hero = static_cast<HeroActor*>(Actor::GetNamed("Hero"));
		ActorSet	actor = theTagList.GetObjectsTagged("actor");

		if (hero->GetBody() == contact->GetFixtureA()->GetBody()) {
			std::cout << "------------ END -------------" << std::endl;
			std::cout << "X: " << hero->GetBody()->GetWorldCenter().x << ":" << contact->GetFixtureB()->GetBody()->GetWorldCenter().x << std::endl;
			std::cout << "Y: " << hero->GetBody()->GetWorldCenter().y << ":" << contact->GetFixtureB()->GetBody()->GetWorldCenter().y << std::endl;
			for (ActorSet::iterator it = actor.begin(); it != actor.end(); it++) {
				if (static_cast<PhysicsActor*>(*it)->GetBody() == contact->GetFixtureB()->GetBody()) {
					//if contactB == ground - TODO
					if (hero->GetBody()->GetWorldCenter().y > contact->GetFixtureB()->GetBody()->GetWorldCenter().y + 1 &&
						(hero->GetBody()->GetWorldCenter().x > contact->GetFixtureB()->GetBody()->GetWorldCenter().x + 1.05 ||
						 hero->GetBody()->GetWorldCenter().x > contact->GetFixtureB()->GetBody()->GetWorldCenter().x - 1.05)) {
						//Leaving the ground
						std::cout << "Leaving ground" << std::endl;

						hero->touchingGround--;
						if (hero->touchingGround <= 0) {
							hero->jumping--;
							hero->touchingGround = 0;
						}
					}
					else if (hero->touchingWall > 0) {
						std::cout << "Leaving wall" << std::endl;
						hero->touchingWall--;
					}
				}
			}
			std::cout << "-------------- /END ----------" << std::endl;
		}
	};
};


class GroundActor: public PhysicsActor {
public:
	virtual const String	GetClassName() {
		return "GroundActor";
	}
	bool _isRightUsed;
	bool _isLeftUsed;
	bool _isTopUsed;
	bool _isBotUsed;
};


class Hero: public GameManager {

public:
	Hero(void) {

		this->p1 = new HeroActor();
		this->p1->SetPosition(-3.0f, 5.0f);
		this->p1->SetDrawShape(ADS_Square);
		this->p1->SetSize(1.0f);
		this->p1->SetColor(0,0,0);
		this->p1->SetDensity(1.0f);
		this->p1->SetFriction(1.0f);
		this->p1->SetName("Hero");
		this->p1->SetRestitution(0.0f);
//		this->p1->SetSprite("Resources/Images/kappa.png");
		this->p1->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
		this->p1->InitPhysics();
		this->p1->GetBody()->SetFixedRotation(true);
		theWorld.Add(this->p1);


		for (int i = -13; i <= 18; i++) {
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
			(*it)->Tag("Floor, actor");
			(*it)->SetFriction(1.0f);
			(*it)->SetRestitution(0.0f);
			(*it)->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
			(*it)->InitPhysics();
			i++;
			theWorld.Add(*it);
		}

		theSwitchboard.SubscribeTo(this, "Jump");
		theSwitchboard.SubscribeTo(this, "ForPressed");
		theSwitchboard.SubscribeTo(this, "BackPressed");
		theSwitchboard.SubscribeTo(this, "ForReleased");
		theSwitchboard.SubscribeTo(this, "BackReleased");
		theSwitchboard.SubscribeTo(this, "Smash");

		theSwitchboard.SubscribeTo(this, "Attack");
		theSwitchboard.SubscribeTo(this, "CollisionStartWithHero");
		theSwitchboard.SubscribeTo(this, "CollisionEndWithHero");
	};

	~Hero(void) {
	};

	void	ReceiveMessage(Message *m) {
		if (m->GetMessageName() == "Jump" && this->p1->jumping > 0) {
			this->p1->ApplyForce(Vector2(0.0f, 500.0f), Vector2(0.0f, 0.0f));
			if (p1->touchingGround == 0)
				p1->jumping--;
		}

		if (m->GetMessageName() == "Smash") {
			this->p1->ApplyForce(Vector2(0.0f, -10000.0f), Vector2(0.0f, 0.0f));
		}

		if (m->GetMessageName() == "ForPressed" || m->GetMessageName() == "ForReleased") {
			MoveForward();
		}
		if (m->GetMessageName() == "BackPressed" || m->GetMessageName() == "BackReleased") {
			MoveBackward();
		}
	};

 	void	MoveForward(void) {
 		if (this->p1->GetBody()->GetLinearVelocity().x < 5) {
 			this->p1->ApplyForce(Vector2(50.0f, 0.0f), Vector2(0.0f, 0.0f));
		}
 	};

 	void	MoveBackward(void) {
 		if (this->p1->GetBody()->GetLinearVelocity().x > -5) {
 			this->p1->ApplyForce(Vector2(-50.0f, 0.0f), Vector2(0.0f, 0.0f));
		}
 	};

private:
	std::list<GroundActor*> floor;
	HeroActor		*p1;
	PhysicsActor	*map;

};

int main(int argc, char* argv[])
{
	theWorld.Initialize(1920, 1024, "Test", false, false, false);
	theWorld.Add(new GridActor(), -1);

	theWorld.SetupPhysics();
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
