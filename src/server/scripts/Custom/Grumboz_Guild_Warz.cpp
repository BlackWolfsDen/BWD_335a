/*
-- **g****************************************s***
-- ********© Grumbo'z Guild Warz System™ ©********
-- ********** Brought to you by Grumbo  *******l**
-- **r*************** slp13at420 ****p************
-- ********************** of *********************
-- ****************  Emudevs.com  **********1*****
-- **u******************?*********3***************
-- *********************?*************************
-- ************ This is A C++ SCRIPT **a**********
-- ***m***********  This is For  *****************
-- ************** TRINITY Core ONLY *t************
-- *?*******************4***********************?*
-- *b* Please Do Not Rem©ve any of the credits ***
-- **** and/or attempt to release as your own **2*
-- ***o******************©*************0**********
-- **************** First Public *****************
-- ********** release date 03-10-2013 ************
-- ***********************************************
Grumbo'z Guild Warz
my fucked up idea of a Guild plot system.
Guilds can own multiple locations and take locations from another guild via PvP.
Scripted By Slp13at420 of EmuDevs.com
Trinity Core2 WotlK C++ version.
First Public release for BOOST date 03-10-2013.
*/
// !! On to the Madness Now !!

#include "Grumboz_Guild_Warz.h"
#include "ScriptPCH.h"
#include "Common.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "item.h"
#include "chat.h"
#include "ObjectMgr.h"
#include "player.h"
#include "Config.h"
#include "WorldSession.h"
#include "World.h"
#include <cstring>
#include <unordered_map>

// hard stored settings //
uint64 Guard_Died_Drop = 20558; // wsg's
float table_version = 2.75f;
float core_version = 6.50f;
float pigpayz_version = 2.50f;
float tele_version = 1.50f;
float pvp_version = 4.80f;
float vendor_version = 1.50f;

uint64 SERVER_GUILD_ID = 0;
std::string SERVER_GUILD_NAME = "SERVER";

// db address's in string value for sql updates
std::string Guild_Warz_DB = sConfigMgr->GetStringDefault("guild_warz_DB.address", "guild_warz_335");
std::string commands_db = Guild_Warz_DB + ".commands";
std::string help_db = Guild_Warz_DB + ".help";
std::string zones_db = Guild_Warz_DB + ".zones";

/*
// ---------------------------------------------------- -
// built - in vendors operational switches and item tables
// ---------------------------------------------------- -
uint8 vendor1 = 1; // use built - in vendor 1 0 / 1 no / yes.
uint8 vendor2 = 1; // use built - in vendor 2 0 / 1 no / yes.
uint8 vendor3 = 1; // use built - in vendor 3 0 / 1 no / yes.
*/

std::unordered_map<uint64, Commands>GWCOMM;
std::unordered_map<uint64, Help>GWHELP;
std::unordered_map<uint64, LocData>GWARZ;

GuildWarz::GuildWarz() { }

GuildWarz::~GuildWarz()
{
}

class LoadGWtable : public WorldScript
{
public: LoadGWtable() : WorldScript("LoadGWtable"){ };

