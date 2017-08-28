//shop.cpp
#include "Shop.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "CharacterInfo.h"
#include "ShowHpManager.h"
Shop::Shop()
{
}

Shop::~Shop()
{
}

void Shop::init()
{
	
	ShopUI.pos.Set(30, 40, 0);
	ShopUI.resize_button(50,50);
	ShopUI.mesh = MeshList::GetInstance()->getMesh("Shop");

	ShopHeader.pos.Set(85, 40, 0);
	ShopHeader.resize_button(30, 80);
	ShopHeader.mesh = MeshList::GetInstance()->getMesh("header");

	Currentcoins.pos.Set(60, 5, 0);
	Currentcoins.resize_button(15, 15);
	Currentcoins.mesh = MeshList::GetInstance()->getMesh("currentcoins");
	//Buy Items
	Buy1.pos.Set(80, 65, 0);
	Buy1.resize_button(5, 5);
	Buy1.mesh = MeshList::GetInstance()->getMesh("Buy");


	Buy2.pos.Set(80, 55, 0);
	Buy2.resize_button(5, 5);
	Buy2.mesh = MeshList::GetInstance()->getMesh("Buy");
	
	Buy3.pos.Set(80, 45, 0);
	Buy3.resize_button(5, 5);
	Buy3.mesh = MeshList::GetInstance()->getMesh("Buy");

	Buy4.pos.Set(80 ,35, 0);
	Buy4.resize_button(5, 5);
	Buy4.mesh = MeshList::GetInstance()->getMesh("Buy");

	Buy5.pos.Set(80, 25, 0);
	Buy5.resize_button(5, 5);
	Buy5.mesh = MeshList::GetInstance()->getMesh("Buy");

	Buy6.pos.Set(80, 15, 0);
	Buy6.resize_button(5, 5);
	Buy6.mesh = MeshList::GetInstance()->getMesh("Buy");

	Buy7.pos.Set(80, 5, 0);
	Buy7.resize_button(5, 5);
	Buy7.mesh = MeshList::GetInstance()->getMesh("Buy");

	Buy8.pos.Set(80, -5, 0);
	Buy8.resize_button(5, 5);
	Buy8.mesh = MeshList::GetInstance()->getMesh("Buy");

	
	//Sell Items--------------------------------------------------------------------------------//
	Sell1.pos.Set(90, 65, 0);
	Sell1.resize_button(5, 5);
	Sell1.mesh = MeshList::GetInstance()->getMesh("Sell");

	Sell2.pos.Set(90, 55, 0);
	Sell2.resize_button(5, 5);
	Sell2.mesh = MeshList::GetInstance()->getMesh("Sell");

	Sell3.pos.Set(90, 45, 0);
	Sell3.resize_button(5, 5);
	Sell3.mesh = MeshList::GetInstance()->getMesh("Sell");

	Sell4.pos.Set(90, 35, 0);
	Sell4.resize_button(5, 5);
	Sell4.mesh = MeshList::GetInstance()->getMesh("Sell");

	Sell5.pos.Set(90, 25, 0);
	Sell5.resize_button(5, 5);
	Sell5.mesh = MeshList::GetInstance()->getMesh("Sell");

	Sell6.pos.Set(90, 15, 0);
	Sell6.resize_button(5, 5);
	Sell6.mesh = MeshList::GetInstance()->getMesh("Sell");

	Sell7.pos.Set(90, 5, 0);
	Sell7.resize_button(5, 5);
	Sell7.mesh = MeshList::GetInstance()->getMesh("Sell");



}

void Shop::Update(double dt)
{
	//cout << "test" << endl;
	//cout << walletshop->getsmallrepair() << endl;
	//worldHeight = 100;
	//worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	double x, y;
	GameLogic::GetInstance()->get_world_size(worldWidth, worldHeight);
	Application::GetCursorPos(&x, &y);

	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	//std::cout << float(x / w * worldWidth) << std::endl;

	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);
	Collision cursor_collider;
	cursor_collider.collisionType = Collision::POINT;
	cursor_collider.mid = &cursor_point_in_world_space;

	static bool mousereleased = true;
	if (Application::IsMousePressed(0) && mousereleased == true)
	{
		if (Buy1.collision.isCollide(cursor_collider))
		{
			walletshop->addi_smallrepair(walletshop->getsmallrepair());
			
		}
		if (Buy2.collision.isCollide(cursor_collider))
		{
			walletshop->addi_medrepair(walletshop->getmediumrepair());

		}
		if (Buy3.collision.isCollide(cursor_collider))
		{
			walletshop->addi_bigrepair(walletshop->getbigrepair());

		}
		//Drakes
		if (Buy4.collision.isCollide(cursor_collider))
		{
			walletshop->addi_greendrake(walletshop->getgreendrake());

		}
		if (Buy5.collision.isCollide(cursor_collider))
		{
			walletshop->addi_bluedrake(walletshop->getbluedrake());

		}
		if (Buy6.collision.isCollide(cursor_collider))
		{
			walletshop->addi_browndrake(walletshop->getbrowndrake());

		}
		if (Buy7.collision.isCollide(cursor_collider))
		{
			walletshop->addi_blackdrake(walletshop->getblackdrake());

		}
		//Weapon level
		if (Buy8.collision.isCollide(cursor_collider))
		{
			walletshop->addi_weaplevel(walletshop->getweaplevel());

		}
		
		//----------------------------------------------Sell------------------------------//
		if (Sell1.collision.isCollide(cursor_collider))
		{
			walletshop->removei_smallrepair(walletshop->getsmallrepair());
		}
		if (Sell2.collision.isCollide(cursor_collider))
		{
			walletshop->removei_medrepair(walletshop->getmediumrepair());

		}
		if (Sell3.collision.isCollide(cursor_collider))
		{
			walletshop->removei_bigrepair(walletshop->getbigrepair());

		}
		if (Sell4.collision.isCollide(cursor_collider))
		{
			walletshop->removei_greendrake(walletshop->getgreendrake());

		}
		if (Sell5.collision.isCollide(cursor_collider))
		{
			walletshop->removei_bluedrake(walletshop->getbluedrake());

		}
		if (Sell6.collision.isCollide(cursor_collider))
		{
			walletshop->removei_browndrake(walletshop->getbrowndrake());

		}
		if (Sell7.collision.isCollide(cursor_collider))
		{
			walletshop->removei_blackdrake(walletshop->getblackdrake());

		}
		mousereleased = false;
	}
	else if (!Application::IsMousePressed(0) && mousereleased == false)
		mousereleased = true;
}

