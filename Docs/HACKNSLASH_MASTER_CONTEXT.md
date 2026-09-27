# HacknSlash_Demo — MASTER PROJECT CONTEXT

Updated: 2026-09-22  
Project: `F:\HacknSlash_Demo`  
Engine: Unreal Engine 5.8  
Platform: PC  
Core stack: Unreal Engine + Gameplay Ability System (GAS) + Animation Montages + Blueprint/C++  
Working language: Vietnamese + Vietlish, practical Blueprint steps, KISS.

> **Purpose of this file**
>
> Đây là **single source of truth** cho toàn bộ bài technical test Hack-and-Slash hiện tại.
> File này gom:
>
> - Requirement gốc của bài test.
> - Kế hoạch 7 ngày ban đầu.
> - Trạng thái implementation hiện tại.
> - GAS / melee / TargetData / EffectContext / GameplayCue / VFX context.
> - Requirement-vs-status audit.
> - Priority P0 / P1 / P2.
> - Revised execution order.
> - Definition of Done / regression checklist.
> - Submission checklist.
> - Technical architecture diagram.
> - Boundaries, intentional skips, known risks.
> - Prompt ngắn để tiếp tục ở chat/session khác.
>
> Nếu có conflict giữa kế hoạch cũ và phần **MASTER PRIORITY / NEXT ACTION** trong file này,
> ưu tiên phần MASTER ở đầu file.

---

# 1. TECHNICAL TEST — ORIGINAL REQUIREMENTS

## Game Combat Engineer Test 1

**Deadline:** Within 7 days from the day the technical test was received.

### Tech stacks

- Game Engine: Unreal Engine 5.4 or later
- Current project engine: Unreal Engine 5.8
- Platform: PC
- Language: Any

### Objective

Develop a Hack-and-Slash mini project.

Primary focus:

- Combo mechanics
- Gameplay Ability System (GAS)
- Game flow implementation

### Deliver Content

- Git source: GitHub link
- YouTube demo link
- 1–2 pages Technical Document & Diagram

### General Requirement

If unsure about anything, make a reasonable design/implementation choice.

---

# 2. REQUIRED GAMEPLAY FEATURES

## 2.1 Combat System — Melee Combo

Must have:

- Melee combat using Animation Montages
- Ground combo chain: 3+ attacks
- Air combo chain: 2+ attacks
- Bare-handed combat mechanics
- Smooth animation transitions

## 2.2 Dynamic Camera System

Must have:

- Smooth follow behavior
- Combat-aware camera adjustments
- Impact feedback via Camera Shake
- Collision handling

## 2.3 Game HUD

Must have:

- Player HP visualization
- Stamina bar
- Enemy health
- Combo counter

---

# 3. ORIGINAL 7-DAY PLAN

| Day | Main goal | Work | Definition of Done |
| --- | --- | --- | --- |
| Day 1 | Combat foundation | Chốt character/skeleton, retarget Kwang hoặc animation chính, setup weapon socket, tạo `GA_MeleeAttack`, stamina cost, melee trace, damage | Nhấn attack → montage chạy → trúng enemy → enemy mất HP → stamina giảm |
| Day 2 | Ground Combo | Tạo Montage Sections, input buffering, combo window bằng AnimNotifyState, 3-hit ground chain, heavy/finisher branch | Có ít nhất Light → Light → Light và 1 nhánh finisher hoạt động ổn định |
| Day 3 | Air Combo + Launcher | Tạo launcher attack, launch enemy/player, air state, 2+ air attack, downward finisher nếu kịp | Launcher → Air1 → Air2 chạy ổn, không spam input phá montage |
| Day 4 | Bare-hand + 5 combos | Retarget martial arts animation, weapon equip state, bare-hand ability/montage, hoàn thiện 5+ combo patterns | Reviewer có thể trigger ít nhất 5 combo khác nhau, gồm sword + air + bare hand |
| Day 5 | Poison + HUD | `GE_Poison`, periodic DoT, GameplayCue poison VFX, HP/Stamina UI, enemy HP, combo counter | Poison gây tick damage + VFX; HUD cập nhật đúng từ AttributeSet |
| Day 6 | Camera + game feel | Combat camera, Camera Shake, hitstop nhẹ, hit VFX, sword trail, impact SFX, collision camera | Combat bắt đầu “có lực”, camera không xuyên tường, heavy hit khác biệt rõ |
| Day 7 | Polish + submission | Bug fixing, balance stamina/damage, clean project, README, controls, architecture notes, build Windows Shipping/Development, record demo | Build chạy trên máy sạch, README đủ, video demo rõ requirement+ |

---

# 4. MASTER AUDIT — REQUIREMENT VS CURRENT STATUS

Legend:

- ✅ = đã có / core path tồn tại
- 🟡 = đã chuẩn bị hoặc từng pass một phần, nhưng cần fresh end-to-end proof
- 🔴 = chưa final / chưa prove đủ cho submission

| Requirement | Current status | Priority |
| --- | --- | --- |
| Unreal 5.4+ | ✅ Project đang ở UE 5.8 | Done |
| GAS foundation | ✅ ASC / GA / GE / AttributeSet path đang dùng | Done nền tảng |
| Melee via Animation Montage | ✅ `AM_Kwang_GroundCombo` | Regression needed |
| Ground combo 3+ | 🟡 Attack 01 → 02 → 03 tồn tại / prior fixture pass | **P0 verify in PIE** |
| Input buffer / combo window | 🟡 `ANS_CombatWindow` tồn tại | **P0 verify** |
| Air combo 2+ | 🟡 Assets/abilities đã chuẩn bị | **P0** |
| Bare-handed combat | 🟡 Ability/montage/trace đã chuẩn bị | **P0** |
| Melee trace / damage | ✅ Current path hoạt động về mặt architecture | Regression needed |
| Dynamic camera smooth follow | 🔴 Chưa final | **P0** |
| Combat-aware camera | 🔴 Chưa final | **P0** |
| Camera shake | 🔴 Chưa final | **P0** |
| Camera collision | 🔴 Chưa final | **P0** |
| Player HP HUD | 🔴/🟡 Chưa final | **P0** |
| Player Stamina HUD | 🔴/🟡 Chưa final | **P0** |
| Enemy Health | 🔴/🟡 Chưa final | **P0** |
| Combo Counter | 🔴 Chưa final | **P0** |
| Game flow | 🔴 Chưa final | **P0** |
| GitHub | 🔴 Submission phase | **P0 final** |
| YouTube demo | 🔴 Submission phase | **P0 final** |
| Technical doc 1–2 pages | 🔴 Submission phase | **P0 final** |
| Poison | ✅ gần hoàn chỉnh | P2 / bonus |
| Sword slash / impact VFX | 🟡 Current polish checkpoint | P1 |
| Floating damage number | intentionally skipped | Not required |

