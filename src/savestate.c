#include <common.h>

byte* savestate_region = 0x80200000;
byte* local_savestate_region;

void SaveState() {
	local_savestate_region = savestate_region;

	memcopy(local_savestate_region, &GAME_orbs_collected_count, 0x4);
	local_savestate_region += 0x4;

	memcopy(local_savestate_region, &GAME_orbs_collected_status, 0x20);
	local_savestate_region += 0x20;

	memcopy(local_savestate_region, &GAME_num_talismans, 0x4);
	local_savestate_region += 0x4;

	memcopy(local_savestate_region, &GAME_end_level_portals_status, 0x1c);
	local_savestate_region += 0x1c;

	memcopy(local_savestate_region, &GAME_gems_collected_value, 0x4);
	local_savestate_region += 0x4;

	memcopy(local_savestate_region, &GAME_world_gems_collected, 0x80);
	local_savestate_region += 0x80;

	memcopy(local_savestate_region, &GAME_gems_collected_status, 0x400);
	local_savestate_region += 0x400;

	memcopy(local_savestate_region, &GAME_worlds_entered, 0x20);
	local_savestate_region += 0x20;

	memcopy(local_savestate_region, &GAME_NPC_talked_flags, 0x20);
	local_savestate_region += 0x20;

	memcopy(local_savestate_region, &GAME_crushDeathCounter, 0x8);
	local_savestate_region += 0x8;

	memcopy(local_savestate_region, &GAME_unknown_boss_thing, 0x20);
	local_savestate_region += 0x20;

	memcopy(local_savestate_region, &GAME_global_progress_flags, 0x9a);
	local_savestate_region += 0x9a;

	memcopy(local_savestate_region, &GAME_skillpoint_flags, 0x20);
	local_savestate_region += 0x20;

	// Load static mobys UP TO unchangable sparx data
	int size_of_moby_arr_in_level = ((byte*)ptrToEndOfMobys) - ((byte*)ptr_MobyArray);
	printf("up to sparx data: %X", size_of_moby_arr_in_level);
	memcopy(local_savestate_region, ptr_MobyArray, size_of_moby_arr_in_level);
	local_savestate_region += size_of_moby_arr_in_level;

	//Copy rest of moby data past that unchangable sparx data
	byte * rest_of_moby_data = ptrToEndOfMobys + 0x14;
	memcopy(local_savestate_region, rest_of_moby_data, 0x10000);
	local_savestate_region += 0x10000;

	memcopy(local_savestate_region, &ptr_DynamicMobyArray, 0x4);
	local_savestate_region += 0x4;

	memcopy(local_savestate_region, &count_DynamicMobys, 0x4);
	local_savestate_region += 0x4;

	 // Copy spyro
	memcopy((byte*)local_savestate_region, &_spyro, 0x2E0);
	local_savestate_region += 0x2E0;

	// Copy sparx pointer
	memcopy((byte*)local_savestate_region, 0x80067028, 0x4);
	local_savestate_region += 0x4;

	// Copy sparx data
	//memcopy((byte*)local_savestate_region, 0x80068078, 0x14);
	//local_savestate_region += 0x14;

	//Copy boss counters
	memcopy(local_savestate_region , 0x80066e7c , 0x5);
	local_savestate_region += 0x5;

	//Copy misc stuff counters
	memcopy(local_savestate_region , 0x80066f60 , 0x2c);
	local_savestate_region += 0x2c;

	//Copy spirit particles
	memcopy(local_savestate_region , 0x80066fb0 , 0x4);
	local_savestate_region += 0x4;

	 // Copy camera
	memcopy((byte*)local_savestate_region, 0x80067e84, 0x1F3);
	local_savestate_region += 0x1F3;

	// Copy lives
	memcopy((byte*)local_savestate_region, 0x8006712c, 0x4);
	local_savestate_region += 0x4;

	// Copy checkpoint data
	memcopy((byte*)local_savestate_region, 0x8006718c, 0x248);
	local_savestate_region += 0x248;

	// Copy checkpoint storage
	memcopy( (byte*)local_savestate_region , 0x80067414 , 0x248);
	local_savestate_region += 0x248;

	// Copy hud
	memcopy( (byte*)local_savestate_region , 0x8006765c , 0x34);
	local_savestate_region += 0x34;

	// Copy pointers
	memcopy((byte*)local_savestate_region , 0x800687c4 ,  0x1D4);
	local_savestate_region += 0x1D4;

	// Copy unk pointer
	memcopy((byte*)local_savestate_region , 0x800670d8 ,  0x4);
	local_savestate_region += 0x4;

	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80067148 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80066ff0 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80066f44 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80066ff4 ,  0x4);
	local_savestate_region += 0x4;

	// Copy counter1
	memcopy((byte*)local_savestate_region , 0x80067084  ,  0x4);
	local_savestate_region += 0x4;
	// Copy counter2
	memcopy((byte*)local_savestate_region , 0x80067680  ,  0x4);
	local_savestate_region += 0x4;

	// Copy block2
	memcopy((byte*)local_savestate_region , 0x80067000 , 0x1000);
	local_savestate_region += 0x1000;

	// Copy block2
	memcopy((byte*)local_savestate_region , 0x80068000 , 0x1000);
	local_savestate_region += 0x1000;

	// Copy unk
	memcopy((byte*)local_savestate_region , 0x8006700c ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80067008 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80067100 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x8006701c ,  0x4);
	local_savestate_region += 0x4;
	// Copy level complete popup timer
	memcopy((byte*)local_savestate_region , 0x800676bc ,  0x4);
	local_savestate_region += 0x4;
	// Copy gems complete popup timer
	memcopy((byte*)local_savestate_region , 0x800676b4 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80066fec ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80067084 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80067088 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x8006708c ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80066f30 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80066efc ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80066f50 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80067038 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x800670f4 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x80067174 ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x800670bc ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy((byte*)local_savestate_region , 0x800670d8 ,  0x4);
	local_savestate_region += 0x4;

	// Copy fireball
	memcopy((byte*)local_savestate_region , 0x800698bb ,  0x1);
	local_savestate_region += 0x1;

	// Copy fodder to next life
	memcopy((byte*)local_savestate_region , 0x80061aac , 0x4);
	local_savestate_region += 0x4;

	//Copy particle array
	memcopy(local_savestate_region, ptr_ParticleArray , 0x2000);
	local_savestate_region += 0x2000;

	//Copy next free particle slot
	memcopy(local_savestate_region, 0x80066fd8 , 0x4);
	local_savestate_region += 0x4;

	//Copy flame data
	memcopy(local_savestate_region, 0x8006aa00, 0x14c);
	local_savestate_region += 0x14c;

	//Copy terrain data
	char * startOfCurrentBlock = ptr_dynamic_terrain;
	int sizeOfCurrentBlock = *((int*) startOfCurrentBlock);

	printf("1:Start of block: %X\nSize of block: %X\n", startOfCurrentBlock, sizeOfCurrentBlock);

	memcopy(local_savestate_region,startOfCurrentBlock,sizeOfCurrentBlock);
	local_savestate_region += sizeOfCurrentBlock;

	startOfCurrentBlock += sizeOfCurrentBlock;
	sizeOfCurrentBlock = *((int*) startOfCurrentBlock);

	printf("2:Start of block: %X\nSize of block: %X\n", startOfCurrentBlock, sizeOfCurrentBlock);

	memcopy(local_savestate_region,startOfCurrentBlock,sizeOfCurrentBlock);
	local_savestate_region += sizeOfCurrentBlock;

	startOfCurrentBlock += sizeOfCurrentBlock;
	sizeOfCurrentBlock = *((int*) startOfCurrentBlock);

	printf("3:Start of block: %X\nSize of block: %X\n", startOfCurrentBlock, sizeOfCurrentBlock);

	memcopy(local_savestate_region,startOfCurrentBlock,sizeOfCurrentBlock);
	local_savestate_region += sizeOfCurrentBlock;

	SaveGeoData(local_savestate_region);

}