void Shop::Render()
{
	MS& ms = Graphics::GetInstance()->modelStack;

	float defaultheight = 100.f * 600.f / 800.f;

	//hardcoded values are the default values

	//Buy----------------------------------------------------
	Buy1.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Buy1.pos.x = 80 * worldHeight / defaultheight;
	Buy1.pos.y = 65 * worldHeight / defaultheight;
	
	
	Buy2.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Buy2.pos.x = 80 * worldHeight / defaultheight;
	Buy2.pos.y = 55 * worldHeight / defaultheight;


	Buy3.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Buy3.pos.x = 80 * worldHeight / defaultheight;
	Buy3.pos.y = 45 * worldHeight / defaultheight;


	Buy4.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Buy4.pos.x = 80 * worldHeight / defaultheight;
	Buy4.pos.y = 35 * worldHeight / defaultheight;

	Buy5.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Buy5.pos.x = 80 * worldHeight / defaultheight;
	Buy5.pos.y = 25 * worldHeight / defaultheight;

	Buy6.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Buy6.pos.x = 80 * worldHeight / defaultheight;
	Buy6.pos.y = 15 * worldHeight / defaultheight;


	Buy7.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Buy7.pos.x = 80 * worldHeight / defaultheight;
	Buy7.pos.y = 5 * worldHeight / defaultheight;

	Buy8.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Buy8.pos.x = 80 * worldHeight / defaultheight;
	Buy8.pos.y = -5 * worldHeight / defaultheight;

	//Sell-------------------------------------------------
	Sell1.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Sell1.pos.x =90 * worldHeight / defaultheight;
	Sell1.pos.y = 65 * worldHeight / defaultheight;

	
	Sell2.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Sell2.pos.x = 90 * worldHeight / defaultheight;
	Sell2.pos.y = 55 * worldHeight / defaultheight;


	Sell3.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Sell3.pos.x = 90 * worldHeight / defaultheight;
	Sell3.pos.y = 45 * worldHeight / defaultheight;


	Sell4.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Sell4.pos.x = 90 * worldHeight / defaultheight;
	Sell4.pos.y = 35 * worldHeight / defaultheight;

	Sell5.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Sell5.pos.x = 90 * worldHeight / defaultheight;
	Sell5.pos.y = 25 * worldHeight / defaultheight;

	Sell6.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Sell6.pos.x = 90 * worldHeight / defaultheight;
	Sell6.pos.y = 15 * worldHeight / defaultheight;


	Sell7.resize_button(5.f * worldHeight / defaultheight, 5.f * worldHeight / defaultheight);
	Sell7.pos.x = 90 * worldHeight / defaultheight;
	Sell7.pos.y = 5 * worldHeight / defaultheight;

	
	//===================
	ms.PushMatrix();
	//this is here to make the shop image looks legit
	ms.Scale(worldHeight / defaultheight, worldHeight / defaultheight, 1);
	ShopUI.render_button();
	ShopHeader.render_button();
	Currentcoins.render_button();
	ms.PopMatrix();
	//Buy
	Buy1.render_button();
	Buy2.render_button();
	Buy3.render_button();
	Buy4.render_button();
	Buy5.render_button();
	Buy6.render_button();
	Buy7.render_button();
	Buy8.render_button();
	
	//Sell
	Sell1.render_button();
	Sell2.render_button();
	Sell3.render_button();
	Sell4.render_button();
	Sell5.render_button();
	Sell6.render_button();
	Sell7.render_button();

	ms.PushMatrix();
	ms.Translate(60, 0, 0);
	ms.Scale(5, 5, 5);
	RenderHelper::RenderText(&ShowHpManager::GetInstance()->get_font(), std::to_string(walletshop->getcoins()), Color(1,1,1));
	ms.PopMatrix();
}

void Shop::attachWalletInfo(Wallet * walletshop)
{
	this->walletshop = walletshop;
}