---

# 5. MASTER PRIORITY

## P0 — Reviewer bắt buộc phải thấy

1. Ground Combo 3+
2. Air Combo 2+
3. Bare-handed combat
4. GAS integration
5. Player HP
6. Stamina
7. Enemy HP
8. Combo Counter
9. Camera smooth follow
10. Combat camera adjustment
11. Camera Shake
12. Camera collision
13. Game flow
14. Build chạy được
15. GitHub source
16. YouTube demo
17. 1–2 page technical document + diagram

## P1 — Làm bài test trông tốt hơn

- Sword Trail / SwordSlash
- Impact VFX
- Hitstop nhẹ
- SFX
- Heavy Attack / Finisher
- Launcher polish
- Better visual timing

## P2 — Bonus / không được block P0

- Poison DoT
- Poison stacking
- Fancy Poison VFX
- Damage numbers
- Complex finishers
- Extra UI animation
- Advanced camera logic

### Priority rule

> Nếu một P2 bug có nguy cơ tốn nhiều thời gian trong khi Air Combo / Bare-hand / HUD / Camera / Game Flow chưa pass,
> **stop P2 và quay lại P0**.

---

# 6. REVISED EXECUTION ORDER

Sau khi review current state, thứ tự nên là:

1. **Finish current SwordSlash visual checkpoint**
2. Ground Combo fresh regression
3. Air Combo + Launcher
4. Bare-hand combat
5. HUD
6. Dynamic Camera
7. Game Flow
8. Final combat polish
9. Build / README / GitHub
10. Demo video
11. 1–2 page Technical Document + Diagram

Compact version:

```text
SwordSlash checkpoint
    ↓
Ground regression
    ↓
Air Combo
    ↓
Bare-hand
    ↓
HUD
    ↓
Camera
    ↓
Game Flow
    ↓
Final Polish
    ↓
Build / README / GitHub
    ↓
Video Demo
    ↓
Technical Document
```

---

# 7. CURRENT NEXT ACTION — DO THIS FIRST

Current stage:

**GameplayCue / VFX polish — `GC_SwordSlash` attachment and trajectory validation.**

The graph-side attachment fix already exists.

## Test

1. Open `Map_Startup`.
2. Run PIE with no enemy in attack range.
3. Play one `Attack_01`.
4. Observe only `NS_SwordSlash`.
5. Confirm:
   - one SwordSlash per intended swing/notify;
   - effect starts from `FX_weapon_base`;
   - visible effect follows the weapon during swing;
   - effect still appears on a miss.
6. Stop PIE.
7. Determine:
   - Niagara component follows correctly; or
   - component follows but emitted particles remain in world space.

## If component follows but particles stay behind

Test Niagara emitter `Local Space`.

If desired output is a true continuous blade trail/arc, consider native Kwang trail options:

- `P_Kwang_Primary_Trail`
- `P_Kwang_Primary_Trail_L`
- `P_Kwang_Primary_Trail_R`
- `P_Sword_Tip_Drag`

### Stop condition

Once effect is visually acceptable for demo:

> **Freeze SwordSlash / VFX and return to P0 combat requirements.**

Do not spend production-level polish time here.

---

# 8. GROUND COMBO — SUBMISSION REGRESSION

Fresh PIE validation required.

## Acceptance matrix

| Test | Expected |
| --- | --- |
| LMB once | `Attack_01` → End |
| LMB → LMB | `Attack_01` → `Attack_02` |
| LMB → LMB → LMB | `Attack_01` → `Attack_02` → `Attack_03` |
| Spam LMB | Montage không restart / no duplicate attacks |
| LMB outside combo window | Không queue sai |
| Hit enemy | Mỗi swing gây damage 1 lần / target |
| Miss | Montage vẫn chạy bình thường |
| Miss + SwordSlash | Slash vẫn hiện |
| Hit | Impact VFX hiện |
| Insufficient stamina | Ability fail/blocked đúng design |
| Combo end | Ability End sạch |
| Move after attack | Control trả lại bình thường |

## Ground combo Done

Ground combo chỉ được mark **DONE** khi current build pass runtime/visual test,
không chỉ dựa vào fixture cũ.

---

# 9. AIR COMBO — TARGET IMPLEMENTATION

Prepared assets currently include:

- `GA_AirAttack`
- `GA_Launcher`
- `AM_Kwang_AirCombo`
- `AM_Kwang_Launcher`

Minimum required flow:

```text
Ground
  ↓
Launcher
  ↓
Enemy airborne
Player airborne / air-combat state
  ↓
AirAttack_01
  ↓
AirAttack_02
  ↓
Landing / reset
```

## Air Combo DoD

Must prove:

- launcher works;
- enemy is launched;
- player enters correct air state;
- Air1 runs;
- Air2 runs;
- hit/damage works;
- input spam does not restart/break montage;
- landing resets air combo state.

Optional bonus:

```text
Air2
 ↓
Downward Finisher
```

Downward finisher is **not required** if time is tight.

---

# 10. BARE-HAND COMBAT — TARGET IMPLEMENTATION

Prepared assets currently include:

