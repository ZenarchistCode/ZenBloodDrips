modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		#ifdef ZENMODPACK 
		if (!ZenModEnabled("ZenBloodDrips"))
			return;
		#endif

		GetZenBloodDripsConfig();
	}
}