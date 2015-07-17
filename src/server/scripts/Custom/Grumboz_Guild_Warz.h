#ifndef GRUMBOZ_GUILD_WARZ_H_INCLUDED
#define GRUMBOZ_GUILD_WARZ_H_INCLUDED

// #include <ace/Singleton.h>

struct Commands
{
	std::string guild;
	std::string commands;
	std::string info_loc;
	std::string list_loc;
	std::string tele;
	std::string version;
    uint8 GLD_lvlb;
    uint8 GLD_lvls;
	std::string respawn_flag;
	std::string details_loc;
	std::string table;
    uint8 GM_admin;
    uint8 GM_minimum;
    uint32 currency;
    uint32 pig_payz;
    uint32 pig_payz_timer;
    uint32 gift_count;
    uint32 flag_require;
	std::string Server;
	std::string command_set;
	std::string anarchy;
	std::string flag_timer;
	std::string spawn_timer;
	uint64 guild_id;
	std::string guild_invite;
	std::string loc;
    uint32 loc_cost;
    uint32 flag_id;
	std::string farm;
    uint32 farm_cost;
    uint32 farm_L;
    uint32 farm_id;
	std::string barrack;
    uint32 barrack_cost;
    uint32 barrack_L;
    uint32 barrack_id;
	std::string hall;
    uint32 hall_cost;
    uint32 hall_L;
    uint32 hall_id;
	std::string pig;
    uint32 pig_cost;
    uint32 pig_L;
    uint32 pig_id;
	std::string guard;
    uint32 guard_cost;
    uint32 guard_L;
    uint32 guard_id;
	std::string vendor1;
    uint32 vendor1_cost;
    uint32 vendor1_L;
    uint32 vendor1_id;
	std::string vendor2;
    uint32 vendor2_cost;
    uint32 vendor2_L;
    uint32 vendor2_id;
	std::string vendor3;
    uint32 vendor3_cost;
    uint32 vendor3_L;
    uint32 vendor3_id;
	std::string cannon;
    uint32 cannon_cost;
    uint32 cannon_L;
    uint32 cannon_id;
	std::string vault;
    uint32 vault_cost;
    uint32 vault_L;
    uint32 vault_id;
	std::string mailbox;
    uint32 mailbox_cost;
    uint32 mailbox_L;
    uint32 mailbox_id;
	std::string color_1;
	std::string color_2;
	std::string color_3;
	std::string color_4;
	std::string color_5;
	std::string color_6;
	std::string color_7;
	std::string color_8;
	std::string color_9;
	std::string color_10;
	std::string color_11;
	std::string color_12;
	std::string color_13;
	std::string color_14;
	std::string color_15;
};

struct Help
{
    uint32 entry;
    std::string name;
    std::string command;
	std::string description;
	std::string example;
    uint32 command_level;
};

struct LocData
{
    uint64 entry;
    uint64 map_id;
    uint64 area_id;
    uint64 zone_id;
	std::string guild_name;
    uint64 team;
    float x;
    float y;
    float z;
    uint64 farm_count;
    uint64 barrack_count;
    uint64 hall_count;
    uint64 pig_count;
    uint64 guard_count;
    uint64 vendor1_count;
    uint64 vendor2_count;
    uint64 vendor3_count;
    uint64 cannon_count;
    uint64 vault_count;
    uint64 mailbox_count;
    uint64 flag_id;
    uint64 fs_time;
    uint64 guild_id;
};

class GuildWarz
{
//	friend class ACE_Singleton<GuildWarz, ACE_Null_Mutex>;

    public:

		static uint64 LoadGuildCommands(uint64 guild_id);
		static uint64 LoadCommandHelp(uint64 entry_id);
		static uint64 LoadGuildLocation(uint64 loc_id);

		static uint64 GetLocationID(uint64 map_id, uint64 area_id, uint64 zone_id);
		static uint64 CreateGuildLocation(uint64 map_id, uint64 area_id, uint64 zone_id);

		static void UpdateGuildLocString(std::string column_target, std::string data_target, uint64 loc_id);
		static void UpdateGuildLocData(std::string column_target, uint64 data_target, uint64 loc_id);
		static void UpdateGuildCommandData(std::string command_target, std::string new_data, uint64 guild_id);

	protected:

    private:
        GuildWarz();
        ~GuildWarz();
};
#endif // GRUMBOZ_GUILD_WARZ_H_INCLUDED