- `GA_BareHandAttack`
- `GA_BareHandHeavyAttack`
- `AM_Kwang_BareHand`
- `ANS_BareHandTrace`
- `MM_Attack_01`
- `MM_Attack_02`
- `MM_Attack_03`
- `MM_ChargedAttack`

Do not create a second combat architecture from scratch.

Recommended reuse:

```text
Weapon State
     ↓
┌───────────────┬────────────────┐
│ Sword         │ Unarmed        │
▼               ▼
GA_MeleeAttack  GA_BareHandAttack
│               │
Sword Montage   BareHand Montage
│               │
Sword Trace     Fist Trace
└───────┬───────┘
        ▼
    Damage GE
```

## Bare-hand minimum DoD

```text
Switch / equip state
        ↓
Weapon hidden or inactive
        ↓
LMB
        ↓
Punch_01 → Punch_02 → Punch_03
        ↓
Trace
        ↓
Damage
```

Heavy bare-hand attack is bonus until basic 3-hit sequence is reliable.

---

# 11. HUD — TARGET IMPLEMENTATION

Required HUD:

```text
WBP_GameHUD
├── Player HP
├── Player Stamina
├── Enemy HP
└── Combo Counter
```

Prefer event/delegate-driven update instead of unnecessary Tick bindings.

Recommended flow:

```text
AttributeSet
    ↓
ASC Attribute Changed Delegate
    ↓
Character / Controller
    ↓
HUD Widget
```

## Player HP

```text
Health / MaxHealth
```

## Stamina

```text
Stamina / MaxStamina
```

## Enemy Health

Recommended simple flow:

```text
Current target / enemy ASC
    ↓
Health changed
    ↓
Enemy health widget
```

## Combo Counter

Simple acceptable logic:

```text
Successful hit
    ↓
ComboCount++
    ↓
Refresh reset timer
    ↓
Update UI

No hit for X seconds / combo broken
    ↓
ComboCount = 0
```

### Important

Floating damage number is intentionally skipped and is not a required HUD item.

---

# 12. DYNAMIC CAMERA — TARGET IMPLEMENTATION

Minimum design is enough.

Recommended components:

```text
Character
  ↓
SpringArm
  ↓
Camera
```

## Normal state

- Smooth follow
- Camera Lag enabled
- Camera collision enabled

## Combat state

Interpolate one or more of:

- `TargetArmLength`
- `FOV`
- `SocketOffset`

Example only:

```text
Normal:
Arm ≈ 350
FOV ≈ 90

Combat:
Arm ≈ 430
FOV ≈ 95
```

Tune visually; these numbers are not a frozen requirement.

## Hit feedback

```text
Light hit
  ↓
Small CameraShake

Heavy / Launcher / Finisher
  ↓
Stronger CameraShake
```

## Camera DoD

- follows player smoothly;
- changes framing during combat;
- does not clip badly through walls;
- hit feedback visible;
- heavy/launcher feedback distinguishable if implemented.

---

# 13. GAME FLOW — REQUIRED MINI-GAME LOOP

Objective explicitly includes **game flow implementation**.

Minimum acceptable loop:

```text
Boot
 ↓
Playing
 ↓
┌──────────────┬──────────────┐
│ Player Dead  │ Enemies Dead │
▼              ▼
Defeat         Victory
└───────┬──────┘
        ↓
      Restart
```

## Minimum behavior

Player death:

```text
Health <= 0
  ↓
Disable input
  ↓
Death state / animation
  ↓
Defeat UI
  ↓
Restart
```

Victory:

```text
All required enemies dead
  ↓
Victory UI
  ↓
Restart
```

The goal is to ship a small playable mini-game, not only a combat sandbox.

---

# 14. CURRENT COMBAT ARCHITECTURE

High-level architecture:

```text
              Enhanced Input
                    │
                    ▼
          Ability System Component
                    │
            ┌───────┴────────┐
            ▼                ▼
      GA_MeleeAttack     GA_AirAttack
            │                │
            └───────┬────────┘
                    ▼
             Animation Montage
                    │
          ┌─────────┴──────────┐
          ▼                    ▼
   Combo Window            Melee Trace
   AnimNotifyState         AnimNotifyState
          │                    │
          ▼                    ▼
    Input Buffer         Gameplay Event
                               │
                               ▼
                        TargetData / Hit
                               │
                               ▼
                        Gameplay Effect
                               │
                    ┌──────────┴──────────┐
                    ▼                     ▼
                AttributeSet          GameplayCue
                    │                     │
                HP/Stamina              VFX/SFX
                    │
                    ▼
                   HUD
```

Current melee runtime contract:

```text
LMB
  -> GA_MeleeAttack
  -> Play AM_Kwang_GroundCombo
  -> ANS_MeleeTrace Begin / Update / End
  -> Event.Combat.MeleeHit(Target + Damage + TargetData)
  -> GA_MeleeAttack routes EventTag
  -> GE_MeleeDamage (SetByCaller Data.Damage)
  -> Hit Result copied into Effect Context
  -> Apply GE_MeleeDamage
  -> Apply GE_Poison to same target
```

---

# 15. CURRENT DAMAGE / TRACE CONTRACT

Current trace sockets:

- `FX_weapon_base`
- `FX_weapon_tip`

Both belong under Kwang weapon hierarchy.

`BP_HeroCharacter.UpdateMeleeTrace` sends per accepted hit:

- `Target` = hit actor
- `EventTag` = `Event.Combat.MeleeHit`
- `EventMagnitude` = current melee damage
- `TargetData` = `AbilityTargetDataFromHitResult` using actual sweep HitResult

One-hit-per-swing guard:

- `HitActorsThisSwing`

Important contract:

> Preserve existing target actor + damage behavior while carrying proper TargetData / HitResult / EffectContext information.

---

# 16. GAMEPLAY EFFECTS / GAMEPLAY CUES

## 16.1 Melee Damage

Current `GE_MeleeDamage`:

