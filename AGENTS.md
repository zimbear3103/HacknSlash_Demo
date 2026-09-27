# Repository Guidelines

## Project Structure & Module Organization

This Unreal Engine 5.8 C++ project uses the Gameplay Ability System (GAS).

- `Source/HacknSlash_Demo/`: runtime module; `Public/` contains headers and `Private/` implementations, grouped into Characters, Player, AI, and UI. GameMode and module rules sit at the module root.
- `Content/GASDocumentation/`: gameplay Blueprints, abilities, UI, and `Maps/Map_Startup.umap`, the configured startup map. Other `Content/` folders contain character, animation, and VFX assets.
- `Config/`: engine, input, gameplay tags, and project defaults. No dedicated automated test directory exists.

## Build, Test, and Development Commands

Use Unreal Engine 5.8 and Visual Studio with C++ game development tools. Install plugins enabled in `HacknSlash_Demo.uproject`, including ModelContextProtocol, Terminal, and EditorToolset.

Run from the repository root in PowerShell; adjust `$ueRoot` for your installation:

```powershell
$ueRoot = 'G:\UE_5.8'
$projectFile = (Resolve-Path '.\HacknSlash_Demo.uproject').Path
& "$ueRoot\Engine\Build\BatchFiles\Build.bat" HacknSlash_DemoEditor Win64 Development "-Project=$projectFile" -WaitMutex
& "$ueRoot\Engine\Binaries\Win64\UnrealEditor.exe" $projectFile
```

The first command builds the Editor target; the second opens the project. Use Play In Editor (PIE) for gameplay checks. Run `git diff --check` before submitting changes.

## Coding Style & Naming Conventions

Match surrounding indentation: C++ generally uses tabs and braces on separate lines. Preserve Unreal type prefixes (`A`, `U`, `F`) and existing `GD` class names. For new fields, use private `m_camelCase` and public `camelCase`; preserve existing reflected names and Unreal-required conventions. Expose editable fields through `UPROPERTY`, not Unity's `[SerializeField]`. Write comments in English. No repository formatter or linter configuration is present.

## Testing Guidelines

No project automation suite, test naming convention, or coverage threshold is configured. Validate changes in a focused test map, tune parameters, then test `Map_Startup` in PIE. Check affected spawn/possession, movement, attacks/combo timing, damage, HUD, and respawn flows. For replication changes, include server/client PIE checks. Record reproduction steps and distinguish compilation from visual/runtime validation.

## Commit & Pull Request Guidelines

Use `feature/<bug-or-function>` branches. History uses short descriptive messages such as `add starter project`; no mandatory commit prefix exists. Keep commits focused. PRs should describe behavior changes, link relevant issues, list tested maps/modes and results, and include screenshots or clips for animation, UI, or VFX changes.

## Asset & Configuration Risks

Coordinate binary `.uasset`/`.umap` edits. Renaming reflected properties can affect Blueprint references. Exclude generated `Binaries/`, `Intermediate/`, `Saved/`, and `DerivedDataCache/` from commits.
