//shop.cpp
#include "Shop.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "CharacterInfo.h"
Shop::Shop()
{
}

Shop::~Shop()
{
}

void Shop::init()
{
	ShopUI.pos.Set(40, 40, 0);
	ShopUI.resize_button(80,70);
	ShopUI.mesh = MeshList::GetInstance()->getMesh("Shop");
	//Buy Items
	Buy1.pos.Set(80, 50, 0);
	Buy1.resize_button(10, 10);
	Buy1.mesh = MeshList::GetInstance()->getMesh("Buy");


	Buy2.pos.Set(80, 40, 0);
	Buy2.resize_button(10, 10);
	Buy2.mesh = MeshList::GetInstance()->getMesh("Buy");
	/*
	Buy3.pos.Set(0, 9, 0);
	Buy3.resize_button(20, 10);
	Buy3.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	Buy4.pos.Set(0, 9, 0);
	Buy4.resize_button(20, 10);
	Buy4.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	Buy5.pos.Set(0, 9, 0);
	Buy5.resize_button(20, 10);
	Buy5.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	Buy6.pos.Set(0, 9, 0);
	Buy6.resize_button(20, 10);
	Buy6.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	Buy7.pos.Set(0, 9, 0);
	Buy7.resize_button(20, 10);
	Buy7.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	Buy8.pos.Set(0, 9, 0);
	Buy8.resize_button(20, 10);
	Buy8.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	Buy9.pos.Set(0, 9, 0);
	Buy9.resize_button(20, 10);
	Buy9.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");*/
	//Sell Items--------------------------------------------------------------------------------//
	Sell1.pos.Set(90, 50, 0);
	Sell1.resize_button(10, 10);
	Sell1.mesh = MeshList::GetInstance()->getMesh("Sell");

	Sell2.pos.Set(90, 40, 0);
	Sell2.resize_button(10, 10);
	Sell2.mesh = MeshList::GetInstance()->getMesh("Sell");

	//Sell3.pos.Set(0, 9, 0);
	//Sell3.resize_button(20, 10);
	//Sell3.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	//Sell4.pos.Set(0, 9, 0);
	//Sell4.resize_button(20, 10);
	//Sell4.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	//Sell5.pos.Set(0, 9, 0);
	//Sell5.resize_button(20, 10);
	//Sell5.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	//Sell6.pos.Set(0, 9, 0);
	//Sell6.resize_button(20, 10);
	//Sell6.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	//Sell7.pos.Set(0, 9, 0);
	//Sell7.resize_button(20, 10);
	//Sell7.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	//Sell8.pos.Set(0, 9, 0);
	//Sell8.resize_button(20, 10);
	//Sell8.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");

	//Sell9.pos.Set(0, 9, 0);
	//Sell9.resize_button(20, 10);
	//Sell9.mesh = MeshList::GetInstance()->getMesh("PLAYBUTTON");
}

void Shop::Update(double dt)
{
	//cout << "test" << endl;
	cout << walletshop->getsmallrepair() << endl;
	worldHeight = 100;
	worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	double x, y;
	Application::GetCursorPos(&x, &y);

	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	//std::cout << float(x / w * worldWidth) << std::endl;

	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);
	Collision cursor_collider;
	cursor_collider.collisionType = Collision::POINT;
	cursor_collider.mid = &cursor_point_in_world_space;

	if (Application::IsMousePressed(0))
	{
		if (Buy1.collision.isCollide(cursor_collider))
		{
			walletshop->addi_smallrepair(walletshop->getsmallrepair());
			
		}
		if (Sell1.collision.isCollide(cursor_collider))
		{
			walletshop->removei_smallrepair(walletshop->getsmallrepair());
		}

	}
}

void Shop::Render()
{
	ShopUI.render_button();
	//Buy
	Buy1.render_button();
	Buy2.render_button();
	/*Buy3.render_button();
	Buy4.render_button();
	Buy5.render_button();
	Buy6.render_button();
	Buy7.render_button();
	Buy8.render_button();
	Buy9.render_button();*/
	//Sell
	Sell1.render_button();
	Sell2.render_button();
	/*Sell3.render_button();
	Sell4.render_button();
	Sell5.render_button();
	Sell6.render_button();
	Sell7.render_button();
	Sell8.render_button();
	Sell9.render_button();*/
}

void Shop::attachWalletInfo(Wallet * walletshop)
{
	this->walletshop = walletshop;
}