- Duration Policy: Instant
- Damage via SetByCaller:
  - key: `Data.Damage`
- writes to:
  - `GDAttributeSetBase.Damage`
- no active Execution entries in current live asset
- GameplayCue:
  - `GameplayCue.Shared.MeleeImpact`

## 16.2 Melee Impact Cue

```text
GE_MeleeDamage
  ↓
GameplayCue.Shared.MeleeImpact
  ↓
GC_MeleeImpact
  ↓
HasHitResult(EffectContext)
  ↓
NS_Free_Magic_Area2 at ImpactPoint
```

Impact cue is **hit-only**.

## 16.3 Sword Slash Cue

Requirement chosen for project:

> Sword slash visual should appear for every intended swing, even when the sword misses.

Therefore SwordSlash is **not** driven by `GE_MeleeDamage`.

Current flow:

```text
Montage GameplayCue notify
  ↓
GameplayCue.Shared.SwordSlash
  ↓
GC_SwordSlash.OnExecute
  ↓
TargetAttachComponent validity
  ↓
SpawnSystemAttached(
    NS_SwordSlash,
    TargetAttachComponent,
    FX_weapon_base
  )
```

## 16.4 Poison

Frozen values:

- Duration: 5 s
- Period: 1 s
- Execute periodic effect on application: false
- Modifier:
  - Attribute: `GDAttributeSetBase.Damage`
  - Operation: AddBase
  - Magnitude: +10 per tick
- Stacking: AggregateByTarget
- Stack limit: 3
- Duration refresh: RefreshOnSuccessfulApplication
- Period reset: ResetOnSuccessfulApplication
- Expiry: ClearEntireStack
- Owned tag: `State.Debuff.Poison`
- GameplayCue: `GameplayCue.Shared.Poison`

Poison cue:

```text
GE_Poison
  ↓
GameplayCue.Shared.Poison
  ↓
GC_Poison
  ↓
WhileActive: Activate NS_PoisonCloud
OnRemove: Deactivate NS_PoisonCloud
```

### Poison priority

Poison is now considered **bonus / P2** for scheduling purposes.

Do not rebalance it unless explicitly needed.

---

# 17. ASSETS CURRENTLY IN USE

## GASDocumentation custom project assets

- `/Game/GASDocumentation/Characters/Hero/BP_HeroCharacter`
- `/Game/GASDocumentation/Characters/Hero/ABP_Hero`

## Ground combat

- `GA_MeleeAttack`
- `GA_MeleeHeavyAttack`
- `AM_Kwang_GroundCombo`
- `ANS_CombatWindow`
- `ANS_MeleeTrace`
- `GE_MeleeStaminaCost`

## Effects / GameplayCues

- `GE_MeleeDamage`
- `GE_Poison`
- `GC_MeleeImpact`
- `GC_SwordSlash`
- `GC_Poison`

## VFX

Free3DVFXSamplerVol1:

- `/Game/Free3DVFXSamplerVol1/Systems/NS_PoisonCloud`
- `/Game/Free3DVFXSamplerVol1/Systems/NS_SwordSlash`

Free_Magic:

- `/Game/Free_Magic/VFX_Niagara/NS_Free_Magic_Area2`

## Paragon Kwang

- `/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC`
- `Kwang_Skeleton`

Native Kwang FX alternatives available:

- `P_Kwang_Primary_Impact`
- `P_Kwang_Primary_Trail`
- `P_Kwang_Primary_Trail_L`
- `P_Kwang_Primary_Trail_R`
- `P_Kwang_Sword_Attach`
- `P_Kwang_Sword_Impact`
- `P_Sword_Tip_Drag`

## Minion branch

- `BP_MinionRed`
- `BP_MinionBlue`
- `GE_RedMinionAttributes`
- `GE_BlueMinionAttributes`
- `ABP_Minion`

## Existing UI assets inspected

- `/Game/GASDocumentation/UI/UI_DamageNumber`
- `/Game/GASDocumentation/UI/WC_DamageText`
- `/Game/GASDocumentation/UI/GDFloatingStatusBar_Hero`
- `/Game/GASDocumentation/UI/GDFloatingStatusBar_Minion`

## C++ damage calculation audited

- `Source/HacknSlash_Demo/Public/Characters/Abilities/GDDamageExecCalculation.h`
- `Source/HacknSlash_Demo/Private/Characters/Abilities/GDDamageExecCalculation.cpp`

Current note:

`GDDamageExecCalculation` exists and was audited, but current melee damage does **not** use it because `GE_MeleeDamage.Executions` is empty.

---

# 18. PREVIOUSLY RECORDED CHECKPOINTS

Prior notes record:

- Combo-window regression: 8/8 cases pass in documented fixture.
- Air-hold regression: 10/10 assertions pass in documented fixture.
- Bare-hand RMB input checkpoint: 4 pass.

Important:

These are **not equivalent to current end-to-end visual/runtime proof**.

Before submission, required systems must be re-tested in current build.

---

# 19. INTENTIONAL SKIPS / BOUNDARIES

Keep these decisions unless explicitly changed:

- Poison numbers are frozen.
- Floating damage numbers are skipped.
- Do not inject `GDDamageExecCalculation` into melee just for current VFX work.
- Do not move SwordSlash into `GE_MeleeDamage`.
  - It must play on miss.
- Do not replace `FX_weapon_base` / `FX_weapon_tip` trace sockets during VFX placement work.
- Do not regenerate unrelated Blueprint graphs.
- Do not overwrite unrelated dirty assets.
- Do not stage/commit unrelated changes automatically.
- Distinguish:
  - static graph inspection;
  - Blueprint compile success;
  - saved asset state;
  - PIE log evidence;
  - visual acceptance;
  - full functional acceptance.

---

# 20. KNOWN RISKS