void LoadState() {
	local_savestate_region = savestate_region;

	memcopy(&GAME_orbs_collected_count, local_savestate_region, 0x4);
	local_savestate_region += 0x4;

	memcopy(&GAME_orbs_collected_status, local_savestate_region, 0x20);
	local_savestate_region += 0x20;

	memcopy(&GAME_num_talismans, local_savestate_region, 0x4);
	local_savestate_region += 0x4;

	memcopy(&GAME_end_level_portals_status, local_savestate_region, 0x1c);
	local_savestate_region += 0x1c;

	memcopy(&GAME_gems_collected_value, local_savestate_region, 0x4);
	local_savestate_region += 0x4;

	memcopy(&GAME_world_gems_collected, local_savestate_region, 0x80);
	local_savestate_region += 0x80;

	memcopy(&GAME_gems_collected_status, local_savestate_region, 0x400);
	local_savestate_region += 0x400;

	memcopy(&GAME_worlds_entered, local_savestate_region, 0x20);
	local_savestate_region += 0x20;

	memcopy(&GAME_NPC_talked_flags, local_savestate_region, 0x20);
	local_savestate_region += 0x20;

	memcopy(&GAME_crushDeathCounter, local_savestate_region, 0x8);
	local_savestate_region += 0x8;

	memcopy(&GAME_unknown_boss_thing, local_savestate_region, 0x20);
	local_savestate_region += 0x20;

	memcopy(&GAME_global_progress_flags, local_savestate_region, 0x9a);
	local_savestate_region += 0x9a;

	memcopy(&GAME_skillpoint_flags, local_savestate_region, 0x20);
	local_savestate_region += 0x20;

	// Load static mobys UP TO unchangable sparx data
	int size_of_moby_arr_in_level = ((byte*)ptrToEndOfMobys) - ((byte*)ptr_MobyArray);
	printf("up to sparx data: %X", size_of_moby_arr_in_level);
	memcopy(ptr_MobyArray , local_savestate_region, size_of_moby_arr_in_level);
	local_savestate_region += size_of_moby_arr_in_level;

	//Copy rest of moby data past that unchangable sparx data
	byte * rest_of_moby_data = ptrToEndOfMobys + 0x14;
	memcopy(rest_of_moby_data , local_savestate_region,  0x10000);
	local_savestate_region += 0x10000;

	memcopy(&ptr_DynamicMobyArray , local_savestate_region, 0x4);
	local_savestate_region += 0x4;

	memcopy(&count_DynamicMobys , local_savestate_region, 0x4);
	local_savestate_region += 0x4;

	 // Copy spyro
	memcopy(&_spyro , (byte*)local_savestate_region, 0x2E0);
	local_savestate_region += 0x2E0;

	// Copy sparx pointer
	memcopy(0x80067028 , (byte*)local_savestate_region,  0x4);
	local_savestate_region += 0x4;

	// Copy sparx data
	//memcopy(0x80068078 , (byte*)local_savestate_region, 0x14);
	//local_savestate_region += 0x14;

	//Copy boss counters
	memcopy(0x80066e7c , local_savestate_region , 0x5);
	local_savestate_region += 0x5;

	//Copy misc stuff counters
	memcopy(0x80066f60  , local_savestate_region ,  0x2c);
	local_savestate_region += 0x2c;

	//Copy spirit particles
	memcopy(0x80066fb0 , local_savestate_region , 0x4);
	local_savestate_region += 0x4;

	 // Copy camera
	memcopy(0x80067e84, (byte*)local_savestate_region , 0x1F3);
	local_savestate_region += 0x1F3;

	// Copy lives
	memcopy(0x8006712c , (byte*)local_savestate_region, 0x4);
	local_savestate_region += 0x4;

	// Copy checkpoint data
	memcopy( 0x8006718c , (byte*)local_savestate_region, 0x248);
	local_savestate_region += 0x248;

	// Copy checkpoint storage
	memcopy( 0x80067414 , (byte*)local_savestate_region, 0x248);
	local_savestate_region += 0x248;

	// Copy hud
	memcopy( 0x8006765c , (byte*)local_savestate_region , 0x34);
	local_savestate_region += 0x34;

	// Copy pointers
	memcopy( 0x800687c4 , (byte*)local_savestate_region , 0x1D4);
	local_savestate_region += 0x1D4;

	// Copy unk pointer
	memcopy(0x800670d8 , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;

	// Copy unk
	memcopy(0x80067148  , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80066ff0 , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80066f44 , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80066ff4 , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;

	// Copy counter1
	memcopy(0x80067084  , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy counter2
	memcopy(0x80067680  , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;

	// Copy block2
	memcopy(0x80067000 , (byte*)local_savestate_region ,  0x1000);
	local_savestate_region += 0x1000;

	// Copy block2
	memcopy(0x80068000 , (byte*)local_savestate_region ,  0x1000);
	local_savestate_region += 0x1000;

	// Copy unk
	memcopy(0x8006700c , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80067008 , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80067100 , (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x8006701c ,  (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;
	// Copy level complete popup timer
	memcopy(0x800676bc , (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;
	// Copy gems complete popup timer
	memcopy(0x800676b4 , (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80066fec , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80067084 , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80067088 ,  (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x8006708c ,  (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80066f30 , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80066efc , (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80066f50 ,  (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80067038 ,  (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x800670f4 , (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x80067174 , (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x800670bc , (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;
	// Copy unk
	memcopy(0x800670d8 , (byte*)local_savestate_region ,  0x4);
	local_savestate_region += 0x4;

	// Copy fireball
	memcopy(0x800698bb , (byte*)local_savestate_region , 0x1);
	local_savestate_region += 0x1;

	// Copy fodder to next life
	memcopy(0x80061aac , (byte*)local_savestate_region , 0x4);
	local_savestate_region += 0x4;

	//Copy particle array
	memcopy(ptr_ParticleArray , local_savestate_region, 0x2000);
	local_savestate_region += 0x2000;

	//Copy next free particle slot
	memcopy(0x80066fd8 , local_savestate_region, 0x4);
	local_savestate_region += 0x4;

	//Copy flame data
	memcopy(0x8006aa00, local_savestate_region, 0x14c);
	local_savestate_region += 0x14c;

	//Copy terrain data
	char * startOfCurrentBlock = ptr_dynamic_terrain;
	int sizeOfCurrentBlock = *((int*) startOfCurrentBlock);

	memcopy(startOfCurrentBlock, local_savestate_region,sizeOfCurrentBlock);
	local_savestate_region += sizeOfCurrentBlock;

	startOfCurrentBlock += sizeOfCurrentBlock;
	sizeOfCurrentBlock = *((int*) startOfCurrentBlock);

	memcopy(startOfCurrentBlock,local_savestate_region,sizeOfCurrentBlock);
	local_savestate_region += sizeOfCurrentBlock;

	startOfCurrentBlock += sizeOfCurrentBlock;
	sizeOfCurrentBlock = *((int*) startOfCurrentBlock);

	memcopy(startOfCurrentBlock,local_savestate_region,sizeOfCurrentBlock);
	local_savestate_region += sizeOfCurrentBlock;

	LoadGeoData(local_savestate_region);

}