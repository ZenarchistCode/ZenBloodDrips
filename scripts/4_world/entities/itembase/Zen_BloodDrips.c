class Zen_BloodDrips extends Inventory_Base
{
	protected Object m_ZenClutterCutter;
	static const int TEXTURE_COUNT = 10;

	void Zen_BloodDrips()
	{
		SetAllowDamage(false);
	}

	override void DeferredInit()
	{
		super.DeferredInit();

		if (GetGame().IsDedicatedServer())
		{
			SetRandomTexture();
			m_ZenClutterCutter = GetGame().CreateObjectEx("ClutterCutter2x2", GetPosition(), ECE_PLACE_ON_SURFACE);
		}
	}

	void SetRandomTexture()
	{
		int randomTex = Math.RandomIntInclusive(0, TEXTURE_COUNT - 1);
		SetObjectTexture(0, "ZenBloodDrips/data/textures/blood" + randomTex + ".paa");
	}

	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}

	override bool IsInventoryVisible()
	{
		return false;
	}

	override bool CanDisplayCargo()
	{
		return false;
	}

	override bool IsTakeable()
	{
		return false;
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);

		if (m_ZenClutterCutter)
		{
			GetGame().ObjectDelete(m_ZenClutterCutter);
		}
	}
}