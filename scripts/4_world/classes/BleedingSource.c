modded class BleedingSource
{
	protected vector m_LastZenBloodDripPos = vector.Zero;

	// This function is called every ~3 seconds by server
	override void OnUpdateServer(float deltatime, float blood_scale, bool no_blood_loss)
	{
		super.OnUpdateServer(deltatime, blood_scale, no_blood_loss);

		#ifdef ZENMODPACK 
		if (!ZenModEnabled("ZenBloodDrips"))
			return;
		#endif

		if (no_blood_loss || !GetZenBloodDripsConfig().EnablePlayerBloodDrops || !m_Player || !m_Player.IsAlive())
			return;

		float chance;
		vector pos = m_Player.GetPosition();

		/*
		float groundPos = GetGame().SurfaceY(pos[0], pos[2]);
		pos[1] = groundPos + 0.02;
		*/

		// First drop of blood = guaranteed
		if (m_LastZenBloodDripPos == vector.Zero)
		{
			chance = 1.0;
		}
		else
		{
			// If entity hasn't moved more than 1 meter, reduce blood drops
			if (vector.Distance(pos, m_LastZenBloodDripPos) < 1)
				chance = GetZenBloodDripsConfig().Player_BloodDropChanceStationary;
			else
				chance = GetZenBloodDripsConfig().Player_BloodDropChanceMoving;
		}

		if (Math.RandomFloat01() >= chance)
			return;

		EntityAI blood = EntityAI.Cast(GetGame().CreateObjectEx("Zen_BloodDrips", pos, ECE_PLACE_ON_SURFACE));
		//blood.SetPosition(pos);

		if (!blood)
		{
			Error("Failed to spawn Zen_BloodDrips");
			return;
		}

		float ori = Math.RandomFloatInclusive(-180, 180);

		vector oriVec = "0 0 0";
		oriVec[0] = ori;

		blood.SetOrientation(oriVec);
		blood.SetLifetimeMax(GetZenBloodDripsConfig().Player_BloodDropPersistence);
		blood.SetLifetime(GetZenBloodDripsConfig().Player_BloodDropPersistence);
		m_LastZenBloodDripPos = pos;

		ZenStaticBloodDripsFunctions.ZenBlood_AlignToTerrain(blood);
	}
}