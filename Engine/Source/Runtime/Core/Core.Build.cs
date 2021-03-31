// Copyright 2020-2021 Aumoa.lib. All right reserved.

public class CoreBuild : BuildRules
{
    public CoreBuild()
    {
        CppStandardVersion = CppVersion.Cpp20;
        PrivatePCHHeaderFile = "Core";
    }
}