		virtual void OnConfigLoad(bool /*reload*/)
		{
			TC_LOG_INFO("server.loading", "______________________________________");
			TC_LOG_INFO("server.loading", "-         Grumbo'z Guild Warz        -");
			TC_LOG_INFO("server.loading", "______________________________________");
			TC_LOG_INFO("server.loading", "-               LOADING              -");

			QueryResult ComQry = WorldDatabase.Query(("SELECT * FROM " + Guild_Warz_DB + ".commands;").c_str());

			if (ComQry)
			{
				do
				{
					Field *fields = ComQry->Fetch();
					// Save the DB values to the Commands object
					std::string guild = fields[0].GetString();
					std::string commands = fields[1].GetString();
					std::string info_loc = fields[2].GetString();
					std::string list_loc = fields[3].GetString();
					std::string tele = fields[4].GetString();
					std::string version = fields[5].GetString();
					uint8 GLD_lvlb = fields[6].GetUInt8();
					uint8 GLD_lvls = fields[7].GetUInt8();
					std::string respawn_flag = fields[8].GetString();
					std::string details_loc = fields[9].GetString();
					std::string table = fields[10].GetString();
					uint8 GM_admin = fields[11].GetUInt8();
					uint8 GM_minimum = fields[12].GetUInt8();
					uint64 currency = fields[13].GetUInt64();
					uint64 pig_payz = fields[14].GetUInt64();
					uint64 pig_payz_timer = fields[15].GetUInt64();
					uint64 gift_count = fields[16].GetUInt64();
					bool flag_require = fields[17].GetBool();
					std::string Server = fields[18].GetString();
					std::string command_set = fields[19].GetString();
					bool anarchy = fields[20].GetBool();
					uint64 flag_timer = fields[21].GetUInt64();
					uint64 spawn_timer = fields[22].GetUInt64();
					uint64 guild_id = fields[23].GetUInt64();
					bool guild_invite = fields[24].GetBool();
					std::string loc = fields[25].GetString();
					uint64 loc_cost = fields[26].GetUInt64();
					uint64 flag_id = fields[27].GetUInt64();
					std::string farm = fields[28].GetString();
					uint64 farm_cost = fields[29].GetUInt64();
					uint64 farm_L = fields[30].GetUInt64();
					uint64 farm_id = fields[31].GetUInt64();
					std::string barrack = fields[32].GetString();
					uint64 barrack_cost = fields[33].GetUInt64();
					uint64 barrack_L = fields[34].GetUInt64();
					uint64 barrack_id = fields[35].GetUInt64();
					std::string hall = fields[36].GetString();
					uint64 hall_cost = fields[37].GetUInt64();
					uint64 hall_L = fields[38].GetUInt64();
					uint64 hall_id = fields[39].GetUInt64();
					std::string pig = fields[40].GetString();
					uint64 pig_cost = fields[41].GetUInt64();
					uint64 pig_L = fields[42].GetUInt64();
					uint64 pig_id = fields[43].GetUInt64();
					std::string guard = fields[44].GetString();
					uint64 guard_cost = fields[45].GetUInt64();
					uint64 guard_L = fields[46].GetUInt64();
					uint64 guard_id = fields[47].GetUInt64();
					std::string vendor1 = fields[48].GetString();
					uint64 vendor1_cost = fields[49].GetUInt64();
					uint64 vendor1_L = fields[50].GetUInt64();
					uint64 vendor1_id = fields[51].GetUInt64();
					std::string vendor2 = fields[52].GetString();
					uint64 vendor2_cost = fields[53].GetUInt64();
					uint64 vendor2_L = fields[54].GetUInt64();
					uint64 vendor2_id = fields[55].GetUInt64();
					std::string vendor3 = fields[56].GetString();
					uint64 vendor3_cost = fields[57].GetUInt64();
					uint64 vendor3_L = fields[58].GetUInt64();
					uint64 vendor3_id = fields[59].GetUInt64();
					std::string cannon = fields[60].GetString();
					uint64 cannon_cost = fields[61].GetUInt64();
					uint64 cannon_L = fields[62].GetUInt64();
					uint64 cannon_id = fields[63].GetUInt64();
					std::string vault = fields[64].GetString();
					uint64 vault_cost = fields[65].GetUInt64();
					uint64 vault_L = fields[66].GetUInt64();
					uint64 vault_id = fields[67].GetUInt64();
					std::string mailbox = fields[68].GetString();
					uint64 mailbox_cost = fields[69].GetUInt64();
					uint64 mailbox_L = fields[70].GetUInt64();
					uint64 mailbox_id = fields[71].GetUInt64();
					std::string color_1 = fields[72].GetString();
					std::string color_2 = fields[73].GetString();
					std::string color_3 = fields[74].GetString();
					std::string color_4 = fields[75].GetString();
					std::string color_5 = fields[76].GetString();
					std::string color_6 = fields[77].GetString();
					std::string color_7 = fields[78].GetString();
					std::string color_8 = fields[79].GetString();
					std::string color_9 = fields[80].GetString();
					std::string color_10 = fields[81].GetString();
					std::string color_11 = fields[82].GetString();
					std::string color_12 = fields[83].GetString();
					std::string color_13 = fields[84].GetString();
					std::string color_14 = fields[85].GetString();
					std::string color_15 = fields[86].GetString();

					Commands& data = GWCOMM[guild_id]; // like Lua table GWARZ[guild_id].entry
					data.guild = guild;
					data.commands = commands;
					data.info_loc = info_loc;
					data.list_loc = list_loc;
					data.tele = tele;
					data.version = version;
					data.GLD_lvlb = GLD_lvlb;
					data.GLD_lvls = GLD_lvls;
					data.respawn_flag = respawn_flag;
					data.details_loc = details_loc;
					data.table = table;
					data.GM_admin = GM_admin;
					data.GM_minimum = GM_minimum;
					data.currency = currency;
					data.pig_payz = pig_payz;
					data.pig_payz_timer = pig_payz_timer;
					data.gift_count = gift_count;
					data.flag_require = flag_require;
					data.Server = Server;
					data.command_set = command_set;
					data.anarchy = anarchy;
					data.flag_timer = flag_timer;
					data.spawn_timer = spawn_timer;
					data.guild_id = guild_id;
					data.guild_invite = guild_invite;
					data.loc = loc;
					data.loc_cost = loc_cost;
					data.flag_id = flag_id;
					data.farm = farm;
					data.farm_cost = farm_cost;
					data.farm_L = farm_L;
					data.farm_id = farm_id;
					data.barrack = barrack;
					data.barrack_cost = barrack_cost;
					data.barrack_L = barrack_L;
					data.barrack_id = barrack_id;
					data.hall = hall;
					data.hall_cost = hall_cost;
					data.hall_L = hall_L;
					data.hall_id = hall_id;
					data.pig = pig;
					data.pig_cost = pig_cost;
					data.pig_L = pig_L;
					data.pig_id = pig_id;
					data.guard = guard;
					data.guard_cost = guard_cost;
					data.guard_L = guard_L;
					data.guard_id = guard_id;
					data.vendor1 = vendor1;
					data.vendor1_cost = vendor1_cost;
					data.vendor1_L = vendor1_L;
					data.vendor1_id = vendor1_id;
					data.vendor2 = vendor2;
					data.vendor2_cost = vendor2_cost;
					data.vendor2_L = vendor2_L;
					data.vendor2_id = vendor2_id;
					data.vendor3 = vendor3;
					data.vendor3_cost = vendor3_cost;
					data.vendor3_L = vendor3_L;
					data.vendor3_id = vendor3_id;
					data.cannon = cannon;
					data.cannon_cost = cannon_cost;
					data.cannon_L = cannon_L;
					data.cannon_id = cannon_id;
					data.vault = vault;
					data.vault_cost = vault_cost;
					data.vault_L = vault_L;
					data.vault_id = vault_id;
					data.mailbox = mailbox;
					data.mailbox_cost = mailbox_cost;
					data.mailbox_L = mailbox_L;
					data.mailbox_id = mailbox_id;
					data.color_1 = color_1;
					data.color_2 = color_2;
					data.color_3 = color_3;
					data.color_4 = color_4;
					data.color_5 = color_5;
					data.color_6 = color_6;
					data.color_7 = color_7;
					data.color_8 = color_8;
					data.color_9 = color_9;
					data.color_10 = color_10;
					data.color_11 = color_11;
					data.color_12 = color_12;
					data.color_13 = color_13;
					data.color_14 = color_14;
					data.color_15 = color_15;

				} while (ComQry->NextRow());

				TC_LOG_INFO("server.loading", "- commands loaded                    -");

			}

			QueryResult HlpQry = WorldDatabase.Query(("SELECT * FROM " + Guild_Warz_DB + ".help;").c_str());

			if (HlpQry)
			{
				do
				{
					Field *fields = HlpQry->Fetch();
					// Save the DB values to the Help object
					uint64 entry = fields[0].GetUInt64();
					std::string name = fields[1].GetString();
					std::string description = fields[2].GetString();
					std::string example = fields[3].GetString();
					uint8 command_level = fields[4].GetUInt8();

					Help& data = GWHELP[entry]; // like Lua table GWHELP[entry].entry
					data.entry = entry;
					data.name = name;
					data.description = description;
					data.example = example;
					data.command_level = command_level;
				} while (HlpQry->NextRow());

				TC_LOG_INFO("server.loading", "- help system loaded                 -");

			}

			QueryResult LocQry = WorldDatabase.Query(("SELECT * FROM " + Guild_Warz_DB + ".zones").c_str());

			if (LocQry)
			{
				do
				{
					Field *fields = LocQry->Fetch();
					// Save the DB values to the LocData object
					uint64 entry = fields[0].GetUInt64();
					uint64 map_id = fields[1].GetUInt64();
					uint64 area_id = fields[2].GetUInt64();
					uint64 zone_id = fields[3].GetUInt64();
					std::string guild_name = fields[4].GetString();
					uint64 team = fields[5].GetUInt8();
					float x = fields[6].GetFloat();
					float y = fields[7].GetFloat();
					float z = fields[8].GetFloat();
					uint64 farm_count = fields[9].GetUInt64();
					uint64 barrack_count = fields[10].GetUInt64();
					uint64 hall_count = fields[11].GetUInt64();
					uint64 pig_count = fields[12].GetUInt64();
					uint64 guard_count = fields[13].GetUInt64();
					uint64 vendor1_count = fields[14].GetUInt64();
					uint64 vendor2_count = fields[15].GetUInt64();
					uint64 vendor3_count = fields[16].GetUInt64();
					uint64 cannon_count = fields[17].GetUInt64();
					uint64 vault_count = fields[18].GetUInt64();
					uint64 mailbox_count = fields[19].GetUInt64();
					uint64 flag_id = fields[20].GetUInt64();
					uint64 fs_time = fields[21].GetUInt64();
					uint64 guild_id = fields[22].GetUInt64();

					LocData& data = GWARZ[entry]; // like Lua table GWARZ[guild_id].entry
					data.entry = entry;
					data.map_id = map_id;
					data.area_id = area_id;
					data.zone_id = zone_id;
					data.guild_name = guild_name;
					data.team = team;
					data.x = x;
					data.y = y;
					data.z = z;
					data.farm_count = farm_count;
					data.barrack_count = barrack_count;
					data.hall_count = hall_count;
					data.pig_count = pig_count;
					data.guard_count = guard_count;
					data.vendor1_count = vendor1_count;
					data.vendor2_count = vendor2_count;
					data.vendor3_count = vendor3_count;
					data.cannon_count = cannon_count;
					data.vault_count = vault_count;
					data.mailbox_count = mailbox_count;
					data.flag_id = flag_id;
					data.fs_time = fs_time;
					data.guild_id = guild_id;

				} while (LocQry->NextRow());
				uint32 id = GWCOMM[SERVER_GUILD_ID].currency;
                const ItemTemplate* temp = sObjectMgr->GetItemTemplate(id);
//				std::string Currencyname = temp->Name1; // std::string
				
				TC_LOG_INFO("server.loading", "SERVER_GUILD_ID ID:%u", SERVER_GUILD_ID);
				TC_LOG_INFO("server.loading", "ITEM ID:%u", GWCOMM[SERVER_GUILD_ID].currency);
				TC_LOG_INFO("server.loading", "ITEM TEMPLATE:%s", temp);
//				TC_LOG_INFO("server.loading", "- Guild Warz Currency:%s             -", Currencyname);

				TC_LOG_INFO("server.loading", "- locations loaded                   -");
				TC_LOG_INFO("server.loading", "- Guild Warz tables version:%.2f     -", table_version);
				TC_LOG_INFO("server.loading", "______________________________________");

			}
		};
};

