/*

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);

		actions.Insert(ActionCutMyself);
	}
}

class ActionCutMyselfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(1);
	}
}

class ActionCutMyself : ActionContinuousBase
{
	void ActionCutMyself()
	{
		m_CallbackClass = ActionCutMyselfCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_SHAVE;
		m_FullBody = false;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "Cut myself";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return true;
	}

	override bool HasTarget()
	{
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		action_data.m_Player.GetBleedingManagerServer().AttemptAddBleedingSource(0);
	}
}

modded class CombatKnife
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionCutMyself);
	}
}

modded class HuntingKnife extends ToolBase
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionCutMyself);
	}
}

*/