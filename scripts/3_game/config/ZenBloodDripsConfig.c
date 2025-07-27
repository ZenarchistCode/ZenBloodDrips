class ZenBloodDripsConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\";
	private const static string zenConfigName = "ZenBloodDripsConfig.json";
	private const static string CURRENT_VERSION = "3";
	string CONFIG_VERSION = "";

	// Settings data
	bool EnablePlayerBloodDrops;
	float Player_BloodDropChanceStationary; // Chance of blood drop per every 3 seconds
	float Player_BloodDropChanceMoving;
	float Player_BloodDropPersistence;

	bool EnableAnimalBloodDrops;
	int Animal_StopBleedingAfterSecs;
	float Animal_BloodDropChanceStationary; // Chance of blood drop per every 3 seconds
	float Animal_BloodDropChanceMoving;
	float Animal_BloodDropPersistence;
	ref array<string> Animal_IncludeList;

	void Load()
	{
		if (!GetGame().IsDedicatedServer())
			return;

		SetDefaults();

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<ZenBloodDripsConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			if (CONFIG_VERSION != CURRENT_VERSION)
			{
				JsonFileLoader<ZenBloodDripsConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
				CONFIG_VERSION = CURRENT_VERSION;
				SetDefaults();
				Save();
			}
			else
			{
				// Config exists and version matches, stop here.
				return;
			}
		}

		CONFIG_VERSION = CURRENT_VERSION;
		SetDefaults();
		Save();
	}

	void SetDefaults()
	{
		EnablePlayerBloodDrops = true;
		Player_BloodDropChanceStationary = 0.25; // Chance of blood drop per every ~3 seconds
		Player_BloodDropChanceMoving = 0.95;
		Player_BloodDropPersistence = 1800; // 30 minutes

		EnableAnimalBloodDrops = true;
		Animal_StopBleedingAfterSecs = 300; // 5 minutes
		Animal_BloodDropChanceStationary = 0.0; // Chance of blood drop per every ~1 seconds
		Animal_BloodDropChanceMoving = 0.95;
		Animal_BloodDropPersistence = 600; // 10 minutes

		Animal_IncludeList = new array<string>;
		Animal_IncludeList.Insert("Animal_CapreolusCapreolus");
		Animal_IncludeList.Insert("Animal_CervusElaphus");
		Animal_IncludeList.Insert("Animal_LepusEuropaeus");
		Animal_IncludeList.Insert("Animal_SusScrofa");
		Animal_IncludeList.Insert("Animal_VulpesVulpes");
	}

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ZenBloodDripsConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}
}

ref ZenBloodDripsConfig m_ZenBloodDripsConfig;

static ZenBloodDripsConfig GetZenBloodDripsConfig()
{
#ifdef SERVER
	if (!m_ZenBloodDripsConfig)
	{
		m_ZenBloodDripsConfig = new ZenBloodDripsConfig;
		m_ZenBloodDripsConfig.Load();
	}
#endif

	return m_ZenBloodDripsConfig;
}