uint64 GuildWarz::LoadGuildCommands(uint64 guild_id)
{
	const char guild_ID = guild_id;

	QueryResult ComQry = WorldDatabase.Query(("SELECT * FROM " + Guild_Warz_DB + ".commands WHERE guild_id = " + guild_ID + ";").c_str());

	if (!ComQry)
	{
		TC_LOG_INFO("server.loading", "Error loading Guild Command Guild ID:%u .", guild_id);
		return false;
	}

	if (ComQry)
	{
		Field *fields = ComQry->Fetch();
		// Save the DB values to the Commands object
		std::string guild = fields[0].GetString();
		std::string commands = fields[1].GetString();
		std::string info_loc = fields[2].GetString();
		std::string list_loc = fields[3].GetString();
		std::string tele = fields[4].GetString();
		std::string version = fields[5].GetString();
		uint8 GLD_lvlb = fields[6].GetUInt8();
		uint8 GLD_lvls = fields[7].GetUInt8();
		std::string respawn_flag = fields[8].GetString();
		std::string details_loc = fields[9].GetString();
		std::string table = fields[10].GetString();
		uint8 GM_admin = fields[11].GetUInt8();
		uint8 GM_minimum = fields[12].GetUInt8();
		uint64 currency = fields[13].GetUInt64();
		uint64 pig_payz = fields[14].GetUInt64();
		uint64 pig_payz_timer = fields[15].GetUInt64();
		uint64 gift_count = fields[16].GetUInt64();
		bool flag_require = fields[17].GetBool();
		std::string Server = fields[18].GetString();
		std::string command_set = fields[19].GetString();
		bool anarchy = fields[20].GetBool();
		uint64 flag_timer = fields[21].GetUInt64();
		uint64 spawn_timer = fields[22].GetUInt64();
		uint64 guild_id = fields[23].GetUInt64();
		bool guild_invite = fields[24].GetBool();
		std::string loc = fields[25].GetString();
		uint64 loc_cost = fields[26].GetUInt64();
		uint64 flag_id = fields[27].GetUInt64();
		std::string farm = fields[28].GetString();
		uint64 farm_cost = fields[29].GetUInt64();
		uint64 farm_L = fields[30].GetUInt64();
		uint64 farm_id = fields[31].GetUInt64();
		std::string barrack = fields[32].GetString();
		uint64 barrack_cost = fields[33].GetUInt64();
		uint64 barrack_L = fields[34].GetUInt64();
		uint64 barrack_id = fields[35].GetUInt64();
		std::string hall = fields[36].GetString();
		uint64 hall_cost = fields[37].GetUInt64();
		uint64 hall_L = fields[38].GetUInt64();
		uint64 hall_id = fields[39].GetUInt64();
		std::string pig = fields[40].GetString();
		uint64 pig_cost = fields[41].GetUInt64();
		uint64 pig_L = fields[42].GetUInt64();
		uint64 pig_id = fields[43].GetUInt64();
		std::string guard = fields[44].GetString();
		uint64 guard_cost = fields[45].GetUInt64();
		uint64 guard_L = fields[46].GetUInt64();
		uint64 guard_id = fields[47].GetUInt64();
		std::string vendor1 = fields[48].GetString();
		uint64 vendor1_cost = fields[49].GetUInt64();
		uint64 vendor1_L = fields[50].GetUInt64();
		uint64 vendor1_id = fields[51].GetUInt64();
		std::string vendor2 = fields[52].GetString();
		uint64 vendor2_cost = fields[53].GetUInt64();
		uint64 vendor2_L = fields[54].GetUInt64();
		uint64 vendor2_id = fields[55].GetUInt64();
		std::string vendor3 = fields[56].GetString();
		uint64 vendor3_cost = fields[57].GetUInt64();
		uint64 vendor3_L = fields[58].GetUInt64();
		uint64 vendor3_id = fields[59].GetUInt64();
		std::string cannon = fields[60].GetString();
		uint64 cannon_cost = fields[61].GetUInt64();
		uint64 cannon_L = fields[62].GetUInt64();
		uint64 cannon_id = fields[63].GetUInt64();
		std::string vault = fields[64].GetString();
		uint64 vault_cost = fields[65].GetUInt64();
		uint64 vault_L = fields[66].GetUInt64();
		uint64 vault_id = fields[67].GetUInt64();
		std::string mailbox = fields[68].GetString();
		uint64 mailbox_cost = fields[69].GetUInt64();
		uint64 mailbox_L = fields[70].GetUInt64();
		uint64 mailbox_id = fields[71].GetUInt64();
		std::string color_1 = fields[72].GetString();
		std::string color_2 = fields[73].GetString();
		std::string color_3 = fields[74].GetString();
		std::string color_4 = fields[75].GetString();
		std::string color_5 = fields[76].GetString();
		std::string color_6 = fields[77].GetString();
		std::string color_7 = fields[78].GetString();
		std::string color_8 = fields[79].GetString();
		std::string color_9 = fields[80].GetString();
		std::string color_10 = fields[81].GetString();
		std::string color_11 = fields[82].GetString();
		std::string color_12 = fields[83].GetString();
		std::string color_13 = fields[84].GetString();
		std::string color_14 = fields[85].GetString();
		std::string color_15 = fields[86].GetString();

		Commands& data = GWCOMM[guild_id]; // like Lua table GWARZ[guild_id].entry
		data.guild = guild;
		data.commands = commands;
		data.info_loc = info_loc;
		data.list_loc = list_loc;
		data.tele = tele;
		data.version = version;
		data.GLD_lvlb = GLD_lvlb;
		data.GLD_lvls = GLD_lvls;
		data.respawn_flag = respawn_flag;
		data.details_loc = details_loc;
		data.table = table;
		data.GM_admin = GM_admin;
		data.GM_minimum = GM_minimum;
		data.currency = currency;
		data.pig_payz = pig_payz;
		data.pig_payz_timer = pig_payz_timer;
		data.gift_count = gift_count;
		data.flag_require = flag_require;
		data.Server = Server;
		data.command_set = command_set;
		data.anarchy = anarchy;
		data.flag_timer = flag_timer;
		data.spawn_timer = spawn_timer;
		data.guild_id = guild_id;
		data.guild_invite = guild_invite;
		data.loc = loc;
		data.loc_cost = loc_cost;
		data.flag_id = flag_id;
		data.farm = farm;
		data.farm_cost = farm_cost;
		data.farm_L = farm_L;
		data.farm_id = farm_id;
		data.barrack = barrack;
		data.barrack_cost = barrack_cost;
		data.barrack_L = barrack_L;
		data.barrack_id = barrack_id;
		data.hall = hall;
		data.hall_cost = hall_cost;
		data.hall_L = hall_L;
		data.hall_id = hall_id;
		data.pig = pig;
		data.pig_cost = pig_cost;
		data.pig_L = pig_L;
		data.pig_id = pig_id;
		data.guard = guard;
		data.guard_cost = guard_cost;
		data.guard_L = guard_L;
		data.guard_id = guard_id;
		data.vendor1 = vendor1;
		data.vendor1_cost = vendor1_cost;
		data.vendor1_L = vendor1_L;
		data.vendor1_id = vendor1_id;
		data.vendor2 = vendor2;
		data.vendor2_cost = vendor2_cost;
		data.vendor2_L = vendor2_L;
		data.vendor2_id = vendor2_id;
		data.vendor3 = vendor3;
		data.vendor3_cost = vendor3_cost;
		data.vendor3_L = vendor3_L;
		data.vendor3_id = vendor3_id;
		data.cannon = cannon;
		data.cannon_cost = cannon_cost;
		data.cannon_L = cannon_L;
		data.cannon_id = cannon_id;
		data.vault = vault;
		data.vault_cost = vault_cost;
		data.vault_L = vault_L;
		data.vault_id = vault_id;
		data.mailbox = mailbox;
		data.mailbox_cost = mailbox_cost;
		data.mailbox_L = mailbox_L;
		data.mailbox_id = mailbox_id;
		data.color_1 = color_1;
		data.color_2 = color_2;
		data.color_3 = color_3;
		data.color_4 = color_4;
		data.color_5 = color_5;
		data.color_6 = color_6;
		data.color_7 = color_7;
		data.color_8 = color_8;
		data.color_9 = color_9;
		data.color_10 = color_10;
		data.color_11 = color_11;
		data.color_12 = color_12;
		data.color_13 = color_13;
		data.color_14 = color_14;
		data.color_15 = color_15;
	}
	return true;
};

