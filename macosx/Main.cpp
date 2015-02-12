#include <list>
#include "stdafx.h"


class Hero: public GameManager {

public:
	Hero(void) {
		this->p1 = new PhysicsActor();
		this->p1->SetPosition(-3.0f, 5.0f);
		this->p1->SetDrawShape(ADS_Square);
//		this->p1->SetColor(1, 0, 0);
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
		theSwitchboard.SubscribeTo(this, "Jump");
		theSwitchboard.SubscribeTo(this, "Forward");
		theSwitchboard.SubscribeTo(this, "Backward");
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
		if (m->GetMessageName() == "Forward") {
			b2Vec2	curr(this->p1->GetBody()->GetLinearVelocity());
			curr
			this->p1->GetBody()->SetLinearVelocity(b2Vec2(1.0f, 0.0f));
		}
		if (m->GetMessageName() == "Backward") {
			this->p1->ApplyForce(Vector2(-100.0f, 0.0f), Vector2(0.0f, 0.0f));
		}
		if (m->GetMessageName() == "CollisionStartWithHero") {
			this->_jumping = 0;
		}
	}
private:
	PhysicsActor	*p1;
	int				_jumping;
};

int main(int argc, char* argv[])
{
	theWorld.Initialize(1024, 768, "Test", false, false, false);
	theWorld.Add(new GridActor(), -1);



	theWorld.SetupPhysics();

	Hero salut;

	std::list<PhysicsActor*> floor;

	for (int i = -13; i <= 18; i++) {
		floor.push_back(new PhysicsActor());
	}

	int i = -13;
	for (std::list<PhysicsActor*>::iterator it = floor.begin(); it != floor.end(); it++) {
		if (i > 13)
			(*it)->SetPosition(5, 8 - i);
		else
			(*it)->SetPosition(i, -10);
		(*it)->SetColor(0.0f, 0.0f, 0.0f);
		(*it)->SetDrawShape(ADS_Square);
		(*it)->SetSize(1.0f);
		(*it)->SetDensity(0.0f);
		(*it)->SetFriction(1.0f);
		(*it)->SetRestitution(0.0f);
		(*it)->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
		(*it)->InitPhysics();
		i++;
		theWorld.Add(*it);
	}

	theWorld.StartGame();


	theWorld.Destroy();
	return 0;
}
