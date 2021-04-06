// Copyright 2020-2021 Aumoa.lib. All right reserved.

public class Win32PlatformBuild : BuildRules
{
    public Win32PlatformBuild()
    {
        PrivatePCHHeaderFile = "Win32Platform";
        
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core"
        });
    }
}