uint64 GuildWarz::LoadCommandHelp(uint64 entry_id)
{
	const char entry_ID = entry_id;

	QueryResult HlpQry = WorldDatabase.Query(("SELECT * FROM " + Guild_Warz_DB + ".help WHERE entry_id = " + entry_ID + ";").c_str());

	if (!HlpQry)
	{
		TC_LOG_INFO("server.loading", "Error loading Command Help entry:%u .", entry_id);
		return false;
	}

	if (HlpQry)
	{
		Field *fields = HlpQry->Fetch();
		// Save the DB values to the Help object
		uint64 entry = fields[0].GetUInt64();
		std::string name = fields[1].GetString();
		std::string description = fields[2].GetString();
		std::string example = fields[3].GetString();
		uint8 command_level = fields[4].GetUInt8();

		Help& data = GWHELP[entry]; // like Lua table GWHELP[entry].entry
		data.entry = entry;
		data.name = name;
		data.description = description;
		data.example = example;
		data.command_level = command_level;
	}
	return true;
};

uint64 GuildWarz::LoadGuildLocation(uint64 loc_id)
{
	const char loc_ID = loc_id;

	QueryResult LocQry = WorldDatabase.Query(("SELECT * FROM " + Guild_Warz_DB + ".help WHERE entry_id = " + loc_ID + ";").c_str());

	if (!LocQry)
	{
		TC_LOG_INFO("server.loading", "Error loading Location ID:%u .", loc_id);
		return false;
	}

	if (LocQry)
    {
		Field *fields = LocQry->Fetch();
		// Save the DB values to the LocData object
		uint64 entry = fields[0].GetUInt64();
		uint64 map_id = fields[1].GetUInt64();
		uint64 area_id = fields[2].GetUInt64();
		uint64 zone_id = fields[3].GetUInt64();
		std::string guild_name = fields[4].GetString();
		uint64 team = fields[5].GetUInt8();
		float x = fields[6].GetFloat();
		float y = fields[7].GetFloat();
		float z = fields[8].GetFloat();
		uint64 farm_count = fields[9].GetUInt64();
		uint64 barrack_count = fields[10].GetUInt64();
		uint64 hall_count = fields[11].GetUInt64();
		uint64 pig_count = fields[12].GetUInt64();
		uint64 guard_count = fields[13].GetUInt64();
		uint64 vendor1_count = fields[14].GetUInt64();
		uint64 vendor2_count = fields[15].GetUInt64();
		uint64 vendor3_count = fields[16].GetUInt64();
		uint64 cannon_count = fields[17].GetUInt64();
		uint64 vault_count = fields[18].GetUInt64();
		uint64 mailbox_count = fields[19].GetUInt64();
		uint64 flag_id = fields[20].GetUInt64();
		uint64 fs_time = fields[21].GetUInt64();
		uint64 guild_id = fields[22].GetUInt64();

		LocData& data = GWARZ[entry]; // like Lua table GWARZ[guild_id].entry
		data.entry = entry;
		data.map_id = map_id;
		data.area_id = area_id;
		data.zone_id = zone_id;
		data.guild_name = guild_name;
		data.team = team;
		data.x = x;
		data.y = y;
		data.z = z;
		data.farm_count = farm_count;
		data.barrack_count = barrack_count;
		data.hall_count = hall_count;
		data.pig_count = pig_count;
		data.guard_count = guard_count;
		data.vendor1_count = vendor1_count;
		data.vendor2_count = vendor2_count;
		data.vendor3_count = vendor3_count;
		data.cannon_count = cannon_count;
		data.vault_count = vault_count;
		data.mailbox_count = mailbox_count;
		data.flag_id = flag_id;
		data.fs_time = fs_time;
		data.guild_id = guild_id;
	}
	return true;
const ItemTemplate* temp = sObjectMgr->GetItemTemplate(GWCOMM[SERVER_GUILD_ID].currency);
std::string Currencyname = temp->Name1;
};