- `SpawnSystemAttached` moves the Niagara component but does not automatically create a historical sword trail.
- World-space Niagara particles can visually remain behind even if the component follows the socket.
- Switching to Kwang native trails may require different sockets or notify timing.
- Montage GameplayCue notify can fire on miss by design.
- Hit impact cue must remain dependent on a valid HitResult.
- Poison tick/stack/expiry behavior should be verified in PIE when revisited.
- Git worktree contains existing dirty/untracked changes and should be handled carefully.

---

# 21. POLISH RULES

Only polish after P0 works.

Recommended combat feel additions:

- light hit CameraShake;
- stronger heavy/launcher CameraShake;
- subtle hitstop;
- sword trail;
- impact VFX;
- impact SFX;
- distinct heavy hit feedback.

Avoid overengineering:

- no production-scale lock-on system unless already almost free;
- no complex cinematic camera;
- no advanced combo editor;
- no large skill tree;
- no unnecessary UI animations before required HUD works.

---

# 22. FINAL SUBMISSION CHECKLIST

## Gameplay

- [ ] Ground 3-hit combo
- [ ] Air 2-hit combo
- [ ] Launcher
- [ ] Bare-hand combat
- [ ] Stamina cost
- [ ] Damage / HP
- [ ] Smooth combo transition
- [ ] Input spam cannot break combo
- [ ] Enemy takes one intended damage per swing

## HUD

- [ ] Player HP
- [ ] Player Stamina
- [ ] Enemy HP
- [ ] Combo Counter

## Camera

- [ ] Smooth follow
- [ ] Combat-aware framing
- [ ] Camera Shake
- [ ] Camera collision

## Game Flow

- [ ] Start
- [ ] Play
- [ ] Player death / defeat
- [ ] Enemy clear / victory
- [ ] Restart

## Polish

- [ ] Sword trail / SwordSlash acceptable
- [ ] Impact VFX
- [ ] SFX
- [ ] Optional hitstop
- [ ] Poison bonus works acceptably

## Technical

- [ ] No major Blueprint compile errors
- [ ] No repeatable runtime crash
- [ ] Clean test map
- [ ] Controls documented
- [ ] Windows build created
- [ ] Build tested
- [ ] GitHub repo prepared
- [ ] README prepared

## Submission

- [ ] GitHub link
- [ ] YouTube demo link
- [ ] 1–2 page Technical Document
- [ ] Architecture diagram

---

# 23. RECOMMENDED DEMO VIDEO ORDER

Keep video short and requirement-oriented.

Suggested sequence:

1. Start game / HUD visible
2. Ground combo 3-hit
3. Ground heavy / finisher if available
4. Launcher
5. Air1 → Air2
6. Bare-hand combo
7. Player HP / Stamina changes
8. Enemy HP
9. Combo Counter
10. Camera follow
11. Camera combat adjustment
12. Camera Shake on hit
13. Wall/camera collision
14. Poison as bonus
15. Victory / defeat / restart
16. Very short architecture/Blueprint overview if useful

Do not let bonus Poison/VFX consume the majority of the demo.

---

# 24. TECHNICAL DOCUMENT — 1–2 PAGE STRUCTURE

## Page 1

### Project Overview

- UE 5.8
- PC
- GAS-based combat
- Montage-driven combos
- trace-based melee detection

### Main Architecture

Use this diagram:

```text
Enhanced Input
      │
      ▼
Ability System Component
      │
      ▼
Gameplay Ability
      │
      ▼
Animation Montage
      │
      ├── Combo Window Notify
      │
      └── Melee Trace Notify
              │
              ▼
       Gameplay Event
              │
              ▼
     TargetData / HitResult
              │
              ▼
       Gameplay Effect
        │           │
        ▼           ▼
  AttributeSet   GameplayCue
        │           │
        ▼           ▼
      HUD         VFX/SFX
```

## Page 2

### Key Design Decisions

Possible points:

- GAS owns ability activation, cost and gameplay effect flow.
- Animation Montage Sections / notifies control combo timing.
- Trace is only active during attack hit windows.
- `HitActorsThisSwing` prevents duplicate damage per swing.
- HitResult is preserved via TargetData / EffectContext.
- Impact VFX is hit-driven.
- SwordSlash VFX is swing-driven so it can appear on miss.
- HUD reacts to gameplay attributes.
- Camera responds to combat state and impact.
- Game state handles victory/defeat/restart.

### Tradeoffs

Mention scope management:

- Poison implemented as GAS bonus.
- Floating damage numbers intentionally omitted.
- Focus placed on required combat systems and stable submission.

---

# 25. MASTER CONTINUATION PROMPT

Use this when continuing in another chat/session:

> Project `F:\HacknSlash_Demo`, Unreal Engine 5.8, PC, GAS-based Hack-and-Slash technical test. Treat `HACKNSLASH_MASTER_CONTEXT.md` as the single source of truth. Work in Vietnamese + Vietlish, practical Blueprint steps, KISS, one short checkpoint at a time. Distinguish static inspection / compile / saved asset / PIE log / visual proof / full functional proof. Current immediate checkpoint is `GC_SwordSlash`: it already uses `SpawnSystemAttached` with `NS_SwordSlash` at `TargetAttachComponent` + `FX_weapon_base`; runtime logs prove cue execution but visual trajectory still needs PIE acceptance. Test a deliberate miss. If the component follows but particles stay behind, test Niagara Local Space; if needed use `P_Kwang_Primary_Trail` or `P_Sword_Tip_Drag`, then freeze VFX. After that, priority order is Ground Combo regression → Air Combo/Launcher → Bare-hand → HUD → Camera → Game Flow → polish → Windows build/README/GitHub → demo video → 1–2 page technical doc. Poison is frozen at 5s duration, 1s period, +10 Damage/tick, AggregateByTarget limit 3, refresh/reset on application and is now bonus/P2. Floating damage numbers are intentionally skipped.

---

# 26. DETAILED ORIGINAL COMBAT / VFX CONTEXT

The following section is preserved from the previous context file so no implementation detail is lost.

---

# HacknSlash_Demo — Combat / GameplayCue / VFX Context

