modded class ComponentAnimalBleeding
{
	protected ref Timer m_ZenBleedTimer;
	protected int m_LastZenWoundTimestamp;
	protected vector m_LastZenBloodDripPos = vector.Zero;

	override void CreateWound(TotalDamageResult damage_result, string zone_name, string ammo)
	{
		super.CreateWound(damage_result, zone_name, ammo);

		m_LastZenWoundTimestamp = GetGame().GetTime();

		if (m_BleedTimer && m_BleedTimer.IsRunning())
		{
			StopZenBleedTimer();
			return;
		}
		else 
		if (!m_ZenBleedTimer)
		{
			m_ZenBleedTimer = new Timer(CALL_CATEGORY_SYSTEM);
			m_ZenBleedTimer.Run(1, this, "HandleZenBloodDrips", NULL, true);
		}
	}

	override void Bleed(float wound_intensity)
	{
		super.Bleed(wound_intensity);

		HandleZenBloodDrips();
	}

	void HandleZenBloodDrips()
	{
		#ifdef ZENMODPACK 
		if (!ZenModEnabled("ZenBloodDrips"))
			return;
		#endif

		if (!GetZenBloodDripsConfig().EnableAnimalBloodDrops)
		{
			return;
		}

		if (!m_ThisEntityAI || !m_ThisEntityAI.IsAlive())
		{
			StopZenBleedTimer();
			return;
		}

		if (GetGame().GetTime() - m_LastZenWoundTimestamp >= GetZenBloodDripsConfig().Animal_StopBleedingAfterSecs * 1000)
		{
			StopZenBleedTimer();
			return;
		}

		float chance;
		vector pos = m_ThisEntityAI.GetPosition();
		
		/*float groundPos = GetGame().SurfaceY(pos[0], pos[2]);
		pos[1] = groundPos + 0.02;*/

		// First drop of blood = guaranteed
		if (m_LastZenBloodDripPos == vector.Zero)
		{
			chance = 1.0;
		}
		else
		{
			// If entity hasn't moved more than 1 meter, reduce blood drops
			if (vector.Distance(pos, m_LastZenBloodDripPos) < 1)
				chance = GetZenBloodDripsConfig().Animal_BloodDropChanceStationary;
			else
				chance = GetZenBloodDripsConfig().Animal_BloodDropChanceMoving;
		}

		if (Math.RandomFloat01() >= chance)
			return;

		EntityAI blood = EntityAI.Cast(GetGame().CreateObjectEx("Zen_BloodDrips", pos, ECE_PLACE_ON_SURFACE));
		//blood.SetPosition(pos);

		if (!blood)
		{
			Error("Failed to spawn Zen_BloodDrips");
			StopZenBleedTimer();
			return;
		}

		float ori = Math.RandomFloatInclusive(-180, 180);

		vector oriVec = "0 0 0";
		oriVec[0] = ori;

		blood.SetOrientation(oriVec);
		blood.SetLifetimeMax(GetZenBloodDripsConfig().Animal_BloodDropPersistence);
		blood.SetLifetime(GetZenBloodDripsConfig().Animal_BloodDropPersistence);
		m_LastZenBloodDripPos = pos;

		ZenStaticBloodDripsFunctions.ZenBlood_AlignToTerrain(blood);
	}

	void StopZenBleedTimer()
	{
		if (m_ZenBleedTimer)
		{
			if (m_ZenBleedTimer.IsRunning())
			{
				m_ZenBleedTimer.Stop();
			}
			
			m_ZenBleedTimer = NULL;
		}
	}
}