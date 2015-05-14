#include "monster.h"
#include "map.h"
#include "keyboard.h"
#include "actions.h"
#include "system.h"
#include "global.h"
#include "directions.h"
#include "options.h"
#include "attrib.h"
#include "level.h"
#include "places.h"
#include "parser.h"

extern GAME game;
extern KEYBOARD keyboard;
extern LEVEL level;
extern MYSCREEN screen;
extern DEFINITIONS definitions;
extern class OPTIONS options;

void PLACES :: print_on_terminal(int x, int y, string text)
{
	for (size_t a=0;a<text.size();a++)
	{
		char character = text[a];
		if (character!=' ')
			set_color(10);
		else
		{
			set_color(2);
			character='.';
		}
		print_character(x+4+a,y+4,character);
	}
}

void PLACES :: draw_terminal()
{
	screen.clear_all();
	int x,y;
	int sizex=57,sizey=21;
	for (x=2;x<=sizex;x++)
	{
		for (y=2;y<=sizey;y++)
		{
			if (x==2 || x==sizex || y==2 || y==sizey)
				set_color(2);
			else
				set_color(2);
			
			print_character(x,y,'.');
		}
	}
	
	set_color(8);
	for (x=3;x<=sizex+1;x++)
		print_character(x,sizey+1,'.');
	for (y=3;y<=sizey+1;y++)
		print_character(sizex+1,y,'.');	

}
void PLACES :: print_laboratory()
{
	draw_terminal();
	
	set_color(10);
				
	int px,py;
	px = 0;
	py = 0;
	string text;
	print_on_terminal(px,py++,"Ȧ�α׷� �͹̳� ver.0.7a");	
	py++;
	switch (random(5))
	{
	case 0: text="�ڻ��, �ȳ��ϼ���.";
		break;
	case 1: text="�ڻ��, �� ���̳׿�.";
		break;
	case 2: text="�ڻ��, �������̿���.";
		break;
	case 3: text="�ڻ��, �ݰ�����.";
		break;
	case 4: text="�ڻ��, ����� �����ּ���.";
		break;
	}
	print_on_terminal(px,py++,text);
	switch (random(5))
	{
	case 0: text="����� �����Դϱ�?";
		break;
	case 1: text="� ���α׷��� �����մϱ�?";
		break;
	case 2: text="������ ������Ʈ:";
		break;
	case 3: text="�������ּ���:";
		break;
	case 4: text="������ �����?";
		break;
	}
	print_on_terminal(px,py++,text);
	py++;
	print_on_terminal(px,py++,">1.����ü �缳�� 7");
	print_on_terminal(px,py++,">2.DNA ����");
	print_on_terminal(px,py++,">3.DI 227BS - DNA ����");
	print_on_terminal(px,py++,">4.���� ����");

	myrefresh();
}
	
bool PLACES::GeneticLaboratory()
{
	taken_DNA = "";
	print_laboratory();
	while(1)
	{
		int key = keyboard.wait_for_key();
		if (key == keyboard.escape || key == keyboard.readmore || key == keyboard.readmore2)
		{
			break;
		}		
		else if (key == '1')
		{
			if (GenLabBioRebuild()==true)
				return true;
			print_laboratory();
		}
		else if (key == '2')
		{
			if (GenLabDNAModif()==true)
				return true;
			print_laboratory();
		}
		else if (key == '3')
		{
			if (GenLabIntegration()==true)
				return true;
			print_laboratory();
		}
		else if (key == '4')
		{
			GenLabPersonalLog();
			print_laboratory();
		}
	}
	return false;
}

void PLACES::print_program_1()
{
	int px,py;
	px=0,py=0;

	draw_terminal();
	print_on_terminal(px,py++,"-= ����ü �缳�� ���α׷� =- ver. 7.12.24");
	py++;
	print_on_terminal(px,py++,"���� ����: 2081-02-05");
	py++;
	print_on_terminal(px,py++,"�ڰ� ����... CRC OK.");
	py++;
	print_on_terminal(px,py++,"�ϵ���� ����:");
	py++;
	print_on_terminal(px,py++,"����ü ������ ������... OK.");
	print_on_terminal(px,py++,"DNA ����� ������... OK.");
	print_on_terminal(px,py++,"�ϵ���� ���� �Ϸ�.");
	py++;
	py++;
	print_on_terminal(px,py++,"����� �ɼ�:");
	print_on_terminal(px,py++,">1.DNA�� ����� ����ü �缳��.");
	
	myrefresh();
}