Updated: 2026-09-22
Project: `F:\HacknSlash_Demo`
Engine: Unreal Engine 5.8
Language for continuation: Vietnamese + Vietlish, practical Blueprint steps, KISS.

## 1. Current status in one sentence

The GAS melee damage and Target Data path has been reconnected, Poison VFX and impact VFX are in place, and the current stage is the final visual polish of the per-swing `NS_SwordSlash` cue so it follows Kwang's weapon instead of only appearing at its first position.

Current phase: **GameplayCue/VFX integration — SwordSlash attachment and trajectory validation**.

Do not treat the whole project as complete yet. The older project plan still has separate regen, heavy-combo, air/bare-hand visual, camera, HUD, game-flow and final-demo checkpoints.

## 2. Chronological summary of this conversation

### A. Poison contract and application

- We audited `GA_MeleeAttack` applying `GE_Poison` to the same enemy ASC as normal melee damage.
- The agreed Poison stats were kept unchanged for now:
  - Duration: 5 seconds.
  - Period: 1 second.
  - Periodic execution on application: `false`.
  - Modifier: `GDAttributeSetBase.Damage`, `AddBase`, magnitude `+10` per periodic tick.
  - Stacking: `AggregateByTarget`, stack limit `3`.
  - Duration refresh: `RefreshOnSuccessfulApplication`.
  - Period reset: `ResetOnSuccessfulApplication`.
  - Expiry: `ClearEntireStack`.
  - Owned tag: `State.Debuff.Poison`.
  - Gameplay Cue tag: `GameplayCue.Shared.Poison`.
- The user requested to freeze these numbers and move to GameplayCues instead of balancing them.

### B. `GC_Poison`

- Created/connected `GC_Poison` as an actor cue.
- `WhileActive` activates its `NS_PoisonCloud` component.
- `OnRemove` deactivates the component.
- The user tested the Poison visual and considered it acceptable.
- This is a visual/user-confirmed checkpoint; fresh runtime proof of every periodic tick, expiry, refresh and stack limit is still a separate validation task.

### C. Damage-number investigation

- We inspected `GD_damagenumber`, `WC_DamageText`, `UI_DamageNumber` and `GDDamageExecCalculation` because minions were not showing floating damage.
- The UI path was debugged, but the user explicitly chose to skip floating damage display for now.
- `GDDamageExecCalculation` exists in C++, captures source `Damage` and target `Armor`, calculates mitigated damage, and broadcasts `ReceiveDamage`.
- It is **not on the current melee path** because live `GE_MeleeDamage.Executions` is empty. Current melee damage uses a SetByCaller `Data.Damage` modifier directly on the `Damage` meta attribute.
- Do not reopen this UI/C++ branch while finishing the current VFX checkpoint unless the user explicitly asks for it.

### D. Melee impact GameplayCue

- Created `GC_MeleeImpact` with tag `GameplayCue.Shared.MeleeImpact`.
- The cue checks whether the effect context has a Hit Result.
- On a valid Hit Result it spawns `NS_Free_Magic_Area2` at the hit `ImpactPoint`.
- On the false branch it returns without spawning impact VFX.
- The user reported the impact VFX checkpoint complete.

### E. Target Data and Effect Context repair

- The sword trace uses Kwang sockets `FX_weapon_base` and `FX_weapon_tip`.
- `BP_HeroCharacter.UpdateMeleeTrace` was repaired so every accepted hit sends:
  - `Target` = hit actor.
  - `EventTag` = `Event.Combat.MeleeHit`.
  - `EventMagnitude` = current melee damage.
  - `TargetData` = `AbilityTargetDataFromHitResult` for the actual sweep Hit Result.
- Duplicate trace nodes were removed and `HitActorsThisSwing` remains the one-hit-per-swing guard.
- The graph was compiled/saved in the earlier repair checkpoint.
- `GA_MeleeAttack` now preserves the Hit Result in the outgoing `GE_MeleeDamage` Effect Context before applying damage, then applies `GE_Poison` to the same target.
- The important contract is: preserve the existing hit actor/damage wires; only add/repair Target Data and Effect Context payloads.

### F. Sword slash cue and current problem

- The requirement was changed to: show a sword slash on **every montage swing, including a miss**.
- Therefore `SwordSlash` is driven by a montage GameplayCue notify/tag, not by `GE_MeleeDamage` or the hit-only impact cue.
- Registered tag: `GameplayCue.Shared.SwordSlash`.
- `GC_SwordSlash` was first implemented with a world-space `SpawnSystemAtLocation` using the socket transform. It appeared in the correct initial position but did not follow the weapon during the rest of the swing.
- The attachment fix was then applied. The current live graph uses `SpawnSystemAttached` to `FX_weapon_base`.
- Current Output Log evidence contains repeated `SwordSlash` messages, so the cue is being executed at runtime. That proves cue execution, not yet the final visual trajectory quality.

## 3. Current live implementation contract

### Melee flow

```text
LMB
  -> GA_MeleeAttack
  -> Play AM_Kwang_GroundCombo (starts Attack_01)
  -> ANS_MeleeTrace Begin / Update / End
  -> Event.Combat.MeleeHit(Target + Damage + TargetData)
  -> GA_MeleeAttack routes by EventTag first
  -> GE_MeleeDamage (SetByCaller Data.Damage)
  -> Hit Result copied into Effect Context
  -> Apply GE_MeleeDamage to target
  -> Apply GE_Poison to the same target
```

### Hit VFX flow

```text
GE_MeleeDamage cue tag: GameplayCue.Shared.MeleeImpact
  -> GC_MeleeImpact
  -> HasHitResult(EffectContext)
  -> NS_Free_Magic_Area2 at ImpactPoint
```

### Poison VFX flow

```text
GE_Poison cue tag: GameplayCue.Shared.Poison
  -> GC_Poison actor
  -> WhileActive: Activate NS_PoisonCloud
  -> OnRemove: Deactivate NS_PoisonCloud
```

