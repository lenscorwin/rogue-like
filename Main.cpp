
#include "stdafx.h"

class	acteur : public GameManager, public b2ContactListener {
	public:
		acteur(void) {
			this->a = new PhysicsActor();
			this->a->SetPosition(0, 0);
			this->a->SetColor(1, 0, 0);
			this->a->SetDrawShape(ADS_Square);
			this->a->SetSize(2);
			this->a->SetName("John");
			this->a->Tag("Hero");
			this->a->SetDensity(1.0f);
			this->a->SetFriction(0.5f);
			this->a->SetRestitution(0.0f);
			this->a->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
			this->a->InitPhysics();
			theWorld.Add(this->a);
			theSwitchboard.SubscribeTo(this, "Jump");
			theSwitchboard.SubscribeTo(this, "Done.");
			theSwitchboard.SubscribeTo(this, "CollisionStartWith:hero.ground");
			theSwitchboard.SubscribeTo(this, "CollisionStartWith:ground.hero");
			this->isJump = 0;

			this->b = new PhysicsActor();
			this->b->SetPosition(0, -9);
			this->b->SetColor(1, 0, 0);
			this->b->SetDrawShape(ADS_Square);
			this->b->SetSize(2);
			this->b->Tag("Ground");
			this->b->SetName("Ground");
			this->b->SetDensity(1.0f);
			this->b->SetFriction(0.5f);
			this->b->SetRestitution(0.0f);
			this->b->SetShapeType(PhysicsActor::SHAPETYPE_BOX);
			this->b->InitPhysics();
			this->b->ApplyForce(Vector2(0, 1500), Vector2(0, 0));
			theWorld.Add(this->b);

		};

		~acteur() {};
		void	ReceiveMessage(Message *m) {
				std::cout << m->GetMessageName() << std::endl;
				if (m->GetMessageName() == "Jump") {
					if (this->a->GetBody()->IsAwake() == 0) {
						this->a->ApplyForce(Vector2(0, 1500), Vector2(0, 0));
					}
				} else if (m->GetMessageName() == "Done.") {
					std::cout << "Done." << std::endl;
					this->a->MoveTo(Vector2(this->a->GetPosition().X, 0), 0.4f, true, "");
				}
		};

	private:
		PhysicsActor	*a;
		PhysicsActor	*b;
		int				isJump;
};

int main(int argc, char* argv[])
{
	theWorld.Initialize(1024, 768, "Test", false, false, false);
	theWorld.SetupPhysics();
	theWorld.Add(new GridActor(), -1);
	theWorld.SetSideBlockers(true, 0.0f);
	new acteur();
	theWorld.StartGame();
	theWorld.Destroy();
	return 0;
}

