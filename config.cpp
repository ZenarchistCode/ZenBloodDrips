class CfgPatches
{
	class ZenBloodDrips
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class ZenBloodDrips
	{
		dir = "ZenBloodDrips";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ZenBloodDrips";
		credits = "";
		author = "Zenarchist";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = { "Game","World","Mission" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = { "ZenBloodDrips/scripts/3_game" };
			};
			class worldScriptModule
			{
				value = "";
				files[] = { "ZenBloodDrips/scripts/4_world" };
			};
			class missionScriptModule
			{
				value = "";
				files[] = { "ZenBloodDrips/scripts/5_mission" };
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class Zen_BloodDrips : Inventory_Base
	{
		scope = 2;
		model = "\ZenBloodDrips\data\models\blood_drip_texture.p3d";
		physLayer = "item_small";
		carveNavmesh = 0;
		hiddenSelections[] = { "texture" };
		hiddenSelectionsTextures[] = { "ZenBloodDrips\data\textures\blood1.paa" };
	};
};