### Per-swing slash flow

```text
Montage GameplayCue notify: GameplayCue.Shared.SwordSlash
  -> GC_SwordSlash.OnExecute
  -> Break GameplayCue Parameters
  -> TargetAttachComponent validity check
  -> SpawnSystemAttached(NS_SwordSlash, TargetAttachComponent, "FX_weapon_base")
  -> PrintString("SwordSlash")
```

The last flow is independent of hit success, so it can play on a miss.

## 4. Fresh live checks made for this context

These are current EditorToolset checks on 2026-09-22, not assumptions from an old DSL snapshot.

- `GC_SwordSlash` exists, is saved/clean according to the asset dirty check, and its live `OnExecute` DSL contains `SpawnSystemAttached` with `NS_SwordSlash` and socket `FX_weapon_base`.
- `GC_MeleeImpact` live DSL uses `NS_Free_Magic_Area2` and the Effect Context Hit Result.
- `GC_Poison` live graphs contain `WhileActive` activation and `OnRemove` deactivation of `NS_PoisonCloud`.
- `GE_Poison` live properties match the frozen contract in section 2.
- `GE_MeleeDamage` is `Instant`, uses `Data.Damage` SetByCaller on `GDAttributeSetBase.Damage`, has no Execution entries, and carries `GameplayCue.Shared.MeleeImpact`.
- `BP_HeroCharacter.UpdateMeleeTrace` live DSL creates Target Data from each sweep Hit Result and keeps the `HitActorsThisSwing` uniqueness guard.
- `Kwang_GDC` contains the expected sockets. Both `FX_weapon_base` and `FX_weapon_tip` are parented to `weapon_r`.
- Fresh `LogBlueprintUserMessages` entries contain multiple `SwordSlash` prints and matching melee trace Begin/End messages.
- The current session did not produce fresh `MeleeImpact`, `Apply Damage` or Poison tick entries, so those are not claimed as newly runtime-verified here. The user had previously reported those visual/application checkpoints as complete.

## 5. Current plan stage and next direction

### Current stage

**Phase 3 — GameplayCue/VFX polish, substep 3.2: make SwordSlash follow Kwang's weapon.**

The graph-side attachment fix is already present. The next checkpoint is visual verification, not another damage/Poison graph rewrite.

### Next bounded checkpoint

1. Open `Map_Startup` and run PIE with no enemy in range.
2. Play one `Attack_01` swing and watch only `NS_SwordSlash`.
3. Confirm all four points:
   - One `SwordSlash` per intended swing/notify.
   - It starts on `FX_weapon_base`.
   - The visible effect follows the weapon during the swing.
   - It also appears when the trace misses.
4. Stop PIE and record whether the component itself moves or only the emitted particles stay behind.

If the component follows but the particles still stay at the first position:

- Inspect `NS_SwordSlash` Niagara emitter settings and test `Local Space` on the moving emitters.
- If the desired result is a true continuous blade arc/trail, do not keep spawning a one-shot burst and expect it to draw a history of the socket. Use a trail/ribbon system or the native Kwang options such as:
  - `/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Trail`
  - `/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Trail_L`
  - `/Game/ParagonKwang/FX/Particles/Abilities/Primary/FX/P_Kwang_Primary_Trail_R`
  - `/Game/ParagonKwang/FX/Particles/Abilities/Sword/FX/P_Sword_Tip_Drag`
- Only make that second change after the attached-system test is observed; do not change `GE_Poison`, `GA_MeleeAttack` or the trace payload for this visual issue.

### After SwordSlash is visually accepted

1. Test one real minion hit and one deliberate miss.
2. Confirm `GC_MeleeImpact` appears only on a valid Hit Result.
3. Confirm Poison visual lifetime matches the frozen 5-second effect and that reapplication behavior is intentional.
4. Test Attack_01 → Attack_02 → Attack_03 and the heavy branch for visual timing, one hit per swing, HP reduction and no duplicate cue spam.
5. Then return to the broader project backlog: regen, heavy-routing proof, air/bare-hand visual alignment, camera/HUD/game flow and final demo/documentation.

## 6. Asset packs and assets currently used

### Active in the current sword/Poison/VFX path

| Pack / area | Assets in use | Role |
| --- | --- | --- |
| `GASDocumentation` custom project assets | `/Game/GASDocumentation/Characters/Hero/BP_HeroCharacter`, `/Game/GASDocumentation/Characters/Hero/ABP_Hero` | Kwang hero actor and animation blueprint |
| `GASDocumentation` ground combat | `GA_MeleeAttack`, `GA_MeleeHeavyAttack`, `AM_Kwang_GroundCombo`, `ANS_CombatWindow`, `ANS_MeleeTrace`, `GE_MeleeStaminaCost` | GAS ability, montage, combo-window notify and trace |
| `GASDocumentation` effects/cues | `GE_MeleeDamage`, `GE_Poison`, `GC_MeleeImpact`, `GC_SwordSlash`, `GC_Poison` | Damage, DoT, hit VFX, per-swing VFX and Poison VFX |
| `Free3DVFXSamplerVol1` | `/Game/Free3DVFXSamplerVol1/Systems/NS_PoisonCloud`, `/Game/Free3DVFXSamplerVol1/Systems/NS_SwordSlash` | Active Poison cloud and sword-slash Niagara systems |
| `Free_Magic` | `/Game/Free_Magic/VFX_Niagara/NS_Free_Magic_Area2` | Active melee impact Niagara system |
| `ParagonKwang` | `/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC`, `Kwang_Skeleton` | Kwang mesh/skeleton, weapon sockets and source animation/FX pack |
| `GASDocumentation` minion branch | `BP_MinionRed`, `BP_MinionBlue`, `GE_RedMinionAttributes`, `GE_BlueMinionAttributes`, `ABP_Minion` | Test targets and enemy health/ASC setup |

### Supporting assets that are part of the current project path