uint64 GuildWarz::GetLocationID(uint64 map_id, uint64 area_id, uint64 zone_id)
{
//	const ItemTemplate* temp = sObjectMgr->GetItemTemplate(GWCOMM[SERVER_GUILD_ID].currency);
//	std::string Currencyname = temp->Name1;

	uint64 GWARZsize = GWARZ.size();

    TC_LOG_INFO("server.loading", "- GUILD SIZE %u -", GWARZsize);

//	uint64 loc_id = 0;

	for (uint64 loc_id = 1; loc_id < GWARZsize+1;loc_id++)
	{
		TC_LOG_INFO("server.loading", "- GUILD Location ID %u -", loc_id);

		if (GWARZ[loc_id].map_id == map_id)
		{
			if (GWARZ[loc_id].area_id == area_id)
			{
				if (GWARZ[loc_id].zone_id == zone_id)
				{
					return loc_id;
					break;
				}
			}
		}
	}
 return false;
};

uint64 GuildWarz::CreateGuildLocation(uint64 map_id, uint64 area_id, uint64 zone_id)
{

uint64 CLentry = (GWARZ.size() + 1);

TC_LOG_INFO("server.loading", "Guild Warz STORING NEW LOCATION:%u", CLentry);

LocData& data = GWARZ[CLentry]; // like Lua table GWARZ[guild_id].entry
	data.entry = CLentry;
	data.map_id = map_id;
	data.area_id = area_id;
	data.zone_id = zone_id;
	data.guild_name = "SERVER";
	data.team = 2;
	data.x = 0;
	data.y = 0;
	data.z = 0;
	data.farm_count = 0;
	data.barrack_count = 0;
	data.hall_count = 0;
	data.pig_count = 0;
	data.guard_count = 0;
	data.vendor1_count = 0;
	data.vendor2_count = 0;
	data.vendor3_count = 0;
	data.cannon_count = 0;
	data.vault_count = 0;
	data.mailbox_count = 0;
	data.flag_id = 0;
	data.fs_time = 0;
	data.guild_id = 0;

	std::string zones_db = "" + Guild_Warz_DB + ".zones";

	PreparedStatement* create = WorldDatabase.GetPreparedStatement(GUILD_WARZ_ADD_LOCATION);
	create->setUInt64(0, CLentry);
	create->setUInt64(1, GWARZ[CLentry].map_id);
	create->setUInt64(2, GWARZ[CLentry].area_id);
	create->setUInt64(3, GWARZ[CLentry].zone_id);
	create->setString(4, GWARZ[CLentry].guild_name);
	create->setUInt64(5, GWARZ[CLentry].guild_id);
	create->setUInt64(6, GWARZ[CLentry].team);
	WorldDatabase.Execute(create);

	TC_LOG_INFO("server.loading", "Guild Warz Location: %u : created ", GWARZ[CLentry].entry);

	TC_LOG_INFO("server.loading", "ENTRY:%u ", GWARZ[CLentry].entry);
	TC_LOG_INFO("server.loading", "MAP:%u   ", GWARZ[CLentry].map_id);
	TC_LOG_INFO("server.loading", "AREA:%u  ", GWARZ[CLentry].area_id);
	TC_LOG_INFO("server.loading", "ZONE:%u  ", GWARZ[CLentry].zone_id);

return CLentry;
};

