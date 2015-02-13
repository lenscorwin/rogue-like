#include <list>
#include "stdafx.h"

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

class Hero: public GameManager {

public:
	Hero(void) {
		this->p1 = new PhysicsActor();
		this->p1->SetPosition(-3.0f, 5.0f);
		this->p1->SetDrawShape(ADS_Square);
		this->p1->SetSize(1.0f);
		this->p1->SetDensity(1.0f);
		this->p1->SetFriction(1.0f);
		this->p1->SetName("Hero");
		this->p1->SetRestitution(0.0f);
		this->p1->SetSprite("Resources/Images/kappa.png");
		this->p1->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
		this->p1->InitPhysics();
		this->p1->GetBody()->SetFixedRotation(true);
		theWorld.Add(this->p1);

		for (int i = -13; i <= 18; i++) {
			this->floor.push_back(new PhysicsActor());
		}

		int i = -13;
		for (std::list<PhysicsActor*>::iterator it = this->floor.begin(); it != this->floor.end(); it++) {
			if (i > 13)
				(*it)->SetPosition(5, 8 - i);
			else
				(*it)->SetPosition(i, -10);
			(*it)->SetDrawShape(ADS_Square);
			(*it)->SetSize(1);
			(*it)->SetDensity(0.0f);
			(*it)->SetColor(1, 0, 0);
			(*it)->Tag("Floor");
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
		if (m->GetMessageName() == "Jump" && this->_jumping == 0) {
			this->p1->ApplyForce(Vector2(0.0f, 500.0f), Vector2(0.0f, 0.0f));
			this->_jumping = 1;
		}

		if (m->GetMessageName() == "Smash") {
			this->p1->ApplyForce(Vector2(0.0f, -10000.0f), Vector2(0.0f, 0.0f));
		}

		if (m->GetMessageName() == "ForPressed") {
			MoveForward();
		}
		if (m->GetMessageName() == "BackPressed") {
			MoveBackward();
		}
		if (m->GetMessageName() == "ForReleased") {
			MoveForward();
		}
		if (m->GetMessageName() == "BackReleased") {
			MoveBackward();
		}

		if (m->GetMessageName() == "CollisionStartWithHero") {
			std::cout << "Collision" << std::endl;
			this->_jumping = 0;
		}
	};

 	void	MoveForward(void) {
 		if (this->p1->GetBody()->GetLinearVelocity().x < 5) {
			std::cout << this->p1->GetBody()->GetLinearVelocity().x << std::endl;
 			this->p1->ApplyForce(Vector2(200.0f, 0.0f), Vector2(0.0f, 0.0f));
		}
 	};

 	void	MoveBackward(void) {
 		if (this->p1->GetBody()->GetLinearVelocity().x > -5) {
			std::cout << this->p1->GetBody()->GetLinearVelocity().x << std::endl;
 			this->p1->ApplyForce(Vector2(-200.0f, 0.0f), Vector2(0.0f, 0.0f));
		}
 	};

private:
	std::list<PhysicsActor*> floor;
	PhysicsActor	*p1;

	int				_jumping;
};

int main(int argc, char* argv[])
{
	theWorld.Initialize(1920, 1024, "Test", false, false, false);
	theWorld.Add(new GridActor(), -1);



	theWorld.SetupPhysics();
	theWorld.SetSideBlockers(true, 0.7f);

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