- `AnimStarterPack` is still referenced by the existing hero/minion animation support and minion death assets, for example `UE4_Mannequin_Skeleton`, `Death_1_Montage`, `Death_3_Montage`, hit reactions and locomotion assets.
- HUD/UI assets inspected during the skipped damage-number branch:
  - `/Game/GASDocumentation/UI/UI_DamageNumber`
  - `/Game/GASDocumentation/UI/WC_DamageText`
  - `/Game/GASDocumentation/UI/GDFloatingStatusBar_Hero`
  - `/Game/GASDocumentation/UI/GDFloatingStatusBar_Minion`
- C++ damage calculation audited:
  - `Source/HacknSlash_Demo/Public/Characters/Abilities/GDDamageExecCalculation.h`
  - `Source/HacknSlash_Demo/Private/Characters/Abilities/GDDamageExecCalculation.cpp`

### Prepared/roadmap branches, not the current SwordSlash path

- Air combo assets: `GA_AirAttack`, `GA_Launcher`, `AM_Kwang_AirCombo`, `AM_Kwang_Launcher`.
- Bare-hand assets: `GA_BareHandAttack`, `GA_BareHandHeavyAttack`, `AM_Kwang_BareHand`, `ANS_BareHandTrace`, `MM_Attack_01/02/03`, `MM_ChargedAttack`.
- The project contains UE Mannequin unarmed source/retarget assets under `/Game/Characters/Mannequins/Anims/Unarmed`; no folder/file named `Motifect` was found in `Content` during this check.
- Native Kwang trail/impact systems exist, but they are alternatives, not currently assigned to `GC_SwordSlash`:
  - `P_Kwang_Primary_Impact`
  - `P_Kwang_Primary_Trail`, `_L`, `_R`
  - `P_Kwang_Sword_Attach`
  - `P_Kwang_Sword_Impact`
  - `P_Sword_Tip_Drag`
- `NS_Free_Magic_Hit1` and `NS_Free_Magic_Hit2` exist but are not the current `GC_MeleeImpact` system; the live cue uses `NS_Free_Magic_Area2`.
- `NS_BloodSplatter` exists in the Free3D pack but is not currently wired into the melee cue.

## 7. Plan baseline versus this thread

`Docs/PROJECT_CONTEXT.md` is an older snapshot from 2026-09-19. Its broad DoD still includes:

- regen backing-attribute repair and 5-tick PIE proof;
- heavy input routing and section proof;
- ground combo regression cases;
- air combo and bare-hand visual/damage validation;
- camera, HUD/combo counter, game flow and final demo/documentation.

Separate notes record these prior checkpoints:

- Combo-window regression: 8/8 cases pass in the documented fixture.
- Air-hold regression: 10/10 assertions pass in the documented fixture.
- Bare-hand RMB input checkpoint: 4 pass, but it is not full damage/visual/multiplayer validation.

Those results do not replace a fresh visual test of the current dirty/untracked VFX assets. Keep the current thread focused on SwordSlash attachment first, then return to the broad backlog.

## 8. Intentional skips and boundaries

- Poison numbers are frozen; do not rebalance them in the next step.
- Floating damage numbers are intentionally skipped.
- `GDDamageExecCalculation` is audited but not injected into `GE_MeleeDamage` in this VFX pass.
- Do not move the sword slash cue into `GE_MeleeDamage`; that would break the requirement that it plays on a miss.
- Do not replace the existing `FX_weapon_base` / `FX_weapon_tip` trace sockets while fixing VFX placement.
- Do not Save All, regenerate graphs from DSL, stage, commit, switch branch or overwrite unrelated dirty assets.
- Distinguish static graph inspection, Blueprint compile, saved asset state, PIE log evidence and visual acceptance.

## 9. Risks / side effects

- `SpawnSystemAttached` fixes component attachment, but it cannot by itself turn a one-shot Niagara burst into a continuous blade trail.
- Niagara emitters using world-space particle simulation can still leave particles behind even when the Niagara component follows the socket.
- Switching to a Kwang native trail may require different sockets/timing and should be tested separately from the existing `NS_SwordSlash` cue.
- A montage GameplayCue notify can fire on a miss by design; a hit-only impact cue must continue to depend on a valid Hit Result.
- Poison runtime behavior must not be inferred solely from the asset graph; tick, expiry, refresh and stack behavior need focused PIE evidence when that branch is revisited.
- The Git worktree is intentionally dirty with existing Blueprint/config/assets and untracked additions. Preserve those changes.

## 10. Prompt để tiếp tục ở chat khác

> Project ở `F:\HacknSlash_Demo`, Unreal Engine 5.8, GAS. Đọc `AGENTS.md` và `Docs/COMBAT_VFX_CONTEXT.md`. Dùng tiếng Việt pha Vietlish, đi từng checkpoint ngắn, kiểm tra live Blueprint trước khi kết luận và phân biệt static inspection / compile / saved asset / PIE / visual proof. Current stage là GameplayCue/VFX polish: `GC_SwordSlash` hiện đã dùng `SpawnSystemAttached` với `NS_SwordSlash` tại `TargetAttachComponent` và socket `FX_weapon_base`; log đã in `SwordSlash`, nhưng cần PIE xác nhận effect thật sự bám theo quỹ đạo kiếm. Nếu component bám nhưng particle vẫn đứng ở vị trí đầu, kiểm tra Niagara Local Space; nếu cần blade trail liên tục thì đánh giá `P_Kwang_Primary_Trail` hoặc `P_Sword_Tip_Drag`. Giữ nguyên Poison stats (5s duration, 1s period, +10 Damage, AggregateByTarget limit 3, refresh/reset on application), không quay lại damage-number UI trừ khi tôi yêu cầu. Sau khi SwordSlash pass, test một hit và một miss, rồi kiểm tra `GC_MeleeImpact` (`NS_Free_Magic_Area2`) và `GC_Poison` (`NS_PoisonCloud`) trước khi quay lại backlog regen/combo/air/bare-hand/camera/HUD/game flow.