void GuildWarz::UpdateGuildLocString(std::string column_target, std::string data_target, uint64 loc_id)
{
	std::string zones_db = "" + Guild_Warz_DB + ".zones";

	PreparedStatement* update_loc_str = WorldDatabase.GetPreparedStatement(GUILD_WARZ_UPD_LOCATION_DATA);
	update_loc_str->setString(0, column_target);
	update_loc_str->setString(1, data_target);
	update_loc_str->setUInt64(3, loc_id);
	WorldDatabase.Execute(update_loc_str);
};

void GuildWarz::UpdateGuildLocData(std::string column_target, uint64 data_target, uint64 loc_id)
{
	std::string zones_db = "" + Guild_Warz_DB + ".zones";

	PreparedStatement* update_loc_data = WorldDatabase.GetPreparedStatement(GUILD_WARZ_UPD_LOCATION_DATA);
	update_loc_data->setString(0, column_target);
	update_loc_data->setUInt64(1, data_target);
	update_loc_data->setUInt64(3, loc_id);
	WorldDatabase.Execute(update_loc_data);
};




void GuildWarz::UpdateGuildCommandData(std::string command_target, std::string new_data, uint64 guild_id)
{
	const char guild_ID = guild_id;

	WorldDatabase.PExecute("UPDATE INTO %s SET %s=%u WHERE entry = %u;", commands_db.c_str(), command_target, new_data, guild_id);

	GuildWarz::LoadGuildCommands(guild_id);
};