void PLACES::print_program_2()
{
	int px,py;
	px=0,py=0;

	draw_terminal();
	print_on_terminal(px,py++,"����: ���� ������ �������� �ʽ��ϴ�.");
	print_on_terminal(px,py++,"���ο� ���� ������ ���ε��Ͻʽÿ�.");
	myrefresh();
}

void PLACES::print_program_3()
{
	int px,py;
	px=0,py=0;
	
	draw_terminal();
	print_on_terminal(px,py++,"���� DI 227BS");
	print_on_terminal(px,py++,"DNA ����");
	py++;
	if (taken_DNA=="")
		print_on_terminal(px,py++,"������ ���� DNA ������ �������� �ʽ��ϴ�.");
	else
		print_on_terminal(px,py++,"DNA ���� " + taken_DNA);
	py++;
	print_on_terminal(px,py++,">1.DNA�� ������ ����ü ����.");
	if (taken_DNA=="")
		print_on_terminal(px,py++," 2.��� �ִ� ����ü�� ������ DNA ����.");
	else
		print_on_terminal(px,py++,">2.��� �ִ� ����ü�� ������ DNA ����.");

	myrefresh();
}

void PLACES::print_program_4(int page)
{
	int px,py;
	px=0,py=0;

	draw_terminal();

	switch(page) {
	case 1:
		print_on_terminal(px,py++,"[ED 06-12-2189]");
		print_on_terminal(px,py++,"���� �����̴�! �����ڱ�赵 �� �۵��ϰ�,");
		print_on_terminal(px,py++,"DNA �ռ��� �� �̷������ �ִ�. �����δ�.");
		print_on_terminal(px,py++,"���� ȭ������ ������ ������ ��ٸ��� �ϸ� ���Ҵ�.");
		print_on_terminal(px,py++,"ȭ���� �̸��� ������? \"��Ʋ��\"��� �ߴ���?");
		print_on_terminal(px,py++,"���� ������ ������ �ٿ�.");
		print_on_terminal(px,17,">2. ���� ��");
		break;
	case 2:
		print_on_terminal(px,py++,"[ED 08-12-2189] (1/2)");
		print_on_terminal(px,py++,"������ �� �ִ� �����̶�� �ϳ��� �� ���Ҵµ�");
		print_on_terminal(px,py++,"���� ����� �����϶��? ���� ��� �������� �ƴϱ�!");
		print_on_terminal(px,py++,"ȭ������ ���� �����ؾ� ���ٵ�.");
		print_on_terminal(px,py++,"�������δ� ������ �鿩���� ������, �����δ�");
		print_on_terminal(px,py++,"�� �ӿ� ������ ���� �ܰ� ����ü���� ��� �ִ�.");
		print_on_terminal(px,py++,"�׷��� �� DNA ������ ��� �� �� �ְ���!");
		print_on_terminal(px,16,">1. �� ��");
		print_on_terminal(px,17,">2. ���� ��");
		break;
	case 3:
		print_on_terminal(px,py++,"[ED 08-12-2189] (2/2)");		
		print_on_terminal(px,py++,"�� ��ٸ��� ���ƴ�. ��û�� ���ε� �� ������ ����");
		print_on_terminal(px,py++,"����� ã�� ���ƾ� �ұ�? �Ƴ�, �׳���� �� ������");
		print_on_terminal(px,py++,"�󸶳� �߿������� ������ ���� �ֳ�. ��ġ �յ� ���ٺ���");
		print_on_terminal(px,py++,"���ϴ� ��û�̵�! �ֱ� �� �� ���� �ǹ��簡");
		print_on_terminal(px,py++,"�߻��ߴµ�, �׳���� �� ���迡�� ������ ����ü��");
		print_on_terminal(px,py++,"�����̶�� �ǽ��Ѵ�. ���� ����ü���� �� ���ּ� �����ϰ�");
		print_on_terminal(px,py++,"�����ϰ� �ִٰ� �׷��� ������ �ߴµ��� �� ���� ����");
		print_on_terminal(px,py++,"�ʴ´�. �ǹ����� ������ �����Լ��� ã�ٴ�, ��û��");
		print_on_terminal(px,py++,"���ε� �����϶��. �ڱ�� �߿� �ǿ� ȯ���� ���� ���ι���");
		print_on_terminal(px,py++,"������ ���� �˰ڳ�.");
		print_on_terminal(px,16,">1. �� ��");
		break;
	default:;
	}	
	myrefresh();
}


