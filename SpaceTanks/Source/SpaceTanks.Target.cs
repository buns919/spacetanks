// Copyright 2018 TestGames

using UnrealBuildTool;
using System.Collections.Generic;

public class SpaceTanksTarget : TargetRules
{
	public SpaceTanksTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "SpaceTanks" } );
	}
}