/*
-- ****************************************************
-- ******************* CORE ENGINE ********************
-- ****************************************************
*/
/*
class GWcommands : public PlayerScript
{
public: GWcommands() : PlayerScript("GWcommands"){ };

	virtual void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild)
	{
		uint64 map_id = 5;// player->GetMapId();
		uint64 area_id = 5;// player->GetAreaId();
		uint64 zone_id = 5;// player->GetZoneId();
		uint64 guild_id = player->GetGuildId();
		std::string guild_name = guild->GetName();
		uint8 pGuildRank = player->GetRank();
		uint8 pGMRank = player->GetSession()->GetSecurity();
		std::string pName = player->GetName();

		uint64 LocId = GuildWarz::GetLocationID(map_id, area_id, zone_id);

		if (! LocId)
		{
			LocId = GuildWarz::CreateGuildLocation(map_id, area_id, zone_id);
		}
	}
};
*/

class GetLoc : public WorldScript
{
public: GetLoc() : WorldScript("GetLoc"){ };

		virtual void OnConfigLoad(bool /*reload*/) // OnStartup()
		{
			uint64 pMap = 5;// 1;
			uint64 pArea = 5;// 1114;
			uint64 pZone = 5;// 357;

				TC_LOG_INFO("server.loading", "MAP:%u AREA:%u ZONE:%u", pMap, pArea, pZone);
			uint64 loc_ID = GuildWarz::GetLocationID(pMap, pArea, pZone);

			if (!loc_ID)
			{
				loc_ID = GuildWarz::CreateGuildLocation(pMap, pArea, pZone);
			}
			if (loc_ID)
			{
				TC_LOG_INFO("server.loading", "------------------------");
				TC_LOG_INFO("server.loading", "- GUILD Location ID %u -", loc_ID);
				TC_LOG_INFO("server.loading", "NAME:%s ", GWARZ[loc_ID].guild_name.c_str());
				TC_LOG_INFO("server.loading", "MAP:%u", GWARZ[loc_ID].map_id);
				TC_LOG_INFO("server.loading", "AREA:%u", GWARZ[loc_ID].area_id);
				TC_LOG_INFO("server.loading", "ZONE:%u", GWARZ[loc_ID].zone_id);
				TC_LOG_INFO("server.loading", "------------------------");
			};
		}
};

void AddSC_Grunboz_Guild_Warz()
{
	new LoadGWtable;
	new GetLoc;
}
//	new GWcommands;
