// Copyright 2018 TestGames

using UnrealBuildTool;
using System.Collections.Generic;

public class SpaceTanksEditorTarget : TargetRules
{
	public SpaceTanksEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "SpaceTanks" } );
	}
}
