class ZenStaticBloodDripsFunctions
{
	//! Aligns given object to underlying terrain (taken from ZenModPack.pbo/ZenFunctions.c - www.zenarchist.io)
	static void ZenBlood_AlignToTerrain(Object obj)
	{
		vector transform[4];
		obj.GetTransform(transform);
		vector ground_position, ground_dir;
		int component;
		DayZPhysics.RaycastRV(transform[3], transform[3] + transform[1] * -1000, ground_position, ground_dir, component, null, null, null, false, true);
		vector surface_normal = GetGame().SurfaceGetNormal(ground_position[0], ground_position[2]);
		vector local_ori = obj.GetDirection();
		transform[0] = surface_normal * local_ori;
		transform[1] = surface_normal;
		transform[2] = surface_normal * (local_ori * vector.Up);
		obj.SetTransform(transform);
		obj.Update();
	}
}