bool PLACES::GenLabBioRebuild()
{
	print_program_1();
	while(1)
	{
		int key = keyboard.wait_for_key();
		if (key == keyboard.escape || key == keyboard.readmore || key == keyboard.readmore2)
		{
			break;
		}		
		else if (key == '1')
		{
			level.player->hit_points.val = level.player->hit_points.max;

			for (int a=0;a<NUMBER_OF_STATES;a++)
				level.player->state[a]=0;

			screen.console.add("���̺� ���� ���´�. ��谡 �ֻ縦 ���´�. �� ���� �ٱ� �����Ѵ�...",7);
			screen.console.add("�Ǹ��� �۴�... �������� �� �ð��� ������. �� �ð��� �������� �� �� ����. ������ ���� ������ ����̴�.",7);

			level.player->wait(random(200)+100);				

			level.is_player_on_level = false;
			level.monsters.remove(level.player);
			level.map.setBlockMove(level.player->pX(),level.player->pY());
			
			return true;
		}
	}		
	return false;
}

bool PLACES::GenLabDNAModif()
{
	print_program_2();
	while(1)
	{
		int key = keyboard.wait_for_key();
		if (key == keyboard.escape || key == keyboard.readmore || key == keyboard.readmore2)
		{
			break;
		}		
	}		
	return false;
}


bool PLACES::GenLabIntegration()
{
	int character;
	ITEM *temp;
	CORPSE *cialo;
	MONSTER *monster;
	string text;
	int zwracana;

	print_program_3();
	while(1)
	{
		int key = keyboard.wait_for_key();

		if (key == keyboard.escape || key == keyboard.readmore || key == keyboard.readmore2)
		{
			break;
		}		
		else if (key == '1')
		{
			level.player->show_backpack(NULL,INV_SHOW_HIGHLIGHT_CORPSES);
            set_color(10);
			text = " ��� ��ü���� DNA�� �����մϱ�? ";
			level.player->adaptation_points = 6;
            print_text(40-text.size()/2,0,text);
			myrefresh();
            while (1)
            {
				character=keyboard.wait_for_key();
				if ((character>='a' && character<='z') || (character>='A' && character<='Z'))
				{
					temp=level.player->choose_item_from_backpack(character);
					if (temp!=NULL) // gdy cos wybrano
					{
						cialo = temp->IsCorpse();
						if (cialo!=NULL)
						{
							taken_DNA = cialo->of_what;
							cialo->death();
							print_program_3();
							break;							
						}
					}
				}
				else if (character==keyboard.escape || character==keyboard.readmore || character==keyboard.readmore2)
				{
					print_program_3();
					break;
				}				
			}
		}		
		else if (key == '2')
		{
			if (taken_DNA!="")
			{
				monster = definitions.find_monster(taken_DNA);

				draw_terminal();
				int px=0,py=0;
				print_on_terminal(px,py++,"�ڻ��!");
				print_on_terminal(px,py++,"�̰��� �ִ� ������ ��� ���Դϴ�!");
				print_on_terminal(px,py++,"������ ����� �ռ� ���� ����մϱ�?");
				py++;
				print_on_terminal(px,py++,"(y/n)");
				py++;
				print_on_terminal(px,py++,"(���輺�� �������̽��ϱ�?)");
				myrefresh();
				zwracana=keyboard.wait_for_key();
				if (zwracana!='y' && zwracana!='Y')
				{
					print_program_3();
					break;							
				}
				print_on_terminal(6,4,"Y");
				myrefresh();
				if (level.player->adaptation_points<1)
				{
					print_on_terminal(px,py++,"����� �������� �� DNA�� ������ �� �����ϴ�.");
					myrefresh();
					keyboard.wait_for_key();
					print_program_3();
					break;							
				}
				print_on_terminal(px,py++,"�����մϴ�...");
				delay(150);
				myrefresh();
				
				if (IntegratePlayerWith(monster)==false)
					return false;

				level.player->wait(random(500)+500);				
				level.is_player_on_level = false;
				level.monsters.remove(level.player);
				level.map.setBlockMove(level.player->pX(),level.player->pY());				
				return true;
			}
		}		
	}
	return false;
}


#define LOG_PAGES 3

bool PLACES::GenLabPersonalLog()
{
	int page = 1;
	print_program_4(page);
	while(1)
	{
		int key = keyboard.wait_for_key();
		if (key == '1' && page>1)
			page--;
		else if (key == '2' && page<LOG_PAGES)
			page++;		
		else if (key == keyboard.escape || key == keyboard.readmore || key == keyboard.readmore2)
		{
			break;
		}	
		print_program_4(page);		
	}		
	return false;
}

bool PLACES::IntegratePlayerWith(MONSTER *monster)
{
	if (monster==NULL)
		return false;
		
	level.player->adaptation_points--;

	screen.console.add(" \"����: DNA �ռ��� �����մϴ�.\".\n",11);		
	screen.console.add("���� ���...\n",7);		
	screen.console.add("... ... ... ...\n",7);		
	screen.console.add("������ ���� �� �ῡ�� �����.\n",7);		
	
	int random_value;

	int new_value;
	// power	

	if (level.player->strength.val < monster->strength.val)
		screen.console.add("���� ������ �����̴�...",7);
	else if (level.player->strength.val > monster->strength.val)
		screen.console.add("���� ������ �����̴�...",7);
	
	new_value = (level.player->strength.max + monster->strength.max)/2;
	level.player->strength.val += new_value - level.player->strength.max;
	level.player->strength.max = new_value;
	
	// zrecznosc
	if (level.player->dexterity.val < monster->dexterity.val)
		screen.console.add("���� �������� �����̴�...",7);
	else if (level.player->dexterity.val > monster->dexterity.val)
		screen.console.add("���� ������ �����̴�...",7);

	new_value = (level.player->dexterity.max + monster->dexterity.max)/2;
	level.player->dexterity.val += new_value - level.player->dexterity.max;
	level.player->dexterity.max = new_value;
	
	// wytrzymalosc
	if (level.player->endurance.val < monster->endurance.val)
		screen.console.add("���� �������� �����̴�...",7);
	else if (level.player->endurance.val > monster->endurance.val)
		screen.console.add("���� ������� �����̴�...",7);

	new_value = (level.player->endurance.max + monster->endurance.max)/2;
	level.player->endurance.val += new_value - level.player->endurance.max;
	level.player->endurance.max = new_value;
	
	// inteligencja
	if (level.player->intelligence.val < monster->intelligence.val)
		screen.console.add("��� ��Ȯ������...",7);
	else if (level.player->intelligence.val > monster->intelligence.val)
		screen.console.add("������ �� �� �ȴ�...",7);

	new_value = (level.player->intelligence.max + monster->intelligence.max)/2;
	level.player->intelligence.val += new_value - level.player->intelligence.max;
	level.player->intelligence.max = new_value;
	
	// szybko��
	if (level.player->speed.val < monster->speed.val)
		screen.console.add("�ൿ�� �绡������...",7);
	else if (level.player->intelligence.val > monster->intelligence.val)
		screen.console.add("�ൿ�� ��������...",7);
	
	new_value = (level.player->speed.max + monster->speed.max)/2;
	level.player->speed.val += new_value - level.player->speed.max;
	level.player->speed.max = new_value;
	
	// hit points

	if (level.player->hit_points.max < monster->hit_points.max)
		screen.console.add("������� ������ �����̴�...",7);
	else if (level.player->hit_points.max > monster->hit_points.max)
		screen.console.add("������� ������ �����̴�...",7);
	
	new_value = (level.player->hit_points.max + monster->hit_points.max)/2;
	level.player->hit_points.val += new_value - level.player->hit_points.max;
	level.player->hit_points.max = new_value;

	if (level.player->hit_points.val<=0)
		level.player->hit_points.val=1;
	
	// metabolizm
	random_value = level.player->metabolism.val - monster->metabolism.val;
	
	if (random_value>0) // player szybszy
	{
		if (random_value>4)
			random_value=4;
		
		random_value = random(random_value-1)+1;
		level.player->metabolism.val-=random_value;
		level.player->metabolism.val-=random_value;
	}
	else if (random_value<0) // player wolniejszy
	{
		if (random_value<4)
			random_value=-4;
		
		random_value = random(random_value-1)+1;
		level.player->metabolism.val+=random_value;
		level.player->metabolism.val+=random_value;
	}
	// skora
	bool change = false;
	if (level.player->no_armor.name != monster->no_armor.name)
	{
		if (level.player->no_armor.ARM < monster->no_armor.ARM)
		{
			level.player->no_armor.ARM++;
			change = true;
		}
		else if (level.player->no_armor.ARM > monster->no_armor.ARM)
		{
			level.player->no_armor.ARM--;
			change = true;
		}
		else // ARM jest takie samo, nabiera properties
		{
			for (PROPERTIES a=1;a!=TYPE_LAST_UNUSED;a+=a)
			{
				if (monster->no_armor.properties&a) // gdy ma ceche
				{
					if (!level.player->no_armor.properties&a) // gdy cechy nie ma
						if (random(3)==0)
						{
							level.player->no_armor.properties^=a; // ustawiamy bit
							change = true;						
							break;
						}
				}
				else if (!monster->no_armor.properties&a) // gdy nie ma cechy
				{
					if (level.player->no_armor.properties&a) // gdy ma ceche
						if (random(3)==0)
						{
							level.player->no_armor.properties^=a; // zerujemy w ten sposob dany bit
							change = true;						
							break;
						}
				}
			}			
		}
		if (monster->no_armor.ARM == level.player->no_armor.ARM &&
			monster->no_armor.properties == level.player->no_armor.properties)
		{
			screen.console.add(level.player->no_armor.name + "�� " + monster->no_armor.name + "���� �����Ǿ���.",7);			
			level.player->no_armor.name = monster->no_armor.name;
			level.player->no_armor.color = monster->no_armor.color;
		}
		else if (change)
			screen.console.add(level.player->no_armor.name + "�� " + monster->no_armor.name + "���� �����Ǿ���.",7);

	}
	// gole rece
	change = false;
	if (level.player->unarmed.name != monster->unarmed.name)
	{
		if (level.player->unarmed.DEF < monster->unarmed.DEF)
		{
			level.player->unarmed.DEF++;
			change = true;
		}
		else if (level.player->unarmed.DEF > monster->unarmed.DEF)
		{
			level.player->unarmed.DEF--;
			change = true;
		}

		if (level.player->unarmed.HIT < monster->unarmed.HIT)
		{
			level.player->unarmed.HIT++;
			change = true;
		}
		else if (level.player->unarmed.HIT > monster->unarmed.HIT)
		{
			level.player->unarmed.HIT--;
			change = true;
		}

		if (level.player->unarmed.DMG < monster->unarmed.DMG)
		{
			level.player->unarmed.DMG++;
			change = true;
		}
		else if (level.player->unarmed.DMG > monster->unarmed.DMG)
		{
			level.player->unarmed.DMG--;
			change = true;
		}
		
		for (PROPERTIES a=1;a<=TYPE_LAST_UNUSED;a+=a)
		{
			if (monster->unarmed.properties&a) // gdy ma ceche
			{
				if ((level.player->unarmed.properties&a)==0) // gdy cechy nie ma
				{
					change = true;						
					if (random(5)==0)
					{
						level.player->unarmed.properties^=a; // ustawiamy bit
						break;
					}
				}
			}
			else if (!monster->unarmed.properties&a) // gdy nie ma cechy
			{
				if ((level.player->unarmed.properties&a)==0) // gdy cechy nie ma
				{
					change = true;						
					if (random(5)==0)
					{
						level.player->unarmed.properties^=a; // zerujemy w ten sposob dany bit
						break;
					}
				}
			}
		}
		if (change)
			screen.console.add(level.player->unarmed.name + "�� ���̸� ����Ų��...",7);		
		else
		{
			screen.console.add(level.player->unarmed.name + "�� " + monster->unarmed.name + "���� �����Ǿ���!",7);		
			level.player->unarmed.name = monster->unarmed.name;
			level.player->unarmed.color = monster->unarmed.color;
		}
		
	}

	// resisty

	for (int b=0;b<NUMBER_OF_RESISTS;b++)
	{
		if (level.player->resist[b]<monster->resist[b])
			level.player->resist[b] += random(min(3,monster->resist[b] - level.player->resist[b]));
		else if (level.player->resist[b]>monster->resist[b])
			level.player->resist[b] -= random(min(3,level.player->resist[b] - monster->resist[b]));
	}
	
	level.player->set_weapon(&level.player->unarmed);
	level.player->set_armor(&level.player->no_armor);
	
	screen.console.add("\n \"DNA �ռ��� �Ϸ�Ǿ����ϴ�.\".",11);			
	return true;
}

